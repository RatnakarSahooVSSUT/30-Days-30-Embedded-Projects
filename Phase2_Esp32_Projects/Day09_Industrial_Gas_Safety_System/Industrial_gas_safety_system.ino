#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define GAS_PIN 34
#define DHTPIN 4
#define DHTTYPE DHT22
#define FAN_LED 26
#define BUZZER 33
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(FAN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  int gasValue = analogRead(GAS_PIN);
  float temp = dht.readTemperature();
  bool fanOn = false;
  bool alarm = false;
  String status = "SAFE";
  if (gasValue > 2500){
    fanOn = true;
    alarm = true;
    status = "GAS DANGER!";
  }
  else if (gasValue > 1200){ 
    fanOn = true;
    status = "GAS HIGH";
  }
  if (temp > 35 && gasValue > 1200) {
    fanOn = true;
    alarm = true;
    status = "EMERGENCY!";
  }
  digitalWrite(FAN_LED, fanOn);
  if (alarm) {
    tone(BUZZER, 2000);
  } else {
    noTone(BUZZER);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Gas: ");
  display.println(gasValue);
  display.print("T:");
  display.print(temp);
  display.setCursor(0,50);
  display.setTextSize(2);
  display.println(status);
  display.display();

  Serial.print("Gas: "); Serial.print(gasValue);
  Serial.print("  Temp: "); Serial.print(temp);
  Serial.print("  Fan: "); Serial.print(fanOn);
  Serial.print("  Status: "); Serial.println(status);

  delay(1000);
}