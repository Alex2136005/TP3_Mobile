#include <Arduino.h>
#include <unity.h>
#include <ArduinoJson.h>
#include "../../lib/RGBLedManager/src/RGBLedManager.h"
#include "../../lib/RGBLedManager/src/RGBColor.h"
#include "../../lib/RevolvairAPI/src/RevlovairAPI.h"
#include "../../lib/EPAScale/src/EPAScale.h"

const char* json =
R"({
  "ranges": [
    {
      "min": 0,
      "max": 10,
      "label": "Faible risque",
      "color": "00ccff",
      "health_effect": "Population touchée : Profitez de vos activités habituelles en plein air.",
      "note": "Population en général : Qualité de l'air idéale pour les activités en plein air."
    },
    {
      "min": 10,
      "max": 20,
      "label": "Faible risque",
      "color": "0099cc",
      "health_effect": "Population touchée : Profitez de vos activités habituelles en plein air.",
      "note": "Population en général : Qualité de l'air idéale pour les activités en plein air."
    }
  ]
})";

void test_function_getLabelFromPM25(void)
{
    DynamicJsonDocument ranges(4096);
    deserializeJson(ranges, json);
    EPAScale scale(ranges);
    String result = scale.getLabelFromPM25(uint16_t(1));
    TEST_ASSERT_EQUAL_STRING("Faible risque", result.c_str());
}

void test_function_getRGBFromHexColor(void)
{
    RGBLedManager* ledManager = new RGBLedManager(0,0,0);
    RGBColor result = ledManager->getRGBColorFromHex("#ffffff");
    TEST_ASSERT_EQUAL(255, result.red);
    TEST_ASSERT_EQUAL(255, result.green);
    TEST_ASSERT_EQUAL(255, result.blue);
}

void test_function_getRGBFromPm25(void)
{
  DynamicJsonDocument ranges(4096);
  deserializeJson(ranges, json);
  EPAScale scale(ranges);
  RGBColor result = scale.getRGBColorFromPM25(12);
  TEST_ASSERT_EQUAL(0, result.red);
  TEST_ASSERT_EQUAL(153, result.green);
  TEST_ASSERT_EQUAL(204, result.blue);
}

void setUp(void) {
}

void tearDown(void) {
}


void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_function_getLabelFromPM25);
    RUN_TEST(test_function_getRGBFromHexColor);
    RUN_TEST(test_function_getRGBFromPm25);
    UNITY_END();
}

void loop() {
  
}