// Import the material design widgets
import 'package:flutter/material.dart';

// Import custom widgets and values
import 'package:lights_on/values/bluetooth.dart';
import 'package:lights_on/values/settings.dart';
import 'package:lights_on/widgets/slider.dart';
import 'package:lights_on/widgets/nav_button.dart';
import 'package:lights_on/widgets/spacer.dart';
import 'package:lights_on/icons/lights_on_icons_icons.dart';

//::Home::
//  Stateful widget (dynamic) that is the home screen of the app
class Home extends StatefulWidget {
  _HomeState createState() => _HomeState();
}

//::_HomeState::
//  Definition of the Home class
class _HomeState extends State<Home> {
  // The names of the effect buttons; they are dynamically assigned
  final buttonNames = [
    "Solid",
    "Fade",
    "Strobe",
    "Halloween Eyes",
    "Cylon",
    "Twinkle",
    "Sparkle",
    "NoisePlusPallete",
    "Running Lights",
    "Color Wipe",
    "Rainbow",
    "Theater Chase",
    "Fire",
    "Pride2015",
    "Meteor Rain",
    "Pacifica",
    "Twinkle Fox"
  ];

  // Keep track of the selected effect for lightbulb action
  int selectedButtonId;
  int lastSelected; // A little bit useless on this revision, but hey if it works, don't touch it!

  // An boolean array of the effects, with true being the selected one
  List<bool> isSelected = List.filled(18, false);

  //::lightBuldChanged::(which effect)
  //  Handles the effect change; changes the active lightbuld and sends the effect selection to the mc
  void lightBulbChanged(int index) async {
    setState(() {
      // The effect isn't the already selected one, proceed
      if (!isSelected[index]) {
        // Turn all the elements in the list to false
        for (int i = 0; i < isSelected.length; i++) {
          isSelected[i] = false;
        }

        // Set the selected button id to the index
        selectedButtonId = index;

        // Set the selected item in the list to true
        isSelected[index] = true;

        // Turn off the random effect switch; both an effect and a random one can't be selected
        randomEffect = false;
      }
    });

    // Send the selected effect to the mc
    sendData(0, 0, index);

    // Turn of the random effect; if it's selected or not
    sendData(0, 8, 0);
  }

