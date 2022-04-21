#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Servo.h>

#define motor1Pin1 14 //D5
#define motor1Pin2 12  //D6
#define en1 13  //D7

Servo servo;
int v = 0;

typedef struct message{
    int pot;
    int pot2;
} message;
message myMessage;

void printSerial(){
  myMessage.pot2 = map(myMessage.pot2, 0, 255, 42, 132);
  Serial.print(myMessage.pot);
  Serial.print(".");
  Serial.println(myMessage.pot2);
}

void mover(){
  if (myMessage.pot > 140) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    v = map(myMessage.pot, 140, 255, 100, 255);
  }
  else if (myMessage.pot < 130) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    v = map(myMessage.pot, 130, 0, 100, 255);
  }
    else {
    v = 0;
  }

  analogWrite(en1, v);
  
  servo.write(myMessage.pot2);
}

void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
   //Serial.println("Message received.");
   // We don't use mac to verify the sender
   // Let us transform the incomingData into our message structure
  memcpy(&myMessage, incomingData, sizeof(myMessage));

  printSerial();
  mover();
}
void setup() {
  Serial.begin(115200);
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(en1, OUTPUT);
  servo.attach(4); //D2
  
  WiFi.disconnect();
  ESP.eraseConfig();
  WiFi.mode(WIFI_STA);
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nESP-Now Receiver");
   
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // We can register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);
}

void loop() {}
