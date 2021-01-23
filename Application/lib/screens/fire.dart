// Goto solid.dart for comments; all the effect screens use the same codebase

import 'package:flutter/material.dart';
import 'package:lights_on/values/settings.dart';

import 'package:lights_on/widgets/color_dl_button.dart';
import 'package:lights_on/widgets/slider.dart';
import 'package:lights_on/widgets/spacer.dart';

import 'package:lights_on/widgets/flutter_hsvcolor_picker.dart';

import 'package:lights_on/values/buttonTypes.dart';

import 'package:lights_on/values/bluetooth.dart';

class FirePage extends StatefulWidget {
  _FirePageState createState() => _FirePageState();
}

class _FirePageState extends State<FirePage> {
  final colorStartIndex = 0;

  var buttonType = [ButtonType.Slider, ButtonType.Slider, ButtonType.Slider];

  var buttonNames = [
    "Cooling",
    "Sparking",
    "Speed Delay",
  ];

  void setColor(int index, Color color) {
    setState(() {
      color = color;
    });
  }

  Color getColor(int index) {
    return Colors.white;
  }

  double getMin(int index) {
    if (index == 0) return 1;
    return 0;
  }

  double getMax(int index) {
    if (index == 0) return 50;
    if (index == 1) return 300;
    return 200;
  }

  double getValue(int index) {
    if (index == 0) return fireCooling;
    if (index == 1) return fireSparking;
    return fireSpeedDelay;
  }

  String getNumber(int index) {
    return getValue(index).round().toString();
  }

  int getDivisions(int index) {
    if (index == 0) return 49;
    if (index == 1) return 30;
    return 20;
  }

  bool getBoolValue(int index) {
    return false;
  }

  void setValue(int index, double value) {
    if (index == 0) fireCooling = value;
    if (index == 1) fireSparking = value;
    if (index == 2) fireSpeedDelay = value;
  }

  void setBoolValue(int index, bool value) {
    value = value;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        floatingActionButton: FloatingActionButton.extended(
          onPressed: () {
            sendData(13, 11, fireSpeedDelay.toInt());

            sendData(13, 12, fireCooling.toInt());

            sendData(13, 13, fireSparking.toInt());
          },
          label: Text("Apply"),
          icon: Icon(Icons.check),
          backgroundColor: Colors.greenAccent[400],
        ),
        backgroundColor: Colors.grey[900],
        body: Container(
            height: 1000,
            alignment: Alignment.center,
            child: Column(
              children: [
                CustomSpacer1(),
                Expanded(
                  child: ListView.builder(
                      itemCount: buttonType.length,
                      itemBuilder: (BuildContext context, int index) {
                        if (buttonType[index] == ButtonType.Switch) {
                          return Container(
                              margin: EdgeInsets.only(
                                  left: 6, bottom: 15, right: 6),
                              width: 340, //390
                              height: 100,
                              alignment: Alignment.center,
                              decoration: BoxDecoration(
                                  borderRadius:
                                      BorderRadius.all(Radius.circular(18)),
                                  color: Colors.grey[850]),
                              child: SwitchListTile(
                                title: Text(
                                  buttonNames[index],
                                  style: TextStyle(
                                      color: Colors.white,
                                      fontSize: 28,
                                      fontFamily: 'Montserrat',
                                      fontWeight: FontWeight.w500),
                                  textAlign: TextAlign.center,
                                ),
                                value: getBoolValue(index),
                                onChanged: (bool value) {
                                  setState(() {
                                    setBoolValue(index, value);
                                  });
                                },
                              ));
                        }
                        if (buttonType[index] == ButtonType.Slider) {
                          return SliderWidget(
                              text: buttonNames[index],
                              slider: Slider(
                                  divisions: getDivisions(index),
                                  min: getMin(index),
                                  max: getMax(index),
                                  value: getValue(index),
                                  onChanged: (value) {
                                    setState(() {
                                      setValue(index, value);
                                    });
                                  }),
                              number: getNumber(index));
                        }
                        if (buttonType[index] == ButtonType.Space)
                          return CustomSpacer1();
                        return ColorDialogButton(
                            text: buttonNames[index],
                            child: Container(
                              width: 60,
                              height: 100,
                              decoration: BoxDecoration(
                                  color: getColor(index - colorStartIndex),
                                  borderRadius: BorderRadius.only(
                                      topRight: Radius.circular(18),
                                      bottomRight: Radius.circular(18))),
                            ),
                            dialogChild: AlertDialog(
                              title: Text(
                                "Select ${buttonNames[index]}",
                                style: TextStyle(color: Colors.white),
                              ),
                              content: Container(
                                alignment: Alignment.center,
                                width: 380,
                                height: 400,
                                margin: EdgeInsets.only(top: 30),
                                padding: EdgeInsets.all(8),
                                decoration: BoxDecoration(
                                    borderRadius: BorderRadius.circular(18),
                                    color: Colors.grey[850]),
                                child: ColorPicker(
                                  onChanged: (value) {
                                    setColor(index - colorStartIndex, value);
                                  },
                                  color: getColor(index - colorStartIndex),
                                ),
                              ),
                              contentPadding: EdgeInsets.all(0),
                              backgroundColor: Colors.grey[850],
                              titlePadding: EdgeInsets.fromLTRB(24, 24, 24, 0),
                              shape: RoundedRectangleBorder(
                                  borderRadius: BorderRadius.circular(18)),
                              insetPadding: EdgeInsets.fromLTRB(15, 40, 15, 40),
                            ));
                      }),
                ),
              ],
            )));
  }
}
