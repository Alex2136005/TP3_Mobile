#include "RevlovairAPI.h"

RevolvairAPI::RevolvairAPI(){}

void RevolvairAPI::postJSON(String& encodedJSON) 
{
    HTTPClient http;
    http.begin(config::API_POST_URL);
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(config::API_TOKEN));
    int httpCode = http.POST(encodedJSON);
    String payload = http.getString();

    http.end();
}

String RevolvairAPI::getJSONFromURL(const string url) const 
{
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

    Serial.println(payload);
    
    return payload;
}

void RevolvairAPI::sendPM25Data(String value)
{
  DynamicJsonDocument doc(1024);
  doc["esp8266id"] = WifiManager::getUniqueId();
  doc["PMS_P2"]  = value;
  doc["signal"]   = WifiManager::getWifiRSSI();
  String jsonPm25Package = "";
  serializeJson(doc, jsonPm25Package);
  Serial.println(jsonPm25Package);
  postJSON(jsonPm25Package);  
}