#include "revolvairWebServer.h"

const int redPin = 12;
const int greenPin = 13;
const int bluePin = 14;
uint8_t red, green, blue;

WebServer* RevolvairWebServer::server = nullptr;
RevolvairWebServer::RevolvairWebServer(WebServer* webserver){  
    this->server = webserver;
    Serial2.begin(9600);
}

void RevolvairWebServer::handleNotFound(){
    digitalWrite(led, 1);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server->uri();
    message += "\nMethod: ";
    message += (server->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server->args();
    message += "\n";
    for (uint8_t i = 0; i < server->args(); i++) {
        message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
    }
    server->send(404, "text/plain", message);
    digitalWrite(led, 0);
}


void RevolvairWebServer::handleRoot(){
    digitalWrite(led, 1);
    File file = SPIFFS.open("/index.html", "r");
    if (!file) 
    {
        Serial.println("Le fichier index.html est introuvable.");
        return ;
    }

    String htmlContent = file.readString();
    
    server->send(200, "text/html", htmlContent);
    file.close();

    digitalWrite(led, 0);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

String RevolvairWebServer::updateHtmlContentPage1(String niveau, String description, String hexColor) {
    File file = SPIFFS.open("/airQuality.html", "r");
    if (!file) 
    {
        Serial.println("Le fichier airQuality.html est introuvable.");
        return "<html>Une erreur est survenue avec le fichier demandé.</html>";
    }
 
    String htmlContentPage1 = file.readString();
    htmlContentPage1.replace("%PM_2_5%", String(pm_2_5));
    htmlContentPage1.replace("%NIVEAU%", niveau);
    htmlContentPage1.replace("%DESCRIPTION%", description);
    htmlContentPage1.replace("%HEX_COLOR%", hexColor);
    file.close();

    return htmlContentPage1;
}

String RevolvairWebServer::updateHtmlContentPage2() 
{
    byte mac[6];
    WiFi.macAddress(mac);
    String uniqueId =  String(mac[0],HEX) +String(mac[1],HEX) +String(mac[2],HEX) +String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);
    File file = SPIFFS.open("/deviceInfo.html", "r");
    if (!file) 
    {
        Serial.println("Le fichier deviceInfo.html est introuvable.");
        return "<html>Une erreur est survenue avec le fichier demandé.</html>";
    }

    String htmlContentPage2 = file.readString();
    file.close();
    htmlContentPage2.replace("%MAC_ADDRESS%", WiFi.macAddress());
    htmlContentPage2.replace("%DEVICE_ID%", uniqueId);
    htmlContentPage2.replace("%WIFI_SSID%", WiFi.SSID());
    htmlContentPage2.replace("%WIFI_RSSI%", String(WiFi.RSSI()));

    return htmlContentPage2;   
}


void RevolvairWebServer::initializeServer()
{
    HTTPClient http;
    http.begin("https://staging.revolvair.org/api/revolvair/aqi/aqhi");
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();

    DynamicJsonDocument doc(4096);

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
    }

    //Change la lumière selon le value de la qualité d'aire (aqhi)
    int value = 52;
    String niveau = "";
    String description = "";
    String hexColor = "#ffffff";

    for (int i = 0; i < doc["ranges"].size(); ++i) {
        if (value < doc["ranges"][i]["max"]) {
            niveau = doc["ranges"][i]["label"].as<String>();
            description = doc["ranges"][i]["note"].as<String>();
            hexColor = doc["ranges"][i]["color"].as<String>();
            break;
        }
    }
    Serial.println(hexColor);
    //...

    //tout mettre dans RGBLedManager...
    long number;
    if(hexColor[0] == '#')  number = strtol(&hexColor[1], nullptr, 16);
    else number = strtol(&hexColor[0], nullptr, 16);
    red = number >> 16;
    green = number >> 8 & 0xFF;
    blue = number & 0xFF;
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);

    File file = SPIFFS.open("/navbar.html", "r");
    if (!file) 
    {
        Serial.println("Le fichier navbar.html est introuvable.");
        return ;
    }

    String htmlContentNav = file.readString();

    server->on("/", handleRoot);
    server->on("/qualitedelair", HTTP_GET, [this, htmlContentNav, niveau, description, hexColor](){
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage1(niveau, description, hexColor));
    });
     server->on("/informationdelappareil", HTTP_GET, [this, htmlContentNav](){
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage2());
    });
    server->onNotFound(handleNotFound);
    server->begin();

    Serial.println("HTTP server started");
}

void RevolvairWebServer::setPM25(uint16_t pm_2_5)
{
    this->pm_2_5 = String(pm_2_5);
}
