//This is the messiest file of the program; it contains all raw effect functions and some useful functions and structs
//Most of the code in this file is copied from the internet from different sources and modified if need be

//!!Comments that start with ~ are from the authors of the functions!!

//::Color::
//  Struct that contains a color in its RGB bytes; useful as one function parameter instead of three
struct Color
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

//{from:}[Modified]
//::setPixel::(pixel index, Red color byte, Green color byte, Blue color byte)
//  Function that takes in a pixel index and applies to it the passed color
void setPixel(int Pixel, uint8_t red, uint8_t green, uint8_t blue)
{
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

//{from:}[Modified]
//::setAll::(Red color byte, Green color byte, Blue color byte)
//  Function that takes in a color in its three parts and applies it to the whole LED strip
void setAll(uint8_t red, uint8_t green, uint8_t blue)
{
  //Cycle through all the pixels
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}

//::intToRGB::(color in number/hex format) -> Color struct
//  Function that takes in a color number and outputs that color in a Color struct
Color intToRGB(int rgb)
{
  Color color; //Initialize variable

  //Byte-shift the (int)rgb number to get the R,G and B parts
  //Hex color in bytes 0xRRGGBB, where R is the red part, G is the green part and B the blue part
  color.red = (rgb >> 16) & 0xFF;
  color.green = (rgb >> 8) & 0xFF;
  color.blue = rgb & 0xFF;

  return color;
}

//{from:}
//::fade_all::
//  Used by CylonBounce()
void fadeall()
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i].nscale8(250);
  }
}

