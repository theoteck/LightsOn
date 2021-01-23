// Goto solid.dart for comments; all the effect screens use the same codebase

import 'package:flutter/material.dart';
import 'package:lights_on/values/settings.dart';

import 'package:lights_on/widgets/color_dl_button.dart';
import 'package:lights_on/widgets/slider.dart';
import 'package:lights_on/widgets/spacer.dart';

import 'package:lights_on/widgets/flutter_hsvcolor_picker.dart';

import 'package:lights_on/values/buttonTypes.dart';

import 'package:lights_on/values/bluetooth.dart';

class HalloweenPage extends StatefulWidget {
  _HalloweenPageState createState() => _HalloweenPageState();
}

class _HalloweenPageState extends State<HalloweenPage> {
  final colorStartIndex = 4;

  var buttonType = [
    ButtonType.Switch,
    ButtonType.Slider,
    ButtonType.Slider,
    ButtonType.Slider,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Space,
    ButtonType.Space,
  ];

  var buttonNames = [
    "Random Color",
    "Eye Width",
    "Eye Space",
    "Color Count",
    "Color 1",
    "Color 2",
    "Color 3",
    "Color 4",
    "Color 5",
    "Color 6",
    "Color 7"
  ];

  void setColor(int index, Color color) {
    setState(() {
      eyeColors[index] = color;
    });
  }

  Color getColor(int index) {
    return eyeColors[index];
  }

  double getMin(int index) {
    return 1;
  }

  double getMax(int index) {
    if (index == 1 || index == 2) {
      return 10;
    }
    return 7;
  }

  double getValue(int index) {
    if (index == 1) {
      return eyeEyeWidth;
    }
    if (index == 2) {
      return eyeEyeSpace;
    }
    return eyeActiveColors;
  }

  String getNumber(int index) {
    if (index == 1) {
      return eyeEyeWidth.round().toString();
    }
    if (index == 2) {
      return eyeEyeSpace.round().toString();
    }
    return eyeActiveColors.round().toString();
  }

  int getDivisions(int index) {
    if (index == 1 || index == 2) {
      return 9;
    }
    return 6;
  }

  bool getBoolValue(int index) {
    return eyeRainbow;
  }

  void setValue(int index, double value) {
    if (index == 1) {
      eyeEyeWidth = value;
    }
    if (index == 2) {
      eyeEyeSpace = value;
    }
    if (index == 3) {
      eyeActiveColors = value;
    }
  }

  void setBoolValue(int index, bool value) {
    eyeRainbow = value;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        floatingActionButton: FloatingActionButton.extended(
          onPressed: () {
            sendData(4, 0, eyeActiveColors.toInt());

            for (int i = 0; i < 7; i++) {
              sendData(4, i + 1, eyeColors[i].toRGBInt());
            }

            sendData(4, 8, eyeRainbow.toInt());

            sendData(4, 12, eyeEyeWidth.toInt());

            sendData(4, 13, eyeEyeSpace.toInt());
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
