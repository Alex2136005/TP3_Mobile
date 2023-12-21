#pragma once

#include <Arduino.h>
#include <unity.h>
#include <ArduinoJson.h>
#include "../../lib/RevolvairWebServer/src/revolvairWebServer.h"
#include "../../lib/EPAScale/src/EPAScale.h"
#include "ranges.h"

void test_function_getLabelFromPM25(void)
{
    DynamicJsonDocument ranges(4096);
    deserializeJson(ranges, ranges::json);
    EPAScale scale(ranges);
    String result = scale.getLabelFromPM25(uint16_t(1));
    TEST_ASSERT_EQUAL_STRING("Bon", result.c_str());
}
