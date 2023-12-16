#include "revolvairWebServer.h"

WebServer* RevolvairWebServer::server = nullptr;
RevolvairWebServer::RevolvairWebServer(WebServer* webserver){  
    this->server = webserver;
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
}

void RevolvairWebServer::initializeServer()
{
    String htmlContentNav = "<p> >> <a href=\"/\">Page d'accueil</a></p>";
    htmlContentNav += "<p> >> <a href=\"/qualitedelair\">Page Qualite de l'air</a></p>";
    htmlContentNav += "<p> >> <a href=\"/informationdelappareil\">Page Information de l'appareil</a></p>";

    String htmlContentPage1 = "<html><body>";
    htmlContentPage1 += htmlContentNav;
    htmlContentPage1 += "<h1>Page Qualite de l'air</h1>";
    htmlContentPage1 += "<p>PM 2.5 : {{data}}  μg/m³</p>";
    htmlContentPage1 += "<p>Niveau : {{data}}</p>";
    htmlContentPage1 += "<p>Description : {{data}}</p>";
    htmlContentPage1 += "<p>Couleur : {{data}}</p>";
    htmlContentPage1 += "</body></html>";

    String htmlContentPage2 = "<html><body>";
    htmlContentPage2 += htmlContentNav;
    htmlContentPage2 += "<h1>Page Information de l'appareil</h1>";
    htmlContentPage2 += "<p>Mac ID : {{data}}</p>";
    htmlContentPage2 += " <p>Device Id : {{data}}</p>";
    htmlContentPage2 += "</body></html>";

    server->on("/", handleRoot);
    server->on("/qualitedelair", HTTP_GET, [htmlContentPage1](){
        //digitalWrite(LED_BUILTIN, HIGH);
        server->send(200, "text/html", htmlContentPage1);
    });
     server->on("/informationdelappareil", HTTP_GET, [htmlContentPage2](){
        //digitalWrite(LED_BUILTIN, LOW);
        server->send(200, "text/html", htmlContentPage2);
    });
    server->onNotFound(handleNotFound);
    server->begin();

    Serial.println("HTTP server started");
}