#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;  //for laser distance sensor CJVL 53L0X v2

int ENA = 5;             
int IN1= 7;
int IN2= 8;
int Clock = A5;
int Data = A4;
int distance;
int i=0;
int PWM=0;
void setup() {
  pinMode (IN1,OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT) ;
  Serial.begin (9600);
  Wire.begin();
  pinMode (Data, INPUT);
  pinMode (Clock, INPUT);
  sensor.init();
  sensor.setTimeout(1000);
}

void tof() {
  
  distance = (sensor.readRangeSingleMillimeters());
  
  if (distance <2000){
  int PWM=distance;
  PWM= map (PWM,0,1300,50,0);     // mapping the distance sensor values into PWM signals using Map function
  Serial.print ("distance=");Serial.print(distance); Serial.print("; PWM=");Serial.print(PWM);
  Serial.println(); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA, PWM);
  
  } else {
    int PWM=35;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,PWM);
    Serial.print(" distance=Range cannot be detected");  Serial.print("; PWM="); Serial.print(PWM);
    Serial.println();
   
  }
  
}

void loop() {
  tof();
  
  delay(100);
  //Serial.print(distance);
  //Serial.println();
  if (distance<50){
    i=i+1;
    Serial.print("Time="); Serial.print(i); //Serial.print("sec");
  } else
 {
  i=0;
 }
  if (i>25){
  analogWrite(ENA,0); 
  }
}
  
  
