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
  myMover.attach_servos(); //have to attach servos in the scope of the program
  myMover.cmd_vel(90,90); //initialize motors to stop
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.setBacklight(VIOLET);
  lcd.print("Figure 8");
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();
  delay(200);
  if(buttons){
    lcd.clear();

    if(buttons & BUTTON_UP){
      lcd.print("Making 8 loop");
      lcd.clear();
      lcd.print("1/4 clk");
      myMover.fig8_circle_20(6000);// 1/4 of a circle
      //lcd.clear();
      //lcd.print("1/8 clk");
      //myMover.fig8_circle_20(1000);// 1/8 of a circle
      lcd.clear();
      lcd.print("Straight");
      myMover.move_fwd(4860);//move forward 15inches
      lcd.clear();
      lcd.print("1/8 cnt_clk");
      myMover.fig8_cnt_circle_20(2500); // 1/8 of a circle
      lcd.clear();
      lcd.print("1/2 cnt_clk");
      myMover.fig8_cnt_circle_20(9000); // 1/2 of a circle
      lcd.clear();
      lcd.print("1/8 cnt_clk");
      myMover.fig8_cnt_circle_20(2400); // 1/8 of a cirlce
      lcd.clear();
      lcd.print("Straight");
      myMover.move_fwd(3800);//move forward 15inches
      lcd.clear();
      lcd.print("1/8 clk");
      myMover.fig8_circle_20(2500);// 1/8 of a circle
      lcd.clear();
      lcd.print("1/4 clk");
      myMover.fig8_circle_20(6000);// 1/4 of a circle  
      lcd.clear();
      lcd.print("Done");    
    }
    
  }

}
