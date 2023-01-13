import 'dart:async';
import 'dart:convert';
import 'package:exam_1016/pages/history_list.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:colorful_safe_area/colorful_safe_area.dart';
import 'MQTTManager.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'historyProps.dart';

class DetailedPage extends StatefulWidget {
  const DetailedPage({super.key});
  @override
  State<DetailedPage> createState() => _DetailedPageState();
}

class _DetailedPageState extends State<DetailedPage> {
  late TextEditingController controller;
  late String? matrixText;
  late int watchCount;
  late int byPassers;
  late String textToShow;
  late bool showHistory;
  List<HistoryList> history = [];
  MQTTManager mqttManager = MQTTManager();

  Future<void> setupMqttClient() async {
    await mqttManager.connect();
    mqttManager.subscribe("matrix/sub");
  }

  @override
  void initState() {
    super.initState();
    setupMqttClient();
    setupUpdatesListener();
    controller = TextEditingController();
    matrixText = "";
    watchCount = 0;
    byPassers = 0;
    textToShow = "Show history";
    showHistory = false;
    getStates();
  }

  @override
  void dispose() {
    controller.dispose();
    mqttManager.disconnect();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: ColorfulSafeArea(
            color: const Color.fromRGBO(240, 239, 244, 1),
            child: SafeArea(
              child: Container(
                color: const Color.fromRGBO(240, 239, 244, 1),
                child: Padding(
                  padding: const EdgeInsets.fromLTRB(8.0, 25, 8.0, 8.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                          const Icon(
                            Icons.power_settings_new_rounded,
                            size: 30,
                          )
                        ],
                      ),
                      const SizedBox(
                        height: 20,
                      ),
                      const SizedBox(
                        height: 20,
                      ),
                      Center(
                        child: Container(
                          height: 450,
                          width: 400,
                          decoration: BoxDecoration(
                              borderRadius: BorderRadius.circular(20),
                              boxShadow: [
                                BoxShadow(
                                  color: Colors.grey.withOpacity(0.1),
                                  spreadRadius: 5,
                                  blurRadius: 7,
                                  offset: const Offset(
                                      0, 3), // changes position of shadow
                                ),
                              ],
                              color: Colors.white),
                          child: Column(
                            crossAxisAlignment: CrossAxisAlignment.center,
                            children: [
                              const SizedBox(
                                height: 20,
                              ),
                              const Text(
                                "Current text",
                                style: TextStyle(
                                    fontSize: 20,
                                    fontWeight: FontWeight.bold,
                                    color: Colors.grey),
                              ),
                              GestureDetector(
                                onTap: (() async {
                                  matrixText = await openDialog();

                                  if (matrixText == null ||
                                      matrixText!.isEmpty ||
                                      isDuplicate()) {
                                    return;
                                  }
                                  publishToMQTT();
                                  saveToRTDB();
                                }),
                                child: Text(
                                  matrixText.toString(),
                                  style: const TextStyle(
                                      fontSize: 20,
                                      fontWeight: FontWeight.w600),
                                ),
                              ),
                              const SizedBox(
                                height: 20,
                              ),
                              GestureDetector(
                                onTap: () {
                                  if (showHistory) {
                                    setState(() {
                                      textToShow = "Show history";
                                      showHistory = false;
                                    });
                                  } else {
                                    setState(() {
                                      textToShow = "Hide history";
                                      showHistory = true;
                                    });
                                  }
                                },
                                child: Text(
                                  textToShow,
                                  style: TextStyle(
                                      fontSize: 20,
                                      fontWeight: FontWeight.bold,
                                      color: Colors.grey),
                                ),
                              ),
                              const SizedBox(
                                height: 10,
                              ),
                              StreamBuilder(
                                stream: FirebaseDatabase.instance
                                    .ref()
                                    .child("/state/history")
                                    .onValue,
                                builder: (context, snapshot) {
                                  if (snapshot.hasData) {
                                    Map<dynamic, dynamic>? data =
                                        snapshot.data?.snapshot.value as Map?;
                                    history.clear();

                                    data?.forEach((dynamic, v) {
                                      if (v.toString() == matrixText) {
                                        return;
                                      }
                                      final historyProps = HistoryProps(
                                        ID: dynamic,
                                        txt: v,
                                      );

                                      return history.add(
                                          HistoryList(props: historyProps));
                                    });
                                    if (!showHistory) {
                                      return Container();
                                    }
                                    return ListView.builder(
                                      scrollDirection: Axis.vertical,
                                      shrinkWrap: true,
                                      reverse: false,
                                      itemCount: history.length,
                                      itemBuilder: (context, index) {
                                        return history[index];
                                      },
                                    );
                                  }
                                  return const Text("Loading data");
                                },
                              )
                            ],
                          ),
                        ),
                      ),
                      Padding(
                          padding: const EdgeInsets.fromLTRB(8.0, 25, 8.0, 8.0),
                          child: Row(
                            mainAxisAlignment: MainAxisAlignment.spaceBetween,
                            children: [
                              Container(
                                height: 150,
                                width: 150,
                                decoration: BoxDecoration(
                                    borderRadius: BorderRadius.circular(20),
                                    boxShadow: [
                                      BoxShadow(
                                        color: Colors.grey.withOpacity(0.1),
                                        spreadRadius: 5,
                                        blurRadius: 7,
                                        offset: const Offset(
                                            0, 3), // changes position of shadow
                                      ),
                                    ],
                                    color: Colors.white),
                                child: Column(
                                  children: [
                                    const SizedBox(
                                      height: 20,
                                    ),
                                    const Icon(
                                      Icons.visibility,
                                      size: 30,
                                    ),
                                    const SizedBox(
                                      height: 30,
                                    ),
                                    Text(watchCount.toString(),
                                        style: const TextStyle(fontSize: 30)),
                                  ],
                                ),
                              ),
                              Container(
                                height: 150,
                                width: 150,
                                decoration: BoxDecoration(
                                    borderRadius: BorderRadius.circular(20),
                                    boxShadow: [
                                      BoxShadow(
                                        color: Colors.grey.withOpacity(0.1),
                                        spreadRadius: 5,
                                        blurRadius: 7,
                                        offset: const Offset(
                                            0, 3), // changes position of shadow
                                      ),
                                    ],
                                    color: Colors.white),
                                child: Column(
                                  children: [
                                    const SizedBox(
                                      height: 20,
                                    ),
                                    const Icon(
                                      Icons.directions_walk_rounded,
                                      size: 30,
                                    ),
                                    const SizedBox(
                                      height: 30,
                                    ),
                                    Text(byPassers.toString(),
                                        style: const TextStyle(fontSize: 30)),
                                  ],
                                ),
                              ),
                            ],
                          )),
                    ],
                  ),
                ),
              ),
            )));
  }

  Future<void> publishToMQTT() async {
    var obj = {"msg": matrixText};
    var x = json.encode(obj);
    print(x.toString());
    mqttManager.publishMessage("matrix/pub", x);
    setState(() {
      matrixText = matrixText;
    });
  }

  Future<void> saveToRTDB() async {
    DatabaseReference ref =
        FirebaseDatabase.instance.ref().child("/latestData/data");
    DatabaseReference ref2 =
        FirebaseDatabase.instance.ref().child("/state/history");
    final newKey =
        FirebaseDatabase.instance.ref().child("/state/history").push().key;
    ref.set(matrixText);
    ref2.update({newKey.toString(): matrixText});
  }

  void getStates() async {
    final ref = FirebaseDatabase.instance.ref();
    final snapshot = await ref.child("state").get();
    final snapshot2 = await ref.child("latestData").get();
    if (snapshot.exists && snapshot2.exists) {
      final Map<String, dynamic> responseJson =
          await json.decode(json.encode(snapshot.value));
      final Map<String, dynamic> responseJson2 =
          await json.decode(json.encode(snapshot2.value));
      setState(() {
        matrixText = responseJson2["data"];
        watchCount = responseJson["watchCount"];
        byPassers = responseJson["byPassers"];
      });
    }
  }

  Future<String?> openDialog() => showDialog(
      context: context,
      builder: (context) => AlertDialog(
            title: const Text("Enter text"),
            content: TextField(
              autofocus: true,
              decoration: const InputDecoration(hintText: "Enter text"),
              controller: controller,
              onSubmitted: (_) => updateDisplayMessage(),
            ),
            actions: [
              TextButton(
                  onPressed: (() {
                    updateDisplayMessage();
                  }),
                  child: const Text("Update"))
            ],
          ));

  void updateDisplayMessage() {
    if (isDuplicate()) {
      Navigator.of(context).pop();
    } else {
      Navigator.of(context).pop(controller.text);
    }
    controller.clear();
  }

  void setupUpdatesListener() {
    mqttManager
        .getMessagesStream()!
        .listen((List<MqttReceivedMessage<MqttMessage?>>? c) {
      final recMess = c![0].payload as MqttPublishMessage;
      final msg =
          MqttPublishPayload.bytesToStringAsString(recMess.payload.message);
      final parsedJson = jsonDecode(msg);
      if (parsedJson["watched"] as bool) {
        setState(() {
          watchCount += 1;
          byPassers += 1;
        });
      } else if (parsedJson["passedBy"] as bool) {

      setState(() {
          byPassers += 1;
        });
      }

      if (kDebugMode) {
        print(
            'MQTTClient::Message received on topic: <${c[0].topic}> is $msg\n');
      }
    });
  }

  bool isDuplicate() {
    for (var element in history) {
      return element.props.txt == controller.text ||
          element.props.txt == matrixText;
    }
    return false;
  }
}
