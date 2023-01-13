import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'components/grid_section.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final Future<FirebaseApp> fbApp = Firebase.initializeApp();
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        home: FutureBuilder(
      future: fbApp,
      builder: (context, snapshot) {
        if (snapshot.hasError) {
          print("error");
          return const Text("Error found");
        } else if (snapshot.hasData) {
          print(snapshot);
          print("Done setup db!");
          return MainPage();
        }

        return const Center(
          child: CircularProgressIndicator(),
        );
      },
    ));
  }
}

class MainPage extends StatefulWidget {
  const MainPage({super.key});

  @override
  State<MainPage> createState() => _MainPageState();
}

class _MainPageState extends State<MainPage> {
  @override
  Widget build(BuildContext context) {
    final searchFilter = TextEditingController();
    return Scaffold(
      body: SafeArea(
        child: Container(
          color: const Color.fromARGB(255, 244, 248, 253),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Padding(
                padding: const EdgeInsets.fromLTRB(25, 30, 20, 20),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Text(
                      getGreeting(),
                      style: TextStyle(
                          fontSize: 40,
                          color: Colors.black,
                          fontWeight: FontWeight.bold),
                    ),
                    SizedBox(height: 15),
                    Text(
                      "Barnard",
                      style: TextStyle(
                          fontSize: 25,
                          color: Colors.black,
                          fontWeight: FontWeight.bold),
                    ),
                  ],
                ),
              ),
              SizedBox(height: 20),
              SizedBox(
                height: 50,
                child: TextField(
                  controller: searchFilter,
                  decoration: InputDecoration(
                      contentPadding: EdgeInsets.all(0),
                      prefixIcon: Icon(Icons.search_outlined),
                      border: OutlineInputBorder(
                        borderRadius: BorderRadius.circular(20.0),
                      ),
                      filled: true,
                      hintStyle:
                          TextStyle(color: Colors.grey[800], fontSize: 20),
                      hintText: "Search",
                      fillColor: Colors.white70),
                  onChanged: (value) {
                    setState(() {});
                  },
                ),
              ),
              SizedBox(height: 20),
              Padding(
                padding: const EdgeInsets.fromLTRB(25, 25, 20, 20),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        Text(
                          "All sheds",
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
                                  offset: Offset(
                                      0, 3), // changes position of shadow
                                ),
                              ],
                              color: Colors.white),
                          child: Padding(
                            padding: const EdgeInsets.all(2.0),
                            child: Icon(Icons.add),
                          ),
                        )
                      ],
                    ),
                  ],
                ),
              ),
              SizedBox(
                height: 20,
              ),
              GridSection(),
            ],
          ),
        ),
      ),
    );
  }
}

String getGreeting() {
  final dt = DateTime.now().hour;

  final greeting = (dt >= 0 && dt < 6)
      ? "Good Night!"
      : (dt >= 6 && dt <= 11)
          ? "Good Morning"
          : (dt >= 12 && dt < 18)
              ? "Good Afternoon"
              : "Good Evening";

  return greeting;
}
