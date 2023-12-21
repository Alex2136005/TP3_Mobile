#include <Arduino.h>
#include <string>

using namespace std;

class RGBLedManager {
    public:
    RGBLedManager(uint8_t redPin,uint8_t greenPin, uint8_t bluePin);
    void setLed(String hexColor);

    private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;
    uint8_t red, green, blue;
};