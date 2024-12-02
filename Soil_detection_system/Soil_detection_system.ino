
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Arduino.h> // Required for random()

#define DHTTYPE DHT11
#define DHT11PIN A3
DHT dht(DHT11PIN, DHTTYPE); //Initialize DHT sensor object

#define DE_PIN 2
#define RE_PIN 3

// RS485 transceiver control pins

  // command data for each chemical```
const byte nitro[]  = {0x01,0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
const byte phosp[]  = {0x01,0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};
const byte potas[]  = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};
const byte ph[]     = {0x01,0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};
const byte moist[]  = {0x01,0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0F};

byte nitroValue;
byte phospValue;
byte potassValue;
byte phValue;
byte moistureValue;

byte nitroBuffer[11];
byte phospBuffer[11];
byte potasBuffer[11];
byte phBuffer[11];
byte moistBuffer[11];

char* crop_1;
char* crop_2;
char* crop_3;
char* crop_4;
char* crop_5;
char* crop_6;

// SoftwareSerial object for RS485 communication
SoftwareSerial RS485Serial(11, 12); // RX, TX
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup() {
  Serial.begin(9600); // Serial monitor for debugging
  RS485Serial.begin(4800); // RS485 communication

  pinMode(DE_PIN, OUTPUT);
  pinMode(RE_PIN, OUTPUT);
  digitalWrite(DE_PIN, LOW); // Set DE and RE pins to receive mode
  digitalWrite(RE_PIN, LOW);

  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("Soil Testing Sys");
  lcd.setCursor(7, 1);
  lcd.print("BY");
  lcd.setCursor(2, 2);
  lcd.print("Undergraduate  ");
  lcd.setCursor(2, 3);
  lcd.print("Students BEng.");
  delay(5000);

  lcd.clear();
  lcd.setCursor(2, 2);
  lcd.print("Initializing.");
  delay(250);
  lcd.setCursor(2, 2);
  lcd.print("Initializing..");
  delay(250);
  lcd.setCursor(2, 2);
  lcd.print("Initializing...");
  delay(250);
  
  randomSeed(analogRead(0));
}

void loop() {
   lcd.clear();
 
  // Send request for NPK levels
  sendRequest();

  
  lcd.clear();
  lcd.setCursor(2, 2);
  lcd.print("MEASURING.");
  delay(1000);
  lcd.setCursor(2, 2);
  lcd.print("MEASURING..");
  delay(1000);
  lcd.setCursor(2, 2);
  lcd.print("MEASURING...");
  delay(1000);

  Serial.print("Soil N: ");
  Serial.print(nitroValue);
  Serial.println(" mg/kg");
  Serial.print("Soil P: ");
  Serial.print(phospValue);
  Serial.println(" mg/kg");
  Serial.print("Soil K: ");
  Serial.print(potassValue);
  Serial.println(" mg/kg");
  Serial.print("PH level: ");
  Serial.print(phValue);
  Serial.println(" %");
  Serial.print("Moisture: ");
  Serial.print(moistureValue / 10.0);
  Serial.println(" %");
  Serial.println();
  delay(2000);

  int chk = dht.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)dht.readHumidity(), 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)dht.readTemperature(), 2);

  displayValues(moistureValue, phValue, nitroValue, phospValue, potassValue);
  
 // RecomendationCrops(crop_1, crop_2, crop_3, crop_4, crop_5, crop_6);
  
  //label:
  //stoped();
  //goto label;
  
}
void stoped(){
  lcd.clear();
  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("Soil Testing Sys");
  lcd.setCursor(7, 1);
  lcd.print("BY");
  lcd.setCursor(2, 2);
  lcd.print("Undergraduate  ");
  lcd.setCursor(2, 3);
  lcd.print("Students BEng.");

  delay(10000);
}

void sendRequest() {
 
  // Send request command for each chemical
  nitroValue = getNitro();
  delay(250);
  phospValue = getPhosp();
  delay(250);
  potassValue = getPotass();
  delay(250);
  phValue     = getph();
  delay(250);
  moistureValue = getmoist();
  delay(250);
  
}

byte getNitro(){
  digitalWrite(DE_PIN,HIGH);
  digitalWrite(RE_PIN,HIGH);
    delay(10);
  if(RS485Serial.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE_PIN,LOW);
    digitalWrite(RE_PIN,LOW);
    for(byte i=0;i<7;i++){
      nitroBuffer[i] = RS485Serial.read();
      Serial.print(nitroBuffer[i],HEX);
      Serial.print("\t");
    }
    Serial.println();
  }
  return nitroBuffer[4];
}

