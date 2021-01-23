// Goto solid.dart for comments; all the effect screens use the same codebase

import 'package:flutter/material.dart';
import 'package:lights_on/values/settings.dart';

import 'package:lights_on/widgets/color_dl_button.dart';
import 'package:lights_on/widgets/slider.dart';
import 'package:lights_on/widgets/spacer.dart';

import 'package:lights_on/widgets/flutter_hsvcolor_picker.dart';

import 'package:lights_on/values/buttonTypes.dart';

import 'package:lights_on/values/bluetooth.dart';

class StrobePage extends StatefulWidget {
  _StrobePageState createState() => _StrobePageState();
}

class _StrobePageState extends State<StrobePage> {
  final colorStartIndex = 3;

  var buttonType = [
    ButtonType.Switch,
    ButtonType.Slider,
    ButtonType.Slider,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Slider,
    ButtonType.Slider,
    ButtonType.Space,
    ButtonType.Space,
  ];

  var buttonNames = [
    "Random Color",
    "Strobe Count",
    "Color Count",
    "Color 1",
    "Color 2",
    "Color 3",
    "Color 4",
    "Color 5",
    "Color 6",
    "Color 7",
    "Flash Delay",
    "End Delay"
  ];

  void setColor(int index, Color color) {
    setState(() {
      strobeColors[index] = color;
    });
  }

  double getMin(int index) {
    if (index == 1 || index == 2) {
      return 1;
    }
    if (index == 11) {
      return 500;
    }

    return 0;
  }

  double getMax(int index) {
    if (index == 1) {
      return 20;
    }
    if (index == 2) {
      return 7;
    }
    if (index == 10) {
      return 150;
    }
    return 2000;
  }

  double getValue(int index) {
    if (index == 1) {
      return strobeCount;
    }
    if (index == 2) {
      return strobeActiveColors;
    }
    if (index == 10) {
      return strobeFlashDelay;
    }
    return strobeEndDelay;
  }

  String getNumber(int index) {
    if (index == 1) {
      return strobeCount.round().toString();
    }
    if (index == 2) {
      return strobeActiveColors.round().toString();
    }
    if (index == 10) {
      return strobeFlashDelay.round().toString();
    }
    return strobeEndDelay.round().toString();
  }

  int getDivisions(int index) {
    if (index == 1) {
      return 19;
    }
    if (index == 2) {
      return 6;
    }
    if (index == 10) {
      return 15;
    }
    return 150;
  }

  bool getBoolValue(int index) {
    return strobeRainbow;
  }

  void setValue(int index, double value) {
    if (index == 1) {
      strobeCount = value;
    }
    if (index == 2) {
      strobeActiveColors = value;
    }
    if (index == 10) {
      strobeFlashDelay = value;
    }
    if (index == 11) {
      strobeEndDelay = value;
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        floatingActionButton: FloatingActionButton.extended(
          onPressed: () {
            sendData(3, 0, strobeActiveColors.toInt());

            for (int i = 0; i < 7; i++) {
              sendData(3, i + 1, strobeColors[i].toRGBInt());
            }

            sendData(3, 8, strobeRainbow.toInt());

            sendData(3, 12, strobeCount.toInt());

            sendData(3, 13, strobeFlashDelay.toInt());

            sendData(3, 14, strobeEndDelay.toInt());
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
                                    strobeRainbow = value;
                                  });
                                },
                                /* secondary: Container(
                                  width: 1,
                                ), */
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
                            number: getNumber(index),
                            fontSize: index == 11 ? 22 : 25,
                          );
                        }
                        if (buttonType[index] == ButtonType.Space)
                          return CustomSpacer1();
                        return ColorDialogButton(
                            text: buttonNames[index],
                            child: Container(
                              width: 60,
                              height: 100,
                              decoration: BoxDecoration(
                                  color: strobeColors[index - colorStartIndex],
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
                                  color: strobeColors[index - colorStartIndex],
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
