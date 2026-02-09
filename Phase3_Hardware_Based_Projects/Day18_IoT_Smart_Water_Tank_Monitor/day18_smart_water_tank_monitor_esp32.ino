#define BLYNK_TEMPLATE_ID "TMPL3STc6soRI"
#define BLYNK_TEMPLATE_NAME "Water level monitoring"
#define BLYNK_AUTH_TOKEN    "V9xfTbeALzLprRa6V2bbFlWhgvIq0-Cs"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define TRIG_PIN 5
#define ECHO_PIN 18
#define TANK_HEIGHT 13.0

#define LED_10   13
#define LED_30   12
#define LED_50   14
#define LED_70   27
#define LED_80   26

float readDistanceStable();
float singleDistanceRead();
void updateLEDs(float percent);
String levelStatus(float percent);

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_10, OUTPUT);
  pinMode(LED_30, OUTPUT);
  pinMode(LED_50, OUTPUT);
  pinMode(LED_70, OUTPUT);
  pinMode(LED_80, OUTPUT);

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("SMART WATER TANK");
  display.println("BLYNK CONNECTED");
  display.display();
  delay(1500);
}

void loop() {
  Blynk.run();

  float distance = readDistanceStable();
  if (distance <= 0 || distance > TANK_HEIGHT + 5) return;

  float waterLevel = TANK_HEIGHT - distance;
  if (waterLevel < 0) waterLevel = 0;
  if (waterLevel > TANK_HEIGHT) waterLevel = TANK_HEIGHT;

  float percent = (waterLevel / TANK_HEIGHT) * 100.0;
  String status = levelStatus(percent);

  updateLEDs(percent);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("SMART WATER TANK");
  display.println("----------------");

  display.print("Distance: ");
  display.print(distance, 1);
  display.println(" cm");

  display.print("Level: ");
  display.print(percent, 0);
  display.println(" %");

  display.print("Status: ");
  display.println(status);
  display.display();

  
  Blynk.virtualWrite(V0, percent);
  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V2, status); 

  delay(1200);
}

float readDistanceStable() {
  float sum = 0;
  int validReads = 0;

  for (int i = 0; i < 5; i++) {
    float d = singleDistanceRead();
    if (d > 0 && d < TANK_HEIGHT + 5) {
      sum += d;
      validReads++;
    }
    delay(30);
  }

  if (validReads == 0) return -1;
  return sum / validReads;
}

float singleDistanceRead() {
  long duration;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;

  return (duration * 0.034) / 2.0;
}

void updateLEDs(float p) {
  digitalWrite(LED_10, p >= 10);
  digitalWrite(LED_30, p >= 30);
  digitalWrite(LED_50, p >= 50);
  digitalWrite(LED_70, p >= 60);
  digitalWrite(LED_80, p >= 75);
}

String levelStatus(float p) {
  if (p < 10) return "EMPTY";
  else if (p < 30) return "LOW";
  else if (p < 50) return "MEDIUM";
  else if (p < 70) return "HIGH";
  else return "FULL";
}
