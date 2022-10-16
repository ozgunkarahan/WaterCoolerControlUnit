#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
float temp;
bool flag = true;
OneWire oneWire(2);
DallasTemperature sensors(&oneWire);
void setup() {
  lcd.begin(16,2);
 
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin();
  pinMode(3,OUTPUT);
  
  
}

void loop() {
  sensors.requestTemperatures();
  temp=sensors.getTempCByIndex(0);
  Serial.println(temp);
  flag=controller(3,temp,flag);
  lcd.setCursor(0,0);
  lcd.print("SU SICAKLIGI ");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print(" C");
  delay(1000);

  

}
bool controller(int pinNo,float temp,bool flag){
  if(temp>7){
    digitalWrite(pinNo,LOW);
    flag=true;
    onoff(true);
    
  }
  else if(temp<5){
    flag=false;
    digitalWrite(pinNo,HIGH);
    onoff(false);
  }
  else if(flag==true){
    digitalWrite(pinNo,LOW);
    onoff(true);
  }
  else if(flag==false){
    digitalWrite(pinNo,HIGH);
    onoff(false);
    
  }
  return flag;
}
void onoff(bool check){
  lcd.setCursor(12,1);
  if(check == true){
    
    lcd.print("ON ");
  
    
  }
  else{
    lcd.print("OFF");
  }
}
