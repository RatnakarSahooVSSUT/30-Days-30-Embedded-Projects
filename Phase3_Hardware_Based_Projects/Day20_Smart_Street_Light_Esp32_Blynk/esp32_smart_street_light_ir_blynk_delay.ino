#define BLYNK_TEMPLATE_ID "TMPL3BB0LOSqr"
#define BLYNK_TEMPLATE_NAME "Day20 Smart Street Light"
#define BLYNK_AUTH_TOKEN    "npz_YjNJaUzReGWY97BwvQ0LsbndyGzi"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define IR_ENTRY 34
#define IR_EXIT  35

#define OFF_DELAY_MS 3000  

unsigned long exitDetectedTime = 0;
bool offPending = false;

int streetLights[5] = {13, 12, 14, 27, 26};

bool autoMode = true;
bool lightState = false;

unsigned long lightOnStart = 0;
unsigned long lastOnDuration = 0;
unsigned long totalOnTime = 0;

BlynkTimer timer;

void lightsON(String source) {
  if (!lightState) {
    lightState = true;
    lightOnStart = millis();

    for (int i = 0; i < 5; i++)
      digitalWrite(streetLights[i], HIGH);

    Blynk.virtualWrite(V2, "ON");
    Blynk.virtualWrite(V5, source);
  }
}

void lightsOFF() {
  if (lightState) {
    lightState = false;
    lastOnDuration = (millis() - lightOnStart) / 1000;
    totalOnTime += lastOnDuration;

    for (int i = 0; i < 5; i++)
      digitalWrite(streetLights[i], LOW);

    Blynk.virtualWrite(V2, "OFF");
    Blynk.virtualWrite(V3, lastOnDuration);
    Blynk.virtualWrite(V4, totalOnTime);
  }
}

BLYNK_WRITE(V0) {  
  autoMode = param.asInt();
}

BLYNK_WRITE(V1) {   
  if (!autoMode) {
    if (param.asInt())
      lightsON("MANUAL");
    else
      lightsOFF();
  }
}

void autoLogic() {
  if (!autoMode) return;

  int entryState = digitalRead(IR_ENTRY);
  int exitState  = digitalRead(IR_EXIT);

  if (entryState == LOW) {
    lightsON("IR SENSOR");
    offPending = false; 
  }

  if (exitState == LOW && lightState) {
    exitDetectedTime = millis();
    offPending = true;
  }

  
  if (offPending && (millis() - exitDetectedTime >= OFF_DELAY_MS)) {
    lightsOFF();
    offPending = false;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_EXIT, INPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(streetLights[i], OUTPUT);
    digitalWrite(streetLights[i], LOW);
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(200L, autoLogic);
}

void loop() {
  Blynk.run();
  timer.run();
}
