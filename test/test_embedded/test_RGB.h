#pragma once

#include <Arduino.h>
#include <unity.h>
#include <ArduinoJson.h>
#include "../../lib/RevolvairWebServer/src/revolvairWebServer.h"
#include "../../lib/EPAScale/src/EPAScale.h"
#include "ranges.h"

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
  deserializeJson(ranges, ranges::json);
  EPAScale scale(ranges);
  RGBColor result = scale.getRGBColorFromPM25(52);
  TEST_ASSERT_EQUAL(236, result.red);
  TEST_ASSERT_EQUAL(222, result.green);
  TEST_ASSERT_EQUAL(43, result.blue);
}

void test_DEL_color_changes_when_pm25_value_increment_from_0_to_300(void)
{
  ledcSetup(15, 5000, 8); 

  DynamicJsonDocument ranges(4096);
  deserializeJson(ranges, ranges::json);
  EPAScale scale(ranges);
  RevolvairWebServer* testServer = new RevolvairWebServer(scale);
  
  RGBLedManager ledManager; 

  uint16_t currentReading = 10;
  String colorForLevels[] = {"009982","ecde2b","ff991e","b00085","ff000b","ff000b"};
  int i = 0;
  int pinRead = -1;

  while (currentReading < 301)
  {
      testServer->updateData(currentReading);
      RGBColor currentColor = ledManager.getRGBColorFromHex(colorForLevels[i]); 
      delay(100);

      pinRead = min(255, static_cast<int>(ledcRead(15)));
      delay(100);
      TEST_ASSERT_EQUAL(currentColor.red, pinRead);

      pinRead = min(255, static_cast<int>(ledcRead(14)));
      delay(100);
      TEST_ASSERT_EQUAL(currentColor.green, pinRead);

      pinRead = min(255, static_cast<int>(ledcRead(13)));
      delay(100);
      TEST_ASSERT_EQUAL(currentColor.blue, pinRead);

      currentReading = currentReading + 50;
      i++;
  }

}

void process_test_RGB() 
{  
  RUN_TEST(test_function_getRGBFromHexColor);
  RUN_TEST(test_function_getRGBFromPm25);
  RUN_TEST(test_DEL_color_changes_when_pm25_value_increment_from_0_to_300);
}
