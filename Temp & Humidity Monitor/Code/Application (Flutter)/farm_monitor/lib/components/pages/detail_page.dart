import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter_application_firebase/components/detailed_temp.dart';
import 'package:flutter_application_firebase/components/history_tile.dart';
import 'package:flutter_application_firebase/components/sensor_props_detailed.dart';
import 'package:flutter_application_firebase/components/sensor_props_history.dart';

class DetailPage extends StatefulWidget {
  const DetailPage({super.key, required this.props});
  final SensorPropsDetailed props;

  @override
  State<DetailPage> createState() => _DetailPageState();
}

class _DetailPageState extends State<DetailPage> {
  List<HistoryTile> tiles = [];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      resizeToAvoidBottomInset: false,
      body: SafeArea(
        child: Container(
          color: const Color.fromARGB(255, 244, 248, 253),
          child: SingleChildScrollView(
            child: Column(
              children: [
                Center(
                  child: Column(
                    children: [
                      const SizedBox(
                        height: 30,
                      ),
                      Text(
                        widget.props.iD,
                        style: const TextStyle(
                            fontSize: 25,
                            color: Colors.black,
                            fontWeight: FontWeight.bold),
                      ),
                      const SizedBox(height: 20),
                      DetailedTemp(
                        props: widget.props,
                      )
                    ],
                  ),
                ),
                const SizedBox(
                  height: 20,
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Padding(
                      padding: const EdgeInsets.fromLTRB(25, 20, 15, 20),
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Row(
                            mainAxisAlignment: MainAxisAlignment.spaceBetween,
                            children: [
                              const Text(
                                "Status: Normal",
                                style: TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold),
                              ),
                              ElevatedButton(
                                  onPressed: () async {
                                    DatabaseReference ref =
                                        FirebaseDatabase.instance.ref().child(
                                            "/monitors/Stovner/sensors/alarm");
                                    await ref.set({"isActive": false});
                                  },
                                  child: const Text("Disable alarm"))
                            ],
                          ),
                          const SizedBox(
                            height: 25,
                          ),
                          const Text(
                            "History",
                            style: TextStyle(
                                fontSize: 25,
                                color: Colors.black,
                                fontWeight: FontWeight.bold),
                          ),
                        ],
                      ),
                    ),
                    StreamBuilder(
                      stream: FirebaseDatabase.instance
                          .ref()
                          .child("/monitors/Stovner/history")
                          .onValue,
                      builder: (context, snapshot) {
                        if (snapshot.hasData) {
                          Map<dynamic, dynamic>? data =
                              snapshot.data?.snapshot.value as Map?;
                          tiles.clear();

                          data?.forEach((dynamic, v) {
                            final sensorPropsHistory = SensorPropsHistory(
                                temperature: v["temperature"],
                                humidity: v["humidity"],
                                time: dynamic);

                            return tiles
                                .add(HistoryTile(props: sensorPropsHistory));
                          });

                          return ListView.builder(
                            scrollDirection: Axis.vertical,
                            shrinkWrap: true,
                            reverse: false,
                            itemCount: tiles.length,
                            itemBuilder: (context, index) {
                              return tiles[index];
                            },
                          );
                        }
                        return const Text("Loading data");
                      },
                    )
                  ],
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }


}
