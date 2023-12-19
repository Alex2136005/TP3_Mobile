#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
class WifiManager
{
    public:
        WifiManager( const char* STA_SSID, const char* STA_PW);
        bool isConnected() const;
        void initializeConnexion();
    private:
        const int led = 13;
        const char* SSID ;
        const char* PASSWORD;
        const float WIFI_CONNEXION_ATTEMPT_DELAY = 10000;

};