import 'package:flutter_application_firebase/components/sensor_props_abstract.dart';

class SensorPropsDetailed extends SensorPropsAbstract {
  SensorPropsDetailed(
      {required super.temperature,
      required super.humidity,
      required this.isActive,
      required this.iD});

  late bool isActive;
  late String iD;

  factory SensorPropsDetailed.propsFromRTDB(dynamic,v) {


    return SensorPropsDetailed(temperature: v["sensors"]["temperature"],
                humidity: v["sensors"]["humidity"],
                isActive: v["sensors"]["alarm"]["isActive"],
                iD: dynamic);
  }
}
