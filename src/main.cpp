#include <Arduino.h>
#include <string>
#include "wifiManager.h"
#include "../lib/RevolvairWebServer/src/revolvairWebServer.h"
#include "FS.h"
#include "SPIFFS.h"
#include <PMS.h>
#include "PMSReader.h"
PMS pms(Serial2);
PMS::DATA data;

WifiManager* wifiManager = nullptr;
RevolvairWebServer* webServer = nullptr;
PMSReader* pmsReader = nullptr;

unsigned long previousMillis = 0;
const long interval = 1000;


void setup() {  

  const char* ssid = config::WIFI_NAME;
  const char* password = config::WIFI_PASSWORD;
  
  Serial.begin(115200);
  Serial2.begin(9600);

    if(!SPIFFS.begin(true)){
      Serial.println("SPIFFS Mount Failed");
      return;
    }
    pmsReader = new PMSReader(pms);
    wifiManager = new WifiManager(ssid, password);
    webServer = new RevolvairWebServer(new WebServer(80));
    wifiManager->initializeConnexion();
    webServer->initializeServer();
}


void loop() {
  if(wifiManager->isConnected()){
    webServer->server->handleClient();
  }
  else
  {
    wifiManager->initializeConnexion();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    uint16_t result = pmsReader->getCurrentAirQualityReading(data);
    if(result != std::numeric_limits<uint16_t>::max())
    {
      webServer->setPM25(data.PM_AE_UG_2_5);
      previousMillis = currentMillis;
      Serial.println("PM 2.5 (ug/m3):" + String(data.PM_AE_UG_2_5) ); 
    }
  }
  delay(2);
}
