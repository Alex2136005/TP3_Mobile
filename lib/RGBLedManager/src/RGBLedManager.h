#include <Arduino.h>
#include <string>

using namespace std;

class RGBLedManager {
    public:
    RGBLedManager(int redPin, int greenPin, int bluePin);
    void setLed(String hexColor);

    private:
    int redPin;
    int greenPin;
    int bluePin;
    uint8_t red, green, blue;
};