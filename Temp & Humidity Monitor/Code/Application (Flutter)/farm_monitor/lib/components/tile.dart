import 'package:flutter/material.dart';
import 'package:flutter_application_firebase/components/sensor_props_detailed.dart';
import 'package:flutter_application_firebase/components/pages/detail_page.dart';

class Tile extends StatefulWidget {
  const Tile(
      {super.key,
     required this.props});

  final SensorPropsDetailed props;
  @override
  State<Tile> createState() => _TileState();
}

class _TileState extends State<Tile> {
  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) => DetailPage(
                      props: widget.props

                    )));
      },
      child: Container(
        decoration: BoxDecoration(
            borderRadius: BorderRadius.circular(20),
            boxShadow: [
              BoxShadow(
                color: Colors.grey.withOpacity(0.1),
                spreadRadius: 5,
                blurRadius: 7,
                offset: Offset(0, 3), // changes position of shadow
              ),
            ],
            color: Colors.white),
        child: Padding(
          padding: const EdgeInsets.fromLTRB(25, 30, 20, 20),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text(
                    widget.props.iD,
                    style: TextStyle(
                        fontSize: 25,
                        color: Colors.black,
                        fontWeight: FontWeight.bold),
                  ),
                  Container(
                    decoration: BoxDecoration(
                        borderRadius: BorderRadius.circular(20),
                        boxShadow: [
                          BoxShadow(
                            color: Colors.grey.withOpacity(0.1),
                            spreadRadius: 5,
                            blurRadius: 7,
                            offset: Offset(0, 3), // changes position of shadow
                          ),
                        ],
                        color: Colors.white),
                    child: Padding(
                      padding: const EdgeInsets.all(2.0),
                      child: GestureDetector(
                          onTap: () {
                            print("hi");
                          },
                          child: Icon(Icons.more_vert_outlined)),
                    ),
                  )
                ],
              ),
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Row(
                    children: [
                      Icon(
                        Icons.thermostat_rounded,
                        size: 25,
                      ),
                      SizedBox(width: 5),
                      Text(widget.props.temperature.toString(),
                          style: TextStyle(fontSize: 30, color: Colors.black)),
                      Text("°",
                          style: TextStyle(fontSize: 30, color: Colors.black)),
                    ],
                  ),
                  SizedBox(
                    height: 2,
                  ),
                  Container(
                    child: Row(
                      children: [
                        Icon(
                          Icons.water_drop_rounded,
                          size: 25,
                        ),
                        SizedBox(width: 5),
                        Text(widget.props.humidity.toString(),
                            style:
                                TextStyle(fontSize: 30, color: Colors.black)),
                        SizedBox(width: 3),
                        Text("%",
                            style:
                                TextStyle(fontSize: 18, color: Colors.black)),
                      ],
                    ),
                  ),
                ],
              )
            ],
          ),
        ),
      ),
    );
  }
}
