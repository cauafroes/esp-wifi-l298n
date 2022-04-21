/**
 * ESP-NOW: ESP32 Broadcast with ESP-Now
 * 
 * 
*/
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#define potPin 35
#define pot2Pin 34

// ESP8266 Mac address
uint8_t mac_peer1[] = {0x34, 0x94, 0x54, 0x62, 0x78, 0x92};
esp_now_peer_info_t peer1;
int i, potValue = 0;

typedef struct message {
   //bool led;
   int pot;
   int pot2;
};
struct message myMessage;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("ESP32 ESP-Now Broadcast");
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  memcpy(peer1.peer_addr, mac_peer1, 6);
  peer1.channel = 1;
  peer1.encrypt = 0;
  // Register the peer
  Serial.println("Registering peer 1");
  if ( esp_now_add_peer(&peer1) == ESP_OK) {
    Serial.println("Peer 1 added");
  }
}
void loop() {
  /*
  myMessage.red = random(0, 254);
  myMessage.green = random(0, 254);
  myMessage.blue = random(0, 254);
  */

  /*
  if(myMessage.led){
    myMessage.led = 0;
  } else {
    myMessage.led = 1;
  }
  */
  potValue = analogRead(potPin);
  potValue = map(potValue, 4095, 0, 0, 255);
  myMessage.pot = potValue;

  potValue = analogRead(pot2Pin);
  potValue = map(potValue, 4095, 0, 0, 255);
  myMessage.pot2 = potValue;
  
  //Serial.print("Send a new message: ");
  //Serial.println(myMessage.pot);

  esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
  delay(20);
}
