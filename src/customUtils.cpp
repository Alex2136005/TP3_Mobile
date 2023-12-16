#include "customUtils.h"

String customUtils::getJSONFromURL(String url) const {
    HTTPClient http;
    http.begin("https://api.github.com/users/hadley/repos");
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
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

    http.end();

    return payload;
    /*CURL* curl = curl_easy_init();
    std::string result;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return result;*/
}