//{from:}[Modified]
//::*Wheel::(byte position)
//  Used by rainbowCycle() and theaterChaseRainbow()
uint8_t *Wheel(uint8_t WheelPos)
{
  static uint8_t c[3];

  if (WheelPos < 85)
  {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  }
  else
  {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

//{from:}
//::setPixelHeatColor::(pixel index, byte temperature)
//  Used by Fire()
void setPixelHeatColor(int Pixel, uint8_t temperature)
{
  //~Scale 'heat' down from 0-255 to 0-191            <- Comment from the function author
  uint8_t t192 = round((temperature / 255.0) * 191);

  //~calculate ramp up from
  uint8_t heatramp = t192 & 0x3F; //~0..63
  heatramp <<= 2;                 //~scale up to 0..252

  //~figure out which third of the spectrum we're in:
  if (t192 > 0x80)
  { //~hottest
    setPixel(Pixel, 255, 255, heatramp);
  }
  else if (t192 > 0x40)
  { //~middle
    setPixel(Pixel, 255, heatramp, 0);
  }
  else
  { //~coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

//{from:}
//::pacifica_one_layer::(pacifica palette, other stuff :) )
//  Used by pacifica_loop()
//~Add one layer of waves into the led array
void pacifica_one_layer(CRGBPalette16 &p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    waveangle += 250;
    uint16_t s16 = sin16(waveangle) + 32768;
    uint16_t cs = scale16(s16, wavescale_half) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16(ci) + 32768;
    uint8_t sindex8 = scale16(sindex16, 240);
    CRGB c = ColorFromPalette(p, sindex8, bri, LINEARBLEND);
    leds[i] += c;
  }
}

//{from:}
//::pacifica_add_whitecaps::
//  Used by pacifica_loop()
//~Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps()
{
  uint8_t basethreshold = beatsin8(9, 55, 65);
  uint8_t wave = beat8(7);

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    uint8_t threshold = scale8(sin8(wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = leds[i].getAverageLight();
    if (l > threshold)
    {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8(overage, overage);
      leds[i] += CRGB(overage, overage2, qadd8(overage2, overage2));
    }
  }
}

//{from:}
//::pacifica_deepen_colors::
//  Used by pacifica_loop()
//~Deepen the blues and greens
void pacifica_deepen_colors()
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i].blue = scale8(leds[i].blue, 145);
    leds[i].green = scale8(leds[i].green, 200);
    leds[i] |= CRGB(2, 5, 7);
  }
}

//{from:}
//::attackDecayWave8::(number)
//  Used by computeOneTwinkle()
uint8_t attackDecayWave8(uint8_t i)
{
  if (i < 86)
  {
    return i * 3;
  }
  else
  {
    i -= 86;
    return 255 - (i + (i / 2));
  }
}

//{from:}
//::coolLikeIncandescent::(CRGB color, byte phase)
//  Used by computeOneTwinkle()
void coolLikeIncandescent(CRGB &c, uint8_t phase)
{
  if (phase < 128)
    return;

  uint8_t cooling = (phase - 128) >> 4;
  c.g = qsub8(c.g, cooling);
  c.b = qsub8(c.b, cooling * 2);
}

//--Palettes used by the Twinkle Fox effect--//
const TProgmemRGBPalette16 RedGreenWhite_p FL_PROGMEM =
    {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
     CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
     CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray,
     CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green};

#define Holly_Green 0x00580c
#define Holly_Red 0xB00402
const TProgmemRGBPalette16 Holly_p FL_PROGMEM =
    {Holly_Green, Holly_Green, Holly_Green, Holly_Green,
     Holly_Green, Holly_Green, Holly_Green, Holly_Green,
     Holly_Green, Holly_Green, Holly_Green, Holly_Green,
     Holly_Green, Holly_Green, Holly_Green, Holly_Red};

const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
    {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
     CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
     CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
     CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray};

const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
    {CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
     CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
     CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
     CRGB::Blue, CRGB::Gray, CRGB::Gray, CRGB::Gray};

#define HALFFAIRY ((CRGB::FairyLight & 0xFEFEFE) / 2)
#define QUARTERFAIRY ((CRGB::FairyLight & 0xFCFCFC) / 4)
const TProgmemRGBPalette16 FairyLight_p FL_PROGMEM =
    {CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight,
     HALFFAIRY, HALFFAIRY, CRGB::FairyLight, CRGB::FairyLight,
     QUARTERFAIRY, QUARTERFAIRY, CRGB::FairyLight, CRGB::FairyLight,
     CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight};

const TProgmemRGBPalette16 Snow_p FL_PROGMEM =
    {0x304048, 0x304048, 0x304048, 0x304048,
     0x304048, 0x304048, 0x304048, 0x304048,
     0x304048, 0x304048, 0x304048, 0x304048,
     0x304048, 0x304048, 0x304048, 0xE0F0FF};

#define C9_Red 0xB80400
#define C9_Orange 0x902C02
#define C9_Green 0x046002
#define C9_Blue 0x070758
#define C9_White 0x606820
const TProgmemRGBPalette16 RetroC9_p FL_PROGMEM =
    {C9_Red, C9_Orange, C9_Red, C9_Orange,
     C9_Orange, C9_Red, C9_Orange, C9_Red,
     C9_Green, C9_Green, C9_Green, C9_Green,
     C9_Blue, C9_Blue, C9_Blue,
     C9_White};

#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
const TProgmemRGBPalette16 Ice_p FL_PROGMEM =
    {
        Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
        Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
        Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
        Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3};

const TProgmemRGBPalette16 *ActivePaletteList[] = {
    &RetroC9_p,
    &BlueWhite_p,
    &RainbowColors_p,
    &FairyLight_p,
    &RedGreenWhite_p,
    &PartyColors_p,
    &RedWhite_p,
    &Snow_p,
    &Holly_p,
    &Ice_p};
//-------------------------------------------//

//{from:}
//::chooseNextColorPalette::(palette)
//  Used by loop()
void chooseNextColorPalette(CRGBPalette16 &pal)
{
  const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
  static uint8_t whichPalette = -1;
  whichPalette = addmod8(whichPalette, 1, numberOfPalettes);

  pal = *(ActivePaletteList[whichPalette]);
}

//{from:}
//::computeOneTwinkle::(time in ms, salt?)
//  Used by drawTwinkles()
CRGB computeOneTwinkle(uint32_t ms, uint8_t salt)
{
  uint16_t ticks = ms >> (8 - settings[17][11]);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8(slowcycle16);
  slowcycle16 = (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

  uint8_t bright = 0;
  if (((slowcycle8 & 0x0E) / 2) < settings[17][12])
  {
    bright = attackDecayWave8(fastcycle8);
  }

  uint8_t hue = slowcycle8 - salt;
  CRGB c;
  if (bright > 0)
  {
    c = ColorFromPalette(gCurrentPalette, hue, bright, NOBLEND);
    if (COOL_LIKE_INCANDESCENT == 1)
    {
      coolLikeIncandescent(c, fastcycle8);
    }
  }
  else
  {
    c = CRGB::Black;
  }
  return c;
}

//--Variables used by the NoisePlusPalette effect--//
uint16_t speed = 20;

uint16_t scale = 30;

uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

CRGBPalette16 currentPalette(PartyColors_p);
uint8_t colorLoop = 1;
//-------------------------------------------------//

//{from:}
//::SetupRandomPalette::
//  Used by ChangePaletteAndSettingsPeriodically()
void SetupRandomPalette()
{
  currentPalette = CRGBPalette16(
      CHSV(random8(), 255, 32),
      CHSV(random8(), 255, 255),
      CHSV(random8(), 128, 255),
      CHSV(random8(), 255, 255));
}

//{from:}
//::SetupBlackAndWhiteStripedPalette::
//  Used by ChangePaletteAndSettingsPeriodically()
//~This function sets up a palette of black and white stripes,
//~using code.  Since the palette is effectively an array of
//~sixteen CRGB colors, the various fill_* functions can be used
//~to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid(currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
}

//{from:}
//::SetupPurpleAndGreenPalette::
//  Used by ChangePaletteAndSettingsPeriodically()
//~This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV(HUE_PURPLE, 255, 255);
  CRGB green = CHSV(HUE_GREEN, 255, 255);
  CRGB black = CRGB::Black;

  currentPalette = CRGBPalette16(
      green, green, black, black,
      purple, purple, black, black,
      green, green, black, black,
      purple, purple, black, black);
}

