#include "RGBLedManager.h"

RGBLedManager::RGBLedManager(int redPin, int greenPin, int bluePin)
{  
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}
RGBLedManager::RGBLedManager(){  }


void RGBLedManager::setLed(String hexColor) 
{
    RGBColor color = getRGBColorFromHex(hexColor);
    
    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);	
}

RGBColor RGBLedManager::getRGBColorFromHex(String hexColor)
{
    uint8_t red, green, blue;
    long number;
    if(hexColor[0] == '#')  number = strtol(&hexColor[1], nullptr, 16);
    else number = strtol(&hexColor[0], nullptr, 16);
    red = number >> 16;
    green = number >> 8 & 0xFF;
    blue = number & 0xFF;

    RGBColor color = {red, green, blue};
    return color;
}

