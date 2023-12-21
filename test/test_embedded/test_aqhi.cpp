#include <Arduino.h>
#include <unity.h>
#include <ArduinoJson.h>
#include "../../lib/RevolvairWebServer/src/revolvairWebServer.h"
#include "../../lib/EPAScale/src/EPAScale.h"

const char* json =
R"({
   "ranges": [
    {
      "min": 0,
      "max": 50,
      "label": "Bon",
      "color": "009982",
      "health_effect": "La qualité de l’air est considérée comme satisfaisante et la pollution de l’air pose peu ou pas de risque.",
      "note": "Aucune."
    },
    {
      "min": 51,
      "max": 100,
      "label": "Modéré",
      "color": "ecde2b",
      "health_effect": "La qualité de l’air est acceptable; cependant, pour certains polluants, il peut y avoir un problème de santé modéré pour un très petit nombre de personnes qui sont inhabituellement sensibles à la pollution atmosphérique.",
      "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, telles que l’asthme, devraient limiter les efforts prolongés à l’extérieur."
    },
    {
      "min": 101,
      "max": 150,
      "label": "Mauvais pour les groupes sensibles",
      "color": "ff991e",
      "health_effect": "Les membres de groupes sensibles peuvent subir des effets sur la santé. Le grand public ne sera probablement pas affecté.",
      "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, telles que l’asthme, devraient limiter les efforts prolongés à l’extérieur."
    },
    {
      "min": 151,
      "max": 200,
      "label": "Mauvais pour la santé",
      "color": "b00085",
      "health_effect": "Tout le monde peut commencer à ressentir des effets sur la santé; les membres de groupes sensibles peuvent subir des effets plus graves sur la santé.",
      "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, telles que l’asthme, devraient éviter les efforts prolongés à l’extérieur; tout le monde, en particulier les enfants, devrait limiter les efforts prolongés à l’extérieur."
    },
    {
      "min": 201,
      "max": 300,
      "label": "Très mauvais pour la santé",
      "color": "ff000b",
      "health_effect": "Avertissements sanitaires des conditions d’urgence. La population entière est plus susceptible d’être touchée.",
      "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, comme l’asthme, devraient éviter tout effort extérieur; tout le monde, en particulier les enfants, devrait limiter les efforts à l’extérieur."
    },
    {
      "min": 300,
      "max": 10000,
      "label": "Dangereux",
      "color": "ff000b",
      "health_effect": "Alerte santé: tout le monde peut subir des effets sanitaires plus graves.",
      "note": "Tout le monde devrait éviter tout effort extérieur."
    }
  ]
})";

void test_function_getLabelFromPM25(void)
{
    DynamicJsonDocument ranges(4096);
    deserializeJson(ranges, json);
    EPAScale scale(ranges);
    String result = scale.getLabelFromPM25(uint16_t(1));
    TEST_ASSERT_EQUAL_STRING("Bon", result.c_str());
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
  RGBColor result = scale.getRGBColorFromPM25(52);
  TEST_ASSERT_EQUAL(236, result.red);
  TEST_ASSERT_EQUAL(222, result.green);
  TEST_ASSERT_EQUAL(43, result.blue);
}

void test_DEL_color_changes_when_pm25_value_increment_from_0_to_300(void)
{
  ledcSetup(15, 5000, 8); 

  DynamicJsonDocument ranges(4096);
  deserializeJson(ranges, json);
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

void setUp(void) {
}

void tearDown(void) {
}


void setup() 
{
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_function_getLabelFromPM25);
  RUN_TEST(test_function_getRGBFromHexColor);
  RUN_TEST(test_function_getRGBFromPm25);
  RUN_TEST(test_DEL_color_changes_when_pm25_value_increment_from_0_to_300);
  UNITY_END();
}

void loop() {
  
}