#include <irDist.h>
#include <robotMover.h>
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

robotMover myMover; //holds all movement code

void setup() {
  // put your setup code here, to run once:
  //LServo.attach(2);
  //RServo.attach(3);
  myMover.attach_servos(); //have to attach servos in the scope of the program
  myMover.cmd_vel(90,90); //initialize motors to stop

  lcd.begin(16, 2);
  lcd.setBacklight(TEAL);
  lcd.print("openLoopMotor");
  //lcd.print("SETUP DONE");
}
  
  
void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();
  delay(200);
  if (buttons){
    //delay(200);
    lcd.clear();

    //for debugging purposes
    if (buttons & BUTTON_SELECT){
      if(debugMovement == 0) 
      {
        myMover.cmd_vel(100, 80); //move forward
        debugMovement = 1;
        lcd.print("Moving...");
      } else if (debugMovement == 1){

        myMover.cmd_vel(90, 90); //stop the robot
        debugMovement = 0;
        lcd.print("Stopped");
      }
    } else if( buttons & BUTTON_UP){
      lcd.print("Forward 50 Inches");
      myMover.move_fwd(9000);
      lcd.clear();
      lcd.print("Backward 50 Inches");
      myMover.move_bkwd(9000);
      lcd.clear();
      
    } else if(buttons & BUTTON_LEFT){
      lcd.print("Counter");
      lcd.setCursor(0,1);
      lcd.print("Clockwise");
      
      myMover.cnt_circle_20(20000); //20 seconds
    } else if(buttons & BUTTON_RIGHT){
      lcd.print("Clockwise");
      myMover.circle_20(20000); //20 seconds   
    }
  }
  
  //delay(2000);
}

