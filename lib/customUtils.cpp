#include "customUtils.h"

String customUtils::getJSONFromURL(const string url) const {
    HTTPClient http;
    http.begin(String(url.c_str()));
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    if (httpCode == HTTP_CODE_OK) {
        Serial.println("------data------");
        Serial.println(httpCode);
        Serial.println(payload);
        Serial.println("------close------");
    } else {
        Serial.println("HTTP request failed");
        Serial.println("HTTP Code: " + String(httpCode));
    }

    return payload;
}
