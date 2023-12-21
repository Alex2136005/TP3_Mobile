#include "RGBLedManager.h"


RGBLedManager::RGBLedManager(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){  

    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}
RGBLedManager::RGBLedManager(){  }


void RGBLedManager::setLed(RGBColor color) 
{
    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);	
}

RGBColor RGBLedManager::getRGBColorFromHex(String hexColor) 
{
    uint8_t red, green, blue;
    long number;

    if (hexColor.length() < 6)
    {
        Serial.println("Invalid hex color format");
        return {0, 0, 0};
    }

    if (hexColor[0] == '#')  
        hexColor = hexColor.substring(1);

    number = strtol(hexColor.c_str(), nullptr, 16);

    red = (number >> 16) & 0xFF;
    if (red > 255) red = 255;

    green = (number >> 8) & 0xFF;
    if (green > 255) green = 255;

    blue = number & 0xFF;
    if (blue > 255) blue = 255;

    RGBColor color = {red, green, blue};
    return color;
}



