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
  modem.restart();

  // To send an SMS, call modem.sendSMS(SMS_TARGET, smsMessage)
  String smsMessage = "Hello GSM";
  if (modem.sendSMS(SMS_TARGET, smsMessage)) {
    SerialMon.println(smsMessage);
  }
  else {
    SerialMon.println("SMS failed to send");
  }

  SerialAT.println("AT"); // Handshake ?
  updateSerial();
  delay(200);
  SerialAT.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  delay(200);
  SerialAT.println("AT+CNMI=2,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
}

char smsBuffer[250]; // Buffer to store SMS messages

void loop() {
  String sender;
  String message;
  updateSerial();
  static String currentLine = "";
  while(SerialAT.available()) {
    char c = SerialAT.read();

    if(c == '\n') {
      currentLine.trim();
      if(currentLine.startsWith("+CMT:")) {
        // Extract SMS index from the line
        SerialMon.println(currentLine);
        int smsIndex = currentLine.substring(13).toInt();
        // Read the SMS with extracted index using AT commands
        SerialAT.print("AT+CMGR=");
        SerialAT.println(smsIndex);
        delay(100);

        // Process the SMS message
        if(SerialAT.find("+CMGR:")) {
          String receivedMessage = SerialAT.readStringUntil('\n');
          receivedMessage.trim();

          int firstComma = receivedMessage.indexOf(',');
          int secondComma = receivedMessage.indexOf(',', firstComma + 1);
          int thirdComma = receivedMessage.indexOf(',', secondComma + 1);
          int fourthComma = receivedMessage.indexOf(',', thirdComma + 1);
          sender = receivedMessage.substring(secondComma + 1, thirdComma);
          int fifthComma = receivedMessage.indexOf(',', fourthComma + 1);
          message = receivedMessage.substring(fifthComma + 12);
          SerialMon.print("Message de : ");
          SerialMon.print(sender);
          SerialMon.print(" ");
          SerialMon.println(message);

          SerialMon.println("Received SMS: " + receivedMessage);
          // Store the received message in the buffer
          receivedMessage.toCharArray(smsBuffer, sizeof(smsBuffer));
          SerialMon.println("Stored in buffer: " + String(smsBuffer));

          // Delete the SMS after processing
          SerialAT.print("AT+CMGD=");
          SerialAT.println(smsIndex);
          delay(100); // Allow time for response

        }
      }
      SerialMon.println(currentLine + " 2");
      currentLine = ""; // Clear the line
      SerialMon.print("Message de : ");
      SerialMon.print(sender);
      SerialMon.print(" ");
      SerialMon.println(message);
      if (modem.sendSMS(sender, message)) {
        SerialMon.println(message);
      }
      else {
        SerialMon.println("SMS failed to send");
      }
      SerialMon.println("");
      SerialMon.println(smsBuffer);
    } else {
      currentLine += c; // Append character to the line
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
