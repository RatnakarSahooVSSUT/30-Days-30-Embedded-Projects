#include <DHT.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Sensors
#define DHTPIN 15
#define DHTTYPE DHT22
#define GAS_PIN 34
#define LDR_PIN 35
#define BUTTON 4

// Actuators
#define RELAY_FAN 19
#define SERVO_PIN 13
#define BUZZER 18

// RGB LED
#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

DHT dht(DHTPIN, DHTTYPE);
Servo ventServo;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

bool manualMode = false;

void setLED(bool r, bool g, bool b) {
  digitalWrite(RED_LED, r);
  digitalWrite(GREEN_LED, g);
  digitalWrite(BLUE_LED, b);
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_FAN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  ventServo.attach(SERVO_PIN);
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("System Started");
}

void loop() {

  // ----- Manual override toggle -----
  if (digitalRead(BUTTON) == LOW) {
    manualMode = !manualMode;
    delay(300);
  }

  // ----- Read sensors -----
  float temperature = dht.readTemperature();
  int gasValue = analogRead(GAS_PIN);
  int lightValue = analogRead(LDR_PIN);

  String mode = "NORMAL";

  // ----- Default state -----
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(BUZZER, LOW);
  ventServo.write(0);
  setLED(LOW, HIGH, LOW);  // Green

  // ----- Automatic control -----
  if (!manualMode) {

    if (gasValue > 2500) {
      mode = "DANGER";
      digitalWrite(RELAY_FAN, HIGH);
      ventServo.write(90);
      digitalWrite(BUZZER, HIGH);
      setLED(HIGH, LOW, LOW); // Red
    }
    else if (temperature >= 32 || lightValue < 1500) {
      mode = "WARNING";
      digitalWrite(RELAY_FAN, HIGH);
      ventServo.write(45);
      setLED(HIGH, HIGH, LOW); // Yellow
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(BUZZER, LOW);
    }

  } else {
    mode = "MANUAL";
    setLED(LOW, LOW, HIGH); // Blue
  }

  // ----- OLED Display -----
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.print("Temp: "); display.print(temperature); display.println(" oC");
  display.print("Gas : "); display.println(gasValue);
  display.print("Light: "); display.println(lightValue);
  display.print("Mode: "); display.println(mode);

  display.display();

  delay(1000);
}
