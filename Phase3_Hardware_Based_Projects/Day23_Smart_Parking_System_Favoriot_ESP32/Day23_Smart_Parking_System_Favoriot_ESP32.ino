#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "wifiname";
const char* password = "password";

const char* favoriotURL = "https://apiv2.favoriot.com/v2/streams";
const char* deviceAccessToken = "----------------------";
const char* deviceID = "------------------------";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Servo gateServo;
#define SERVO_PIN 25
#define SERVO_FREQ 50

#define GATE_CLOSED 0
#define GATE_OPEN   90

int currentGateAngle = GATE_CLOSED;
bool gateIsOpen = false;
unsigned long gateCloseTimer = 0;
bool waitingToClose = false;

#define IR_SLOT1     34
#define IR_SLOT2     35
#define IR_ENTRY     32
#define IR_GATE_SAFE 33

#define RED1     12
#define GREEN1   13
#define RED2     14
#define GREEN2   27
#define FULL_LED 26

#define BUTTON_PIN 4

unsigned long lastUpload = 0;
const unsigned long UPLOAD_INTERVAL = 60000;
const unsigned long MIN_UPLOAD_GAP  = 3000;

unsigned long slot1Start = 0;
unsigned long slot2Start = 0;
unsigned long slot1Duration = 0;
unsigned long slot2Duration = 0;

bool prevSlot1 = false;
bool prevSlot2 = false;
bool prevGate  = false;
int  prevAvailable = -1;

int gateObstructionFlag = 0;
int prevGateObstruction = 0;

void sendDataToFavoriot(bool slot1, bool slot2, int available,
                        int vehicleCount, bool gateOpen,
                        unsigned long dur1, unsigned long dur2,
                        String alert) {

  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(favoriotURL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", deviceAccessToken);

  String payload = "{";
  payload += "\"device_developer_id\":\"" + String(deviceID) + "\",";
  payload += "\"data\":{";
  payload += "\"slot1\":" + String(slot1);
  payload += ",\"slot2\":" + String(slot2);
  payload += ",\"available\":" + String(available);
  payload += ",\"vehicle_count\":" + String(vehicleCount);
  payload += ",\"gate\":\"" + String(gateOpen ? "OPEN" : "CLOSED") + "\"";
  payload += ",\"slot1_duration_sec\":" + String(dur1);
  payload += ",\"slot2_duration_sec\":" + String(dur2);
  payload += ",\"alert\":\"" + alert + "\"";
  payload += ",\"gate_obstruction\":" + String(gateObstructionFlag);
  payload += "}}";

  int httpCode = http.POST(payload);
  Serial.print("Favoriot Upload: ");
  Serial.println(httpCode);

  http.end();
}

void moveGateSlow(int targetAngle) {

  if (currentGateAngle < targetAngle) {
    for (int a = currentGateAngle; a <= targetAngle; a++) {
      gateServo.write(a);
      delay(15);
    }
    gateIsOpen = true;
  }
  else {
    for (int a = currentGateAngle; a >= targetAngle; a--) {

      if (digitalRead(IR_GATE_SAFE) == LOW) {
        moveGateSlow(GATE_OPEN);
        return;
      }

      gateServo.write(a);
      delay(15);
    }
    gateIsOpen = false;
  }

  currentGateAngle = targetAngle;
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  pinMode(IR_SLOT1, INPUT);
  pinMode(IR_SLOT2, INPUT);
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_GATE_SAFE, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(FULL_LED, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  gateServo.setPeriodHertz(SERVO_FREQ);
  gateServo.attach(SERVO_PIN, 500, 2400);
  gateServo.write(GATE_CLOSED);

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {

  bool slot1Occupied = digitalRead(IR_SLOT1) == LOW;
  bool slot2Occupied = digitalRead(IR_SLOT2) == LOW;
  bool entryDetected = digitalRead(IR_ENTRY) == LOW;
  bool gateUnsafe    = digitalRead(IR_GATE_SAFE) == LOW;
  bool manualOpen    = digitalRead(BUTTON_PIN) == LOW;

  digitalWrite(RED1, slot1Occupied);
  digitalWrite(GREEN1, !slot1Occupied);
  digitalWrite(RED2, slot2Occupied);
  digitalWrite(GREEN2, !slot2Occupied);

  int available = (!slot1Occupied) + (!slot2Occupied);
  bool parkingFull = (available == 0);
  digitalWrite(FULL_LED, parkingFull);

  bool shouldOpenGate = gateUnsafe || manualOpen || (!parkingFull && entryDetected);

  if (shouldOpenGate) {
    waitingToClose = false;
    moveGateSlow(GATE_OPEN);
  }
  else {
    if (!waitingToClose) {
      gateCloseTimer = millis();
      waitingToClose = true;
    }
    if (millis() - gateCloseTimer >= 1000) {
      moveGateSlow(GATE_CLOSED);
      waitingToClose = false;
    }
  }

  if (slot1Occupied && slot1Start == 0) slot1Start = millis();
  if (!slot1Occupied && slot1Start) {
    slot1Duration = (millis() - slot1Start) / 1000;
    slot1Start = 0;
  }

  if (slot2Occupied && slot2Start == 0) slot2Start = millis();
  if (!slot2Occupied && slot2Start) {
    slot2Duration = (millis() - slot2Start) / 1000;
    slot2Start = 0;
  }

  int vehicleCount = 2 - available;

  String alert = "NONE";
  if (gateUnsafe)       alert = "GATE_BLOCKED";
  else if (parkingFull) alert = "PARKING_FULL";

  gateObstructionFlag = gateUnsafe ? 1 : 0;

  unsigned long now = millis();

  bool stateChanged =
    slot1Occupied != prevSlot1 ||
    slot2Occupied != prevSlot2 ||
    available     != prevAvailable ||
    gateIsOpen    != prevGate ||
    gateObstructionFlag != prevGateObstruction;

  if ((stateChanged && now - lastUpload > MIN_UPLOAD_GAP) ||
      (now - lastUpload > UPLOAD_INTERVAL)) {

    sendDataToFavoriot(slot1Occupied, slot2Occupied, available,
                       vehicleCount, gateIsOpen,
                       slot1Duration, slot2Duration, alert);

    lastUpload = now;
    prevSlot1 = slot1Occupied;
    prevSlot2 = slot2Occupied;
    prevAvailable = available;
    prevGate = gateIsOpen;
    prevGateObstruction = gateObstructionFlag; 
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("SMART PARKING");
  display.print("S1: "); display.println(slot1Occupied ? "OCC" : "FREE");
  display.print("S2: "); display.println(slot2Occupied ? "OCC" : "FREE");
  display.print("Avail: "); display.print(available); display.println("/2");
  display.print("Gate: "); display.println(gateIsOpen ? "OPEN" : "CLOSED");
  display.display();

  delay(200);
}
