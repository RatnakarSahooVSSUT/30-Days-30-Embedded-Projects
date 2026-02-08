
#define BLYNK_TEMPLATE_ID "TMPL3qzgTLxLI"
#define BLYNK_TEMPLATE_NAME "Traffic System"
#define BLYNK_AUTH_TOKEN "c_LeMyadMESrr7SnS8oB1zasVaK5vJDy"

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

#define TRAFFIC_RED     14
#define TRAFFIC_YELLOW  27
#define TRAFFIC_GREEN   26

#define PED_RED     25
#define PED_GREEN   33

#define PED_BUTTON       32
#define EMERGENCY_BUTTON 13

volatile bool emergencyActive = false;
volatile bool pedestrianRequest = false;

bool smartDelay(unsigned long duration);
void normalTraffic();
void pedestrianCrossing();
void emergencyMode();
void showStatus(String traffic, String pedestrian, String emergency);

BLYNK_WRITE(V0) {
  if (!emergencyActive) {
    pedestrianRequest = true;
  }
  Blynk.virtualWrite(V0, 0);
}


BLYNK_WRITE(V1) {
  emergencyActive = param.asInt();
  Blynk.virtualWrite(V4, emergencyActive ? 1 : 0);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRAFFIC_RED, OUTPUT);
  pinMode(TRAFFIC_YELLOW, OUTPUT);
  pinMode(TRAFFIC_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);

  pinMode(PED_BUTTON, INPUT_PULLUP);
  pinMode(EMERGENCY_BUTTON, INPUT_PULLUP);

  digitalWrite(PED_RED, HIGH);
  digitalWrite(PED_GREEN, LOW);

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  showStatus("NORMAL", "WAIT", "NO");
}

void loop() {
  Blynk.run();

  if (digitalRead(EMERGENCY_BUTTON) == LOW || emergencyActive) {
    emergencyActive = true;
    Blynk.virtualWrite(V4, 1);
    emergencyMode();
    return;
  }

  if (!emergencyActive &&
      (digitalRead(PED_BUTTON) == LOW || pedestrianRequest)) {
    pedestrianRequest = false;
    pedestrianCrossing();
    return;
  }

  normalTraffic();
}


void normalTraffic() {
  showStatus("GO", "WAIT", "NO");
  Blynk.virtualWrite(V2, "GO");
  Blynk.virtualWrite(V3, 0);

  digitalWrite(TRAFFIC_GREEN, HIGH);
  digitalWrite(TRAFFIC_YELLOW, LOW);
  digitalWrite(TRAFFIC_RED, LOW);
  if (!smartDelay(5000)) return;

  showStatus("SLOW", "WAIT", "NO");
  Blynk.virtualWrite(V2, "SLOW");

  digitalWrite(TRAFFIC_GREEN, LOW);
  digitalWrite(TRAFFIC_YELLOW, HIGH);
  if (!smartDelay(2000)) return;

  showStatus("STOP", "WAIT", "NO");
  Blynk.virtualWrite(V2, "STOP");

  digitalWrite(TRAFFIC_YELLOW, LOW);
  digitalWrite(TRAFFIC_RED, HIGH);
  smartDelay(5000);
}


void pedestrianCrossing() {
  showStatus("STOP", "WALK", "NO");
  Blynk.virtualWrite(V2, "STOP");
  Blynk.virtualWrite(V3, 1);

  digitalWrite(TRAFFIC_GREEN, LOW);
  digitalWrite(TRAFFIC_YELLOW, LOW);
  digitalWrite(TRAFFIC_RED, HIGH);

  digitalWrite(PED_RED, LOW);
  digitalWrite(PED_GREEN, HIGH);
  smartDelay(5000);

  digitalWrite(PED_GREEN, LOW);
  digitalWrite(PED_RED, HIGH);
  Blynk.virtualWrite(V3, 0);
}

void emergencyMode() {
  showStatus("GO", "STOP", "YES");
  Blynk.virtualWrite(V2, "GO");
  Blynk.virtualWrite(V3, 0);

  digitalWrite(TRAFFIC_RED, LOW);
  digitalWrite(TRAFFIC_YELLOW, LOW);
  digitalWrite(TRAFFIC_GREEN, HIGH);

  digitalWrite(PED_GREEN, LOW);
  digitalWrite(PED_RED, HIGH);

  smartDelay(5000);
}


bool smartDelay(unsigned long duration) {
  unsigned long start = millis();

  while (millis() - start < duration) {
    Blynk.run();

    if (digitalRead(EMERGENCY_BUTTON) == LOW || emergencyActive) {
      emergencyActive = true;
      emergencyMode();
      return false;
    }


    if (!emergencyActive &&
        (digitalRead(PED_BUTTON) == LOW || pedestrianRequest)) {
      pedestrianRequest = false;
      pedestrianCrossing();
      return false;
    }
  }
  return true;
}

void showStatus(String traffic, String pedestrian, String emergency) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("TRAFFIC SYSTEM");
  display.println("----------------");
  display.print("Traffic: ");
  display.println(traffic);
  display.print("Pedestrian: ");
  display.println(pedestrian);
  display.print("Emergency: ");
  display.println(emergency);

  display.display();
}
