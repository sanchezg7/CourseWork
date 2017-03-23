#include <robotMover.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int debugMovement = 0; //0 - stopped, 1 - moving
int go = 0; //not started the motion

robotMover myMover; //mover object
void setup() {
  // put your setup code here, to run once:
// put your setup code here, to run once:
  //LServo.attach(2);
  //RServo.attach(3);
  myMover.attach_servos(); //have to attach servos in the scope of the program
  myMover.cmd_vel(90,90); //initialize motors to stop
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.setBacklight(WHITE);
  lcd.print("square");
  //lcd.print("SETUP DONE");
}

void loop() {
  // put your main code here, to run repeatedly:
 uint8_t buttons = lcd.readButtons();
  delay(100);
  if (buttons){
    //delay(200);
    lcd.clear();

    //for debugging purposes
    if (buttons & BUTTON_SELECT){
      if(debugMovement == 0) 
      {
        lcd.print("Moving...");
        myMover.cmd_vel(100, 80); //move forward
        
        debugMovement = 1;
        
      } else if (debugMovement == 1){

        
      }
    } else if( buttons & BUTTON_UP){
      
      for(int i = 0; i < 4; ++i)
      {
        lcd.print("moving forward");
        myMover.move_fwd(3800);
        lcd.clear();
        lcd.print("left turn");
        myMover.spin_cntclkwse();
        lcd.clear();
      }
      
      
      
    } else if(buttons & BUTTON_LEFT){
      
    } else if(buttons & BUTTON_RIGHT){
      for(int i = 0; i < 4; ++i)
      {
        lcd.print("moving forward");
        myMover.move_fwd(3800);
        lcd.clear();
        lcd.print("right turn");
        myMover.spin_clkwse();
        lcd.clear();
      }
      
    }
}
}
