#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "yourrouterusername"
#define STAPSK  "yourrouterpassword"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

void indexz() {
  server.send(200, "text/plain", "Home");
}

void relayone(){
  server.send(200, "text/plain", "relay 1 shutdown");
  digitalWrite(D0, HIGH);
}

void relaytwo(){
  server.send(200, "text/plain", "relay 2 shutdown");
  digitalWrite(D1, HIGH);
}

void relaythree(){
  server.send(200, "text/plain", "relay 3 shutdown");
  digitalWrite(D2, HIGH);
}

void relayfour(){
  server.send(200, "text/plain", "relay 4 shutdown");
  digitalWrite(D3, HIGH);
}

void relayoneoff(){
  server.send(200, "text/plain", "relay 1 on");
  digitalWrite(D0, LOW);
}

void relaytwooff(){
  server.send(200, "text/plain", "relay 2 on");
  digitalWrite(D1, LOW);
}

void relaythreeoff(){
  server.send(200, "text/plain", "relay 3 on");
  digitalWrite(D2, LOW);
}

void relayfouroff(){
  server.send(200, "text/plain", "relay 4 on");
  digitalWrite(D3, LOW);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", indexz);
  server.on("/relayone", relayoneoff);
  server.on("/relaytwo", relaytwooff);
  server.on("/relaythree", relaythreeoff);
  server.on("/relayfour", relayfouroff);

  server.on("/relayonemati", relayone);
  server.on("/relaytwomati", relaytwo);
  server.on("/relaythreemati", relaythree);
  server.on("/relayfourmati", relayfour);
  

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("[--------------------]");
  Serial.println("[Simple-Smarthome By FajarTheGGman]");
  Serial.println("[--------------------]");
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
