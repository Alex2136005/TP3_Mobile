#include "AQHIScale.h"

DynamicJsonDocument AQHIScale::rangeJson(4096);
AQHIScale::AQHIScale(DynamicJsonDocument ranges)
{
    String jsonString;
    serializeJson(ranges, jsonString);
    Serial.println(jsonString);    
    this->api = new RevolvairAPI();
    this->level = "";
    this->rangeJson = ranges;
    this->description = "";
    this->hexColor = "";
}

void AQHIScale::updateInfos(String pm_2_5)
{
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
        if (String(pm_2_5).toInt() < rangeJson["ranges"][i]["max"]) 
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

