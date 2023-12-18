#include "revolvairWebServer.h"
#include "../../customUtils.h"
#include "../../../src/config.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

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
    String htmlContent = "<html><body>";
    htmlContent += "<h1>Alexis Chatigny et Mathys Deshaies Web Server</h1>";
    htmlContent += "<p><a href=\"/\">Page d'accueil</a></p>";
    htmlContent += "<p><a href=\"/qualitedelair\">Page Qualité de l'air</a></p>";
    htmlContent += "<p><a href=\"/informationdelappareil\">Page Information de l'appareil</a></p>";
    htmlContent += "</body></html>";

    server->send(200, "text/html", htmlContent);
    //server->send(200, "text/plain", "hello from esp32!");
    digitalWrite(led, 0);
    
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

String RevolvairWebServer::updateHtmlContentPage1(String niveau, String description, String hexColor) {
    String htmlContentPage1 = "<h1>Page Qualite de l'air</h1>";
    htmlContentPage1 += "<p>PM 2.5 : "+this->pm_2_5+" μg/m³</p>";
    htmlContentPage1 += "<p>Niveau : "+niveau+"</p>";
    htmlContentPage1 += "<p>Description : "+description+"</p>";
    htmlContentPage1 += "<p style='color: "+hexColor+";'>Couleur : "+hexColor+"</p>";
    htmlContentPage1 += "</body></html>";

    return htmlContentPage1;
}

String RevolvairWebServer::updateHtmlContentPage2() {
    String htmlContentPage2 = "<h1>Page Information de l'appareil</h1>";
    htmlContentPage2 += "<p>Mac ID : {{data}}</p>";
    htmlContentPage2 += " <p>Device Id : {{data}}</p>";
    htmlContentPage2 += "</body></html>";

    return htmlContentPage2;
}

void RevolvairWebServer::initializeServer()
{
    // customUtils utils;
    // String jsonString;

    //Because getJSONFromURL not working except in main 
    HTTPClient http;
    http.begin("https://staging.revolvair.org/api/revolvair/aqi/aqhi");
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();

    //jsonString = utils.getJSONFromURL("https://staging.revolvair.org/api/revolvair/aqi/aqhi");
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

    //---------
    String htmlContentNav = "<html><body><p> >> <a href=\"/\">Page d'accueil</a></p>";
    htmlContentNav += "<p> >> <a href=\"/qualitedelair\">Page Qualite de l'air</a></p>";
    htmlContentNav += "<p> >> <a href=\"/informationdelappareil\">Page Information de l'appareil</a></p>";

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
