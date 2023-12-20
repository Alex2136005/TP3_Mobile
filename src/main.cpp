#include <Arduino.h>
#include <string>
#include "../lib/RevolvairWebServer/src/revolvairWebServer.h"
#include <PMS.h>
#include "PMSReader.h"
PMS pms(Serial2);
PMS::DATA data;

WifiManager* wifiManager = nullptr;
RevolvairWebServer* webServer = nullptr;
PMSReader* pmsReader = nullptr;
RevolvairAPI* api = nullptr;

unsigned long previousMillis = 0;
const long airScanDelay = 5000;
const long dataSendingDelay = 10000;

uint16_t lastScanResult = 0;

void setup() {  

  const char* ssid = config::WIFI_NAME;
  const char* password = config::WIFI_PASSWORD;
  
  Serial.begin(115200);
  Serial2.begin(9600);

    pmsReader = new PMSReader(pms);
    wifiManager = new WifiManager(ssid, password);
    webServer = new RevolvairWebServer(new WebServer(80));
    api = new RevolvairAPI();
    wifiManager->initializeConnexion();
    webServer->initializeServer();
}


void loop() 
{
  if(wifiManager->isConnected()){
    webServer->server->handleClient();
  }
  else
  {
    wifiManager->initializeConnexion();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= airScanDelay) 
  {
    uint16_t scanResult = pmsReader->getCurrentAirQualityReading(data);
    if(scanResult != std::numeric_limits<uint16_t>::max())
    {
      webServer->setPM25(data.PM_AE_UG_2_5);
      lastScanResult = scanResult;
      previousMillis = currentMillis;
      Serial.println("PM 1 (μg/m3):" + String(data.PM_SP_UG_1_0) );
      Serial.println("PM 2.5 (μg/m3):" + String(data.PM_AE_UG_2_5) ); 
      Serial.println("PM 10 (μg/m3):" + String(data.PM_AE_UG_10_0) );
    }
  }

  static unsigned long lastDataSendingMillis = 0;
   if (currentMillis - lastDataSendingMillis >= dataSendingDelay) 
   {
    Serial.println("Sending data to API");
    api->sendPM25Data(String(data.PM_AE_UG_1_0), String(data.PM_AE_UG_10_0), String(data.PM_AE_UG_2_5));
    lastDataSendingMillis = currentMillis;
  }


  delay(2);
}
