#ifndef CONFIG_H
#define CONFIG_H

#include <string>

using namespace std;

class config {
public:
    static const string URL_REVOLVAIR;
    static const string URL_AQHI;
    static const char* WIFI_NAME;
    static const char* WIFI_PASSWORD;
    static const char* API_POST_URL;
    static const char* API_TOKEN;
};

#endif 