byte getPhosp(){
  digitalWrite(DE_PIN,HIGH);
  digitalWrite(RE_PIN,HIGH);
  delay(10);
  if(RS485Serial.write(phosp,sizeof(phosp))==8){
    digitalWrite(DE_PIN,LOW);
    digitalWrite(RE_PIN,LOW);
    for(byte i=0;i<7;i++){
      phospBuffer[i] = RS485Serial.read();
      Serial.print(phospBuffer[i],HEX);
    Serial.print("\t");
    }
    Serial.println();
  }
  return phospBuffer[6];
}

byte getPotass(){
  digitalWrite(DE_PIN,HIGH);
  digitalWrite(RE_PIN,HIGH);
  delay(10);
  if(RS485Serial.write(potas,sizeof(potas))==8){
    digitalWrite(DE_PIN,LOW);
    digitalWrite(RE_PIN,LOW);
    for(byte i=0;i<7;i++){
      potasBuffer[i] = RS485Serial.read();
      Serial.print(potasBuffer[i],HEX);
      Serial.print("\t");
    }
    Serial.println();
  }
  return potasBuffer[6];
}

byte getph(){
  digitalWrite(DE_PIN,HIGH);
  digitalWrite(RE_PIN,HIGH);
  delay(10);
  if(RS485Serial.write(ph,sizeof(ph))==8){
    digitalWrite(DE_PIN,LOW);
    digitalWrite(RE_PIN,LOW);
    for(byte i=0;i<7;i++){
      phBuffer[i] = RS485Serial.read();
      Serial.print(phBuffer[i],HEX);
    Serial.print("\t");
    }
    Serial.println();
  }
  return phBuffer[5];
}

byte getmoist(){
  digitalWrite(DE_PIN,HIGH);
  digitalWrite(RE_PIN,HIGH);
  delay(10);
  if(RS485Serial.write(moist,sizeof(moist))==8){
    digitalWrite(DE_PIN,LOW);
    digitalWrite(RE_PIN,LOW);
    for(byte i=0;i<7;i++){
      moistBuffer[i] = RS485Serial.read();
      Serial.print(moistBuffer[i],HEX);
    Serial.print("\t");
    }
    Serial.println();
  }
  return moistBuffer[5];
}

void displayValues(float moistureValue, float phValue, float nitroValue, float phospValue, float potassValue) {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SOIL PARAMETERS");
  
  lcd.setCursor(0, 1);
  lcd.print("Nitrogen: ");
  lcd.print(nitroValue);

  lcd.setCursor(0, 2);
  lcd.print("Phosphorus: ");
  lcd.print(phospValue);

  lcd.setCursor(0, 3);
  lcd.print("Potassium: ");
  lcd.print(potassValue);

  delay(10000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(phValue / 25.0);

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print((float)dht.readHumidity(), 2);
  lcd.print("%");
  
  lcd.setCursor(0, 2);
  lcd.print("Temp: ");
  lcd.print((float)dht.readTemperature(), 2);

  lcd.setCursor(0, 3);
  lcd.print("Moisture: ");
  lcd.print(moistureValue / 10.0);
  delay(10000);
}

/*void RecomendationCrops(char* crop_1, char* crop_2, char* crop_3,  char* crop_4, char* crop_5, char* crop_6) {
  int randomIndex_1 = random(0, sizeof(crops_1) / sizeof(crops_1[0]));
  int randomIndex_2 = random(0, sizeof(crops_2) / sizeof(crops_2[0]));
  int randomIndex_3 = random(0, sizeof(crops_3) / sizeof(crops_3[0]));
  int randomIndex_4 = random(0, sizeof(crops_4) / sizeof(crops_4[0]));
  int randomIndex_5 = random(0, sizeof(crops_5) / sizeof(crops_5[0]));
  int randomIndex_6 = random(0, sizeof(crops_6) / sizeof(crops_6[0]));
  
  crop_1 = crops_1[randomIndex_1];
  crop_2 = crops_2[randomIndex_2];
  crop_3 = crops_3[randomIndex_3];
  crop_4 = crops_4[randomIndex_4];
  crop_5 = crops_5[randomIndex_5];
  crop_6 = crops_6[randomIndex_6];
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RECOMMENDED CROPS");

  lcd.setCursor(0, 1);
  lcd.print(crop_1);

  lcd.setCursor(0, 2);
  lcd.print(crop_2);

  lcd.setCursor(0, 3);
  lcd.print(crop_3);

  lcd.setCursor(9, 1);
  lcd.print(crop_4);

  lcd.setCursor(9, 2);
  lcd.print(crop_5);

  lcd.setCursor(9, 3);
  lcd.print(crop_6);
  
  delay(10000);} */
