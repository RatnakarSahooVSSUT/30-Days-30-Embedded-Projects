#include <ModbusMaster.h>

#define RXD2 16
#define TXD2 17
#define MAX485_RE_DE 4

ModbusMaster node;

void preTransmission() {
  digitalWrite(MAX485_RE_DE, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_RE_DE, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(MAX485_RE_DE, OUTPUT);
  digitalWrite(MAX485_RE_DE, LOW);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  node.begin(1, Serial2);

  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {

  uint8_t result = node.readHoldingRegisters(0x001E, 3);

  if (result == node.ku8MBSuccess) {

    uint16_t nitrogen   = node.getResponseBuffer(0);
    uint16_t phosphorus = node.getResponseBuffer(1);
    uint16_t potassium  = node.getResponseBuffer(2);

    Serial.print("N: ");
    Serial.print(nitrogen);
    Serial.print(" mg/kg   P: ");
    Serial.print(phosphorus);
    Serial.print(" mg/kg   K: ");
    Serial.print(potassium);
    Serial.println(" mg/kg");
  }
  else {
    Serial.print("Error: ");
    Serial.println(result);
  }

  delay(2000);
}