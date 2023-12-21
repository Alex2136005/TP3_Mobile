#ifndef RGBLED_MANAGER_H
#define RGBLED_MANAGER_H

#include <Arduino.h>
#include <string>
#include "RGBColor.h"

using namespace std;

class RGBLedManager
{
public:
    RGBLedManager(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    RGBLedManager();
    void setLed(RGBColor color);
    RGBColor getRGBColorFromHex(String color);

private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;
    uint8_t red, green, blue;
};
#endif 