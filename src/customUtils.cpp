#include "customUtils.h"

String customUtils::getJSONFromURL(String url) const {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.GET();
    String payload = http.getString();
    if (httpCode == HTTP_CODE_OK) {
        Serial.println("------data------");
        Serial.println(httpCode);
        Serial.println(payload);
        Serial.println("------close------");
    } else {
        Serial.println("HTTP request failed");
        Serial.println(httpCode);
    }

    http.end();

    return payload;
}

