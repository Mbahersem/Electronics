/*
* codeNPK.ino
* ------------
* Code flashé dans l'ESP8266 pour la collecte de données NPK et transmission via HTTPS au serveur via un point d'API POST
*
* Liens utilisés :
*   https://how2electronics.com/measure-soil-nutrient-using-arduino-soil-npk-sensor/
*   https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/
*   https://randomnerdtutorials.com/esp32-http-get-post-arduino/
*   https://microdigisoft.com/send-and-receive-sms-using-esp32-ttgo-t1-call-with-arduino-ide/
*
* Rédigé par l'équipe de stagiaires
*
* Créé le 26/08/2023
* Modifié le 05/09/2023
*/

const char simPIN[] = "";
String basic = "http://localhost:8000/npkmeter/npkph/"; 
String prediction = "http://localhost:8000/npkmeter/npkph/prediction"; // URL de la prédiction

// Module utilisé et buffer
#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER 1024

#define TEST_NPK
// Importation des bibliothèques nécessaires
#include <SoftwareSerial.h>
#include <Wire.h>

#if defined(ESP8266)
  #define MICROCONTROLLER_TYPE "ESP8266"
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
  WiFiServer server(80);
#elif defined(ESP32)
  #define MICROCONTROLLER_TYPE "ESP32"
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <TinyGsmClient.h>
  #include <WiFiClient.h>

  struct Message {
    String phoneNumber;
    String message;
  };

  typedef struct Message SMS;

  SMS listSMS[50];
  
  int count;

  // Broches pour la communication avec le module SIM800 à travers l'ESP32
  #define MODEM_RST 5
  #define MODEM_PWKEY 4
  #define MODEM_POWER_ON 23
  #define MODEM_TX 27 
  #define MODEM_RX 26
  #define I2C_SDA 21
  #define I2C_SCL 22

  char smsBuffer[250];

  #define IP5306_ADDR 0x75
  #define IP5306_REG_SYS_CTL0 0x00

  #define SerialMon Serial
  #define SerialAT Serial1

  TinyGsm modem(SerialAT);

  bool setPowerBoostKeepOn(int en) {
    Wire.beginTransmission(IP5306_ADDR);
    Wire.write(IP5306_REG_SYS_CTL0);
    if(en) {
      Wire.write(0x37);
    }
    else {
      Wire.write(0x35);
    }
    return Wire.endTransmission() == 0;
  }

  void updateSerial() {
    while(SerialMon.available()) {
      SerialAT.write(SerialMon.read());
    }

    while(SerialAT.available()) {
      SerialMon.write(SerialAT.read());
    }
  }

  void sendMessage(String phoneNumber,String content){
    SerialAT.print("AT+CMGS=\"");
    SerialAT.print(phoneNumber);
    SerialAT.println("\"");
    delay(1000);
    SerialAT.print(content);
    delay(100);
    SerialAT.println((char)26);
    delay(1000);
    Serial.println("Message envoyé !");    
  }

  void getUnreadSMS() {
    SerialAT.println("AT+CMGL=\"REC UNREAD\"");
    int i = 0;
    count = 0;

    while(SerialAT.available()) {
      String line = SerialAT.readStringUntil('\n');
      if(line.startsWith("+CMGL:")) {
        int firstComma = line.indexOf(',');
        int secondComma = line.indexOf(',', firstComma + 1);
        int thirdComma = line.indexOf(',', secondComma + 1);
        int fourthComma = line.indexOf(',', thirdComma + 1);
        String sender = line.substring(secondComma + 1, thirdComma);
        int fifthComma = line.indexOf(',', fourthComma + 1);
        String message = line.substring(fifthComma + 12);
        listSMS[i] = {sender, message};
        i++;
        Serial.print("Message de : ");
        Serial.print(sender);
        Serial.print(" ");
        Serial.println(message);
      }
    }
    count = i;
  }

  void processMessages() {
    for(int i = 0; i < count; i++) {
      if(listSMS[i].message == "get") {
        // httpPOSTRequest(basic);
        String response = httpGETRequest(basic);
        sendMessage(listSMS[i].phoneNumber, response);
      }
      if(listSMS[i].message == "predict") {
        // httpPOSTRequest(basic);
        String response = httpGETRequest(prediction);
        sendMessage(listSMS[i].phoneNumber, response);
      }
    }
  }
