#include <Arduino.h>
#include <string>
#include "customUtils.h"
#include "config.h"

customUtils utils;
String json;

void setup() {
  Serial.begin(115200);
  json = utils.getJSONFromURL("https://staging.revolvair.org/api/revolvair/stations/cegep-de-ste-foy/");//config::URL_REVOLVAIR
  Serial.println(json);
}

void loop() {
  Serial.println("test2");
  delay(10000);
}