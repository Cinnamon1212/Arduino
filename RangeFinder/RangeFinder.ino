#include <dht.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define trigPin 6
#define echoPin 5
#define DHT11_PIN 7
#define buzzPin 9
#define buzzVolume 100
dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2);

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 return Temp;
}


void setup() {
  Serial.begin (9600);
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  lcd.clear();
  float duration, distance;
  float speed;
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  speed = 331.4 + (0.606 * DHT.temperature) + (0.0124 * DHT.humidity);
  distance = (duration / 2) * (speed / 10000);
  
  if (distance >= 150 || distance <= 2){
    Serial.print("Distance = ");
    Serial.print("Out of range: ");
    Serial.println(distance);
    analogWrite(buzzPin, 0);
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    lcd.print("Distance: ");
    lcd.setCursor(2,1);
    lcd.print(distance);
    lcd.setCursor(10,1);
    lcd.print("cm");
    delay(1000);
    analogWrite(buzzPin, buzzVolume);
  }
  delay(1000);
}
