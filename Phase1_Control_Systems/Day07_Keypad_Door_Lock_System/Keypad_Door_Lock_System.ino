#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,A0,A1,A2,A3);

Servo doorServo;

const byte ROWS= 4;
const byte COLS= 4;

char keys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS]={9,8,7,6};
byte colPins[COLS]={5,4,3,2};

Keypad keypad= Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

String password= "1234";
String input= "";

const int greenLED= A4;
const int redLED= A5;
const int buzzer= 13;

int wrongAttempts= 0;
bool lockedOut= false;

void setup(){
  doorServo.attach(10);
  doorServo.write(90);

  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(buzzer,OUTPUT);

  digitalWrite(redLED, HIGH);

  lcd.begin(16,2);
  lcd.print("Enter Password");
}

void loop(){

  if (lockedOut) return;
  
  char key= keypad.getKey();

  if (key){
    if (key =='#'){
      checkPassword();
    }
    else if(key =='*'){
      clearInput();
    }
    else if(key =='A'){
      changePassword();
    }
    else{
      input+=key;
      lcd.setCursor(input.length()-1,1);
      lcd.print("*");
    }
  }
}

void clearInput(){
  input ="";
  lcd.clear();
  lcd.print("Cleared");
  delay(800);
  lcd.clear();
  lcd.print("Enter Password");
  digitalWrite(redLED, HIGH);
}

void checkPassword(){
  lcd.clear();

  if(input== password){
    lcd.print("Access Granted");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    tone(buzzer, 1000, 300);

    doorServo.write(0);
    delay(5000);
    doorServo.write(90);

    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    wrongAttempts=0;
  }
  else{
    lcd.print("Wrong Password");
    tone(buzzer,200,800);
    delay(1500);

    wrongAttempts++;
    if(wrongAttempts >= 3) alarmLockout();
  }

  input = "";
  delay(1000);
  lcd.clear();
  lcd.print("Enter Password");
  digitalWrite(redLED, HIGH);
}

void alarmLockout(){
  lcd.clear();
  lcd.print("SYSTEM LOCKED!");

  for (int i=0; i<10; i++){
    digitalWrite(redLED, HIGH);
    tone(buzzer,500);
    delay(300);
    digitalWrite(redLED, LOW);
    noTone(buzzer);
    delay(300);
  }

  lockedOut=true;
  delay(10000);
  lockedOut=false;
  wrongAttempts=0;

  digitalWrite(redLED, HIGH);
  lcd.clear();
  lcd.print("Enter Password");
}

void changePassword(){
  lcd.clear();
  lcd.print("Old Password:");
  input="";

  while(input.length() < 4){
    char key = keypad.getKey();
    if(key && key != '*' && key !='#'){
      input+=key;
      lcd.setCursor(input.length()-1,1);
      lcd.print("*");
    }
  }

  if (input== password){
    lcd.clear();
    lcd.print("New Password:");
    input = "";

    while (input.length()<4){
      char key=keypad.getKey();
      if (key && key!='*' && key!='#'){
        input+= key;
        lcd.setCursor(input.length()-1,1);
        lcd.print("*");
      }
    }

    password=input;
    lcd.clear();
    lcd.print("Password Saved");
    tone(buzzer,1200,400);
    delay(1500);
  }
  else{
    lcd.clear();
    lcd.print("Wrong Old Pass");
    tone(buzzer,300,800);
    delay(1500);
  }

  input= "";
  lcd.clear();
  lcd.print("Enter Password");
  digitalWrite(redLED, HIGH);
}
