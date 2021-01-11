
#include "DHT.h"
#include <LiquidCrystal.h>

const int DHTPIN = 6;     // Anturin pinni
const int DHTTYPE = DHT22;   // DHT 22  (AM2302)
const int fan = 8; // Tuulettimen pinni
/*const int LCD = 11; // Näytön pinni*/

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // LCD pinnien määritys
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT dht(DHTPIN, DHTTYPE);
int maxHum = 50;  //määritetään kosteus milloin tuuletin menee päälle
int maxTemp = 30; //määritetään lämpötila milloin tuuletin menee päälle

void setup() {
  pinMode(fan, OUTPUT);
  /*pinMode(LCD, OUTPUT);
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);*/
  Serial.begin(9600); // Alustetaan sarjaportti
  dht.begin();

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Temperature");

  lcd.setCursor(0,1);
  lcd.print("Humidity");
}

void loop() {
  // viive
  delay(200);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
   }else{
    lcd.setCursor(12,1); 
    lcd.print(h);
    lcd.setCursor(12,0); 
    lcd.print(t); 
    delay(500);
    if (Serial.available()){
      lcd.write(Serial.read());
    }
   }
  
  if(h > maxHum || t > maxTemp) {
      digitalWrite(fan, HIGH);
  } else {
     digitalWrite(fan, LOW); 
  }
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

}
