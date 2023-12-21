#include "RGBLedManager.h"

RGBLedManager::RGBLedManager(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){  
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBLedManager::setLed(String hexColor) {
    long number;
    if(hexColor[0] == '#')  number = strtol(&hexColor[1], nullptr, 16);
    else number = strtol(&hexColor[0], nullptr, 16);
    red = number >> 16;
    green = number >> 8 & 0xFF;
    blue = number & 0xFF;
    
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);	
}