//NoisePlusPalette constant
#define HOLD_PALETTES_X_TIMES_AS_LONG 2

//{from:}
//::ChangePaletteAndSettingsPeriodically::
//  Used by draw_noice()
void ChangePaletteAndSettingsPeriodically()
{
  uint8_t secondHand = ((millis() / 1000) / HOLD_PALETTES_X_TIMES_AS_LONG) % 60;
  static uint8_t lastSecond = 99;

  if (lastSecond != secondHand)
  {
    lastSecond = secondHand;
    if (secondHand == 0)
    {
      currentPalette = RainbowColors_p;
      speed = 20;
      scale = 30;
      colorLoop = 1;
    }
    if (secondHand == 5)
    {
      SetupPurpleAndGreenPalette();
      speed = 10;
      scale = 50;
      colorLoop = 1;
    }
    if (secondHand == 10)
    {
      SetupBlackAndWhiteStripedPalette();
      speed = 20;
      scale = 30;
      colorLoop = 1;
    }
    if (secondHand == 15)
    {
      currentPalette = ForestColors_p;
      speed = 8;
      scale = 120;
      colorLoop = 0;
    }
    if (secondHand == 20)
    {
      currentPalette = CloudColors_p;
      speed = 4;
      scale = 30;
      colorLoop = 0;
    }
    if (secondHand == 25)
    {
      currentPalette = LavaColors_p;
      speed = 8;
      scale = 50;
      colorLoop = 0;
    }
    if (secondHand == 30)
    {
      currentPalette = OceanColors_p;
      speed = 20;
      scale = 90;
      colorLoop = 0;
    }
    if (secondHand == 35)
    {
      currentPalette = PartyColors_p;
      speed = 20;
      scale = 30;
      colorLoop = 1;
    }
    if (secondHand == 40)
    {
      SetupRandomPalette();
      speed = 20;
      scale = 20;
      colorLoop = 1;
    }
    if (secondHand == 45)
    {
      SetupRandomPalette();
      speed = 50;
      scale = 50;
      colorLoop = 1;
    }
    if (secondHand == 50)
    {
      SetupRandomPalette();
      speed = 90;
      scale = 90;
      colorLoop = 1;
    }
    if (secondHand == 55)
    {
      currentPalette = RainbowStripeColors_p;
      speed = 30;
      scale = 20;
      colorLoop = 1;
    }
  }
}

