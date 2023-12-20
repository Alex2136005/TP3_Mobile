#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include "../../../src/config.h"
#include "../../wifiController/src/wifiController.h"
class RevolvairAPI
{
    private:
        void postJSON(String& encodedJSON);
    public:
        RevolvairAPI();
        void sendPM25Data(String valueP0, String valueP1, String valueP2);
        String getJSONFromURL(const string url) const;
};