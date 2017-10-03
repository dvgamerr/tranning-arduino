#include <ESP8266WiFi.h>
#include <PubSubClient.h>
WiFiClient wifiClient;
PubSubClient client(wifiClient);
void setup() {
  // connect to wifi
  client.setServer("iot.xenex.io", 1885);
  client.setCallback(mqttCallback);
}
void mqttCallback(char* topic, byte* payload, unsigned int len) {
  
}
void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      if (client.connect("TOUNO-MQTT-", "user", "password")) {
        client.subscribe("server-cmd");
        client.loop(); // เพื่อให้รับค่าจาก MQTT Server ได้
      } else {
        delay(5000);
      }
    } // while
  } else {
    client.publish("topic", "025030", true);
  }
}

