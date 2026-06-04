#include <ModbusMaster.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define RXD2 16
#define TXD2 17
#define MAX485_RE_DE 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
ModbusMaster node;


// RS485 Control
void preTransmission()
{
  digitalWrite(MAX485_RE_DE, HIGH);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_DE, LOW);
}

// Setup
void setup()
{
  Serial.begin(115200);

  pinMode(MAX485_RE_DE, OUTPUT);
  digitalWrite(MAX485_RE_DE, LOW);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  node.begin(1, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("NPK");
  display.display();

  delay(2000);
}

// Loop
void loop()
{
  uint8_t result = node.readHoldingRegisters(0x001E, 3);

  if (result == node.ku8MBSuccess)
  {
    uint16_t nitrogen   = node.getResponseBuffer(0);
    uint16_t phosphorus = node.getResponseBuffer(1);
    uint16_t potassium  = node.getResponseBuffer(2);

    Serial.print("N: ");
    Serial.print(nitrogen);
    Serial.print(" mg/kg   ");

    Serial.print("P: ");
    Serial.print(phosphorus);
    Serial.print(" mg/kg   ");

    Serial.print("K: ");
    Serial.print(potassium);
    Serial.println(" mg/kg");

    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("Soil NPK Sensor");

    display.setCursor(0, 18);
    display.print("N: ");
    display.print(nitrogen);
    display.print(" mg/kg");

    display.setCursor(0, 34);
    display.print("P: ");
    display.print(phosphorus);
    display.print(" mg/kg");

    display.setCursor(0, 50);
    display.print("K: ");
    display.print(potassium);
    display.print(" mg/kg");

    display.display();
  }
  else
  {
    Serial.print("Error: ");
    Serial.println(result);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("ERROR");
    display.display();
  }

  delay(2000);
}