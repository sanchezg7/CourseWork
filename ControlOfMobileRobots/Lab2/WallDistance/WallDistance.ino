#include <robotMover.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <irDist.h>


#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

const int SFSensor = A0;
const int SLSensor = A1;
const int SRSensor = A2;
//const int LFSensor = A3;
int shrtF = 0;

double array[] = {0.5, 1, 3, 5, 20};
int index = 3; //set to 3
double Kp; //Kp value
int gain;
int error;
int rVel; //right wheel
int lVel; //left 

int ctlSig; //value from gain and error
int set_pt = 5; //5 inches

int start = 0;
uint8_t buttons;

robotMover myMover; //holds all movement code

unsigned long tBegin; //for time began
unsigned long cTime; //current time

void setup() {
  // put your setup code here, to run once:
  myMover.attach_servos();
  myMover.cmd_vel(90,90);

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setBacklight(BLUE);
  lcd.print("Wall_Distance");

  Kp = array[index]; //setting the Kp value (0.5, 1, 3, 5, and 20)

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);

  buttons = lcd.readButtons();

  if(buttons)
  {
    delay(200);
    if(buttons & BUTTON_SELECT)
    {
      if(start == 0){
        start = 1;
        tBegin = millis();
      } else if(start == 1){
        start = 0;
      }
    } else if(buttons & BUTTON_UP){
      //increment index and set new Kp
      index = (index + 1) % 5;
      Kp = array[index];
      lcd.setCursor(0,0);
      lcd.print("Kp: ");
      lcd.print(Kp);
    }
  }
  
  if(start == 1){
    
      shrtF = average(SFSensor, 5); //short Front
      
      shrtF = computeDistance_SIR(shrtF);
      //calculate error
      error = set_pt - shrtF;
      gain = Kp * error; //some arbirtary value
    
      lVel = 90 - gain;
      rVel = gain + 90; 
    
      //check for saturation
      if(lVel > 100)
      {
        lVel = 100;
      }else if(lVel < 90)
      {
        lVel = 90;
      }
      if(rVel < 80)
      {
        rVel = 80;
      }else if(rVel > 90)
      {
        rVel = 90;
      }
    
      myMover.cmd_vel(lVel, rVel);

      cTime += millis();
      
      printLCD(shrtF);
      Serial.print(Kp);
      Serial.print("\t");
      Serial.print((cTime-tBegin)/10000);
      //Serial.print("  dis:");
      Serial.print("\t");
      Serial.print(shrtF); //distance from the wall
      Serial.print("\n");

      cTime += millis();
      
      //Serial.print((cTime - tBegin));
      //Serial.print("\n");
      delay(500);
  }
}

void printLCD(int shrtF)
{
  if(shrtF != -1)
  {
    
    lcd.setCursor(0,1);
    lcd.print("dist: ");
    lcd.print(shrtF);
    
  }
}

int average(int sensor, int loops)
{
  int value;
  for(int i = 0; i < loops; ++i)
  {
     value += analogRead(sensor);
  }

  return value / loops;
}



