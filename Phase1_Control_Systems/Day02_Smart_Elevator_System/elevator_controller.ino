//4-floor elevator
#include<Servo.h>
Servo doorServo;

int floorLEDs[4] = {2, 3, 4, 5};

int floorButtons[4] = {8, 9, 10, 11};

int emergencyBtn = 12;

int buzzerOpen = A0;
int buzzerClose = A1;

int servoPin = A2;

int bcdA = 6;
int bcdB = 7;
int bcdC = 13;
int bcdD = A3;

int currentFloor=0;
int targetFloor=-1;
bool doorOpen= false;

int direction = 0;
bool emergencyActive = false;


void displayFloor(int floor){
  digitalWrite(bcdA,bitRead(floor+1,0));
  digitalWrite(bcdB,bitRead(floor+1,1));
  digitalWrite(bcdC,bitRead(floor+1,2));
  digitalWrite(bcdD,bitRead(floor+1,3));
}

void setup(){
  for (int i=0; i<4;i++){
    pinMode(floorLEDs[i],OUTPUT);
    pinMode(floorButtons[i],INPUT_PULLUP);
  }
  pinMode(emergencyBtn, INPUT_PULLUP);
  pinMode(buzzerOpen, OUTPUT);
  pinMode(buzzerClose, OUTPUT);

  pinMode(bcdA, OUTPUT);
  pinMode(bcdB, OUTPUT);
  pinMode(bcdC, OUTPUT);
  pinMode(bcdD, OUTPUT);

  doorServo.attach(servoPin);
  doorServo.write(0);

  digitalWrite(floorLEDs[currentFloor],HIGH);
  displayFloor(currentFloor);
}

void openDoor(){
  doorServo.write(90);
  tone(buzzerOpen,1500,400);
  for (int t = 0; t < 300; t++){
    if (digitalRead(emergencyBtn) == LOW){
      emergencyActive = true;
      break;
    }
    delay(10);
  }
  doorOpen = true;
}

void closeDoor() {
  doorServo.write(0);
  tone(buzzerClose, 1000, 300);
  for (int t = 0; t < 100; t++) {
    if (digitalRead(emergencyBtn) == LOW) {
      emergencyActive = true;
      break;
    }
    delay(10);
  }
  doorOpen = false;
}

void moveToFloor(int floor){

  if(doorOpen)closeDoor();
  direction = (floor > currentFloor) ? 1 : -1;
  while (currentFloor != floor) {

    if (digitalRead(emergencyBtn) == LOW){
      emergencyActive = true;
      break;
    }
    digitalWrite(floorLEDs[currentFloor],LOW);
    for (int t = 0;t < 150; t++){
      if (digitalRead(emergencyBtn) == LOW) {
        emergencyActive = true;
        break;
      }
      delay(10);
    }
    currentFloor +=direction;
    digitalWrite(floorLEDs[currentFloor],HIGH);
    displayFloor(currentFloor);
  }

  if (emergencyActive){
    openDoor();
    while (digitalRead(emergencyBtn) ==LOW) {
    }
    emergencyActive =false;
    return;
  }
  openDoor();
}


void loop(){
  for(int i=0;i<4;i++){
    if (digitalRead(floorButtons[i])==LOW){
      targetFloor = i;
    }
  }
  if (targetFloor!=-1 && targetFloor!=currentFloor) {
    moveToFloor(targetFloor);
    targetFloor = -1;
  }
}
    