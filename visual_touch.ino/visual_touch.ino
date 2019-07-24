#define MOTOR_IN1 10
#define MOTOR_IN2 11
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;  //for laser distance sensor CJVL 53L0X v2
int Clock = A5;
int Data = A4;
int distance;
int PWM;

void setup() {
  Serial.begin(9600);
  while (!Serial){
      delay(10);
    };
  Serial.println("DRV8871 test");
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode (Data, INPUT);
  pinMode (Clock, INPUT);
  Wire.begin();
  sensor.init();
  sensor.setTimeout(1000);
}

void MOTOR() {
 
 digitalWrite(MOTOR_IN1, LOW);
 analogWrite(MOTOR_IN2, PWM);
}

void loop(){
  distance = (sensor.readRangeSingleMillimeters());
  if (distance <2000){
  int PWM=distance;
  PWM= map (PWM,0,1300,75,0);     // mapping the distance sensor values into PWM signals using Map function
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_IN1, PWM);
  Serial.print ("distance=");Serial.print(distance); Serial.print("; PWM=");Serial.print(PWM);
  Serial.println(); 

  
  } else {
    int PWM=35;
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_IN1, PWM);
    Serial.print(" distance=Range cannot be detected");  Serial.print("; PWM="); Serial.print(PWM);
    Serial.println();
   
  }
}
 
