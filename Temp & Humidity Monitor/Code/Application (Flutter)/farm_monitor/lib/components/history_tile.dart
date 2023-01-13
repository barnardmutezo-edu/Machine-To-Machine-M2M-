import 'package:flutter/material.dart';
import 'package:flutter_application_firebase/components/sensor_props_history.dart';

class 
HistoryTile extends StatefulWidget {
  HistoryTile({super.key, required this.props});
  late SensorPropsHistory props;
  @override
  State<HistoryTile> createState() => _HistoryTileState();
}

class _HistoryTileState extends State<HistoryTile> {

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(8.0),
      child: Container(
        child: Container(
          decoration: BoxDecoration(
              borderRadius: BorderRadius.circular(20),
              boxShadow: [
                BoxShadow(
                  color: Colors.grey.withOpacity(0.4),

                  offset: Offset(0, 1), // changes position of shadow
                ),
              ],
              color: Colors.white),
          child: Padding(
            padding: const EdgeInsets.fromLTRB(20, 25, 15, 15),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  widget.props.time,
                  style: const TextStyle(fontSize: 25),
                ),
                const SizedBox(height: 10),
                Row(
                  children: [
                    const Icon(Icons.thermostat_outlined),
                    Text("${widget.props.temperature}",
                        style: const TextStyle(fontSize: 30)),
                    const SizedBox(width: 20),
                    const Icon(Icons.water_drop_outlined),
                    Text("${widget.props.humidity}",
                        style: const TextStyle(fontSize: 30)),
                  ],
                )
              ],
            ),
          ),
        ),
      ),
    );
  }
}
