#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define LDR_PIN 34
#define PIR_PIN 27

#define FAN_LED 26

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN,INPUT);
  pinMode(FAN_LED,OUTPUT);

  dht.begin();

  Wire.begin(21,22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  float temp= dht.readTemperature();
  float hum= dht.readHumidity();
  int lightLevel= analogRead(LDR_PIN);
  bool motion= digitalRead(PIR_PIN);

  bool fanOn= false;
  if (motion && (temp>30 || hum>75)) {
    fanOn= true;
  }
  digitalWrite(FAN_LED, fanOn);

  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C  ");
  Serial.print("Humidity: "); Serial.print(hum); Serial.print(" %  ");
  Serial.print("Light: "); Serial.print(lightLevel); Serial.print("  ");
  Serial.print("Motion: "); Serial.println(motion ? "YES" : "NO");

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(temp,1); display.print("C");

  display.setCursor(70,0);
  display.print(hum,0); display.print("%");

  display.setTextSize(2);
  display.setCursor(0,32);
  display.print("Light:");
  display.println(lightLevel);
  display.setCursor(0,48);
  display.print("Motion:");
  display.println(motion?"YES":"NO");
  display.display();
  delay(1000);
}