#define BLYNK_TEMPLATE_ID "TMPL3z8zmHOS6"
#define BLYNK_TEMPLATE_NAME "Environmental Monitoring"
#define BLYNK_AUTH_TOKEN    "-fwZ-RuAACwespJSscrzMNC5VnBYUFZj"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LED_GREEN 13
#define LED_YELLOW 12
#define LED_RED 14

BlynkTimer timer;

void readAndSendData() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT11 Read Failed");
    return;
  }

  String tempStatus, humStatus;

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);

  if (temperature < 30) {
    digitalWrite(LED_GREEN, HIGH);
    tempStatus = "NORMAL";
  } 
  else if (temperature <= 35) {
    digitalWrite(LED_YELLOW, HIGH);
    tempStatus = "WARNING";
  } 
  else {
    digitalWrite(LED_RED, HIGH);
    tempStatus = "CRITICAL";
  }

  if (humidity >= 30 && humidity <= 60) {
    humStatus = "OK";
  } 
  else if (humidity < 30) {
    humStatus = "LOW";
  } 
  else {
    humStatus = "HIGH";
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("Env Monitoring");

  display.setCursor(0, 16);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" oC");

  display.setCursor(0, 28);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 44);
  display.print("T:");
  display.print(tempStatus);
  display.print(" H:");
  display.println(humStatus);

  display.display();

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, tempStatus);
  Blynk.virtualWrite(V3, humStatus);

  unsigned long uptimeSec = millis() / 1000;
  Blynk.virtualWrite(V4, String(uptimeSec) + " sec");

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" oC | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | ");
  Serial.print(tempStatus);
  Serial.print(" / ");
  Serial.println(humStatus);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not detected");
    while (true);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connecting WiFi...");
  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2500L, readAndSendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
