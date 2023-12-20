#include "AQHIScale.h"

DynamicJsonDocument AQHIScale::rangeJson(4096);
AQHIScale::AQHIScale()
{
    this->api = new RevolvairAPI();
    this->level = "";
    this->description = "";
    this->hexColor = "";
}

void AQHIScale::initialize()
{
    String payload = api->getJSONFromURL("https://staging.revolvair.org/api/revolvair/aqi/aqhi");
    DeserializationError error = deserializeJson(rangeJson, payload);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
    }

}
void AQHIScale::updateInfos(String pm_2_5)
{
    if(!this->initialized){
        initialize();
        this->initialized = true;
    }
    this->scanResult = String(pm_2_5);
    for (int i = 0; i < rangeJson["ranges"].size(); ++i)
    {
        if (pm_2_5.toInt() < rangeJson["ranges"][i]["max"]) 
        {
            this->level = rangeJson["ranges"][i]["label"].as<String>();
            this->description = rangeJson["ranges"][i]["note"].as<String>();
            this->hexColor = rangeJson["ranges"][i]["color"].as<String>();
            break;
        }
    }
}
String AQHIScale::getLastScanResult(){
    return this->scanResult;
}
String AQHIScale::getAqiEpaLabelFromPM25(uint16_t pm_2_5)
{
    for (int i = 0; i < rangeJson["ranges"].size(); ++i)
    {
        if (pm_2_5 < rangeJson["ranges"][i]["max"]) 
        {
            return rangeJson["ranges"][i]["label"].as<String>();
        }
    }
    return "No label foud for this value.";
}
String AQHIScale::getLevel(){
    return this->level;
}
String AQHIScale::getDescription(){
    return this->description;
}
String AQHIScale::getHexColor(){
    return this->hexColor;
}

