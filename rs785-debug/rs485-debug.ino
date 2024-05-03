/*
   Boris Nges.
   Soil NPK Sensor with Arduino for measuring Nitrogen, Phosphorus, and Potassium
*/
#include <SoftwareSerial.h>
#include <Wire.h>

#define RE 7
#define DE 8

// The following are the Inquiry frames which are send to the NPK sensor
//for reading the Nitrogen, Phosphorus, and Potassium values
// We defined three arrays with names nitro_inquiry_frame, phos_inquiry_frame, and pota_inquiry_frame
// Each inquiry frame have 8 values
const byte nitro_inquiry_frame[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos_inquiry_frame[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota_inquiry_frame[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];
SoftwareSerial modbus(2, 3);

void setup() {

  Serial.begin(9600);
  modbus.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)

byte nitrogen_val, phosphorus_val, potassium_val;
void loop() {
  // we will need three variables of the type byte to store the values of
  // Nitrogen, phosphorus, and Potassium.
  //  byte nitrogen_val, phosphorus_val, potassium_val;

  nitrogen_val = nitrogen();
  delay(250);
  phosphorus_val = phosphorous();
  delay(250);
  potassium_val = potassium();
  delay(250);

  // The following code is used to send the data to the serial monitor
  // but as we have connected the Bluetooth module, so it will send data to the
  // Android cell phone Application

  Serial.print("Nitrogen_Val: ");
  Serial.print(nitrogen_val);
  Serial.println(" mg/kg");
  Serial.print("Phosphorous_Val: ");
  Serial.print(phosphorus_val);
  Serial.println(" mg/kg");
  Serial.print("Potassium_Val: ");
  Serial.print(potassium_val);
  Serial.println(" mg/kg");
  delay(500);

}


byte nitrogen() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (modbus.write(nitro_inquiry_frame, sizeof(nitro_inquiry_frame)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    // When we send the inquiry frame to the NPK sensor, then it replies with the response frame
    // now we will read the response frame, and store the values in the values[] arrary, we will be using a for loop.
    for (byte i = 0; i < 7; i++) {
      //Serial.print(modbus.read(),HEX);
      values[i] = modbus.read();
      // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4]; // returns the Nigtrogen value only, which is stored at location 4 in the array
}

byte phosphorous() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (modbus.write(phos_inquiry_frame, sizeof(phos_inquiry_frame)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(modbus.read(),HEX);
      values[i] = modbus.read();
      // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte potassium() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (modbus.write(pota_inquiry_frame, sizeof(pota_inquiry_frame)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(modbus.read(),HEX);
      values[i] = modbus.read();
      //Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
