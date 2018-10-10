#include <AccelStepper.h>
#define HALFSTEP 8
int input = A1;
float voltage;
int count = 0; 
float sum = 0;
int count2 = 0;
float sum2 = 0;
float realaverage;
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input, INPUT);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
}

void loop() {
  if(stepper1.distanceToGo() == 0){
    read();
    if( realaverage>2.5){
    stepper1.moveTo(4096);
    }
  if(realaverage<2.5){
    stepper1.moveTo(-4096);
    }
  }
    stepper1.run();
   if(stepper1.distanceToGo() == 0){
    delay(10000);
   }
}


void read(){
  while(count2<=100){
     while(count<=1000){
         int reading = analogRead(input);
         float voltage = reading*45/1024.0;
         sum += voltage;
         count ++;
        }
     float average = sum/count;
     sum2 += average;
     count2 ++;
     count=0;
     sum=0;
   }
  realaverage = sum2/count2;
  count2 = 0;
  sum2 = 0;
  Serial.println(realaverage);
 }
