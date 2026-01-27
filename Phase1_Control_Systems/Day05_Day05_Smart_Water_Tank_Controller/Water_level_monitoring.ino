#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,A0,A1,A2);

const int trigPin=2;
const int echoPin=3;

const int lowLED=4;
const int midLED=5;
const int fullLED=6;

const int motorPin=9;

const int modeButton=8;
const int manualMotorButton=7;

long duration;
float distance;

bool motorState=false;
bool autoMode=true;

bool lastModeButtonState=HIGH;
bool lastManualButtonState=HIGH;

void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  pinMode(lowLED,OUTPUT);
  pinMode(midLED,OUTPUT);
  pinMode(fullLED,OUTPUT);

  pinMode(motorPin,OUTPUT);

  pinMode(modeButton,INPUT_PULLUP);
  pinMode(manualMotorButton,INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("Tank Controller");
  delay(2000);
  lcd.clear();
}

float getDistance(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration*0.034/2;
}

void checkModeButton(){
  bool current=digitalRead(modeButton);
  if (lastModeButtonState==HIGH && current==LOW) {
    autoMode=!autoMode;
  }
  lastModeButtonState=current;
}

void checkManualMotorButton(){
  bool current=digitalRead(manualMotorButton);
  if (lastManualButtonState==HIGH && current==LOW && !autoMode){
    motorState = !motorState;
  }
  lastManualButtonState=current;
}

void loop(){
  checkModeButton();
  checkManualMotorButton();

  distance=getDistance();

  String level;

  if (distance>40){
    level="LOW";
    digitalWrite(lowLED,HIGH);
    digitalWrite(midLED,LOW);
    digitalWrite(fullLED,LOW);
  }
  else if (distance>20){
    level="MEDIUM";
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, HIGH);
    digitalWrite(fullLED, LOW);
  }
  else {
    level="FULL";
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, LOW);
    digitalWrite(fullLED, HIGH);
  }

  if (autoMode){
    if (distance > 40) motorState = true;
    if (distance <= 40) motorState = false;
  }

  digitalWrite(motorPin, motorState);

  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.print(level);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Motor:");
  lcd.print(motorState ? "ON " : "OFF");
  lcd.print(" Mode:");
  lcd.print(autoMode ? "A" : "M");

  delay(300);
}
