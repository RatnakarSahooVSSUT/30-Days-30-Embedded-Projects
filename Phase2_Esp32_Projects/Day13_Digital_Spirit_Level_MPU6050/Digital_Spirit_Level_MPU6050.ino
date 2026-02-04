#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

LiquidCrystal_I2C lcd(0X27,16,2);
MPU6050   mpu;

int ledlevel =14;
int ledleft =27;
int ledright =26;
int ledforward =25;
int ledback =33;

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);
  lcd.init();
  lcd.backlight();
  mpu.initialize();

  pinMode(ledlevel,OUTPUT);
  pinMode(ledleft,OUTPUT);
  pinMode(ledright,OUTPUT);
  pinMode(ledforward,OUTPUT);
  pinMode(ledback,OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("Digital Level:");
  delay(1500);
  lcd.clear();
}

void loop() {
  int16_t ax,ay,az;
  mpu.getAcceleration(&ax, &ay, &az);

  float angleX = atan2(ay, az)*180 /PI;
  float angleY = atan2(ax, az)*180 /PI;

  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.print(angleX,1);
  lcd.print((char)223);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("Y:");
  lcd.print(angleY,1);
  lcd.print((char)223);
  lcd.print("   ");

  digitalWrite(ledlevel, LOW);
  digitalWrite(ledleft, LOW);
  digitalWrite(ledright, LOW);
  digitalWrite(ledforward, LOW);
  digitalWrite(ledback, LOW);

  if(abs(angleX)<3 && abs(angleY)<3){
    digitalWrite(ledlevel, HIGH);
  } else{
    if(angleX>3) digitalWrite(ledforward, HIGH);
    if(angleX<-3) digitalWrite(ledback, HIGH);
    if(angleY>3) digitalWrite(ledright, HIGH);
    if(angleY<-3) digitalWrite(ledleft, HIGH);
  }

  delay(300);

}