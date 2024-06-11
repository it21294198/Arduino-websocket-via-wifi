#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "webpage.h"

const char *ssid = "";
const char *password = "";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

const int bulbPin = 4;

void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("[%u] Connection from %s\n", num, ip.toString().c_str());
    break;
  }
  case WStype_TEXT:
    if (strcmp((char *)payload, "ON") == 0)
    {
      digitalWrite(bulbPin, HIGH);
    }
    else if (strcmp((char *)payload, "OFF") == 0)
    {
      digitalWrite(bulbPin, LOW);
    }
    break;
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(bulbPin, OUTPUT);
  digitalWrite(bulbPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []()
            { server.send_P(200, "text/html", index_html); });

  webSocket.begin();
  webSocket.onEvent(handleWebSocketMessage);

  server.begin();
}

void loop()
{
  webSocket.loop();
  server.handleClient();
}
