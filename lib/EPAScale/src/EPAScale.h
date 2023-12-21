#include <Arduino.h>
#include <ArduinoJson.h>
#include "../../RGBLedManager/src/RGBLedManager.h"
#include "../../RGBLedManager/src/RGBColor.h"
#include "../../RevolvairAPI/src/RevlovairAPI.h"
class EPAScale 
{

    public:
        EPAScale(DynamicJsonDocument ranges);
        String getLevel( );
        String getDescription();
        String getHexColor();
        String getLabelFromPM25(uint16_t pm_2_5);
        String getLastScanResult();
        RGBColor getRGBColorFromPM25(uint16_t pm_2_5);
        void updateInfos(String pm_2_5);
    private:
        RevolvairAPI* api;
        static DynamicJsonDocument rangeJson;
        String level, description, hexColor, scanResult;
};