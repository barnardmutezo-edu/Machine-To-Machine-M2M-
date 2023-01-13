import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'historyProps.dart';

class HistoryList extends StatefulWidget {
  HistoryList({super.key, required this.props});
  late HistoryProps props;
  @override
  State<HistoryList> createState() => _HistoryListState();
}

class _HistoryListState extends State<HistoryList> {
  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        Text(
          widget.props.txt,
          style: const TextStyle(fontSize: 18, fontWeight: FontWeight.w600),
        ),
        const SizedBox(
          width: 5,
        ),
        GestureDetector(
            onTap: () {
              deleteElement();
            },
            child: const Icon(Icons.delete)),
        const SizedBox(
          height: 10,
        )
      ],
    );
  }

  void deleteElement() async {
    final DatabaseReference ref =
        FirebaseDatabase.instance.ref().child('/state/history');
    ref.child(widget.props.ID).remove();
  }
}
