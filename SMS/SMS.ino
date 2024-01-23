#include <WiFi.h>
#include <HTTPClient.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>

// Paramètres du réseau Wi-Fi
const char* ssid = "Votre_SSID";
const char* password = "Votre_Mot_de_passe";

// Paramètres du serveur local
const char* serverName = "http://adresse_du_serveur";

// Paramètres du module SIM800 (GSM/GPRS)
#define SIM800_TX_PIN 27
#define SIM800_RX_PIN 26
#define BAUDRATE 9600

// Paramètres Modbus
#define MAX485_DE 4
#define MAX485_RE_NEG 5

ModbusMaster mod;

// Variables pour la communication série avec le module SIM800
SoftwareSerial SerialAT(SIM800_TX_PIN, SIM800_RX_PIN);

// Variables pour le suivi du temps et de l'intervalle d'envoi
unsigned long lastTime = 0;
const unsigned long timerDelay = 5000; // Intervalle de 5 secondes

void setup() {
  // Initialisation de la communication série
  Serial.begin(115200);
  SerialAT.begin(BAUDRATE);

  // Configuration du module SIM800
  delay(6000); // Attendre le démarrage du module
  SerialAT.println("AT"); // Vérifier la communication avec le module SIM800
  delay(1000);
  SerialAT.println("AT+CMGF=1"); // Configuration du mode texte pour les SMS
  delay(1000);
  SerialAT.println("AT+CNMI=1,2,0,0,0"); // Activer la réception automatique des SMS
  delay(1000);

  // Connexion au réseau Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi en cours...");
  }
  Serial.println("Connecté au réseau Wi-Fi !");
}

void loop() {
  // Vérifier si le temps écoulé dépasse l'intervalle défini
  if ((millis() - lastTime) > timerDelay) {
    // Vérifier la connexion Wi-Fi
    if (WiFi.status() == WL_CONNECTED) {
      std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

      // Ignorer la validation du certificat SSL
      client->setInsecure();

      HTTPClient https;

      https.begin(*client, serverName); // Initialisation de la communication HTTPS

      // Construire la requête JSON avec les valeurs des capteurs
      String httpRequest = "{\"n\":\"" + String(nitrogen()) +
                           "\",\"p\":\"" + String(phosphorous()) +
                           "\",\"k\":\"" + String(potassium()) +
                           "\",\"pH\":\"" + String(6) + "\"}";

      Serial.println(httpRequest);

      // Envoyer la requête HTTPS POST
      int httpResponseCode = https.POST(httpRequest);

      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);

      https.end();
    }

    // Envoyer un message SMS via le module SIM800
    sendSMS();

    // Mettre à jour le dernier temps
    lastTime = millis();
  }
}

// Fonction pour obtenir la valeur d'azote à partir du capteur NPK via Modbus
byte nitrogen() {
  digitalWrite(MAX485_DE, HIGH);
  digitalWrite(MAX485_RE_NEG, HIGH);
  delay(10);
  if (mod.write(nitro_inquiry_frame, sizeof(nitro_inquiry_frame)) == 8) {
    digitalWrite(MAX485_DE, LOW);
    digitalWrite(MAX485_RE_NEG, LOW);
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
    }
    Serial.println();
  }
  return values[4];
}

// Fonction pour obtenir la valeur de phosphore à partir du capteur NPK via Modbus
byte phosphorous() {
  digitalWrite(MAX485_DE, HIGH);
  digitalWrite(MAX485_RE_NEG, HIGH);
  delay(10);
  if (mod.write(phos_inquiry_frame, sizeof(phos_inquiry_frame)) == 8) {
    digitalWrite(MAX485_DE, LOW);
    digitalWrite(MAX485_RE_NEG, LOW);
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
    }
    Serial.println();
  }
  return values[4];
}

// Fonction pour obtenir la valeur de potassium à partir du capteur NPK via Modbus
byte potassium()

// la fonction `sendSMS()` pour envoyer des messages SMS via le module SIM800 :
String getMessage(String message){
      int phoneNumberStart = message.indexOf("SEND_SMS") + 9;
      int phoneNumberEnd = message.indexOf(",", phoneNumberStart);
  // Extraire le contenu du message
      int messageStart = phoneNumberEnd + 1;
      String content = message.substring(messageStart);
      return content;
}

String getReceiver(String message){
  if (message.indexOf("SEND_SMS") != -1) {
      // Extraire le numéro de téléphone du message
      int phoneNumberStart = message.indexOf("SEND_SMS") + 9;
      int phoneNumberEnd = message.indexOf(",", phoneNumberStart);
      String phoneNumber = message.substring(phoneNumberStart, phoneNumberEnd);

      return phoneNumber;
  }
  else
  {
      return "Aucun numéro";
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
void sendSMS() {
  // Vérifier la disponibilité des messages SMS reçus
  if (SerialAT.available()) {
    String message = SerialAT.readString();
    Serial.print("Message reçu : ");
    Serial.println(message);

    // Vérifier le contenu du message
    if (message.indexOf("SEND_SMS") != -1) {
      // Extraire le numéro de téléphone du message
      int phoneNumberStart = message.indexOf("SEND_SMS") + 9;
      int phoneNumberEnd = message.indexOf(",", phoneNumberStart);
      String phoneNumber = message.substring(phoneNumberStart, phoneNumberEnd);
      
      // Extraire le contenu du message
      int messageStart = phoneNumberEnd + 1;
      String content = message.substring(messageStart);

      // Envoyer le message SMS
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
  }
}

messageContent

// Fonction pour mettre à jour la communication série avec le module SIM800
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    SerialAT.write(Serial.read());
  }
  while (SerialAT.available()) {
    Serial.write(SerialAT.read());
  }
}