//{from:}
//::XY::
//  Used by mapNoiseToLEDsUsingPalette()
uint16_t XY(uint8_t x, uint8_t y)
{
  uint16_t i;
  if (kMatrixSerpentineLayout == false)
  {
    i = (y * kMatrixWidth) + x;
  }
  if (kMatrixSerpentineLayout == true)
  {
    if (y & 0x01)
    {
      //~Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    }
    else
    {
      //~Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  return i;
}

//{from:}
//::FadeInOut::
//  Used by draw_fade()
bool FadeInOut(uint8_t red, uint8_t green, uint8_t blue)
{
  float r, g, b;

  static uint8_t k = 0;
  static int16_t j = 255;
  static bool fade = false;

  if (fade)
  {
    r = (j / 256.0) * red;
    g = (j / 256.0) * green;
    b = (j / 256.0) * blue;
    setAll(r, g, b);
    delay(100);

    if (j > 0)
    {
      j -= 2;
    }
    else
    {
      j = 255;
      fade = false;
      return true;
    }
  }
  else
  {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    delay(100);

    if (k < 255)
    {
      k++;
    }
    else
    {
      k = 0;
      fade = true;
    }
  }

  return false;
}

//{from:}
//::Strobe::
//  Used by draw_strobe()
void Strobe(uint8_t red, uint8_t green, uint8_t blue, int StrobeCount, int FlashDelay, int EndPause)
{
  static uint16_t j = 0;

  setAll(red, green, blue);
  delay(FlashDelay);
  setAll(0, 0, 0);
  delay(FlashDelay);

  if (j < StrobeCount - 1)
  {
    j++;
  }
  else
  {
    j = 0;
    delay(EndPause);
  }
}

//{from:}
//::HalloweenEyes::
//  Used by draw_eye()
void HalloweenEyes(uint8_t red, uint8_t green, uint8_t blue, int EyeWidth, int EyeSpace, bool Fade, int Steps, int FadeDelay, int EndPause)
{
  randomSeed(analogRead(0));

  uint8_t i;
  uint16_t StartPoint = random(0, NUM_LEDS - (2 * EyeWidth) - EyeSpace);
  uint8_t Start2ndEye = StartPoint + EyeWidth + EyeSpace;

  for (i = 0; i < EyeWidth; i++)
  {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }

  FastLED.show();

  if (Fade == true)
  {
    float r, g, b;

    for (int16_t j = Steps; j >= 0; j--)
    {
      r = j * (red / Steps);
      g = j * (green / Steps);
      b = j * (blue / Steps);

      for (i = 0; i < EyeWidth; i++)
      {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }

      FastLED.show();
      delay(FadeDelay);
    }
  }

  setAll(0, 0, 0); //~Set all black

  delay(EndPause);
}

//{from:}
//::CylonBounce::
//  Used by draw_cylom()
void CylonBounce(int SpeedDelay)
{

  static uint8_t hue = 0;
  //~First slide the led in one direction
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    //~Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    //~Show the leds
    FastLED.show();
    //~now that we've shown the leds, reset the i'th led to black
    //~leds[i] = CRGB::Black;
    fadeall();
    //~Wait a little bit before we loop around and do it again
    delay(SpeedDelay);
  }

  //~Now go in the other direction.
  for (int i = (NUM_LEDS)-1; i >= 0; i--)
  {
    //~Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    //~Show the leds
    FastLED.show();
    //~now that we've shown the leds, reset the i'th led to black
    //~leds[i] = CRGB::Black;
    fadeall();
    //~Wait a little bit before we loop around and do it again
    delay(SpeedDelay);
  }
}

//{from:}
//::Twinkle::
//  Used by draw_twinkle()
void Twinkle(uint8_t red, uint8_t green, uint8_t blue, int Count, int SpeedDelay, bool OnlyOne)
{
  static int i = -1;

  if (i < Count - 1)
  {
    i++;
  }
  else
  {
    i = 0;
    setAll(0, 0, 0);
    delay(SpeedDelay);
  }
  setPixel(random(NUM_LEDS), red, green, blue);
  FastLED.show();
  delay(SpeedDelay);
  if (OnlyOne)
  {
    setAll(0, 0, 0);
  }
}

//{from:}
//::TwinkleRandom::
//  Used by draw_twinkle()
void TwinkleRandom(int Count, int SpeedDelay, bool OnlyOne)
{
  static int i = -1;

  if (i < Count - 1)
  {
    i++;
  }
  else
  {
    i = 0;
    setAll(0, 0, 0);
    delay(SpeedDelay);
  }

  setPixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
  FastLED.show();
  delay(SpeedDelay);
  if (OnlyOne)
  {
    setAll(0, 0, 0);
  }
}

//{from:}
//::Sparkle::
//  Used by draw_sparkle()
void Sparkle(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay)
{
  uint16_t Pixel = random(NUM_LEDS);
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  delay(SpeedDelay);
  setPixel(Pixel, 0, 0, 0);
}

//{from:}
//::fillnoise8::
//  Used by draw_noice()
void fillnoise8()
{
  //~If we're runing at a low "speed", some 8-bit artifacts become visible
  //~from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  //~The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 0;
  if (speed < 50)
  {
    dataSmoothing = 200 - (speed * 4);
  }

  for (uint16_t i = 0; i < MAX_DIMENSION; i++)
  {
    uint16_t ioffset = scale * i;
    for (uint16_t j = 0; j < MAX_DIMENSION; j++)
    {
      uint16_t joffset = scale * j;

      uint8_t data = inoise8(x + ioffset, y + joffset, z);

      //~The range of the inoise8 function is roughly 16-238.
      //~These two operations expand those values out to roughly 0..255
      //~You can comment them out if you want the raw noise data.
      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if (dataSmoothing)
      {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8(olddata, dataSmoothing) + scale8(data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }

  z += speed;

  //~apply slow drift to X and Y, just for visual variation.
  x += speed / 8;
  y -= speed / 16;
}

//{from:}
//::mapNoiseToLEDsUsingPalette::
//  Used by draw_noice()
void mapNoiseToLEDsUsingPalette()
{
  static uint8_t ihue = 0;

  for (uint8_t i = 0; i < kMatrixWidth; i++)
  {
    for (uint8_t j = 0; j < kMatrixHeight; j++)
    {
      //~We use the value at the (i,j) coordinate in the noise
      //~array for our brightness, and the flipped value from (j,i)
      //~for our pixel's index into the color palette.

      uint8_t index = noise[j][i];
      uint8_t bri = noise[i][j];

      //~if this palette is a 'loop', add a slowly-changing base value
      if (colorLoop)
      {
        index += ihue;
      }

      //~brighten up, as the color palette itself often contains the
      //~light/dark dynamic range desired
      if (bri > 127)
      {
        bri = 255;
      }
      else
      {
        bri = dim8_raw(bri * 2);
      }

      CRGB color = ColorFromPalette(currentPalette, index, bri);
      leds[XY(i, j)] = color;
    }
  }

  ihue += 1;
}

//{from:}
//::RunningLights::
//  Used by draw_runniing()
void RunningLights(uint8_t red, uint8_t green, uint8_t blue, int WaveDelay)
{
  static uint16_t Position = 1;
  static uint16_t j = 0;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    //~sine wave, 3 offset waves make a rainbow!
    //~float level = sin(i+Position) * 127 + 128;
    //~setPixel(i,level,0,0);
    //~float level = sin(i+Position) * 127 + 128;
    setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
             ((sin(i + Position) * 127 + 128) / 255) * green,
             ((sin(i + Position) * 127 + 128) / 255) * blue);
  }

  FastLED.show();

  if (j < NUM_LEDS * 2 - 1)
  {
    j++;
    Position++;
    delay(WaveDelay);
  }
  else
  {
    j = 0;
    Position = 1;
  }
}

//{from:}
//::colorWipe::
//  Used by draw_wipe()
void colorWipe(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay, bool isOpposite)
{
  static uint16_t k = 0;
  uint16_t i = isOpposite ? k : (NUM_LEDS - 1) - k;
  setPixel(i, red, green, blue);
  FastLED.show();
  delay(SpeedDelay);

  if (k < NUM_LEDS - 1)
  {
    k++;
  }
  else
  {
    k = 0;
  }
}

//{from:}
//::raindbowCycle::
//  Used by draw_rainbow()
void rainbowCycle(int SpeedDelay)
{
  uint8_t *c;
  uint16_t i;
  static uint16_t j = 0;

  for (i = 0; i < NUM_LEDS; i++)
  {
    c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
    setPixel(i, *c, *(c + 1), *(c + 2));
  }

  FastLED.show();

  if (j < 1280 - 1)
  {
    j++;
  }
  else
  {
    j = 0;
  }

  delay(SpeedDelay);
}

//{from:}
//::theaterChase::
//  Used by draw_chase()
void theaterChase(uint8_t red, uint8_t green, uint8_t blue, int SpeedDelay)
{
  static uint8_t j = 0;

  for (uint8_t q = 0; q < 3; q++)
  {
    for (uint16_t i = 0; i < NUM_LEDS; i = i + 3)
    {
      setPixel(i + q, red, green, blue); //~turn every third pixel on
    }

    FastLED.show();

    delay(SpeedDelay);

    for (uint16_t i = 0; i < NUM_LEDS; i = i + 3)
    {
      setPixel(i + q, 0, 0, 0); //~turn every third pixel off
    }
  }

  if (j < 9)
  {
    j++;
  }
  else
  {
    j = 0;
  }
}

//{from:}
//::theaterChaseRainbow::
//  Used by draw_chase()
void theaterChaseRainbow(int SpeedDelay)
{
  uint8_t *c;
  static uint8_t j = 0;

  for (uint8_t q = 0; q < 3; q++)
  {
    for (uint16_t i = 0; i < NUM_LEDS; i = i + 3)
    {
      c = Wheel((i + j) % 255);
      setPixel(i + q, *c, *(c + 1), *(c + 2)); //~turn every third pixel on
    }

    FastLED.show();

    delay(SpeedDelay);

    for (uint16_t i = 0; i < NUM_LEDS; i = i + 3)
    {
      setPixel(i + q, 0, 0, 0); //~turn every third pixel off
    }
  }

  if (j < 255)
  {
    j++;
  }
  else
  {
    j = 0;
  }
}

//{from:}
//::Fire::
//  Used by draw_fire()
void Fire(int Cooling, int Sparking, int SpeedDelay, bool isOpposite)
{
  static uint8_t heat[NUM_LEDS];
  uint16_t cooldown;

  //~Step 1.  Cool down every cell a little
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i])
    {
      heat[i] = 0;
    }
    else
    {
      heat[i] = heat[i] - cooldown;
    }
  }

  //~Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (uint16_t k = NUM_LEDS - 1; k >= 2; k--)
  {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  //~Step 3.  Randomly ignite new 'sparks' near the bottom
  if (random(255) < Sparking)
  {
    uint8_t y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //~heat[y] = random(160,255);
  }

  //~Step 4.  Convert heat to LED colors
  for (uint16_t j = 0; j < NUM_LEDS; j++)
  {
    const uint16_t k = isOpposite ? j : (NUM_LEDS - 1) - j;
    setPixelHeatColor(k, heat[k]);
  }

  FastLED.show();

  delay(SpeedDelay);
}

//{from:}
//::pride::
//  Used by draw_pride()
void pride()
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88(87, 220, 250);
  uint8_t brightdepth = beatsin88(341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16; //~gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis;
  sLastMillis = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88(400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16 += brightnessthetainc16;
    uint16_t b16 = sin16(brightnesstheta16) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV(hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS - 1) - pixelnumber;

    nblend(leds[pixelnumber], newcolor, 64);
  }
}

//{from:}
//::meteorRain::
//  Used by draw_meteor()
bool meteorRain(uint8_t red, uint8_t green, uint8_t blue, uint8_t meteorSize, uint8_t meteorTrailDecay, bool meteorRandomDecay, int SpeedDelay, bool isOpposite)
{

  static uint16_t i = 0;

  if (i < 2 * NUM_LEDS - 1)
  {
    i++;
  }
  else
  {
    i = 0;
    setAll(0, 0, 0);
    return true;
  }

  //~fade brightness all LEDs one step
  for (int j = 0; j < NUM_LEDS; j++)
  {
    if ((!meteorRandomDecay) || (random(10) > 5))
    {
      leds[j].fadeToBlackBy(meteorTrailDecay);
    }
  }

  //~draw meteor
  for (uint8_t j = 0; j < meteorSize; j++)
  {
    if ((i - j < NUM_LEDS) && (i - j >= 0))
    {
      setPixel(i - j, red, green, blue);
    }
  }

  FastLED.show();

  delay(SpeedDelay);

  return false;
}

//--Pacifica effect palettes--//
CRGBPalette16 pacifica_palette_1 =
    {0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
     0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50};
CRGBPalette16 pacifica_palette_2 =
    {0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
     0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F};
CRGBPalette16 pacifica_palette_3 =
    {0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33,
     0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF};
//----------------------------//

//{from:}
//::pacifica_loop::
//  Used by draw_pacifica()
void pacifica_loop()
{
  //~Increment the four "color index start" counters, one for each wave layer.
  //~Each is incremented at a different speed, and the speeds vary over time.
  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011, 10, 13));
  sCIStart2 -= (deltams21 * beatsin88(777, 8, 11));
  sCIStart3 -= (deltams1 * beatsin88(501, 5, 7));
  sCIStart4 -= (deltams2 * beatsin88(257, 4, 6));

  //~Clear out the LED array to a dim background blue-green
  fill_solid(leds, NUM_LEDS, CRGB(2, 6, 10));

  //~Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer(pacifica_palette_1, sCIStart1, beatsin16(3, 11 * 256, 14 * 256), beatsin8(10, 70, 130), 0 - beat16(301));
  pacifica_one_layer(pacifica_palette_2, sCIStart2, beatsin16(4, 6 * 256, 9 * 256), beatsin8(17, 40, 80), beat16(401));
  pacifica_one_layer(pacifica_palette_3, sCIStart3, 6 * 256, beatsin8(9, 10, 38), 0 - beat16(503));
  pacifica_one_layer(pacifica_palette_3, sCIStart4, 5 * 256, beatsin8(8, 10, 28), beat16(601));

  //~Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps();

  //~Deepen the blues and greens a bit
  pacifica_deepen_colors();
}

