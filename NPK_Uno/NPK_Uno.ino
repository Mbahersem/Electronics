#include <SoftwareSerial.h>
#include <Wire.h>

// Broches pour interagir avec le MAX485 modbus (On peut modifier les valeurs)
#define DE 4
#define RE 5

// On peut également modifier ces informations en fonction de nos besoins
#define RX  2// Emulation de la broche qu'on veut pour la réception en série
#define TX  3// Emulation de la broche qu'on veut pour la transmission en série

SoftwareSerial mod(RX, TX); // Initialisation d'une communication série avec le MAX485

// Adresses de l'azote, du  phosphore et du potassium sur le MAX485
const byte nitro_inquiry_frame[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos_inquiry_frame[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota_inquiry_frame[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

void setup() {
  // put your setup code here, to run once:
  mod.begin(9600); // Initialisation pour la communication en série avec le MAX485 modbus
  Serial.begin(9600);
  Serial.println("Modbus initialisé.");
  pinMode(DE, OUTPUT); // Configuration de la broche DE en sortie
  pinMode(RE, OUTPUT); // Configuration de la broche RE en sortie
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("N : ");
  Serial.println(nitrogen());
  Serial.print("P : ");
  Serial.println(potassium());
  Serial.print("K : ");
  Serial.println(phosphorous());
  Serial.println();
  delay(1000);
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
