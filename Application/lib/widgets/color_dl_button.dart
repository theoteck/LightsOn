// Most of the files in the widget folder have many similarities and probably could be optimized together
// but I choose not to

import 'package:flutter/material.dart';

// The following two extensions do not fit in this file, but because they don't take too much space,
// and creating a new file is pointless, I decided to put them here

// Adds the Color.toRGBInt to the Color class
extension IntColor on Color {
  //::toRGBInt::
  //  Returns the color in integer format
  int toRGBInt() {
    int rgb = red;
    rgb = (rgb << 8) + green;
    rgb = (rgb << 8) + blue;

    return rgb;
  }
}

// Adds the Color.toRGBInt to the Color class
extension IntBool on bool {
  //::toInt::
  //  Returns the boolean in integer format (0||1)
  int toInt() {
    if (this)
      return 1;
    else
      return 0;
  }
}

//::ColorDialogButton::
//  The Stateless Widget that is used as the color button for the effects
class ColorDialogButton extends StatelessWidget {
  // Class constructor: (flutter key, color name, right side widget, color picker dialog widget)
  ColorDialogButton({Key key, this.text, this.child, this.dialogChild})
      : super(key: key);

  // Class variables
  final String text;
  final Widget dialogChild;
  final Widget child;

  @override
  Widget build(BuildContext context) {
    // Widget consists of an aligned row that houses a widget that contains the title,
    // and a widget that contains the child widget
    return Align(
        child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
      Container(
          margin: EdgeInsets.only(top: 0, bottom: 15),
          width: 340, //390
          height: 100,
          // When the button is pressed show the color picker dialog, dialogChild
          child: RaisedButton(
            onPressed: () {
              showDialog(context: context, builder: (_) => dialogChild);
            },
            color: Colors.grey[850],
            shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.only(
                    topLeft: Radius.circular(18),
                    bottomLeft: Radius.circular(18))),
            // This contains the title that is shown on the button
            child: Text(
              text,
              style: TextStyle(
                  color: Colors.white,
                  fontSize: 30,
                  fontFamily: 'Montserrat',
                  fontWeight: FontWeight.w500),
            ),
          )),
      // The constainer that holds the child widget that is show on the right side of the button
      Container(
        margin: EdgeInsets.only(bottom: 15),
        width: 60,
        height: 100,
        alignment: Alignment.center,
        child: child,
      )
    ]));
  }
}