#else
  #error "Type de microcontrôleur non pris en charge"
#endif

// Broches pour interagir avec le MAX485 modbus (On peut modifier les valeurs)
#define DE 13
#define RE 15

// On peut également modifier ces informations en fonction de nos besoins
#define RX  4// Emulation de la broche qu'on veut pour la réception en série
#define TX  0// Emulation de la broche qu'on veut pour la transmission en série

SoftwareSerial mod(RX, TX); // Initialisation d'une communication série avec le MAX485

// Adresses de l'azote, du  phosphore et du potassium sur le MAX485
const byte nitro_inquiry_frame[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos_inquiry_frame[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota_inquiry_frame[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

// Informations à modifier si on utilise un autre réseau WiFi
const char* ssid = "Marvelous"; // Nom du point d'accès WiFi
const char* password = "07122023*"; // Mot de passe du point d'accès WiFi

// URL des requêtes HTTP POST et GET, à modifier en fonction de l'API qu'on a créé côté serveur

unsigned long lastTime = 0;
unsigned long timerDelay = 1000; // Délai d'envoi des données

void setup() {
    #if defined(ESP8266)
      mod.begin(9600); // Initialisation pour la communication en série avec le MAX485 modbus
      pinMode(RE, OUTPUT); // Configuration de la broche RE en sortie
      pinMode(DE, OUTPUT); // Configuration de la broche DE en sortie
      Serial.println("Modbus initialisé.");
      SerialMon.begin(115200); // Démarrage de la communication en série avec la vitesse de 115200 pour la connexion au WiFi
      WiFi.begin(ssid, password); // Initialisation de la connexion au point d'accès WiFi

      SerialMon.print("Connexion");
      while(WiFi.status() != WL_CONNECTED) { // Vérification de la connexion au point d'accès
          delay(500);
          Serial.print(".");
      }
      SerialMon.println("");
      SerialMon.print("Connecté au réseau WiFi avec l'adresse IP : ");
      SerialMon.println(WiFi.localIP());

      server.begin();
      Serial.println("Serveur HTTP démarré.");
    #elif defined(ESP32)
      mod.begin(9600); // Initialisation pour la communication en série avec le MAX485 modbus
      pinMode(RE, OUTPUT); // Configuration de la broche RE en sortie
      pinMode(DE, OUTPUT); // Configuration de la broche DE en sortie
      Serial.println("Modbus initialisé.");
      SerialMon.begin(115200);

      Wire.begin(I2C_SDA, I2C_SCL);
      bool isOk = setPowerBoostKeepOn(1);
      SerialMon.println(String("IP5306 KeepOn ") + (isOk ? "OK" : "FAIL"));

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

      SerialMon.println("Initialisation du modem...");
      modem.restart();

      if(strlen(simPIN) && modem.getSimStatus() != 3) {
        modem.simUnlock(simPIN);
      }
      // Décommenter pour tester l'envoi de messages sur ma carte SIM
      // String smsMessage = "Hello from ESP32!";
      // if(modem.sendSMS("+237698851756", smsMessage)) {
      //   SerialMon.println(smsMessage);
      // }
      // else {
      //   SerialMon.println("SMS failed to send");
      // }

      SerialAT.println("AT"); // Handshake réussi
      updateSerial();
      delay(200);
      SerialAT.println("AT+CMGF=1"); // Configurer le mode texte
      updateSerial();
      delay(200);
      SerialAT.println("AT+CNMI=2,2,0,0,0"); // Décider comment les nouveaux messages reçus devront être gérés
      updateSerial();
    #endif
}

void loop() {
        #if defined(ESP8266)
          updateServer();
        #elif defined(ESP32)

          updateSerial();
          getUnreadSMS();
          processMessages();
          // while(SerialAT.available()) {

          //   String message = SerialAT.readString();
          //   Serial.print("Message reçu : ");
          //   Serial.println(message);
          //   String content = getMessage(message);
          //   String phoneNumber = getReceiver(message);
          //   Serial.print(phoneNumber);
          //   Serial.println("");
          //   Serial.print(content);

          //   if(content == "get"){
          //     // httpPOSTRequest(basic);
          //     String response = httpGETRequest(basic);
          //     sendMessage(phoneNumber, response);
          //   }

          //   if(content == "predict"){
          //     // httpPOSTRequest(basic);
          //     String response = httpGETRequest(prediction);
          //     sendMessage(phoneNumber, response);
          //   }

          //   if(content == "doc"){

          //   }
          // }
        #endif

}

/*
* Fonction : nitrogen
* -------------------
* Fonction pour obtenir la valeur d'azote à partir du capteur NPK à travers le MAX485 modbus
*
* Retourne un entier de type byte
*/
byte nitrogen() {
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10);
    if(mod.write(nitro_inquiry_frame, sizeof(nitro_inquiry_frame)) == 8) {
        digitalWrite(DE, LOW);
        digitalWrite(RE, LOW);

        for(byte i = 0; i < 7; i++) {
            values[i] = mod.read();
            Serial.print(values[i], HEX);
        }
        Serial.println();
    }
    return values[4];
}

/*
* Fonction : phosphorous
* ----------------------
* Fonction pour obtenir la valeur de phosphore à partir du capteur NPK à travers le MAX485 modbus
*
* Retourne un entier de type byte
*/
byte phosphorous() {
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10);
    if(mod.write(phos_inquiry_frame, sizeof(phos_inquiry_frame)) == 8) {
        digitalWrite(DE, LOW);
        digitalWrite(RE, LOW);

        for(byte i = 0; i < 7; i++) {
            values[i] = mod.read();
            Serial.print(values[i], HEX);
        }
        Serial.println();
    }
    return values[4];
}

/*
* Fonction : potassium
* --------------------
* Fonction pour obtenir la valeur de potassium à partir du capteur NPK à travers le MAX485 modbus
*
* Retourne un entier de type byte
*/
byte potassium() {
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10);
    if(mod.write(pota_inquiry_frame, sizeof(pota_inquiry_frame)) == 8) {
        digitalWrite(DE, LOW);
        digitalWrite(RE, LOW);

        for(byte i = 0; i < 7; i++) {
            values[i] = mod.read();
            Serial.print(values[i], HEX);
        }
        Serial.println();
    }
    return values[4];
}

