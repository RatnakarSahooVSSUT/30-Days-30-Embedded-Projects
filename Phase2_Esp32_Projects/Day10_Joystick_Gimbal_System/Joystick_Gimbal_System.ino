#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo panServo;
Servo tiltServo;

const int joyX= 34;
const int joyY= 35;
const int joySW= 25;
int panAngle= 90;
int tiltAngle= 90;

void setup(){
  Serial.begin(115200);
  Wire.begin(21, 22);  
  panServo.attach(18);
  tiltServo.attach(19);
  pinMode(joySW,INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println("OLED not found");
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("Day 10");
  display.display();
  delay(1500);

  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
}

void loop() {
  int xValue= analogRead(joyX);
  int yValue= analogRead(joyY);

  panAngle= map(xValue, 0, 4095, 180, 0);
  tiltAngle= map(yValue, 0, 4095, 0, 180);

  panServo.write(panAngle);
  tiltServo.write(tiltAngle);

  if (digitalRead(joySW)==LOW){
    panAngle= 90;
    tiltAngle= 90;
    panServo.write(panAngle);
    tiltServo.write(tiltAngle);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("CENTER");
    display.display();

    while(digitalRead(joySW)==LOW);
    delay(200);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Pan:");
  display.println(panAngle);
  display.setCursor(0, 25);
  display.print("Tilt:");
  display.println(tiltAngle);
  display.display();

  delay(100);
}