// Redirected here by all other effect screens
// The concept is the same in all of them and I don't feel like copying the comments on all of them

// Import the material design widgets
import 'package:flutter/material.dart';

// Import values
import 'package:lights_on/values/settings.dart';
import 'package:lights_on/values/buttonTypes.dart';

// Import custom widgets
import 'package:lights_on/widgets/color_dl_button.dart';
import 'package:lights_on/widgets/slider.dart';
import 'package:lights_on/widgets/spacer.dart';
import 'package:lights_on/widgets/flutter_hsvcolor_picker.dart';

// Import bluetooth class
import 'package:lights_on/values/bluetooth.dart';

//::SolidPage::
//  Stateful widget (dynamic) that is the settings page for the solid effect
class SolidPage extends StatefulWidget {
  _SolidPageState createState() => _SolidPageState();
}

//::_HomeState::
//  Definition of the SolidPage class
class _SolidPageState extends State<SolidPage> {
  //--Effect Specific--//

  // This section contains all the variables and functions that are specific to this effect
  // and used by the All Effects section lower in this file to build the effect screen

  // Variable that stores at what index the 7 ButtonType.Color elements start at the buttonType array
  // Used for correct index accessing by the ListView builder
  final colorStartIndex = 3;

  // A list with the types of buttons used for the effect settings
  var buttonType = [
    ButtonType.Switch,
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

  // The names for the above buttons
  var buttonNames = [
    "Rainbow",
    "Random Color",
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

  //::setColor::(index, color)
  //  Used by the All Effects section to save a color when its been changed by the user
  void setColor(int index, Color color) {
    setState(() {
      solidColors[index] = color;
    });
  }

  //::getColor::(index) -> Color
  //  Used by the All Effects section; returns the color at the selected index
  Color getColor(int index) {
    return solidColors[index];
  }

  //::getMin::(index) -> double
  //  Used by the All Effects section; returns the slider minimum at the selected index
  double getMin(int index) {
    if (index == 2) return 1;
    return 0;
  }

  //::getMax::(index) -> double
  //  Used by the All Effects section; returns the slider maximum at the selected index
  double getMax(int index) {
    if (index == 2) return 7;
    return 200;
  }

  //::getValue::(index) -> double
  //  Used by the All Effects section; returns the slider value at the selected index
  double getValue(int index) {
    if (index == 2) return solidActiveColors;
    return solidSpeedDelay;
  }

  //::getNumber::(index) -> String
  //  Used by the All Effects section; returns the slider value but as a string at the selected index
  String getNumber(int index) {
    return getValue(index).round().toString();
  }

  //::getDivisions::(index) -> int
  //  Used by the All Effects section; returns the amount of slider divisions at the selected index
  int getDivisions(int index) {
    if (index == 2) return 6;
    return 20;
  }

  //::getBoolValue::(index) -> bool
  //  Used by the All Effects section; returns the value of a switch at the selected index
  bool getBoolValue(int index) {
    if (index == 0) return solidRainbow;
    return solidRandom;
  }

  //::setValue::(index, value)
  //  Used by the All Effects section; changes a double value at the selected index
  void setValue(int index, double value) {
    if (index == 2) solidActiveColors = value;
    if (index == 10) solidSpeedDelay = value;
  }

  //::setBoolValue::(index, value)
  //  Used by the All Effects section; changes a boolean value at the selected index
  void setBoolValue(int index, bool value) {
    if (index == 0) {
      solidRainbow = value;
      solidRandom = false;
    }
    if (index == 1) {
      solidRandom = value;
      solidRainbow = false;
    }
  }

  //-------------------//

  //--All Effects--//

  // The same code is used by all effect files; they are only different in the Effect Specific section
  // (Except the onPressed fuction used for sending data; this is different on every effect)
  // (Except the strobe.dart screen which has a smaller font on the End Delay slider because it goes up to 2000)
  // It uses the variables and functions in the Effect Specific section to build the effect screen

  @override
  Widget build(BuildContext context) {
    // The effect screen widget consists of a list of switches, sliders and color selectors for changing each effect's settings
    // It also contains a floating button that when pressed sends the effect data to the mc
    return Scaffold(
        // The floating button
        floatingActionButton: FloatingActionButton.extended(
          onPressed: () {
            // Send the effect data to the mc
            sendData(1, 0, solidActiveColors.toInt());

            for (int i = 0; i < 7; i++) {
              sendData(1, i + 1, solidColors[i].toRGBInt());
            }

            sendData(1, 8, solidRandom.toInt());

            sendData(1, 9, solidRainbow.toInt());

            sendData(1, 11, solidSpeedDelay.toInt());
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
                        // Switch widget
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

                        // Slider widget
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

                        // Space widget
                        if (buttonType[index] == ButtonType.Space)
                          return CustomSpacer1();

                        // Color widget
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
                            // Color change dialog
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

  //---------------//
}
