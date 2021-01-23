[FastLED library link]: https://github.com/FastLED/FastLED
[FastLED examples link]: https://github.com/FastLED/FastLED/tree/master/examples
[Flutter link]: https://flutter.dev/
[Tweaking4All effects link]: https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/

# LightsOn
An ESP32 project for controlling LED strips through a bluetooth app

## A little bit of info
LightsOn is a complete package so to say; It contains an esp32 program (though it can be made to run everywhere), which controls the LED strip (with the [FastLED library][FastLED library link]) and a [Flutter][Flutter link] application for controlling the esp32 (with Bluetooth Low Energy), so it too can be run on both Android and iOS devices (hypothetically able to be run on PCs (Windows, MacOS and Linux) as well as in browsers due to Flutter's flexibility, though I have not tested these use cases)

## Effects
It currently contains 18 effects, most of which are either ripped of the FastLED [examples][FastLED examples link] or [this][Tweaking4All effects link] awesome blogpost from Tweaking4All.

The effects are the following: 
* Solid
* Fade
* Strobe
* Halloween Eyes
* Cylon
* Twinkle
* Sparkle
* NoisePlusPallete
* Running Lights
* Color Wipe
* Rainbow
* Theater Chase
* Fire
* Pride2015
* Meteor Rain
* Pacifica
* Twinkle Fox
* One Color Cycle

## The How-To's
More information about how the program and the application works can be found in their folders, ESP32 and Application, respectively. 
There you will also see more info on how to configure the code to your needs and configurations. A documentation here on GitHub is planned but not currently available.

## Awesome references
* [Flutter Reactive Blue][Flutter Reactive Blue link] for the amazing bluetooth library
* [Flutter HSV Color Picker][Flutter HSV Color Picker link] for the, well, color picker :) (Modified it a bit)
* I think Microsoft for the outline of the app icon, but I can't seem to find any link to it

## Questions
If you have any questions open an issue and add the "question" label and I will answer as soon as I can :).
