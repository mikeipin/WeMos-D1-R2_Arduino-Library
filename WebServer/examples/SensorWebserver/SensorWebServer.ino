/*
 * Sensor Webserver by Michael Ipinyomi
 * This creates a webpage and displays the output 
 * of the sensor connected to analgo input 0

Modify and locate "%02d" in the html string in the 
handleRoot() function to insert the Sensor value within the html web page
content refreshes every 1 second
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
  
const char *ssid = "SSID";
const char *password = "PASSKEY";



String out = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"200\">\n <rect width=\"400\" height=\"200\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n <g stroke=\"black\">\n";
String graph = " ";
//out += "";
//out += "";

String outb = "</g>\n</svg>\n";


int y = 0;
int x = 0;

ESP8266WebServer server ( 80 );

const int led = 13;

void handleRoot() {
  digitalWrite ( led, 1 );
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  
  int sensorValue = analogRead(0);
  sensorValue = map(sensorValue, 0, 1024, 0, 1023);
  
  snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='1'/>\
    <title>Sensor WebServer Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from SensorServer!</h1>\
    <p>Sensor Value= %02d</p>\
    <p>Time:= %02d:%02d</p>\
 
    <img src=\"/test.svg\" />\
  </body>\
</html>",

    sensorValue, min % 60, sec % 60
  );
  server.send ( 200, "text/html", temp );
  digitalWrite ( led, 0 );
}

void handleNotFound() {
  digitalWrite ( led, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( led, 0 );
}

void setup ( void ) {
  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );
  Serial.begin ( 115200 );
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/test.svg", drawGraph );
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();
}

void drawGraph() {
  char temp[100];
  int sensorValue = analogRead(0);
  sensorValue = map(sensorValue, 0, 1024, 0, 1023);
  int y2 = (sensorValue/10);

  sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
  
  graph += temp;
  x = x + 10;

  if (x >= 390){
    x = 0;
    graph = " ";
  }
  y = y2;
   
  String final_out = "";
  final_out += out;
  final_out += graph;
  final_out += outb;


  server.send ( 200, "image/svg+xml", final_out);
  
}
