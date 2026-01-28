const int ldrPin= A0;
const int pirEntry= 2;
const int pirExit= 5;

const int fogButton= 3;
const int emergencyButton= 4;

const int led1= 9;
const int led2= 10;
const int led3= 11;
const int led4= 6;

bool lightsOn= false;

void setup() {
  pinMode(pirEntry, INPUT);
  pinMode(pirExit, INPUT);

  pinMode(fogButton, INPUT_PULLUP);
  pinMode(emergencyButton, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void setAllLights(int brightness) {
  analogWrite(led1, brightness);
  analogWrite(led2, brightness);
  analogWrite(led3, brightness);
  analogWrite(led4, brightness);
}

void loop(){
  int lightLevel= analogRead(ldrPin);

  bool fogPressed = digitalRead(fogButton) == LOW;
  bool emergencyPressed = digitalRead(emergencyButton) == LOW;

  if (lightLevel > 500){
    lightsOn = false;
    setAllLights(0);
    delay(100);
    return;
  }

  
  if (digitalRead(pirEntry)== HIGH){
    lightsOn = true;
  }
  
  if (digitalRead(pirExit)== HIGH){
    lightsOn = false;
  }

  if (fogPressed || emergencyPressed){
    lightsOn = true;
  }

  if (lightsOn){
    setAllLights(255);
  }
  else{
    setAllLights(60);
  }
  delay(100);
}
