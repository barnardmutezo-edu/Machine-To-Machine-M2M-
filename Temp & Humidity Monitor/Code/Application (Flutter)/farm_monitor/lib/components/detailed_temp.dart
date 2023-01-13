import 'package:flutter/material.dart';
import 'package:flutter_application_firebase/components/sensor_props_detailed.dart';

class DetailedTemp extends StatefulWidget {
  const DetailedTemp({super.key, required this.props});
  final SensorPropsDetailed props;
  @override
  State<DetailedTemp> createState() => _DetailedTempState();
}

class _DetailedTempState extends State<DetailedTemp> {
  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      children: [
        Column(
          children: [
            Row(
              children: [
                Text(
                  "${widget.props.temperature}",
                  style: const TextStyle(fontSize: 60),
                ),
                const Text(
                  "°",
                  style: TextStyle(fontSize: 35),
                ),
              ],
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: const [
                    Text("MAX"),
                    Text("28°"),
                  ],
                ),
                Padding(
                  padding: const EdgeInsets.only(left: 15, right: 15),
                  child: Center(
                      child: Container(
                    width: 1,
                    height: 30,
                    color: Colors.grey,
                  )),
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: const [
                    Text("MIN"),
                    Text("10°"),
                  ],
                ),
              ],
            ),
          ],
        ),
        Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Row(
              children: [
                Text(
                  "${widget.props.humidity}",
                  style: TextStyle(fontSize: 60),
                ),
                const Text(
                  "%",
                  style: TextStyle(fontSize: 35),
                ),
              ],
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text("MAX"),
                    Text("28°"),
                  ],
                ),
                Padding(
                  padding: const EdgeInsets.only(left: 15, right: 15),
                  child: Center(
                      child: Container(
                    width: 1,
                    height: 30,
                    color: Colors.grey,
                  )),
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: const [
                    Text("MIN"),
                    Text("10°"),
                  ],
                ),
              ],
            ),
          ],
        ),
      ],
    );
  }
}
