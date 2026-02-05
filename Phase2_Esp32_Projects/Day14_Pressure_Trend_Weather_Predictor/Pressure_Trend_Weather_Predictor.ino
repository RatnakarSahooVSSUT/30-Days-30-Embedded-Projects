#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_BMP085 bmp;

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LED Pins
int ledClear= 14;
int ledCloudy= 27;
int ledRain= 26;

float pressureReadings[5];
int indexP= 0;

float previousAvgPressure= 0;
float previousTemp= 0;

void setup(){
  Serial.begin(115200);
  Wire.begin(21,22);

  lcd.init();
  lcd.backlight();

  if (!bmp.begin()){
    lcd.print("BMP180 Error!");
    while (1);
  }

  dht.begin();

  pinMode(ledClear,OUTPUT);
  pinMode(ledCloudy,OUTPUT);
  pinMode(ledRain,OUTPUT);

  // Initialize pressure history
  for (int i=0; i<5; i++){
    pressureReadings[i] = bmp.readPressure()/100.0;
  }
  previousAvgPressure= pressureReadings[0];
  previousTemp= dht.readTemperature();
}

float getAveragePressure(){
  float sum= 0;
  for (int i=0; i<5; i++) {
    sum+= pressureReadings[i];
  }
  return sum/5.0;
}

void loop(){
  float pressure= bmp.readPressure()/100.0;
  float temp= bmp.readTemperature();
  float humidity= dht.readHumidity();

  pressureReadings[indexP]= pressure;
  indexP= (indexP+1)%5;

  float avgPressure= getAveragePressure();
  float pressureChange= avgPressure-previousAvgPressure;
  float tempChange= temp-previousTemp;

  String forecast;

  if (pressureChange < -1.0 && humidity > 60 && tempChange < 0) {
    forecast= "Rain";
    digitalWrite(ledRain, HIGH);
    digitalWrite(ledCloudy, LOW);
    digitalWrite(ledClear, LOW);
  }
  else if (pressureChange < -0.5){
    forecast= "Cloudy";
    digitalWrite(ledCloudy, HIGH);
    digitalWrite(ledRain, LOW);
    digitalWrite(ledClear, LOW);
  }
  else {
    forecast= "Clear";
    digitalWrite(ledClear, HIGH);
    digitalWrite(ledCloudy, LOW);
    digitalWrite(ledRain, LOW);
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P:");
  lcd.print(avgPressure,0);
  lcd.print("hPa");

  lcd.setCursor(0,1);
  lcd.print("Fcst:");
  lcd.print(forecast);

  Serial.print("Avg Pressure: ");
  Serial.print(avgPressure);
  Serial.print(" Change: ");
  Serial.print(pressureChange);
  Serial.print(" TempChange: ");
  Serial.println(tempChange);

  previousAvgPressure= avgPressure;
  previousTemp= temp;

  delay(5000);
}
