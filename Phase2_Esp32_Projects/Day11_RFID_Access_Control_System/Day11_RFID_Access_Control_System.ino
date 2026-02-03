#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#define SS_PIN 5
#define RST_PIN 22
MFRC522 rfid(SS_PIN, RST_PIN);

Servo doorServo;

const int buzzer = 12;
const int servoPin = 13;

byte allowedUID[4] = {0xAA, 0xBB, 0xCC, 0xDD};

void beepTone(int freq, int duration) {
  int delayTime = 1000000 / freq / 2;
  long cycles = (long)freq * duration / 1000;

  for (long i = 0; i < cycles; i++) {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(delayTime);
  }
}

void beepSuccess() {
  beepTone(1500, 200);
}

void beepError() {
  beepTone(400, 800);
}

void setup() {
  Serial.begin(115200);

  SPI.begin(18, 19, 23, 5);
  rfid.PCD_Init();

  doorServo.setPeriodHertz(50);
  doorServo.attach(servoPin, 500, 2400);
  doorServo.write(0);

  pinMode(buzzer, OUTPUT);

  Serial.println("Scan RFID Card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  bool accessGranted = true;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
    if (rfid.uid.uidByte[i] != allowedUID[i]) accessGranted = false;
  }
  Serial.println();

  if (accessGranted) {
    Serial.println("ACCESS GRANTED");
    beepSuccess();
    doorServo.write(90);
    delay(3000);
    doorServo.write(0);
  } else {
    Serial.println("ACCESS DENIED");
    beepError();
  }

  rfid.PICC_HaltA();
}