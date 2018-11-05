//Library Code
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



void setup() {
  Serial.begin(9600);
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
void loop() {
  stepper1.run();
  lcd.setCursor(0, 0);

  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("OPENING ");
      lcd.setCursor(0, 1);
      lcd.print("BACK ");
      lcd.setCursor(0, 0);
      lcd.setBacklight(TEAL);
      stepper1.moveTo(4096);
    }

    if (buttons & BUTTON_DOWN) {
      lcd.print("CLOSING ");
      lcd.setCursor(0, 1);
      lcd.print("BACK ");
      lcd.setCursor(0, 0);
      lcd.setBacklight(GREEN);
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
