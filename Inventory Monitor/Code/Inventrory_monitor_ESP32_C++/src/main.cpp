#include <Arduino.h>
#include <Arduino_JSON.h>
#include "Button.h"
#include <PubSubClient.h>
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include "Beverage.h"
#include "Inventory.h"
#include <Update.h>
#include <WiFiManager.h>
#include "credentials.h"

u_int8_t beverageIndex = 0;
LiquidCrystal lcd(19, 23, 18, 17, 16, 15); // Tried for days with the TFT, nut i believe it has done its time :(

Button previousButton(33); // go to previous beverage
Button nextButton(35);     // to to next beverage
Button selectButton(32);   // select beverage

WiFiClient espClient;
PubSubClient client(espClient); // Used to publsih to AWS

Inventory inventory; // Managers the Bevereages.

void clearLCD();// Clears the LCD screen after pressing next and previous buttons
void sendData();// sends the payload to LORA via local broker using ip adress
void populateJsonArray(JSONVar &JSONArrayLeft, JSONVar &JSONArraySold); // populates JSON before sending to AWS
void setupWifi();// Sets up WiFi with WiFiManager
void reconnect();// Tries to reconect to the local broker
void monitorButtons();// checking if buttons are clicked
void setupWifi()
{
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("MutezoHome2021", "MutezoFamily1"); // password protected ap
  if (!res)
  {
    Serial.println("Failed to connect");
  }
  else
  {
    Serial.println("connected...yeey :)");
  }
}

void reconnect()
{
  while (!client.connected())
  {
    if (client.connect(BROKER, BROKER_USER, BROKER_PASSWORD))
    {
      Serial.println("Connected");
    }
    else
    {
      Serial.println("reconnecting");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  // Adding three drinks to simulate an inventory.
  inventory.addBeverage(new Beverage("Coca Cola", 20));
  inventory.addBeverage(new Beverage("Fanta", 25));
  inventory.addBeverage(new Beverage("Redbull", 36));
  setupWifi();
  client.setServer(BROKER, 1883);
  lcd.begin(16, 2); // todo try to refactpr LCD
  lcd.print("Select beverage");
}
void loop()
{
  monitorButtons();
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}

void monitorButtons()
{
  previousButton.readState();
  nextButton.readState();
  selectButton.readState();

  if (nextButton.isPressed())
  {
    Serial.println("next");
    if (beverageIndex < inventory.getSize())
    {
      clearLCD();
      beverageIndex++;
    }
  }

  if (previousButton.isPressed())
  {
    Serial.println("prev");
    if (beverageIndex > 0)
    {
      clearLCD();
      beverageIndex--;
    }
  }

  if (selectButton.isPressed())
  {
    Serial.println("selected");
    lcd.setCursor(0, 1);
    clearLCD();
    lcd.print(inventory.getBeverages()->get(beverageIndex, 0)->getName());
    auto selected = inventory.getBeverages()->get(beverageIndex, 0);
    inventory.checkOut(selected);
    sendData();
  }
  lcd.setCursor(0, 1);
  auto beverage = inventory.getBeverages()->get(beverageIndex, 0)->getName();
  lcd.print(beverage);

  previousButton.updateState();
  nextButton.updateState();
  selectButton.updateState();
}

void clearLCD()
{
  uint8_t i = 0;
  lcd.setCursor(0, 1);
  auto beverageNameLength = inventory.getBeverages()->get(beverageIndex, 0)->getName().length();
  while (i < beverageNameLength)
  {
    lcd.print(" ");
    i++;
  }
}

void sendData()
{
  JSONVar data;
  JSONVar JSONArrayLeft;
  JSONVar JSONArraySold;
  populateJsonArray(JSONArrayLeft, JSONArraySold);
  data["profit"] = inventory.getProfit();
  data["remaining"] = JSON.stringify(JSONArrayLeft);
  data["sold"] = JSON.stringify(JSONArraySold);
  String jsonString = JSON.stringify(data);
  client.publish("esp32/data", jsonString.c_str());
}

void populateJsonArray(JSONVar &JSONArrayLeft, JSONVar &JSONArraySold)
{
  const auto remaining = inventory.getBeverages();
  int i = 0;
  for (auto it = remaining->begin(); it != remaining->end(); ++it)
  {
    auto beverage = it.operator*()->getName();
    JSONArrayLeft[i] = beverage;
    i++;
  }

  const auto sold = inventory.getSoldBeverages();
  i = 0;
  for (auto it = sold->begin(); it != sold->end(); ++it)
  {
    auto beverage = it.operator*()->getName();
    JSONArraySold[i] = beverage;
    i++;
  }
}
