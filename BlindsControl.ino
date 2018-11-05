//Set up Stepper Motor
#include <AccelStepper.h>
#define HALFSTEP 8
#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10    // IN3 on the ULN2003 driver 1
#define motorPin4  11    // IN4 on the ULN2003 driver 1
AccelStepper stepMotor(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

//Set up Display
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//Set up User Interface
uint8_t i=0;
uint8_t buttons = lcd.readButtons();

// Backlight Color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

//Define Variables 
int light = A1;
int temp = A2;
int lightRead = 0; 
int tempRead = 0; 
float vLight = 0; 
float vTemp = 0; 

void setup() {
  Serial.begin(9600);

  //Sensors
  pinMode(lightRead, INPUT);
  pinMode(tempRead, INPUT);
  
  // Set Stepper Parameters
  stepMotor.setMaxSpeed(1000.0);
  stepMotor.setAcceleration(100.0);
  stepMotor.setSpeed(200);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  // Welcome Screen
  lcd.print("Welcome");
  lcd.setBacklight(WHITE);

}

void loop() {
  
  //Turn Step Motor on
  stepMotor.run();

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
      stepMotor.moveTo(4096);
    }

    if (buttons & BUTTON_DOWN) {
      lcd.print("CLOSING ");
      lcd.setCursor(0, 1);
      lcd.print("BACK ");
      lcd.setCursor(0, 0);
      lcd.setBacklight(GREEN);
      //Close Blinds
      stepMotor.moveTo(-4096);
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

////Read values from Sensors
//void read(){
//
//  lightRead = analogRead(light);
//  delay(10);
//  lightRead = analogRead(light);
//  delay(10);
//
//  tempRead = analogRead(temp);
//  delay(10);
//  tempRead = analogRead(temp);
//  delay(10);
//
//}
