#include <LiquidCrystal.h> 
#include <SparkFunHTU21D.h>
#include <Servo.h>
//#include <time.h>
#define btn 13
#define photo A0

#define closedValve 70
#define openValve 50

HTU21D myHumidity;
Servo myservo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int PhotoValue = 0;
float vout = 0;
float RLDR = 0; 
float Lux = 0; 

void setup() {
  // put your setup code here, to run once:
 myservo.attach(9);
 myservo.write(closedValve);
 myHumidity.begin();
 lcd.begin(16, 2);
 Serial.begin(9600);
 lcd.print("Elec344 Project"); 
 lcd.setCursor(0,1);
 lcd.print("Miguel and Nolan");
  delay(10000);
 lcd.clear();
}

void loop() {
 
while(!digitalRead(btn)){
  
float humid = myHumidity.readHumidity();  
float temp = myHumidity.readTemperature();
//showtime();

 PhotoValue = analogRead(photo);
  vout = PhotoValue/1024.0;
  RLDR = (10000.0 * (5.0 - vout))/vout;     // Equation to calculate Resistance of LDR, [R-LDR =(R1 (Vin - Vout))/ Vout]
   // R1 = 10,000 Ohms , Vin = 5.0 Vdc.
  Lux = (500.0 / RLDR); 

showSensors(temp, humid, Lux);
Serial.println("Temp: \t");
Serial.print(temp);
Serial.print("Humidity: \t");
Serial.print(humid);
  myservo.write(closedValve);
  delay(200);
}
while(digitalRead(btn)){
float humid = myHumidity.readHumidity();  
float temp = myHumidity.readTemperature();
//showtime();

 PhotoValue = analogRead(photo);
  vout = PhotoValue/1024;
  RLDR = (10000.0 * (5 - vout))/vout;     // Equation to calculate Resistance of LDR, [R-LDR =(R1 (Vin - Vout))/ Vout]
   // R1 = 10,000 Ohms , Vin = 5.0 Vdc.
  Lux = (500.0 / RLDR); 

showSensors(temp, humid, Lux);
Serial.println("Temp: \t");
Serial.print(temp);
Serial.print("Humidity: \t");
Serial.print(humid); 
myservo.write(openValve);
delay(200);
}

}
void showSensors( float temp, float humid, float Lux){
  lcd.print("P");
  lcd.setCursor(1,0);
  lcd.print(":");
  lcd.setCursor(2,0);
  lcd.print(Lux);
  lcd.setCursor(0,1);
  lcd.print("T");
  lcd.setCursor(1,2);
  lcd.print(":");
  lcd.setCursor(2,2);
  lcd.print(temp); 
  lcd.setCursor(8,2);
  lcd.print("H");
  lcd.setCursor(9,2);
  lcd.print(":");
  lcd.setCursor(10,2);
  lcd.print(humid);
  
  
   
}
