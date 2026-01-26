#include <LiquidCrystal.h>
#include <Servo.h>
#include <math.h>

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

Servo gateServo;
const int gatepin=0;

const int trigpins[3]={2,4,6};
const int echopins[3]={3,5,7};

const int greenLED[3]={8,10,12};
const int redLED[3]={9,11,13};

long duration;
long distance;

unsigned long startTime[3]={0,0,0};
unsigned long parkedTime[3]={0,0,0};
bool carWasPresent[3]={false,false,false};

bool showBill=false;
int billSlot=0;
unsigned long billTime=0;
int billFare=0;
unsigned long billDuration=0;

int getdistance(int trigpin,int echopin){
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  duration=pulseIn(echopin, HIGH, 20000);
  distance=duration * 0.034 / 2;
  return distance;
}

void setup(){
  lcd.begin(16,2);
  gateServo.attach(gatepin);

  for(int i=0;i<3;i++){
    pinMode(trigpins[i],OUTPUT);
    pinMode(echopins[i],INPUT);
    pinMode(greenLED[i],OUTPUT);
    pinMode(redLED[i],OUTPUT);
  }

  lcd.print(" Smart Parking ");
  lcd.setCursor(0, 1);
  lcd.print(" Initializing ");
  delay(2000);
  lcd.clear();
}

void loop(){
  bool slotOccupied[3];
  int occupiedCount=0;

  for (int i=0;i<3;i++){
    int d=getdistance(trigpins[i], echopins[i]);

    if (d>0 && d<15){
      slotOccupied[i]=true;
      digitalWrite(redLED[i],HIGH);
      digitalWrite(greenLED[i],LOW);
      occupiedCount++;

      if(!carWasPresent[i]){
        startTime[i]=millis();
        carWasPresent[i]=true;
      }

      parkedTime[i]=(millis()-startTime[i]) / 1000;
    } 
    else{
      slotOccupied[i]=false;
      digitalWrite(redLED[i],LOW);
      digitalWrite(greenLED[i],HIGH);

      if(carWasPresent[i]){
        float hours=parkedTime[i]/3600.0;

        if(hours<=1){
          billFare=50;
        }
        else{
          billFare=50+ceil(hours-1)*20;
        }

        billSlot=i+1;
        billDuration=parkedTime[i];
        showBill=true;
        billTime=millis();
      }

      carWasPresent[i]=false;
      parkedTime[i]=0;
    }
  }

  int freeSlots=3-occupiedCount;

  if (freeSlots > 0){
    gateServo.write(0);
  }
  else{
    gateServo.write(90);
  }

  if(showBill){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Slot ");
    lcd.print(billSlot);
    lcd.print(" Left");

    lcd.setCursor(0,1);
    lcd.print("Time:");
    lcd.print(billDuration);
    lcd.print("s Rs");
    lcd.print(billFare);

    if(millis()-billTime>3000){
      showBill=false;
      lcd.clear();
    }
    return;
  }

  static int displaySlot=0;
  static unsigned long lastUpdate=0;

  if(millis()-lastUpdate>1000){
    lastUpdate=millis();
    displaySlot=(displaySlot+1)%3;

    lcd.clear();
    lcd.setCursor(0,0);

    if(!slotOccupied[displaySlot]){
      lcd.print("Slot ");
      lcd.print(displaySlot+1);
      lcd.print(" FREE");
    }
    else {
      float hours=parkedTime[displaySlot]/3600.0;
      int fare=(hours<=1)?50:50+ceil(hours-1)*20;

      lcd.print("Slot ");
      lcd.print(displaySlot+1);
      lcd.print(" Time:");
      lcd.print(parkedTime[displaySlot]);
      lcd.print("s");

      lcd.setCursor(0,1);
      lcd.print("Fare: Rs ");
      lcd.print(fare);
    }
  }
}
