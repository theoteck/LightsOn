//Functions that are used by the OneColorRound effect
//It's a miniature draw_func.h for fewer effects

//::round_draw_solid::
//  Solid effect
void round_draw_solid(Color color)
{
  setAll(color.red, color.green, color.blue);
}

//::round_draw_fade::
//  Fade effect
void round_draw_fade(Color color)
{
  FadeInOut(color.red, color.green, color.blue);
}

//::round_draw_strobe::
//  Draw effect
void round_draw_strobe(Color color)
{
  Strobe(
      color.red, color.green, color.blue,
      settings[3][12],
      settings[3][13],
      settings[3][14]);
}

//::round_draw_eye::
//  Halloween eyes effect
void round_draw_eye(Color color)
{
  HalloweenEyes(
      color.red, color.green, color.blue,
      settings[4][12],
      settings[4][13],
      true,
      random(5, 20),
      random(50, 150),
      random(1000, 6000));
}

//::round_draw_twinkle::
//  Twinkle effect
void round_draw_twinkle(Color color)
{
  Twinkle(
      color.red, color.green, color.blue,
      settings[6][12],
      settings[6][11],
      false);
}

//::round_draw_sparkle::
//  Sparkle effect
void round_draw_sparkle(Color color)
{
  Sparkle(
      color.red, color.green, color.blue,
      settings[7][11]);
}

//::round_draw_running::
//  Running Lights effect
void round_draw_running(Color color)
{
  RunningLights(
      color.red, color.green, color.blue,
      settings[9][11]);
}

//::round_draw_wipe::
//  Wipe effect
void round_draw_wipe(Color color)
{
  colorWipe(
      color.red, color.green, color.blue,
      settings[10][11],
      settings[10][10]);
  colorWipe(
      0, 0, 0,
      settings[10][11],
      settings[10][10]);
}

//::round_draw_chase::
//  Theater chase effect
void round_draw_chase(Color color)
{
  theaterChase(
      color.red, color.green, color.blue,
      settings[12][11]);
}

//::round_draw_meteor::
//  Meteor effect
void round_draw_meteor(Color color)
{
  meteorRain(
      color.red, color.green, color.blue,
      settings[15][12],
      settings[15][13],
      true,
      settings[15][11],
      settings[15][10]);
}

//Function pointer array, that contains all OneColorRound draw functions, accessible quikly through its index
void (*round_ptr[10])(Color color) = {
    /*00*/ round_draw_solid,
    /*01*/ round_draw_fade,
    /*02*/ round_draw_strobe,
    /*03*/ round_draw_eye,
    /*05*/ round_draw_twinkle,
    /*06*/ round_draw_sparkle,
    /*08*/ round_draw_running,
    /*09*/ round_draw_wipe,
    /*10*/ round_draw_chase,
    /*11*/ round_draw_meteor};

//::drawRound::
//  OneColorRound effect; used as a pass by to the draw_func.h draw_round()
void drawRound(int index)
{
  Color color = intToRGB(settings[18][1]);

  (*round_ptr[index])(color);
}
