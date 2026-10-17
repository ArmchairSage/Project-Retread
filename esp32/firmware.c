#include <WiFi.h>
#include "AsyncUDP.h"

/* 
 *  This is a quick excercise to try receiving UDP datagrams
 *  flash the firmware to your ESP32 and open the serial console in the Arduino IDE to see the packets
 *  ptstanek
 */

// fill these in with your own network details
const char* SSID = "[ssid]"; 
const char* PASSWORD = "[password]";

bool led_state;

AsyncUDP udp;

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA); // WIFI_STA means the ESP32 will connect to a network rather than make a WAP
  WiFi.begin(SSID, PASSWORD);

  Serial.println("Connecting to Wi-Fi...");

  led_state = false;

  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("wifi failed. rebooting");
    delay(3000);
    ESP.restart();
  }
  
  Serial.print("Connected! IP ADDRESS: ");
  Serial.println(WiFi.localIP());

  if (udp.listen(1234)) {
    Serial.print("UDP listening on port 1234");
    
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      
      packet.printf("Got %lu bytes of data", (unsigned long)packet.length());
      led_state = true;
    });
  } else {
    Serial.println("Failed to start UDP listening!");
  }
}

void loop() { 
  delay(2000);
  if(WiFi.status() == WL_CONNECTED) {
    // Serial.println("Sending broadcast...");
    // udp.broadcast("test");
  }
}