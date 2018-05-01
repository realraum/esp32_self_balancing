#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "serial.h"

const char* ssid = "realraum";
const char* password =  "r3alraum";

AsyncWebServer server(80);

const char myindex[] PROGMEM = "<html>\
<head>\
<script type=\"text/javascript\">\
function d(a) {\
    var xmlhttp = new XMLHttpRequest();\
\
    xmlhttp.onreadystatechange = function() {\
        if (xmlhttp.readyState == XMLHttpRequest.DONE) { \
           if (xmlhttp.status == 200) {\
           }\
           else if (xmlhttp.status == 400) {\
              alert('There was an error 400');\
           }\
           else {\
               alert('something else other than 200 was returned');\
           }\
        }\
    };\
\
    xmlhttp.open(\"GET\", \"drive_\"+a+\"\", true);\
    xmlhttp.send();\
}\
</script>\
</head>\
<body>\
<button onclick=\"d(1)\">Front</button><br>\
<button onclick=\"d(2)\">Left</button><button onclick=\"d(3)\">Right</button><br>\
<button onclick=\"d(4)\">Back</button>";





void web_task(void *pvParameter){
  //Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  //  request->send(200, "text/html", index_html);
  //});

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", myindex);
  });



  server.on("/drive_1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "Hello World");
    dir=1;lastdir=millis();
  });
  server.on("/drive_2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "Hello World");
    dir=2;lastdir=millis();
  });
  server.on("/drive_3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "Hello World");
    dir=3;lastdir=millis();
  });
  server.on("/drive_4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "Hello World");
    dir=4;lastdir=millis();
  });

  //server.serveStatic("/page.html", SPIFFS, "/index.html");

  server.begin();
  while(1)delay(10);
}
