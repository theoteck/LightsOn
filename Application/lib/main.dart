// Import the material design widgets
import 'package:flutter/material.dart';

// Import all the app screens
import 'package:lights_on/screens/chase.dart';
import 'package:lights_on/screens/cycle_effect.dart';
import 'package:lights_on/screens/cylor.dart';
import 'package:lights_on/screens/fade.dart';
import 'package:lights_on/screens/fire.dart';
import 'package:lights_on/screens/halloween.dart';
import 'package:lights_on/screens/meteor.dart';
import 'package:lights_on/screens/cycle.dart';
import 'package:lights_on/screens/running.dart';
import 'package:lights_on/screens/solid.dart';
import 'package:lights_on/screens/sparkle.dart';
import 'package:lights_on/screens/strobe.dart';
import 'package:lights_on/screens/wipe.dart';
import 'package:lights_on/screens/twinkle.dart';
import 'package:lights_on/screens/fox.dart';
import 'package:lights_on/screens/home.dart';

//::main::
//  Flutter main function; called at application start
void main() {
  runApp(
      MyApp()); // Runs the widget MyApp defined below and attaches it to the screen
}

//::MyApp::
//  Stateless Widget class that contains the application code
class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // The routes are used for navicating throughout the app
    // It makes it way more easy to work with the different effect screens
    return MaterialApp(
      initialRoute: "/",
      routes: {
        "/": (context) => Home(),
        "/Solid": (context) => SolidPage(),
        "/Fade": (context) => FadePage(),
        "/Strobe": (context) => StrobePage(),
        "/Halloween Eyes": (context) => HalloweenPage(),
        "/Cylon": (context) => CylorPage(),
        "/Twinkle": (context) => TwinklePage(),
        "/Sparkle": (context) => SparklePage(),
        "/Running Lights": (context) => RunningPage(),
        "/Color Wipe": (context) => WipePage(),
        "/Rainbow": (context) => CyclePage(),
        "/Theater Chase": (context) => TheaterPage(),
        "/Fire": (context) => FirePage(),
        "/Meteor Rain": (context) => MeteorPage(),
        "/Twinkle Fox": (context) => FoxPage(),
        "/Effect Cycle": (context) => CEffectPage(),
      },
      // Defines some of the default theme data that parts of the app uses
      theme: ThemeData(
          primaryColor: Colors.grey[900],
          accentColor: Colors.white,
          fontFamily: 'Montserrat',
          textTheme: TextTheme(
            headline5:
                TextStyle(color: Colors.white, fontWeight: FontWeight.w500),
            headline6:
                TextStyle(color: Colors.white, fontWeight: FontWeight.w500),
          ),
          cardColor: Colors.grey[850],
          dividerColor: Colors.grey[700],
          canvasColor: Colors.grey[800]),
    );
  }
}
