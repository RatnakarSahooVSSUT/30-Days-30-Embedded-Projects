#define BLYNK_TEMPLATE_ID "TMPL3JJDEOK40"
#define BLYNK_TEMPLATE_NAME "ESP32 Access Control System"
#define BLYNK_AUTH_TOKEN "DMV-GiNBie3Dda97-qAAlJc6EB-6pabU"

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <time.h>


const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 5 * 3600 + 1800; 
const int daylightOffset_sec = 0;

#define TOUCH_PIN 4
#define BUZZER_PIN 18 
#define RED_LED_PIN 19
#define GREEN_LED_PIN 23
#define SERVO_PIN 26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Servo lockServo;

int PASSWORD[4] = {2, 4, 1, 3};
int changePattern[4] = {2, 2, 2, 2};
int enteredPIN[4];

int currentPin = 0;
int wrongAttempts = 0;
bool locked = false;
bool changeMode = false;

bool touchState = false;
bool lastTouchState = false;

unsigned long touchStartTime = 0;
unsigned long liveSeconds = 0;
unsigned long lockoutStart = 0;

String getTimestamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Time not set";
  }
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%d %b %Y %H:%M:%S", &timeinfo);
  return String(buffer);
}

void setup() {
  Serial.begin(115200);

  pinMode(TOUCH_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);

  lockServo.attach(SERVO_PIN);
  lockServo.write(90);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(1000);

  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V4, "System Ready @ " + getTimestamp());

  showEnterScreen();
}

void loop() {
  Blynk.run();

  if (locked) {
    if (millis() - lockoutStart >= 10000) {
      locked = false;
      wrongAttempts = 0;
      resetSystem();
    }
    return;
  }

  touchState = digitalRead(TOUCH_PIN);

  if (touchState && !lastTouchState) {
    touchStartTime = millis();
  }

  if (touchState) {
    liveSeconds = (millis() - touchStartTime) / 1000;
    if (liveSeconds > 9) liveSeconds = 9;
    showCountingScreen();
  }

  if (!touchState && lastTouchState) {
    enteredPIN[currentPin] = liveSeconds;
    shortBeep();
    currentPin++;
    liveSeconds = 0;

    if (currentPin >= 4) processPIN();
    else showEnterScreen();
  }

  lastTouchState = touchState;
  delay(30);
}

BLYNK_WRITE(V1) { 
  if (param.asInt() == 1 && !locked) {
    unlockSuccess("Unlocked (Remote)");
  }
}

BLYNK_WRITE(V5) {
  if (param.asInt() == 1) {
    locked = false;
    wrongAttempts = 0;
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, "Lockout Reset @ " + getTimestamp());
    resetSystem();
  }
}

void processPIN() {
  if (matchArray(enteredPIN, changePattern)) {
    changeMode = true;
    currentPin = 0;
    showMessage("SET NEW PIN");
    delay(1500);
    return;
  }

  if (changeMode) {
    for (int i = 0; i < 4; i++) PASSWORD[i] = enteredPIN[i];
    changeMode = false;
    longBeep();
    Blynk.virtualWrite(V4, "PIN Changed @ " + getTimestamp());
    resetSystem();
    return;
  }

  if (matchArray(enteredPIN, PASSWORD)) {
    unlockSuccess("Unlocked (Touch)");
  } else {
    wrongAttempts++;
    Blynk.virtualWrite(V2, wrongAttempts);
    Blynk.virtualWrite(V4, "Wrong PIN @ " + getTimestamp());

    if (wrongAttempts >= 3) lockout();
    else wrongFeedback();
  }
}

void unlockSuccess(const char* source) {
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  lockServo.write(0);

  Blynk.virtualWrite(V0, 1);
  Blynk.virtualWrite(V4, String(source) + " @ " + getTimestamp());

  longBeep();
  showMessage("UNLOCKED");
  delay(3000);

  resetSystem();
}

void wrongFeedback() {
  blinkRed(3);
  beepMultiple(3);
  showMessage("WRONG");
  delay(1500);
  resetSystem();
}

void lockout() {
  locked = true;
  lockoutStart = millis();

  Blynk.virtualWrite(V3, 1);
  Blynk.virtualWrite(V4, "LOCKED OUT @ " + getTimestamp());

  blinkRed(5);
  beepMultiple(5);
  showMessage("LOCKED");
  lockServo.write(90);
}

void resetSystem() {
  currentPin = 0;
  for (int i = 0; i < 4; i++) enteredPIN[i] = 0;

  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  lockServo.write(90);

  Blynk.virtualWrite(V0, 0);
  showEnterScreen();
}

bool matchArray(int *a, int *b) {
  for (int i = 0; i < 4; i++) if (a[i] != b[i]) return false;
  return true;
}

void shortBeep() {
  digitalWrite(BUZZER_PIN, LOW); delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
}

void longBeep() {
  digitalWrite(BUZZER_PIN, LOW); delay(600);
  digitalWrite(BUZZER_PIN, HIGH);
}

void beepMultiple(int n) {
  for (int i = 0; i < n; i++) { shortBeep(); delay(150); }
}

void blinkRed(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(RED_LED_PIN, LOW); delay(150);
    digitalWrite(RED_LED_PIN, HIGH); delay(150);
  }
}

void showEnterScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Enter PIN");

  for (int i = 0; i < 4; i++) {
    display.setCursor(0, 16 + i * 12);
    display.print("PIN");
    display.print(i + 1);
    display.print(": ");
    if (i < currentPin) display.println(enteredPIN[i]);
    else display.println("_");
  }
  display.display();
}

void showCountingScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hold Touch");

  display.setTextSize(3);
  display.setCursor(40, 28);
  display.print(liveSeconds);
  display.display();
}

void showMessage(const char *msg) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 25);
  display.println(msg);
  display.display();
}
