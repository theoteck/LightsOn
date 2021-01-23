//Import required files
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>
#include <sstream>
FASTLED_USING_NAMESPACE

//--The following definitions need to be changed according to your configuration--//

#define NUM_LEDS 30 //The amount of LEDs that the strip has (or the amount you want be lit?)

//The pin that is connected to the LED strip data line
//(chose 17 because it didn't have any other functions or uses (touch sensor etc))
#define DATA_PIN 17

#define LED_TYPE WS2812B //The model type of the LED strip that you have (not the manifacturer model)

//The order in which the LEDs receive their color data
//(for WS2812B its generally GRB)(other configurations might be RGB, GBR, BGR, BRG)
#define COLOR_ORDER GRB

//The following two lines are used for the NoisePlusPallete effect. Their multiplication need to result the NUM_LEDS definition
//You can choose whatever integer combination you want, and see which one you like more
const uint8_t kMatrixWidth = 6;
const uint8_t kMatrixHeight = 5;

//The following strings contain the UUIDs that are used by the BLE stack and need to be the same with the ones configured in the LightsOn app
//It is better for them to be changed; but the world wont end if you don't change them
//They need to be different from each other. A useful site from where you can get some are here
#define RECEIVE_SERVICE_UUID "ffa97fbe-93e9-489f-a768-cae63c65c7dd"
#define DATA_CHARACTERISTIC_UUID "6f63f4e0-251e-4374-970e-7fea2104788a"

//This is the bluetooth name of the device that is going to visible by other devices
#define DEVICE_NAME "LightsOn ctf"
//--------------------------------------------------------------------------------//

//--Variables used by the effects--//
const bool kMatrixSerpentineLayout = true;

#define MAX_DIMENSION ((kMatrixWidth > kMatrixHeight) ? kMatrixWidth : kMatrixHeight)

static uint16_t x;
static uint16_t y;
static uint16_t z;

CRGB gBackgroundColor = CRGB::Black;

#define AUTO_SELECT_BACKGROUND_COLOR 0

#define COOL_LIKE_INCANDESCENT 1

CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;
//---------------------------------//

CRGB leds[NUM_LEDS]; //Definition of the leds array

uint8_t drawID = 0; //The current effect that is used by the round color effect

//--Include local files that are used by the program--//
#include "parameters.h"  //Contains the parameters that the entire program use and are accessible with BLE
#include "effects.h"     //Contains the effect functions
#include "round_color.h" //Contains the functions for the One Color Round effects
#include "draw_func.h"   //Contains the functions that are used to draw the effects
//----------------------------------------------------//

//--BLE variable definitions--//
BLEServer *pServer = NULL;
BLEService *pReceiveService = NULL;
BLECharacteristic *pDataCharacteristic = NULL;
BLEAdvertising *pAdvertising = NULL;
//----------------------------//

uint8_t randomIndex = 0; //Variable that is used to draw a random effect

//An array is used instead of just a rand() function because this creates a more "random" randomness
//This is because the rand() funtion can output the same numbers close or next to one another,
//but with the use of an array these problems are gone
uint8_t randomArray[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //Array that stores the random effects index

//::shuffleArray::(pointer to array to shuffle, length of the array)
//  It shuffles the given array randomly
void shuffleArray(uint8_t *array, uint8_t size)
{
  randomSeed(analogRead(0));

  uint8_t last = 0;
  uint8_t temp = array[last];
  for (uint8_t i = 0; i < size; i++)
  {
    uint8_t index = random(size);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}

//::BLECallbackHandler:: This class is a callback implimentation that handles the BLE events
//Currently only the onWrite event is used and implimented
class BLECallbackHandler : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue(); //Reads the value from the BLE characteristic

    if (value.length() > 3) //Checks to see if the received command is (semi-)valid
    {

      //Breaks down the string command into its 3 parts; for more info about the commands see the LightsOn bluetooth.dart documentation
      std::string effect_str = value.substr(0, 2);
      std::string setting_str = value.substr(2, 1);
      std::string data_str = value.substr(3);

      //Convert string to int
      int effect_id = strtol(effect_str.c_str(), NULL, 16);
      int setting_id = strtol(setting_str.c_str(), NULL, 16);
      int rdata = strtol(data_str.c_str(), NULL, 16);

      //Set the command data to the settings
      settings[effect_id][setting_id] = rdata;

      //Change the brightness to the stored value (this is done every time, dispite a command irrelevant to brightness)
      FastLED.setBrightness(settings[0][12]);

      //Changes the characteristic value to OK to notify that the BLE command was valid and executed
      //Used in earlier version on the BLE communication but stuck around because it's usefull and doesn't hurt
      pCharacteristic->setValue("OK");
    }
    else
    {
      //Changes the characteristic value to ERR to notify that the BLE command was invalid
      //Used in earlier version on the BLE communication but stuck around because it's usefull and doesn't hurt
      pCharacteristic->setValue("ERR");
    }
  }
};

