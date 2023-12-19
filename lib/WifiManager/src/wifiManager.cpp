#include "wifiManager.h"


WifiManager::WifiManager(const char* STA_SSID, const char* STA_PW){  
    this->SSID = STA_SSID;
    this->PASSWORD = STA_PW;
};


void WifiManager::initializeConnexion()
{
    WiFi.mode(WIFI_STA);
    long lastAttemptDelay = 0;

    while (WiFi.status() != WL_CONNECTED) 
    {
        WiFi.begin(this->SSID, this->PASSWORD);
        Serial.println();
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(500);
            Serial.print(".");
            lastAttemptDelay += 500;
            if(lastAttemptDelay >= this->WIFI_CONNEXION_ATTEMPT_DELAY)
                break;
        }
        Serial.println("Le Wi-Fi n'a pas pu se connecter. Une nouvelle tentative est en cour.");
        lastAttemptDelay = 0;
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