// String getMessage(String message){
//       int phoneNumberStart = message.indexOf("SEND_SMS") + 9;
//       int phoneNumberEnd = message.indexOf(",", phoneNumberStart);
//   // Extraire le contenu du message
//       int messageStart = phoneNumberEnd + 1;
//       String content = message.substring(messageStart);
//       return content;
// }

// String getReceiver(String message){
//   if (message.indexOf("SEND_SMS") != -1) {
//       // Extraire le numéro de téléphone du message
//       int phoneNumberStart = message.indexOf("SEND_SMS") + 9;
//       int phoneNumberEnd = message.indexOf(",", phoneNumberStart);
//       String phoneNumber = message.substring(phoneNumberStart, phoneNumberEnd);

//       return phoneNumber;
//   }
//   else
//   {
//       return "Aucun numéro";
//   }  
// }

void httpPOSTRequest(String url) {
  WiFiClient client;

  HTTPClient http;

  http.begin(client, url); // Initialisation de la communication HTTP

  http.addHeader("Content-Type", "application/json"); // On ajoute une entête pour spécifier que la requête se fera au format JSON
  String httpRequest = "{\"n\":\"" + String(nitrogen())
    + "\",\"p\":\"" + String(potassium()) + "\",\"k\":\"" + String(potassium())
    + "\",\"ph\":\"" + String(6) + "\"}";
  Serial.println(httpRequest);
  int httpResponseCode = http.POST(httpRequest); // Emission de la requête HTTPS POST

  Serial.print("HTTP Response Code : ");
  Serial.println(httpResponseCode);

  http.end();
}

String httpGETRequest(String url) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, url);

  int httpResponseCode = http.GET();

  String payload = "{}";

  if(httpResponseCode > 0) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error Code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}

void updateServer() {
  #if defined(ESP8266)
    WiFiClient client = server.available();
    if(!client) {
      #ifdef TEST_NPK
        Serial.print("N : ");
        Serial.println(nitrogen());
        Serial.print("P : ");
        Serial.println(potassium());
        Serial.print("K : ");
        Serial.println(phosphorous());
      #endif
      return;
    }

    while(client.connected()) {
      if(client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);

        if(request.indexOf("/post") != -1) {
          if(WiFi.status() == WL_CONNECTED) { // Vérification de l'état de connexion au point d'accès
            httpPOSTRequest(basic);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
          }
        }
      }
    } 
    client.stop();
  #endif
}