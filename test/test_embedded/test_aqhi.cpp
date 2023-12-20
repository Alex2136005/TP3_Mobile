#include <unity.h>
#include <ArduinoJson.h>
#include "../../lib/RevolvairAPI/src/RevlovairAPI.h"
#include "../../lib/AQHIScale/src/AQHIScale.h"
 
const char* json =
R"({
  "ranges": [
    {
      "min": 0,
      "max": 10,
      "label": "1) Faible risque",
      "color": "00ccff",
      "health_effect": "Population touchée : Profitez de vos activités habituelles en plein air.",
      "note": "Population en général : Qualité de l'air idéale pour les activités en plein air."
    },
    {
      "min": 10,
      "max": 20,
      "label": "2 Faible risque",
      "color": "0099cc",
      "health_effect": "Population touchée : Profitez de vos activités habituelles en plein air.",
      "note": "Population en général : Qualité de l'air idéale pour les activités en plein air."
    }
  ]
})";
 
void setup() {
   
}
 
void loop() {
}
 
void tearDown(void) {
}
 
void test_function_getAQILabelFromPM25(void)
{
    DynamicJsonDocument ranges(4096);
    deserializeJson(ranges, json);
    AQHIScale scale(ranges);
    String result = scale.getAqiEpaLabelFromPM25(uint16_t(1));
    TEST_ASSERT_EQUAL_STRING("Bon", result.c_str());
}
 
void process() {
    UNITY_BEGIN();
    RUN_TEST(test_function_getAQILabelFromPM25);
    UNITY_END();
}
 