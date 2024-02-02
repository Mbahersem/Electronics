#define SMS_TARGET "+237694563044"

#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER 1024

#include <Wire.h>
#include <TinyGsmClient.h>

// TTGO T-Call pins
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define I2C_SDA              21
#define I2C_SCL              22

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM800 module)
#define SerialAT  Serial1

// Define the serial console for debug prints, if needed
//#define DUMP_AT_COMMANDS

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

#define IP5306_ADDR          0x75
#define IP5306_REG_SYS_CTL0  0x00

bool setPowerBoostKeepOn(int en) {
  Wire.beginTransmission(IP5306_ADDR);
  Wire.write(IP5306_REG_SYS_CTL0);
  if (en) {
    Wire.write(0x37); // Set bit1: 1 enable 0 disable boost keep on
  } else {
    Wire.write(0x35); // 0x37 is default reg value
  }
  return Wire.endTransmission() == 0;
}

void updateSerial();

void setup() {
  SerialMon.begin(115200);
  // Keep power when running from battery
  Wire.begin(I2C_SDA, I2C_SCL);
  bool isOk = setPowerBoostKeepOn(1);
  SerialMon.println(String("IP5306 KeepOn") + (isOk ? "OK" : "FAIL"));
  // Set modem reset, enable, power pins

  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  SerialMon.println("Initializing modem...");
  modem.init();

  // To send an SMS, call modem.sendSMS(SMS_TARGET, smsMessage)

  SerialAT.println("AT"); // Handshake ?
  updateSerial();
  delay(200);
  SerialAT.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  delay(200);
  SerialAT.println("AT+CNMI=2,1,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
  delay(200);
}

String gsm;

void loop() {
  if(SerialAT.available()) {
    gsm = SerialAT.readString();
    gsm.trim();
    if(gsm.startsWith("+CMTI:")) {
      int comma = gsm.indexOf(',');
      String index = gsm.substring(comma + 1);
      index.trim();

      SerialAT.println("AT+CMGR="+index);
      delay(200);
      if(SerialAT.available()) {
        gsm = SerialAT.readString();
        gsm.trim();
        if(gsm.startsWith("+CMGR:")) {
          int firstComma = gsm.indexOf(',');
          int secondComma = gsm.indexOf(',', firstComma + 1);
          int thirdComma = gsm.indexOf(',', secondComma + 1);
          String number = gsm.substring(firstComma + 2, secondComma - 1);

          int ash = gsm.lastIndexOf('"');
          String message = gsm.substring(ash + 2);
          message.trim();
          if(message.startsWith("get")) {
            if(modem.sendSMS(number, "Donnees ?")) {
              SerialMon.println("Donnees ?");
            }
            else {
              SerialMon.println("SMS failed to send");
            }

          }
          if(message.startsWith("predict")) {
            SerialMon.println("Ok");
            if(modem.sendSMS(number, "Prediction ?")) {
              SerialMon.println("Prediction ?");
            }
            else {
              SerialMon.println("SMS failed to send");
            }
          }
        }
      }
    }
  }

}

void updateSerial() {
  while (SerialMon.available()) {
    SerialAT.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (SerialAT.available()) {

    SerialMon.write(SerialAT.read());//Forward what Software Serial received to Serial Port
  }
}

  // if(SerialAT.available()) {
  //   gsm = SerialAT.readStringUntil('\n');
  //   gsm.trim();
  //   if(gsm.startsWith("+CMGL:")) {
  //     SerialMon.println("Yeah");
  //     int firstComma = gsm.indexOf(',');
  //     int secondComma = gsm.indexOf(',', firstComma + 1);
  //     int thirdComma = gsm.indexOf(',', secondComma + 1);

  //     String number = gsm.substring(secondComma + 2, thirdComma - 1);

  //     int fourthComma = gsm.indexOf(',', thirdComma + 1);
  //     int fifthComma = gsm.indexOf(',', fourthComma + 1);
  //     int space = gsm.indexOf('\n');
  //     String message = gsm.substring(fifthComma);
  //     String message2 = gsm.substring(space);
  //     SerialMon.println(number);
  //     SerialMon.println(message);
  //     SerialMon.println(message2);
  //   }
  //   SerialMon.println(gsm);
