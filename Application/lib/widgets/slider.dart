// Most of the files in the widget folder have many similarities and probably could be optimized together
// but I choose not to

// Import the material design widgets
import 'package:flutter/material.dart';

//::SliderWidget::
//  The Stateless Widget that is used as a slider (obviously)
class SliderWidget extends StatelessWidget {
  // Class constructor(flutter key, slider title, number to show, slider widget)
  SliderWidget(
      {Key key, this.text, this.number, this.slider, this.fontSize = 25})
      : super(key: key);

  // Class variable
  final String text;
  final String number;
  final Widget slider;
  final double fontSize;

  @override
  Widget build(BuildContext context) {
    // Widget that consists of an aligned row that houses a widget that contains the slider title
    // and the slider widget itself, as well as a widget that contains the child widget
    return Align(
        child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
      Container(
          margin: EdgeInsets.only(top: 0, bottom: 15),
          width: 340,
          height: 100,
          padding: EdgeInsets.only(top: 5),
          decoration: BoxDecoration(
              borderRadius: BorderRadius.only(
                  topLeft: Radius.circular(18),
                  bottomLeft: Radius.circular(18)),
              color: Colors.grey[850]),
          // This contains the setting effect title
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                text,
                style: TextStyle(
                    color: Colors.white,
                    fontWeight: FontWeight.w500,
                    fontSize: 25),
              ),
              slider
            ],
          )),
      // This containts the number that is shown next to the slider
      // and is the slider selected number
      Container(
          margin: EdgeInsets.only(bottom: 15),
          width: 60,
          height: 100,
          alignment: Alignment.center,
          child: Text(
            number,
            style: TextStyle(
                color: Colors.white,
                fontSize: fontSize,
                fontFamily: 'Montserrat',
                fontWeight: FontWeight.w500),
          ),
          decoration: BoxDecoration(
              color: Colors.grey[850],
              borderRadius: BorderRadius.only(
                  topRight: Radius.circular(18),
                  bottomRight: Radius.circular(18))))
    ]));
  }
}
