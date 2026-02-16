#define BLYNK_TEMPLATE_ID "TMPL3Ela7U522"
#define BLYNK_TEMPLATE_NAME "Dual Gas Safety Monitor"
#define BLYNK_AUTH_TOKEN "nE_OCqGdjbhPK_I8GwSjLUyYo8q7jK7W"


#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define MQ4_PIN 34
#define MQ7_PIN 35

#define GREEN_LED 13
#define RED_LED   12
#define BUZZER    18  

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define RL_VALUE 10.0
#define VC 5.0

#define R0_MQ4 13.7
#define R0_MQ7 12.8

float ch4_ppm_filt = 0;
float co_ppm_filt  = 0;

float emaFilter(float prev, float current) {
  const float alpha = 0.3;
  return alpha * current + (1.0 - alpha) * prev;
}

unsigned long buzzerTimer = 0;
bool buzzerState = false;

int readADC_Avg(int pin) {
  long sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 50;
}

float getRs(int pin) {
  int adc = readADC_Avg(pin);
  float vout = adc * (3.3 / 4095.0);
  if (vout < 0.01) vout = 0.01;
  return RL_VALUE * (VC - vout) / vout;
}

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  float rs4 = getRs(MQ4_PIN);
  float rs7 = getRs(MQ7_PIN);

  float ratio4 = rs4 / R0_MQ4;
  float ratio7 = rs7 / R0_MQ7;

  float ppm_ch4_raw = 1010 * pow(ratio4, -2.76);
  float ppm_co_raw  = 37143 * pow(ratio7, -3.109);

  ch4_ppm_filt = emaFilter(ch4_ppm_filt, ppm_ch4_raw);
  co_ppm_filt  = emaFilter(co_ppm_filt,  ppm_co_raw);

  bool ch4_alarm = (ch4_ppm_filt > 2000);
  bool co_alarm  = (co_ppm_filt > 50);

  if (ch4_alarm || co_alarm) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    buzzerState = false;
  }

  unsigned long now = millis();

  if (ch4_alarm && co_alarm) {
    digitalWrite(BUZZER, LOW);
  } 
  else if (co_alarm) {
    if (now - buzzerTimer >= 200) {
      buzzerTimer = now;
      buzzerState = !buzzerState;
      digitalWrite(BUZZER, buzzerState ? LOW : HIGH);
    }
  } 
  else if (ch4_alarm) {
    if (now - buzzerTimer >= 1000) {
      buzzerTimer = now;
      buzzerState = !buzzerState;
      digitalWrite(BUZZER, buzzerState ? LOW : HIGH);
    }
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Gas Monitor");

  display.setCursor(0,16);
  display.print("CH4: ");
  display.print(ch4_ppm_filt,1);
  display.println(" ppm");

  display.setCursor(0,28);
  display.print("CO : ");
  display.print(co_ppm_filt,1);
  display.println(" ppm");

  display.setCursor(0,48);
  String status;
  if (ch4_alarm && co_alarm) status = "CRITICAL";
  else if (co_alarm) status = "CO ALERT";
  else if (ch4_alarm) status = "CH4 ALERT";
  else status = "SAFE";

  display.println("STATUS: " + status);
  display.display();

  Blynk.virtualWrite(V0, ch4_ppm_filt);
  Blynk.virtualWrite(V1, co_ppm_filt);
  Blynk.virtualWrite(V2, status);
  Blynk.virtualWrite(V3, (ch4_alarm || co_alarm));
  Blynk.virtualWrite(V4, ch4_alarm);
  Blynk.virtualWrite(V5, co_alarm);

  delay(1000);
}
