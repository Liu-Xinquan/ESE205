#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

#include <AccelStepper.h>
#define HALFSTEP 8
#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10    // IN3 on the ULN2003 driver 1
#define motorPin4  11    // IN4 on the ULN2003 driver 1
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Backlight Color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int light = A1;
int temp = A2;
int rawReadingTemp;
float Temp;
float sumTemp;
float avgTemp;
int rawReadingLight;
float Light;
float sumLight;
float avgLight;

long deltatime = 1000*600;
const long interval = 1000*600;


void setup() {
  Serial.begin(9600);
  Serial.println('a');
  //Set input pins
  pinMode(light, INPUT);
  pinMode(temp, INPUT); 
  
  // Set Stepper Parameters
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  // Welcome Screen
  lcd.print("Welcome");
  lcd.setBacklight(WHITE);
  
}

uint8_t i=0;
uint8_t buttons = lcd.readButtons();
void loop() {
  
  if(stepper1.distanceToGo() == 0){
    
    readTemp();                                   //Read temperature and luminosity
    readLight();
    displayReadings();
    if(avgLight>2.5){                        //Choose how many steps the motor needs to go based on luminosity and temperature
    stepper1.moveTo(4096);
    
    }
    if(avgLight<2.5){                         //Choose how many steps the motor needs to go based on luminosity and temperature
    stepper1.moveTo(-4096);
     }
  }
   stepper1.run();
   
 if(stepper1.distanceToGo() == 0){             //10 min interval between each reading
  while(millis()<deltatime){
   if(stepper1.distanceToGo() == 0){
    userControl();
    
      }
    }
  }
  deltatime += interval;
}


void readTemp(){
   Temp = 0; 
   sumTemp = 0;
   avgTemp = 0;
 for(i=0;i<=100;i++){
   int   rawReadingTem = analogRead(Temp);
   float voltage = rawReadingTem * 5.0;
   voltage /= 1024.0; 
   Serial.println(voltage);
   float temperatureC = (voltage - 0.5) * 100;
   float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
   sumTemp += temperatureF;
 }
   avgTemp = sumTemp/100;
   Serial.println(avgTemp);
}

void readLight(){
   Light = 0; 
   sumLight = 0;
   avgLight = 0;
 for(i=0;i<=1000;i++){
   int rawReadingLight = analogRead(Light);
   Light = rawReadingLight*10/1023 ; 
   sumLight += Light;
   Serial.println('a');
 }
   avgLight = sumLight/1000;
   Serial.println(avgLight);
}

void displayReadings(){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Temp is ");
   lcd.print(avgTemp);
   lcd.setCursor(0, 1);
   lcd.print("Light is ");
   lcd.print(avgLight);
   lcd.setBacklight(TEAL);
}



void userControl(){
  
   //Set Cursor to row 0 column 0 
  lcd.setCursor(0, 0);

  //User Interface Design
  if (buttons) {
    //Clear Display, set cursor to row 0 column 0 
    lcd.clear();
    lcd.setCursor(0,0);
    
    if (buttons & BUTTON_UP) {
      lcd.print("OPENING ");
      lcd.setCursor(0, 1);
      lcd.print("BACK ");
      lcd.setCursor(0, 0);
      lcd.setBacklight(TEAL);
      //Open Blinds
      stepper1.moveTo(4096);
    }

    if (buttons & BUTTON_DOWN) {
      lcd.print("CLOSING ");
      lcd.setCursor(0, 1);
      lcd.print("BACK ");
      lcd.setCursor(0, 0);
      lcd.setBacklight(GREEN);
      //Close Blinds
      stepper1.moveTo(-4096);
      
    }
    
    if (buttons & BUTTON_LEFT) {
      lcd.print("LIGHT SETTINGS ");
      lcd.setBacklight(GREEN);
    }
    
    if (buttons & BUTTON_RIGHT) {
      lcd.print("TEMP SETTINGS ");
      lcd.setBacklight(TEAL);
    }
    
    if (buttons & BUTTON_SELECT) {
      lcd.print("MODE ");
      lcd.setBacklight(VIOLET);
    }
  }
}
