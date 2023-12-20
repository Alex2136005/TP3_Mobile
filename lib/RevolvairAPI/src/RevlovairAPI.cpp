#include "RevlovairAPI.h"

RevolvairAPI::RevolvairAPI(){}

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

void RevolvairAPI::postJSON(String& encodedJSON) 
{
    HTTPClient http;
    http.begin(config::API_POST_URL); //Ces infos sont hardcodés état donné que les post fonctionnent avec la machine d'un seul membre de l'équipe.
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-mac-id", "esp32-083AF2B914C0");
    http.addHeader("x-device-id", "211195251538440");
    int httpCode = http.POST(encodedJSON);
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
    http.end();
}

void RevolvairAPI::sendPM25Data(String valueP1, String valueP10, String valueP2_5)
{
    DynamicJsonDocument doc(1024);
    doc["esp8266id"] = "211195251538440";
    doc["software_version"] = "Revo-2023-v1";
    doc["sensordatavalues"][0]["value_type"] = "PMS_P0"; 
    doc["sensordatavalues"][0]["value"] = valueP1; 
    doc["sensordatavalues"][1]["value_type"] = "PMS_P1"; 
    doc["sensordatavalues"][1]["value"] = valueP10;
    doc["sensordatavalues"][2]["value_type"] = "PMS_P2"; 
    doc["sensordatavalues"][2]["value"] = valueP2_5 ;
    doc["sensordatavalues"][2]["value_type"] = "signal"; 
    doc["sensordatavalues"][2]["value"] = WifiManager::getWifiRSSI(); 
    String jsonPm25Package = "";
    serializeJson(doc, jsonPm25Package);
    Serial.println(jsonPm25Package);
    postJSON(jsonPm25Package);  
}