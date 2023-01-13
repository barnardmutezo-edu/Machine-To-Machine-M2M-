import 'package:flutter_application_firebase/components/sensor_props_abstract.dart';

class SensorPropsHistory extends SensorPropsAbstract {
  SensorPropsHistory(
      {required super.temperature,
      required super.humidity,
      required this.time});
  late String time;
}
