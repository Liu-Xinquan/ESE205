#include <AccelStepper.h>
#define HALFSTEP 8
int light = A1;
int temp = A2;
float voltage;
int count = 0; 
float sum = 0;
float sum1 = 0;
int count2 = 0;
float sum2 = 0;
float sum3 = 0;
float rAvgLight;
float rAvgTemp;
int n = 1;
int lightRead = 0;
int tempRead = 0;

#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10    // IN3 on the ULN2003 driver 1
#define motorPin4  11    // IN4 on the ULN2003 driver 1
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(light, INPUT);
  pinMode(temp, INPUT);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  analogReference(INTERNAL);
}

//void loop() {
//  if(stepper1.distanceToGo() == 0){
//    read();                                       //Read temperature and luminosity
//    if( realaverage1>2.5){                        //Choose how many steps the motor needs to go based on luminosity and temperature
//  //  Serial.println('1');
//    stepper1.moveTo(4096);
//    
//    }
//    if(realaverage1<2.5){                         //Choose how many steps the motor needs to go based on luminosity and temperature
//  //  Serial.println('2');
//    stepper1.moveTo(-4096);
//    
//    }
//  }
// //  Serial.println("run");
//   stepper1.run();
// //  Serial.println(stepper1.currentPosition());
//   if(stepper1.distanceToGo() == 0){
//   //delay(1000);
//   }
//}


void read(){
  //Two loops in case of overflow
  //Take in 1000 readings of temperature and lumonosity 
  //Calculate the average
  while(count2<=3){
     while(count<=1000){
      
         lightRead = analogRead(light);
         delay(20);
         lightRead = analogRead(light);
         delay(20);
         
         tempRead = analogRead(temp);
         delay(20);
         tempRead = analogRead(temp);
         delay(20);
         
         Serial.print(light);
         Serial.print(' ');
         Serial.println(temp);
         float vLight = lightRead*45/1023.0;
         float vTemp = tempRead*1100/1023.0;
         sum += vLight;
         sum1 += vTemp;
         count ++;
        }
        
     float average1 = sum/count;
     float average2 = sum1/count;
     sum2 += average1;
     sum3 += average2;
     count2 ++;
     count = 0;
     sum = 0;
     sum1 = 0;
     
   }
   
//  realaverage1 = sum2/count2;             //Final voltage value of luminosity
//  realaverage2 = sum3/count2;             //Final voltage value of temperature
//  count2 = 0;
//  sum2 = 0;
//  sum3 = 0;
//  float temperature = 25 + (realaverage2 - 750) * .1;           //Convert voltage value to real temperature
//  //Serial.println(realaverage1);
//  //Serial.println(temperature);
 }
