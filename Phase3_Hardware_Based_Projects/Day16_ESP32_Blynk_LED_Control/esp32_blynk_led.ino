#define BLYNK_TEMPLATE_ID   "TMPL3oyaIiudG"
#define BLYNK_TEMPLATE_NAME "ESP32 LED"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "v4mp8uKciUM86otaCtKxCk3O9kjX5bKd";

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define LED_PIN 23

BLYNK_WRITE(V0) {
  int ledState = param.asInt();
  digitalWrite(LED_PIN, ledState);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
