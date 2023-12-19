#include <string>
#include <Arduino.h>
#include <HTTPClient.h>
#include <iostream>
#include <ArduinoJson.h>

using namespace std;

class customUtils {
    public:
    String getJSONFromURL(const string url) const;
    //String postJSON(const string url) const;

    private:
};