  // Upon building the widget run the bluetooth initialization
  @override
  void initState() {
    bleInit();

    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    /// The home widget consists of the LightsOn title, the random effect switch,
    /// the brightness slider, the one color cycle effect, a divider and then the other effect buttons,
    /// with some spacers sprinkled between the widgets
    return Scaffold(
        backgroundColor: Colors.grey[900],
        body: Container(
            height: 1000,
            color: Colors.grey[900],
            alignment: Alignment.center,
            child: Column(
              children: [
                CustomSpacer1(), // Spacer from the top of the page
                Row(mainAxisAlignment: MainAxisAlignment.center, children: [
                  // The LightsOn text, and the required thingies to make the gradient on the "ON"
                  const Text(
                    'Lights',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 30,
                        fontFamily: 'Montserrat',
                        fontWeight: FontWeight.w500),
                  ),
                  Center(
                    child: ShaderMask(
                      shaderCallback: (Rect bounds) {
                        final gradient = LinearGradient(
                            begin: Alignment.topLeft,
                            end: Alignment.bottomRight,
                            colors: [
                              Colors.blue,
                              Colors.cyan,
                              Colors.green,
                              Colors.yellow,
                              Colors.red,
                            ],
                            stops: [
                              0.1,
                              0.2,
                              0.4,
                              0.6,
                              0.9
                            ]);
                        return gradient.createShader(Offset.zero & bounds.size);
                      },
                      child: Text('On',
                          style: TextStyle(
                              fontSize: 30.0,
                              color: Colors.white,
                              fontFamily: 'Montserrat',
                              fontWeight: FontWeight
                                  .w700) // must be white for the gradient shader to work
                          ),
                    ),
                  ),
                ]),
                CustomSpacer(), // Spacer between the text and the buttons
                Expanded(
                    // Button list builder
                    child: ListView.builder(
                        // Account for the four sections that aren't on the buttonNames list
                        itemCount: buttonNames.length + 4,

                        /// builder: (index)
                        /// (0): Random Effect
                        /// (1): Brightness slider
                        /// (2): One Color Cycle effect
                        /// (3): Divider
                        /// (4 .. 20): Other effects
                        itemBuilder: (BuildContext context, int index) {
                          switch (index) {
                            case 0:
                              {
                                return Container(
                                    margin: EdgeInsets.only(
                                      left: 6,
                                      right: 6,
                                      bottom: 15,
                                    ),
                                    width: 400,
                                    height: 100,
                                    alignment: Alignment.center,
                                    decoration: BoxDecoration(
                                        borderRadius: BorderRadius.all(
                                            Radius.circular(18)),
                                        color: Colors.grey[850]),
                                    child: SwitchListTile(
                                      title: Text(
                                        "Random Effect",
                                        style: TextStyle(
                                            color: Colors.white,
                                            fontSize: 28,
                                            fontFamily: 'Montserrat',
                                            fontWeight: FontWeight.w500),
                                        textAlign: TextAlign.center,
                                      ),
                                      value: randomEffect,
                                      onChanged: (bool value) {
                                        setState(() {
                                          // Change the random effect value according to the "value"
                                          randomEffect = value;

                                          // If it is true save the selected button, put -1 in its place and send the effect change
                                          // if it's false send the effect change
                                          if (value) {
                                            setState(() {
                                              lastSelected = selectedButtonId;
                                              selectedButtonId = -1;
                                            });

                                            sendData(0, 8, 1);
                                          } else {
                                            sendData(0, 8, 0);
                                          }

                                          // Make all the elements in the list false
                                          for (int i = 0;
                                              i < isSelected.length;
                                              i++) {
                                            isSelected[i] = false;
                                          }
                                        });
                                      },
                                    ));
                              }
                              break;

                            case 1:
                              {
                                return SliderWidget(
                                  number: brightness.round().toString(),
                                  text: "Brightness",
                                  slider: Slider(
                                    divisions: 256,
                                    min: 0,
                                    max: 255,
                                    value: brightness,
                                    onChanged: (value) {
                                      setState(() {
                                        // Change the on screen value to the slider value
                                        brightness = value;
                                      });
                                    },
                                    onChangeEnd: (value) {
                                      setState(() {
                                        // When the user decides on the value, show it and send it
                                        brightness = value;

                                        sendData(0, 12, brightness.toInt());
                                      });
                                    },
                                  ),
                                );
                              }
                              break;

                            case 2:
                              {
                                return CustomButtonNav(
                                  margin: 0,
                                  text: "One Color Cycle",
                                  route: "/Effect Cycle",
                                  child: Container(
                                    width: 60,
                                    height: 100,
                                    child: RaisedButton(
                                      onPressed: () {
                                        setState(() {
                                          // Change the selected effect
                                          lightBulbChanged(17);
                                        });
                                      },
                                      color: Colors.grey[850],
                                      shape: RoundedRectangleBorder(
                                          borderRadius: BorderRadius.only(
                                              topRight: Radius.circular(18),
                                              bottomRight:
                                                  Radius.circular(18))),
                                      // Change the lightbulb icon on its selection status
                                      child: Icon(
                                          isSelected[17]
                                              ? LightsOnIcons
                                                  .ic_fluent_lightbulb_24_filled
                                              : LightsOnIcons
                                                  .ic_fluent_lightbulb_24_regular,
                                          color: isSelected[17]
                                              ? Colors.amber
                                              : Colors.grey[700],
                                          size: 28),
                                    ),
                                  ),
                                );
                              }
                              break;

                            case 3:
                              {
                                return Divider(
                                  height: 40,
                                  indent: 15,
                                  endIndent: 15,
                                );
                              }
                              break;

                            default:
                              {
                                return CustomButtonNav(
                                  // Account for the four sections
                                  text: buttonNames[index - 4],
                                  //Set the button route according to the button name
                                  route: "/${buttonNames[index - 4]}",
                                  child: Container(
                                    width: 60,
                                    height: 100,
                                    child: RaisedButton(
                                      onPressed: () {
                                        setState(() {
                                          // Change the selected effect
                                          lightBulbChanged(index - 4);
                                        });
                                      },
                                      color: Colors.grey[850],
                                      shape: RoundedRectangleBorder(
                                          borderRadius: BorderRadius.only(
                                              topRight: Radius.circular(18),
                                              bottomRight:
                                                  Radius.circular(18))),
                                      // Change the lightbulb icon on its selection status
                                      child: Icon(
                                          isSelected[index - 4]
                                              ? LightsOnIcons
                                                  .ic_fluent_lightbulb_24_filled
                                              : LightsOnIcons
                                                  .ic_fluent_lightbulb_24_regular,
                                          color: isSelected[index - 4]
                                              ? Colors.amber
                                              : Colors.grey[700],
                                          size: 28),
                                    ),
                                  ),
                                );
                              }
                              break;
                          }
                        }))
              ],
            )));
  }
}
