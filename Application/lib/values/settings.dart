// Import the material design widgets
import 'package:flutter/material.dart';

//--Default color values--//
const red = Color(0xFFFF0000);
const orange = Colors.orange;
const yellow = Color(0xFFFFFF00);
const green = Color(0xFF00FF00);
const blue = Color(0xFF0000FF);
const indigo = Colors.indigo;
const violet = Color(0xFF7F00FF);
//------------------------//

// The rest of the file contain the settings for each effect
// In the microcontroller side this is done by an in array in parameters.h

// For a better visualization of the available settings see the ARRAYDATA.md

// Solid effect
List<Color> solidColors = [red, orange, yellow, green, blue, indigo, violet];
double solidActiveColors = 1;
double solidSpeedDelay = 50;
bool solidRainbow = false;
bool solidRandom = false;

// Fade effect
List<Color> fadeColors = [red, orange, yellow, green, blue, indigo, violet];
bool fadeRainbow = false;
double fadeActiveColors = 1;

// Strobe effect
List<Color> strobeColors = [red, orange, yellow, green, blue, indigo, violet];
bool strobeRainbow = false;
double strobeActiveColors = 1;
double strobeCount = 10;
double strobeFlashDelay = 70;
double strobeEndDelay = 600;

// Halloween eyes effect
List<Color> eyeColors = [red, orange, yellow, green, blue, indigo, violet];
bool eyeRainbow = false;
double eyeActiveColors = 1;
double eyeEyeWidth = 1;
double eyeEyeSpace = 4;

// Cylon effect
double cylonSpeedDelay = 10;

// Twinkle effect
List<Color> twinkleColors = [red, orange, yellow, green, blue, indigo, violet];
bool twinkleRainbow = false;
double twinkleActiveColors = 1;
double twinkleCount = 10;

// Sparkle effect
List<Color> sparkleColors = [red, orange, yellow, green, blue, indigo, violet];
bool sparkleRainbow = false;
double sparkleActiveColors = 1;
double sparkleSparkleDelay = 0;

// Running lights effect
List<Color> runningColors = [red, orange, yellow, green, blue, indigo, violet];
bool runnningRainbow = false;
double runningActiveColors = 1;
double runningSpeedDelay = 50;

// Color wipe effect
List<Color> wipeColors = [red, orange, yellow, green, blue, indigo, violet];
bool wipeRainbow = false;
double wipeActiveColors = 1;
double wipeSpeedDelay = 50;
bool wipeOpposite = false;

// Rainbow cycle effect
double cycleSpeedDelay = 20;

// Theater chase effect
List<Color> chaseColors = [red, orange, yellow, green, blue, indigo, violet];
bool chaseRainbow = false;
bool chaseRandom = false;
double chaseActiveColors = 1;
double chaseSpeedDelay = 50;
double chaseEndDelay = 0;

// Fire effect
double fireCooling = 10;
double fireSparking = 120;
double fireSpeedDelay = 15;

// Meteor effect
List<Color> meteorColors = [red, orange, yellow, green, blue, indigo, violet];
double meteorActiveColors = 1;
double meteorSize = 10;
double meteorDecay = 64;
bool meteorRandomDecay = true;
double meteorSpeedDelay = 30;
bool meteorOpposite = false;

// Twinkle fox effect
double foxSpeed = 5;
double foxDensity = 4;
double foxPerPallete = 30;

// OneColorRound effect
Color roundColor = Colors.blue;
double roundEffectTime = 30;

// Global settings
bool randomEffect = false;
double brightness = 255;
