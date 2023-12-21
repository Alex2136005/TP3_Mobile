#include "EPAScale.h"

DynamicJsonDocument EPAScale::rangeJson(4096);
EPAScale::EPAScale(DynamicJsonDocument ranges)
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

void EPAScale::updateInfos(String pm_2_5)
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
String EPAScale::getLastScanResult(){
    return this->scanResult;
}
String EPAScale::getLabelFromPM25(uint16_t pm_2_5)
{

    for (int i = 0; i < rangeJson["ranges"].size(); ++i)
    {
        if (String(pm_2_5).toInt() < rangeJson["ranges"][i]["max"]) 
        {
            return rangeJson["ranges"][i]["label"].as<String>();
        }
    }
    return "No label found for this value.";
}

RGBColor EPAScale::getRGBColorFromPM25(uint16_t pm_2_5)
{
    RGBColor color  = {0,0,0};

    for (int i = 0; i < rangeJson["ranges"].size(); ++i)
    {
        if (String(pm_2_5).toInt() < rangeJson["ranges"][i]["max"]) 
        {
            return RGBLedManager().getRGBColorFromHex(rangeJson["ranges"][i]["color"].as<String>());
        }
    }
    return color;
}
String EPAScale::getLevel(){
    return this->level;
}
String EPAScale::getDescription(){
    return this->description;
}
String EPAScale::getHexColor(){
    return this->hexColor;
}

