#include <ESP8266WiFi.h>
const char* ssid = "KEM-X";
const char* password = "123456789";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // รอจนกว่าจะต่อ WiFi ได้
    delay(500);
  }
  Serial.println("WiFi Connected");
}

WiFiClient client;
void loop() {
  if (!client.connect("iot.xenex.io", 80)) { return; }
  client.print("GET /upload HTTP/1.1\r\nHost: iot.xenex.io\r\nConnection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {// รอจนกว่าจะได้ข้อมูล แต่ไม่เกิน 5 วินาที
    if (millis() - timeout > 5000) {client.stop(); return;}
  }
  while(client.available()){ // อ่านข้อมูลที่ได้รับจนหมด
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}


