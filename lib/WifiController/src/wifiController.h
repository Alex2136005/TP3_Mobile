#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <WiFiManager.h>
class WifiController
{
    public:
        WifiController( /*const char* STA_SSID, const char* STA_PW*/);
        bool isConnected() const;
        void initializeConnexion();
        static String getMacAddress();
        static String getWifiRSSI();
        static String getSSID();
        static String getUniqueId();
    private:
        const int led = 13;
        //const char* SSID ;
        //const char* PASSWORD;
        const float WIFI_CONNEXION_ATTEMPT_DELAY = 10000;

};