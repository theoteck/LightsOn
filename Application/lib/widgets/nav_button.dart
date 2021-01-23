// Most of the files in the widget folder have many similarities and probably could be optimized together
// but I choose not to

// Import the material design widgets
import 'package:flutter/material.dart';

//::CustomButtonNav::
//  The Stateless Widget that is used as a button for navigating to the selected effect page
class CustomButtonNav extends StatelessWidget {
  // Class constructor(flutter key, effect name, right side widget, effect screen route,bottom margin)
  CustomButtonNav(
      {Key key, this.text, this.child, this.route, this.margin = 15})
      : super(key: key);

  // Class variables
  final String text;
  final String route;
  final Widget child;
  final double margin;

  @override
  Widget build(BuildContext context) {
    // Widget that consists of an aligned row that houses a widget that contains the effect name
    // and a widget that contains the child widget
    return Align(
        child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
      Container(
          margin: EdgeInsets.only(bottom: margin),
          width: 340,
          height: 100,
          // When the button is pressed goto to the page that is pointed by the route
          child: RaisedButton(
            onPressed: () {
              Navigator.pushNamed(
                context,
                route,
              );
            },
            color: Colors.grey[850],
            shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.only(
                    topLeft: Radius.circular(18),
                    bottomLeft: Radius.circular(18))),
            // This contains the effect name that is shown on the button
            child: Text(
              text,
              style: TextStyle(
                  color: Colors.white,
                  fontSize: 30,
                  fontFamily: 'Montserrat',
                  fontWeight: FontWeight.w500),
            ),
          )),
      // The container that holds the widget that is shown on the right side of the button
      Container(
        margin: EdgeInsets.only(bottom: margin),
        width: 60,
        height: 100,
        alignment: Alignment.center,
        child: child,
      )
    ]));
  }
}
