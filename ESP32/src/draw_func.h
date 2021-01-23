//Functions that are used to draw the effects
//They are higher level than the effect functions themselves and impliment the settings
//The use of static variables is important in order to keep the functions as non-blocking and quick as possible

//::draw_solid::
//  Solid effect
void draw_solid()
{
    //Rainbow Solid
    if (settings[1][9])
    {
        static uint8_t i = 0;

        byte *c = Wheel(i);

        setAll(*c, *(c + 1), *(c + 2));
        delay(settings[1][11]);

        if (i < 255)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    //Random Solid
    else if (settings[1][8])
    {
        setAll(random(0, 255), random(0, 255), random(0, 255));
        delay(settings[1][11]);
    }
    //Solid
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[1][i]);

        setAll(color.red, color.green, color.blue);
        delay(settings[1][11]);

        if (i < settings[1][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_fade::
//  Fade effect
void draw_fade()
{
    //Random fade
    if (settings[2][8])
    {
        FadeInOut(random(0, 255), random(0, 255), random(0, 255));
    }
    //Fade
    else
    {

        static uint8_t i = 1;

        Color color = intToRGB(settings[2][i]);

        bool done = FadeInOut(color.red, color.green, color.blue);

        if (done)
        {
            if (i < settings[2][0])
            {
                i++;
            }
            else
            {
                i = 1;
            }
        }
    }
}

//::draw_strobe::
//  Strobe effect
void draw_strobe()
{
    //Random strobe
    if (settings[3][8])
    {
        Strobe(
            random(0, 255), random(0, 255), random(0, 255),
            settings[3][12],
            settings[3][13],
            settings[3][14]);
    }
    //Strobe
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[3][i]);

        Strobe(
            color.red, color.green, color.blue,
            settings[3][12],
            settings[3][13],
            settings[3][14]);

        if (i < settings[3][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_eye::
//  Halloween eyes effect
void draw_eye()
{
    //Random Halloween eyes
    if (settings[4][8])
    {
        HalloweenEyes(
            random(0, 255), random(0, 255), random(0, 255),
            settings[4][12],
            settings[4][13],
            true,
            random(5, 20),
            random(50, 150),
            random(1000, 6000));
    }
    //Halloween eyes
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[4][i]);

        HalloweenEyes(
            color.red, color.green, color.blue,
            settings[4][12],
            settings[4][13],
            true,
            random(5, 20),
            random(50, 150),
            random(1000, 6000));

        if (i < settings[4][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_cylon::
//  Cylon effect
void draw_cylon()
{
    CylonBounce(settings[5][11]);
}

//::draw_twinkle::
//  Twinkle effect
void draw_twinkle()
{
    //Random twinkle
    if (settings[6][8])
    {
        TwinkleRandom(
            settings[6][12],
            200,
            false);
    }
    //Twinkle
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[6][i]);

        Twinkle(
            color.red, color.green, color.blue,
            settings[6][12],
            100,
            false);

        if (i < settings[6][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_sparkle::
//  Sparkle effect
void draw_sparkle()
{
    //Random sparkle
    if (settings[7][8])
    {
        Sparkle(
            random(0, 255), random(0, 255), random(0, 255),
            settings[7][11]);
    }
    //Sparkle
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[7][i]);

        Sparkle(
            color.red, color.green, color.blue,
            settings[7][11]);

        if (i < settings[7][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_noice::
//  NoisePlusPalette effect
void draw_noice() //Yes I know it's noise, yes it's a typo, no I'm keeping it
{
    //Copy-Paste from FastLED examples; see effects.h for more Copy-Paste

    ChangePaletteAndSettingsPeriodically();

    // generate noise data
    fillnoise8();

    // convert the noise data to colors in the LED array
    // using the current palette
    mapNoiseToLEDsUsingPalette();

    FastLED.show();
}

//::draw_running::
//  Running Lights effect
void draw_running()
{
    //Random running lights
    if (settings[9][8])
    {
        RunningLights(
            random(0, 255), random(0, 255), random(0, 255),
            settings[9][11]);
    }
    //Running lights
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[9][i]);

        RunningLights(
            color.red, color.green, color.blue,
            settings[9][11]);

        if (i < settings[9][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_wipe::
//  Color wipe effect; after a revision in now doesn't work as a wipe but as something else, I liked it and I kept it
void draw_wipe()
{
    //Random color wipe
    if (settings[10][8])
    {
        colorWipe(
            random(0, 255), random(0, 255), random(0, 255),
            settings[10][11],
            settings[10][10]);
    }
    //Color wipe with only one color selected
    else if (settings[10][0] == 1)
    {
        Color color = intToRGB(settings[10][1]);

        colorWipe(
            color.red, color.green, color.blue,
            settings[10][11],
            settings[10][10]);

        colorWipe(
            0, 0, 0,
            settings[10][11],
            settings[10][10]);
    }
    //Color wipe with multiple colors selected
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[10][i]);

        colorWipe(
            color.red, color.green, color.blue,
            settings[10][11],
            settings[10][10]);

        if (i < settings[10][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_rainbow::
//  Rainbow effect
void draw_rainbow()
{
    rainbowCycle(
        settings[11][11]);
}

//::draw_chase::
//  Theater Chase effect
void draw_chase()
{
    //Random theater chase
    if (settings[12][8])
    {
        theaterChase(
            random(0, 255), random(0, 255), random(0, 255),
            settings[12][11]);
        delay(settings[12][12]);
    }
    //Rainbow theater chase
    else if (settings[12][9])
    {
        theaterChaseRainbow(
            settings[12][11]);
        delay(settings[12][12]);
    }
    //Theater chase
    else
    {
        static uint8_t i = 1;

        Color color = intToRGB(settings[12][i]);

        theaterChase(color.red, color.green, color.blue, settings[12][11]);
        delay(settings[12][12]);

        if (i < settings[12][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_fire::
//  Fire effect
void draw_fire()
{
    Fire(
        settings[13][12],
        settings[13][13],
        settings[13][11],
        settings[13][10]);
}

//::draw_pride::
//  Pride effect
void draw_pride()
{
    pride();
    FastLED.show();
}

//::draw_meteor::
//  Meteor effect
void draw_meteor()
{
    static uint8_t i = 1;

    Color color = intToRGB(settings[15][i]);

    bool done = meteorRain(
        color.red, color.green, color.blue,
        settings[15][12],
        settings[15][13],
        true,
        settings[15][11],
        settings[15][10]);

    if (done)
    {
        if (i < settings[15][0])
        {
            i++;
        }
        else
        {
            i = 1;
        }
    }
}

//::draw_pacifica
//  Pacifica effect
void draw_pacifica()
{
    pacifica_loop();
    FastLED.show();
}

//::draw_fox::
//  Twinkle Fox effect
void draw_fox()
{
    drawTwinkles();
}

//::draw_round::
//  OneColorRound effect
void draw_round()
{
    drawRound(drawID);
}

//Function pointer array that contains all draw functions, accessible quikly through its index
void (*func_ptr[18])() =
    {
        /*00   */ draw_solid,
        /*01   */ draw_fade,
        /*02   */ draw_strobe,
        /*03   */ draw_eye,
        /*04   */ draw_cylon,
        /*05   */ draw_twinkle,
        /*06   */ draw_sparkle,
        /*07   */ draw_noice,
        /*08   */ draw_running,
        /*09   */ draw_wipe,
        /*10|A */ draw_rainbow,
        /*11|B */ draw_chase,
        /*12|C */ draw_fire,
        /*13|D */ draw_pride,
        /*14|E */ draw_meteor,
        /*15|F */ draw_pacifica,
        /*16|10*/ draw_fox,
        /*17|11*/ draw_round,
};