//{from:}
//::drawTwinkles::
//  Used by draw_twinkles()
void drawTwinkles()
{
  //~"PRNG16" is the pseudorandom number generator
  //~It MUST be reset to the same starting value each time
  //~this function is called, so that the sequence of 'random'
  //~numbers that it generates is (paradoxically) stable.
  uint16_t PRNG16 = 11337;

  uint32_t clock32 = millis();

  //~Set up the background color, "bg".
  //~if AUTO_SELECT_BACKGROUND_COLOR == 1, and the first two colors of
  //~the current palette are identical, then a deeply faded version of
  //~that color is used for the background color
  CRGB bg;
  if ((AUTO_SELECT_BACKGROUND_COLOR == 1) &&
      (gCurrentPalette[0] == gCurrentPalette[1]))
  {
    bg = gCurrentPalette[0];
    uint8_t bglight = bg.getAverageLight();
    if (bglight > 64)
    {
      bg.nscale8_video(16); //~very bright, so scale to 1/16th
    }
    else if (bglight > 16)
    {
      bg.nscale8_video(64); //~not that bright, so scale to 1/4th
    }
    else
    {
      bg.nscale8_video(86); //~dim, scale to 1/3rd.
    }
  }
  else
  {
    bg = gBackgroundColor; //~just use the explicitly defined background color
  }

  uint8_t backgroundBrightness = bg.getAverageLight();

  for (int i = 0; i < NUM_LEDS; i++)
  {
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; //~next 'random' number
    uint16_t myclockoffset16 = PRNG16;         //~use that number as clock offset
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; //~next 'random' number
    //~use that number as clock speed adjustment factor (in 8ths, from 8/8ths to 23/8ths)
    uint8_t myspeedmultiplierQ5_3 = ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t myunique8 = PRNG16 >> 8; //~get 'salt' value for this pixel

    //~We now have the adjusted 'clock' for this pixel, now we call
    //~the function that computes what color the pixel should be based
    //~on the "brightness = f( time )" idea.
    CRGB c = computeOneTwinkle(myclock30, myunique8);

    uint8_t cbright = c.getAverageLight();
    int16_t deltabright = cbright - backgroundBrightness;
    if (deltabright >= 32 || (!bg))
    {
      //~If the new pixel is significantly brighter than the background color,
      //~use the new color.
      leds[i] = c;
    }
    else if (deltabright > 0)
    {
      //~If the new pixel is just slightly brighter than the background color,
      //~mix a blend of the new color and the background color
      leds[i] = blend(bg, c, deltabright * 8);
    }
    else
    {
      //~if the new pixel is not at all brighter than the background color,
      //~just use the background color.
      leds[i] = bg;
    }

    //~FastLED.show();
  }
  FastLED.show();
}
