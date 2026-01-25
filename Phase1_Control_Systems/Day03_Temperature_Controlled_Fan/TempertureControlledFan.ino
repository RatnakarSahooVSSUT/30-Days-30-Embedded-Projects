#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 4, 10, 13);

const int tempPin=A0;
const int potPin=A1;
const int fanPin=9;
const int buttonPin=2;
const int buzzerPin=8;

int redPin=3;
const int greenPin=5;
const int bluePin=6;

bool autoMode=true;
bool lastButtonState=LOW;
bool buttonState=HIGH;
bool lastButtonReading=HIGH;

unsigned long lastDebounceTime=0;
const unsigned long debounceDelay=50;

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  lcd.begin(16,2);
  Serial.begin(9600);
}

void checkButton(){
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (lastButtonReading == HIGH && reading == LOW) {
      autoMode = !autoMode;
    }
    buttonState = reading;
  }
  lastButtonReading = reading;
}

void loop() {

  checkButton();

  bool buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && lastButtonState == LOW) {
    autoMode = !autoMode;
    delay(300);
  }
  lastButtonState = buttonState;

  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100;

  int fanSpeed = 0;

  if (autoMode) {
    if (temperatureC < 25) fanSpeed = 0;
    else if (temperatureC < 30) fanSpeed = 80;
    else if (temperatureC < 35) fanSpeed = 100;
    else if (temperatureC < 40) fanSpeed = 140;
    else if (temperatureC < 45) fanSpeed = 180;
    else fanSpeed = 255;
  }

  else {
    int potValue = analogRead(potPin);
    fanSpeed = map(potValue, 0, 1023, 255, 0);
    fanSpeed = constrain(fanSpeed, 0, 255);
  }

  analogWrite(fanPin, fanSpeed);

  if (temperatureC < 25){ 
    setColor(0, 0, 255); 
  }
  else if (temperatureC < 40){
    setColor(0, 255, 0);
  }
  else {
    setColor(255, 0, 0);
  }

  if (temperatureC > 50) {
    tone(buzzerPin, 1000);
  }
  else {
    noTone(buzzerPin);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperatureC, 1);
  lcd.print((char)178);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(autoMode ? "Mode:AUTO " : "Mode:MANUAL");

  int percent = map(fanSpeed, 0, 255, 0, 100);
  lcd.setCursor(11, 1);
  lcd.print(percent);
  lcd.print("%");

  delay(1000);
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}