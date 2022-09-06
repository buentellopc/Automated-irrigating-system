int Bomba = 5;
// Se incluye libreria Wire para comunicacion I2C
#include <Wire.h>
// Se incluye la libreria NewLiquidCrystal para comunicacion I2C
#include <LiquidCrystal_I2C.h>

const unsigned long SECOND = 1000;
const unsigned long MINUTE = 60*SECOND;
const unsigned long HOUR = 3600*SECOND;


// Definimos los pines de la pantalla LCD
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Direccion del modulo I2C
const int i2c_addr = 0x27;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup() {
  
 
  pinMode(Bomba, OUTPUT);
  digitalWrite(Bomba, HIGH);
  
  
  Serial.begin(9600);
// Se configura la pantalla como 16x2 
  lcd.begin(16,2);
  
}

void loop() {
  
  for (int Sns = 0; Sns < 3; Sns++){
  int sensorValue = analogRead(Sns);
  int HumedadP = map(sensorValue, 1023, 0, 0, 100);
  Serial.print("Porcentaje de humedad del sensor ");
  Serial.print(Sns+1);
  Serial.print(": ");
  Serial.println(HumedadP);  

  // Parte agregada
  lcd.setCursor(0,0);                  
  lcd.print("Sensor ");
  lcd.print(Sns+1);
  lcd.print(": ");
  lcd.print(HumedadP);

  
  delay(10000);

  if (HumedadP < 30){
    
    pinMode(Sns+6, OUTPUT);
    Serial.print("Valvula ");
    Serial.print(Sns+1);
    Serial.println(" activada");

    lcd.setCursor(0,1);   // LCD
    lcd.print("Valvula ");
    lcd.print(Sns+1);
    lcd.print(" activada");
    
    
    digitalWrite(Sns+6, LOW);
    delay(2*MINUTE);

    digitalWrite(Sns+6, HIGH);
    delay(3000);
    
  }


  lcd.clear();
  
  
  }

for (int sec = 4; sec >= 1; sec--){
  
lcd.setCursor(0,0);
lcd.print("Lectura en: ");
lcd.setCursor(3,1);
lcd.print(sec);
lcd.print(" horas");
delay(HOUR);  
}

lcd.clear();

digitalWrite(Bomba, LOW);
delay(5000);

digitalWrite(Bomba, HIGH);

} 
