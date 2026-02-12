#define BLYNK_TEMPLATE_ID "TMPL3JJDEOK40"
#define BLYNK_TEMPLATE_NAME "ESP32 Access Control System"
#define BLYNK_AUTH_TOKEN    "DMV-GiNBie3Dda97-qAAlJc6EB-6pabU"

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Keypad.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Servo lockServo;
#define SERVO_PIN 18
#define LOCK_POS   0
#define UNLOCK_POS 90

#define BUZZER_PIN 19

#define GREEN_LED 4
#define RED_LED   5

#define VP_LOCK_STATUS     V0
#define VP_REMOTE_UNLOCK  V1
#define VP_WRONG_ATTEMPTS  V2
#define VP_LOCKOUT_STATUS  V3
#define VP_LAST_ACCESS     V4
#define VP_RESET_LOCKOUT   V5

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte colPins[COLS] = {13, 12, 14, 27};
byte rowPins[ROWS] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String storedPIN = "1234";
String enteredPIN = "";

int attempts = 0;
bool locked = false;
unsigned long lockStartTime = 0;
const unsigned long LOCK_TIME = 10000;

bool resetMode = false;
String resetSequence = "";

String maskPIN(int len) {
  String s = "";
  for (int i = 0; i < len; i++) s += "*";
  return s;
}

void buzzerON()  { digitalWrite(BUZZER_PIN, LOW); }
void buzzerOFF() { digitalWrite(BUZZER_PIN, HIGH); }

void keyClick() {
  buzzerON(); delay(40); buzzerOFF();
}

void beep(int times) {
  for (int i = 0; i < times; i++) {
    buzzerON(); delay(150);
    buzzerOFF(); delay(150);
  }
}

void redBlinkBeep(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(RED_LED, HIGH);
    buzzerON(); delay(200);
    digitalWrite(RED_LED, LOW);
    buzzerOFF(); delay(200);
  }
  digitalWrite(RED_LED, HIGH);
}

void showMessage(String l1, String l2 = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(l1);
  if (l2 != "") {
    display.setCursor(0, 20);
    display.println(l2);
  }
  display.display();
}

void unlockDoor(String source) {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  lockServo.write(UNLOCK_POS);
  beep(2);

  showMessage("Access Granted");
  Blynk.virtualWrite(VP_LAST_ACCESS, source);
  Blynk.virtualWrite(VP_LOCK_STATUS, 1);

  delay(3000);

  lockServo.write(LOCK_POS);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  showMessage("Enter PIN");
  Blynk.virtualWrite(VP_LOCK_STATUS, 0);
}

void enterResetMode() {
  resetMode = true;
  enteredPIN = "";
  attempts = 0;
  showMessage("Reset PIN", "Enter New PIN");
}


BLYNK_WRITE(VP_REMOTE_UNLOCK) {
  if (param.asInt() == 1 && !locked) {
    unlockDoor("Remote Unlock");
  }
  Blynk.virtualWrite(VP_REMOTE_UNLOCK, 0);
}

BLYNK_WRITE(VP_RESET_LOCKOUT) {
  if (param.asInt() == 1) {
    locked = false;
    attempts = 0;
    showMessage("Unlocked", "Enter PIN");
    Blynk.virtualWrite(VP_LOCKOUT_STATUS, 0);
    Blynk.virtualWrite(VP_WRONG_ATTEMPTS, 0);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  buzzerOFF();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);

  lockServo.attach(SERVO_PIN);
  lockServo.write(LOCK_POS);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showMessage("Connecting WiFi");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  showMessage("System Ready", "Enter PIN");
  Blynk.virtualWrite(VP_LOCK_STATUS, 0);
  Blynk.virtualWrite(VP_LOCKOUT_STATUS, 0);
}

void loop() {
  Blynk.run();

  if (locked) {
    if (millis() - lockStartTime >= LOCK_TIME) {
      locked = false;
      attempts = 0;
      showMessage("Unlocked", "Enter PIN");
      Blynk.virtualWrite(VP_LOCKOUT_STATUS, 0);
      Blynk.virtualWrite(VP_WRONG_ATTEMPTS, 0);
    }
    return;
  }

  char key = keypad.getKey();

  if (key) {
    keyClick();

    resetSequence += key;
    if (resetSequence.length() > 3)
      resetSequence.remove(0, 1);

    if (resetSequence == "ABA") {
      enterResetMode();
      resetSequence = "";
      return;
    }

    if (resetMode) {
      if (key == '#') {
        storedPIN = enteredPIN;
        resetMode = false;
        showMessage("PIN Updated");
        delay(1500);
        showMessage("Enter PIN");
      } else {
        enteredPIN += key;
        showMessage("New PIN", maskPIN(enteredPIN.length()));
      }
      return;
    }

    if (key == '*') {
      enteredPIN = "";
      showMessage("Cleared", "Enter PIN");
    }

    else if (key == '#') {
      if (enteredPIN == storedPIN) {
        attempts = 0;
        unlockDoor("Keypad");
        Blynk.virtualWrite(VP_WRONG_ATTEMPTS, 0);
      } else {
        attempts++;
        Blynk.virtualWrite(VP_WRONG_ATTEMPTS, attempts);
        Blynk.virtualWrite(VP_LAST_ACCESS, "Wrong PIN");

        if (attempts < 3) {
          redBlinkBeep(2);
          showMessage("Wrong PIN");
          delay(1200);
          showMessage("Enter PIN");
        } else {
          redBlinkBeep(5);
          locked = true;
          lockStartTime = millis();
          showMessage("System Locked");
          Blynk.virtualWrite(VP_LOCKOUT_STATUS, 1);
        }
      }
      enteredPIN = "";
    }

    else {
      enteredPIN += key;
      showMessage("Enter PIN", maskPIN(enteredPIN.length()));
    }
  }
}
