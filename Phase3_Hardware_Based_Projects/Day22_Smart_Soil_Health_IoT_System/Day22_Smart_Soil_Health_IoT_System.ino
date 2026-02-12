#define BLYNK_TEMPLATE_ID "TMPL3G4u0BgJr"
#define BLYNK_TEMPLATE_NAME "Day22 Soil Health System"
#define BLYNK_AUTH_TOKEN    "YFP3hxnjLz8b-fs5cG-U_tcNKVDJJnlF"

char ssid[] = "Rk";
char pass[] = "aq12bfgh";

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SOIL_PIN   34

#define LED_DRY    13
#define LED_OK     12
#define LED_WET    14

#define DHTPIN    27
#define DHTTYPE   DHT11

#define OLED_SDA  21
#define OLED_SCL  22

#define SOIL_DRY_RAW  4500
#define SOIL_WET_RAW  1000-

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
BlynkTimer timer;

int soilRaw, soilPercent;
float temperature, humidity;
String soilStatus, recommendation;

void setup() {
  Serial.begin(9600);

  pinMode(LED_DRY, OUTPUT);
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_WET, OUTPUT);

  dht.begin();
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, readAndProcess);
  timer.setInterval(2000L, sendToBlynk);
}

void loop() {
  Blynk.run();
  timer.run();
}

void readAndProcess() {
  readSoil();
  readClimate();
  updateLEDs();
  decideAction();
  updateOLED();
  printSerial();
}


void readSoil() {
  soilRaw = analogRead(SOIL_PIN);
  soilPercent = map(soilRaw, SOIL_DRY_RAW, SOIL_WET_RAW, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  if (soilPercent < 30) soilStatus = "DRY";
  else if (soilPercent < 70) soilStatus = "OPTIMAL";
  else soilStatus = "WET";
}

void readClimate() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    temperature = 0;
    humidity = 0;
  }
}

void updateLEDs() {
  digitalWrite(LED_DRY, LOW);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_WET, LOW);

  if (soilStatus == "DRY") digitalWrite(LED_DRY, HIGH);
  else if (soilStatus == "OPTIMAL") digitalWrite(LED_OK, HIGH);
  else digitalWrite(LED_WET, HIGH);
}

void decideAction() {
  if (soilStatus == "DRY" && temperature > 30 && humidity < 50)
    recommendation = "WATER NOW";
  else if (soilStatus == "DRY")
    recommendation = "WAIT";
  else if (soilStatus == "WET")
    recommendation = "BLOCK";
  else
    recommendation = "SOIL OK";
}

void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" oC");

  display.setCursor(0, 12);
  display.print("Hum : ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 24);
  display.print("Soil: ");
  display.print(soilPercent);
  display.print("% ");
  display.println(soilStatus);

  display.setCursor(0, 40);
  display.print("Reco: ");
  display.println(recommendation);

  display.display();
}

void sendToBlynk() {
  Blynk.virtualWrite(V0, soilPercent);
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, soilStatus);
  Blynk.virtualWrite(V4, recommendation);
}

void printSerial() {
  Serial.print("SoilRaw: ");
  Serial.print(soilRaw);
  Serial.print(" | Soil%: ");
  Serial.print(soilPercent);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" | Hum: ");
  Serial.print(humidity);
  Serial.print(" | ");
  Serial.println(recommendation);
}
