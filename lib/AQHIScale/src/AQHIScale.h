#include <Arduino.h>
#include <ArduinoJson.h>
#include "../../RevolvairAPI/src/RevlovairAPI.h"
class AQHIScale 
{

    public:
        AQHIScale(DynamicJsonDocument ranges);
        String getLevel( );
        String getDescription();
        String getHexColor();
        String getAqiEpaLabelFromPM25(uint16_t pm_2_5);
        String getLastScanResult();
        void updateInfos(String pm_2_5);
    private:
        RevolvairAPI* api;
        static DynamicJsonDocument rangeJson;
        String level, description, hexColor, scanResult;
};