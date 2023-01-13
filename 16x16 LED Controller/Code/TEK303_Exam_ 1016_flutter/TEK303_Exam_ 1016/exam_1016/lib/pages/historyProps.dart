class HistoryProps {
  HistoryProps({
    required this.ID,
    required this.txt,
  });
  late String ID;
  late String txt;
  factory HistoryProps.propsFromRTDB(dynamic, v) {
    return HistoryProps(ID: dynamic, txt: v);
  }
}
