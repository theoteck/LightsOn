# LightsOn ESP32 program

## Info
This program runs on the esp32 microcontroller and with the help of the FastLED library controls the connected LED strip. The microcontroller can be interfaced with Bluetooth LE.
This is done through the application on the user's phone.

## Build
The program is written for arduino boards ( in C/C++ ) in VSCode with the help of the PlatformIO extension.
So if you want to build it yourself for your board (assuming you are also using an esp32 based board) the only thing you have to do is load up the pio project and select your board. If you want to use pio with a board other than the esp32 you need to also change the target as well as modify the code in order to be compatible with your device.

Now, if you want to use the Arduino IDE for this project the only thing you need to do is to change the lights_on.cpp extension from .cpp to .ino (located in the /src directory)
and rename the src folder to lights_on. Then open the lights_on folder using the Arduino IDE and everything should be working perfectly. For more detailed instructions setting up the Arduino IDE and the VSCode pio environment stay tuned for more documentation updates.
