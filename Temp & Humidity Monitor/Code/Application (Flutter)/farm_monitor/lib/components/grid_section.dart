import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter_application_firebase/components/sensor_props_detailed.dart';
import 'package:flutter_application_firebase/components/tile.dart';

class GridSection extends StatefulWidget {
  const GridSection({super.key});

  @override
  State<GridSection> createState() => _GridSectionState();
}

class _GridSectionState extends State<GridSection> {
  List<Tile> tiles = [];

  @override
  Widget build(BuildContext context) {
    return StreamBuilder(
      stream: FirebaseDatabase.instance.ref().child("/monitors").onValue,
      builder: (context, snapshot) {
        if (snapshot.hasData) {
          Map<dynamic, dynamic>? data = snapshot.data?.snapshot.value as Map?;
          tiles.clear();

          data?.forEach((dynamic, v) {
            final props = SensorPropsDetailed.propsFromRTDB(dynamic, v);

            return tiles.add(Tile(props: props));
          });

          return GridView.builder(
            scrollDirection: Axis.vertical,
            shrinkWrap: true,
            gridDelegate:
                const SliverGridDelegateWithFixedCrossAxisCount(crossAxisCount: 2),
            itemCount: tiles.length,
            itemBuilder: (context, index) {
              return Padding(
                padding: const EdgeInsets.all(8.0),
                child: tiles[index],
              );
            },
          );
        }
        return const Text("Loading data");
      },
    );
  }
}
