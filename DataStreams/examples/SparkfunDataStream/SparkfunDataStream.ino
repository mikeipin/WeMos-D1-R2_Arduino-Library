/*
 *  This sketch sends data via HTTP GET requests to https://data.sparkfun.com service, visit the link to create you stream
 *
 *  You need to get the publicKey and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *  The code below has been configured to post the values from the analog pin A0 and digital pin D3
 *  to a stream created online, you can; 
 *  view the stream at https://data.sparkfun.com/streams/EJNm2296Vnf2RNY6W6K0
 *  
 *  To Test the stream visit https://data.sparkfun.com/input/EJNm2296Vnf2RNY6W6K0?private_key=dqbX77z4KDCwKjVozodk&field_1=18.19&field_2=1024.42
 */

#include <ESP8266WiFi.h>
#include <remap.h>

const char* ssid     = "SSID";
const char* password = "PASSKEY";

const char* host = "data.sparkfun.com";
const int sample_period = 5000; // period between sample acquisitions and uploads


const char* publicKey   = "EJNm2296Vnf2RNY6W6K0";
const char* privateKey = "dqbX77z4KDCwKjVozodk";

const char* field1   = "field_1"; // Name assigned to field #1 in sparkfun datastream
const char* field2   = "field_2"; // Name assigned to field #2 in sparkfun datastream
//const char* field3   = "field_3"; // Name assigned to field #3 in sparkfun datastream

int value1 = 0;  // 1st variable you wish to send to datastream, in this case A0
int value2 = 0;  // 2nd variable you wish to send to datastream, in this case D3
//int value3 = 0;  // 3rd variable you wish to send to datastream, in this case --


void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void loop() {

  
  // Update values from sensors
  value1 = analogRead(0);
  value2 = digitalRead(D3);

  value1 = value1 * 1;  // Any processing you intend to do
  value2 = value2 * 1; // 

  Serial.println("Debug Values---->");
  Serial.print("Value 1 = ");
  Serial.println(value1);
  
  Serial.print("Value 2 = ");
  Serial.println(value2);
  Serial.println("<----");

  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/input/";
  url += publicKey;
  url += "?private_key=";
  url += privateKey;
  url += "&";
  url += field1;
  url += "=";
  url += value1;
  url += "&";
  url += field2;
  url += "=";
  url += value2;

//  url += "&";
//  url += field3;
//  url += "=";
//  url += value3;
  
  
  Serial.print("Requesting URL: ");
  Serial.println(url);


  
  // This will send the request to the server
   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
 
  Serial.println("closing connection");
  Serial.println();
    delay(sample_period);
}

