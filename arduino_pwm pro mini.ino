//sda=A4  scl=A5
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x3F);

const int hallPin=10;
const unsigned long sampleTime=1000;


int volume_pin = A1;
int read_ADC;

int pwm_pin = 6;

int duty_cycle;
int Speed;
 
void setup() {
  pinMode(hallPin,INPUT);
  pinMode(volume_pin,INPUT);
  pinMode(pwm_pin, OUTPUT);
  //TCCR0B = (TCCR0B & 0b11111000) | 0x02;
  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  delay(2000);
  lcd.clear();
  lcd.setBacklight(255);
}
 
void loop() {     
int rpm=getRPM();

read_ADC = analogRead(volume_pin);
duty_cycle =map(read_ADC,0,1023,0,255); 
Speed = map(read_ADC, 0, 1023, 100, 0);

if(Speed>0){ 
analogWrite(pwm_pin,duty_cycle); 
}else{digitalWrite(pwm_pin, LOW);}

 
lcd.setCursor(0,0);
lcd.print("Set Speed: ");
lcd.print(Speed); 
lcd.print("%  ");
lcd.setCursor(0,1);
lcd.print("RPM: ");
lcd.print(rpm); 
lcd.print("  ");
   
}

int getRPM(){
//sample for sampleTime in millisecs
int kount=0;
boolean kflag=LOW;
unsigned long currentTime=0;
unsigned long startTime=millis();
while (currentTime<=sampleTime){
if(digitalRead(hallPin)==HIGH){kflag=HIGH;}
if(digitalRead(hallPin)==LOW && kflag==HIGH){
kount++;
kflag=LOW;
}
currentTime=millis()-startTime;
}
int kount2rpm = int(60000./float(sampleTime))*kount;
return kount2rpm;
}
