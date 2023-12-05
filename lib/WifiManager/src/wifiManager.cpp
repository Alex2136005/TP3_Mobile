#include "wifiManager.h"


WifiManager::WifiManager(const char* STA_SSID, const char* STA_PW){  
    this->SSID = STA_SSID;
    this->PASSWORD = STA_PW;
};


void WifiManager::initializeConnexion()
{

    pinMode(led, OUTPUT);
    digitalWrite(led, 0);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->SSID, this->PASSWORD);
    Serial.println("");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(this->SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    if (MDNS.begin("esp32")) {
        Serial.println("MDNS responder started");
    }
}

bool WifiManager::isConnected() const{
    return WiFi.status() == WL_CONNECTED;
}