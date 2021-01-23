//Initial colors that are used to fill the parameters
int red = 0xff0000;
int orange = 0xff9800;
int yellow = 0xffeb3b;
int green = 0x00ff00;
int blue = 0x0000ff;
int indigo = 0x3f51b5;
int violet = 0x7F00FF;

//NONE is used instead of just 0 on the empty parameters to indicate that they are not used
#define NONE 0

/*
 * The settings follow the LightsOn BLE data exchange format only with 2 out of 3 values
 * More info about the LightsOn BLE data exchange format on the settings.dart documentation
 *
 * settings[X][Y]
 *
 *                   -> available range 0..255 (current 0..19)
 * X: the effect id (length: number of effects + 1 for the global settings)
 *
 * Y: the setting id -> range 0..255
 * `0:  Active Colors
 * `1:  Color1
 * `2:  Color2
 * `3:  Color3
 * `4:  Color4
 * `5:  Color5
 * `6:  Color6
 * `7:  Color7
 * `8:  Random
 * `9:  Rainbow
 * `10: Opposite (hardly used after a revision but kept it just because)
 * `11: SpeedDelay
 * `12..255: Effect Specific
 * 
**/

int settings[19][16] =
    /*Y:        0   1     2     3     4     5     6     7     8      9     10    11    12    13    14     15   */
    {
        /*      A   C1    C2    C3    C4    C5    C6    C7    Rand   Rainb Opst  Speed S1   S2    S3    S4   */
        /*00*/ {10, NONE, NONE, NONE, NONE, NONE, NONE, NONE, false, NONE, NONE, NONE, 100, NONE, NONE, NONE},
        /*01*/ {1, red, orange, yellow, green, blue, indigo, violet, false, false, NONE, 50, NONE, NONE, NONE, NONE},
        /*02*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        /*03*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, NONE, NONE, 10, 70, 600, NONE},
        /*04*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, NONE, NONE, 1, 4, NONE, NONE},
        /*05*/ {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 10, NONE, NONE, NONE, NONE},
        /*06*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, NONE, NONE, 10, NONE, NONE, NONE},
        /*07*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, NONE, 0, NONE, NONE, NONE, NONE},
        /*08*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, NONE, 20, NONE, NONE, NONE, NONE},
        /*09*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, false, 50, NONE, NONE, NONE, NONE},
        /*10*/ {1, red, orange, yellow, green, blue, indigo, violet, false, NONE, false, 10, NONE, NONE, NONE, NONE},
        /*11*/ {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, false, 20, NONE, NONE, NONE, NONE},
        /*12*/ {1, red, orange, yellow, green, blue, indigo, violet, false, false, false, 50, 0, NONE, NONE, NONE},
        /*13*/ {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, false, 15, 10, 120, NONE, NONE},
        /*14*/ {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        /*15*/ {1, red, orange, yellow, green, blue, indigo, violet, NONE, NONE, false, 30, 10, 64, true, NONE},
        /*16*/ {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        /*17*/ {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, false, 5, 4, 30, NONE, NONE},
        /*18*/ {NONE, blue, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 30, NONE, NONE, NONE},
};
