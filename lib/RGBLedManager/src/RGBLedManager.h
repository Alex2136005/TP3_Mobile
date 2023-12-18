#include <string>

using namespace std;

class REGBLedManager {
    public:
    RevolvairWebServer(int redPin, int greenPin, int bluePin);
    void setLed(String hexColor) const;

    private:
    const int redPin;
    const int greenPin;
    const int bluePin;
    uint8_t red, green, blue;
};