//::setup::
//  Arduino setup function
void setup()
{

  delay(3000); //For a moment of peace and silence

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); //Adds the configured LED strip to the leds array

  delay(500); //We take things nice and slow

  BLEDevice::init(DEVICE_NAME); //Initialize the BLE device with the DEVICE_NAME as its name

  pServer = BLEDevice::createServer(); //Creates a BLE server and assigns it to the appropriate variable

  //Creates a BLE service with its UUID and assigns it to the appropriate variable
  pReceiveService = pServer->createService(RECEIVE_SERVICE_UUID);

  //Creates a BLE characteristic with its UUID, from the previous service, and assigns it to the appropriate variable
  pDataCharacteristic = pReceiveService->createCharacteristic(
      DATA_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  pDataCharacteristic->setValue("START"); //Sets an initial value to the characteristic

  pDataCharacteristic->setCallbacks(new BLECallbackHandler); //Sets the event handler callback to the characteristic

  pReceiveService->start(); //Starts the BLE service

  pAdvertising = pServer->getAdvertising();           //Sets the server advertising, enabling other devices to see it
  pAdvertising->addServiceUUID(RECEIVE_SERVICE_UUID); //Adds the service to the advertising
  pAdvertising->start();                              //Enables the server advertising

  chooseNextColorPalette(gTargetPalette); //Initial config of the Twinkle Fox effect

  //--Initial config of the NoisePlusPallete effect--//
  x = random16();
  y = random16();
  z = random16();
  //-------------------------------------------------//

  delay(500); //More peace

  shuffleArray(randomArray, 16); //Initial shuffling of the array

  FastLED.setBrightness(settings[0][12]); //Set the brightness to the default in the settings

  delay(500); //Final peace
}

//::loop::
//  Arduino loop funtctiion; called roughly every 20-30ms
//  Most of the functions are non-blocking and need to be this way for smooth led animations
//  and quick response to effect changes
void loop()
{
  //Called every N seconds that the user has selected for the TwinkleFox effect
  EVERY_N_SECONDS(settings[17][13])
  {
    chooseNextColorPalette(gTargetPalette); //Changes the current palette
  }

  //Called every 10ms; used by the TwinkleFox effect
  EVERY_N_MILLISECONDS(10)
  {
    //Blends the current palette to the next one for smooth transition
    nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, 12);
  }

  //Called every N seconds that the user has selected for the OneColorRound(round) effect
  //Counts up OneColorRound effects and when it reaches the max starts from the start
  EVERY_N_SECONDS(settings[18][12])
  {
    if (drawID < 9)
    {
      drawID++;
    }
    else
    {
      drawID = 0;
    }
  }

  //Called every 25s to change the random effect that is selected from the randomArray
  //Counts up index in the randomArray and when it reaches the max starts from the start, shuffing it in the proccess
  EVERY_N_SECONDS(25)
  {
    if (randomIndex < 15)
    {
      randomIndex++;
    }
    else
    {
      randomIndex = 0;
      shuffleArray(randomArray, 16);
    }
  }

  //Called every 20ms and draws the selected effect
  //It handles both random effects and user selected ones
  //It uses a funtion array (func_ptr) because it's faster than if else statements;
  //and likely faster than switch statements, although that's compiler and platform depended
  EVERY_N_MILLISECONDS(20)
  {
    if (settings[0][8])
    {
      //Draw random effect
      (*func_ptr[randomArray[randomIndex]])();
    }
    else
    {
      //Draw user selected effect
      (*func_ptr[settings[0][0]])();
    }
  }
}
