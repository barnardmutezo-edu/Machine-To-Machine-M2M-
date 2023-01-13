import { StatusBar } from 'expo-status-bar';
import { FlatList, SafeAreaView, StyleSheet, Text, View } from 'react-native';
import { Amplify, PubSub } from 'aws-amplify';
import { AWSIoTProvider } from '@aws-amplify/pubsub';
import { useEffect, useState } from 'react';

import {
  REACT_APP_IDENTITY_POOL_ID,
  REACT_APP_REGION,
  REACT_APP_USER_POOL_ID,
  REACT_APP_USER_POOL_WEB_CLIENT_ID,
  REACT_APP_ENDPOINT
} from '@env'
import SectionList from 'react-native/Libraries/Lists/SectionList';

Amplify.configure({
  Auth: {
    identityPoolId: REACT_APP_IDENTITY_POOL_ID,
    region: REACT_APP_REGION,
    userPoolId: REACT_APP_USER_POOL_ID,
    userPoolWebClientId: REACT_APP_USER_POOL_WEB_CLIENT_ID
  }
});

Amplify.addPluggable(new AWSIoTProvider({
  aws_pubsub_region: REACT_APP_REGION,
  aws_pubsub_endpoint: `wss://${process.env.REACT_APP_ENDPOINT}.iot.${process.env.REACT_APP_REGION}.amazonaws.com/mqtt`
  ,
}));
const Buffer = () => <View style={styles.buffer}></View>
const MyList = ({ header, items }) => {
  return (
    <View>
      <Text style={styles.myFontBold}>{header}</Text>
      {items.map(beverage => <Text style={styles.myFontSmall} key={beverage}>{beverage}</Text>)}
    </View>
  )
}
const Details = ({ inventoryStats }) => {
  const { profit, sold, remaining } = inventoryStats;
  return (
    <View>
      <MyList header={"Remaining"} items={remaining} />
      <Buffer />
      <MyList header={"Sold"} items={sold} />
      <Buffer />
      <Text style={styles.myFontBold}>Total revenue:  {profit},- <Text></Text></Text>
    </View>
  )
}

const App = () => {
  const [inventoryStats, setInventoryStats] = useState({ profit: 0 })
  useEffect(() => {
    PubSub.subscribe('LORA/pub').subscribe({
      next: data => setData(data),
      error: error => console.error(error),
      complete: () => console.log('Done'),
    })
  }, [])

  const setData = (data) => {
    const profit = Number(data.value.profit);
    const sold = JSON.parse(data.value.sold);
    const remaining = JSON.parse(data.value.remaining);
    setInventoryStats({ profit, sold, remaining });
  }

  return <SafeAreaView style={styles.container}>
    <View >
      {inventoryStats.profit === 0
        ? <Text style={styles.myFont}>Nothing sold yet...</Text>
        : <Details inventoryStats={inventoryStats} />}
    </View>
  </SafeAreaView>
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  myFont: {
    fontSize: 25
  },
  myFontSmall: {
    fontSize: 20
  },
  myFontBold: {
    fontSize: 25,
    fontWeight: "700"
  },
  buffer: {
    padding: 20,
  }
});

export default App;