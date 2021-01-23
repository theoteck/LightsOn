// Goto solid.dart for comments; all the effect screens use the same codebase

import 'package:flutter/material.dart';
import 'package:lights_on/values/settings.dart';

import 'package:lights_on/widgets/color_dl_button.dart';
import 'package:lights_on/widgets/slider.dart';
import 'package:lights_on/widgets/spacer.dart';

import 'package:lights_on/widgets/flutter_hsvcolor_picker.dart';

import 'package:lights_on/values/buttonTypes.dart';

import 'package:lights_on/values/bluetooth.dart';

class MeteorPage extends StatefulWidget {
  _MeteorPageState createState() => _MeteorPageState();
}

class _MeteorPageState extends State<MeteorPage> {
  final colorStartIndex = 4;

  var buttonType = [
    ButtonType.Slider,
    ButtonType.Slider,
    ButtonType.Switch,
    ButtonType.Slider,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Color,
    ButtonType.Slider,
    ButtonType.Space,
    ButtonType.Space,
  ];

  var buttonNames = [
    "Meteor Size",
    "Decay Size",
    "Random Decay",
    "Color Count",
    "Color 1",
    "Color 2",
    "Color 3",
    "Color 4",
    "Color 5",
    "Color 6",
    "Color 7",
    "Speed Delay",
  ];

  void setColor(int index, Color color) {
    setState(() {
      meteorColors[index] = color;
    });
  }

  Color getColor(int index) {
    return meteorColors[index];
  }

  double getMin(int index) {
    if (index == 0 || index == 3) return 1;
    return 0;
  }

  double getMax(int index) {
    if (index == 0) return 20;
    if (index == 1) return 100;
    if (index == 3) return 7;
    return 200;
  }

  double getValue(int index) {
    if (index == 0) return meteorSize;
    if (index == 1) return meteorDecay;
    if (index == 3) return meteorActiveColors;
    return meteorSpeedDelay;
  }

  String getNumber(int index) {
    return getValue(index).round().toString();
  }

  int getDivisions(int index) {
    if (index == 0) return 19;
    if (index == 1) return 20;
    if (index == 3) return 6;
    return 200;
  }

  bool getBoolValue(int index) {
    return meteorRandomDecay;
  }

  void setValue(int index, double value) {
    if (index == 0) meteorSize = value;
    if (index == 1) meteorDecay = value;
    if (index == 3) meteorActiveColors = value;
    if (index == 11) meteorSpeedDelay = value;
  }

  void setBoolValue(int index, bool value) {
    meteorRandomDecay = value;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        floatingActionButton: FloatingActionButton.extended(
          onPressed: () {
            sendData(15, 0, meteorActiveColors.toInt());

            for (int i = 0; i < 7; i++) {
              sendData(15, i + 1, meteorColors[i].toRGBInt());
            }

            sendData(15, 10, meteorOpposite.toInt());

            sendData(15, 11, meteorSpeedDelay.toInt());

            sendData(15, 12, meteorSize.toInt());

            sendData(15, 13, meteorDecay.toInt());

            sendData(15, 14, meteorRandomDecay.toInt());
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
