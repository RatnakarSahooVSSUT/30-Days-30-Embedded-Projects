#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int ledPins[4]= {23,22,21,19};
const int buttonPins[4]= {32,33,25,26};
const int buzzer = 18;
int sequence[20];
int level= 0;
int highScore= 0;

void setup(){
  Serial.begin(115200);

  for(int i = 0; i<4; i++){
    pinMode(ledPins[i],OUTPUT);
    pinMode(buttonPins[i],INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
  randomSeed(micros());

  Wire.begin(4,5);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Simon Says");
  lcd.setCursor(0, 1);
  lcd.print("Get Ready!");
  delay(1500);
  lcd.clear();
}

void playTone(int duration){
  tone(buzzer,1000,duration);
}

void updateLCD(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(level - 1);

  lcd.setCursor(0, 1);
  lcd.print("Highest: ");
  lcd.print(highScore);
}

void showSequence(){
  int currentScore= level - 1;
  if(currentScore> highScore) {
    highScore = currentScore;
  }

  updateLCD();
  for(int i = 0; i < level; i++) {
    digitalWrite(ledPins[sequence[i]],HIGH);
    playTone(200);
    delay(400);
    digitalWrite(ledPins[sequence[i]],LOW);
    delay(200);
  }
}

int getButtonPressed(){
  while(true) {
    for(int i = 0; i<4; i++) {
      if(digitalRead(buttonPins[i])==LOW){
        delay(200);
        return i;
      }
    }
  }
}

void gameOver(){
  int score= level-1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Game Over!");
  lcd.setCursor(0,1);
  lcd.print("Score: ");
  lcd.print(score);

  for(int i = 0; i<3; i++){
    tone(buzzer,300,200);
    delay(300);
  }

  delay(2000);
  level=0;
}

void loop(){
  sequence[level]= random(0, 4);
  level++;

  showSequence();

  for(int i = 0; i<level; i++){
    int btn= getButtonPressed();

    digitalWrite(ledPins[btn],HIGH);
    playTone(150);
    delay(200);
    digitalWrite(ledPins[btn],LOW);

    if(btn != sequence[i]){
      gameOver();
      return;
    }
  }
  delay(800);
}
