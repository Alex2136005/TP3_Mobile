#ifndef RGBLED_MANAGER_H
#define RGBLED_MANAGER_H

#include <Arduino.h>
#include <string>
#include "RGBColor.h"

class RGBLedManager
{
public:
    RGBLedManager(int redPin, int greenPin, int bluePin);
    RGBLedManager();
    void setLed(RGBColor color);
    RGBColor getRGBColorFromHex(String color);

private:
    int redPin;
    int greenPin;
    int bluePin;
};
#endif 
