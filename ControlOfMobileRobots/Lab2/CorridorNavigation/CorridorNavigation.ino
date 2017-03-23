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
#define SET_PT 5 //5 inches

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
int go = 0;

const int SFSensor = A0;
const int SLSensor = A1;
const int SRSensor = A2;
const int LFSensor = A3;

//SENSOR READINGS
int shrtF = 0; //short front reading
int shrtL = 0; //short left reading
int shrtR = 0; //short right reading

//CONTROL SYSTEM VARIABLES
double array[] = {0.5, 1, 3, 5, 20};
int index = 2;
double Kp; //Kp value
int gainF;
int gainL;
int gainR;
int errorF; //front error
int errorL; //left error
int errorR; //right error

//SERVOR VELOCITIES
int rVel; //right wheel
int lVel; //left 

uint8_t buttons;

robotMover myMover;

void setup() {
  // put your setup code here, to run once:
  myMover.attach_servos();
  myMover.cmd_vel(90,90);

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setBacklight(WHITE);
  //lcd.print("Corridor Navigation");
  lcd.setCursor(0,0);

  Kp = array[index];

}

void loop() {
  // put your main code here, to run repeatedly:
  buttons = lcd.readButtons();
  
  if(buttons)
  {
    delay(200);
    if(buttons & BUTTON_SELECT)
    {
      if(go == 0){
        lVel = 100;
        rVel = 80; 
        go = 1;
      }
           
    } else if(buttons & BUTTON_UP)
      {
        index = (index + 1) % 5;
        Kp = array[(index +1) % 5];
        lcd.setCursor(0,0);
        lcd.print("Kp ");
        lcd.print(Kp);
      }
  }
  if (go == 1){
    corridorNavigation(Kp);  
  }
  printLCD(computeDistance_SIR(average(SFSensor,5))
      , computeDistance_SIR(average(SLSensor,5)), computeDistance_SIR(average(SRSensor,5)), 90, 90);
      
  delay(250);

}

//make multiple measurements and return the average
int average(int sensor, int loops)
{
  int value;
  for(int i = 0; i < loops; ++i)
  {
     value += analogRead(sensor);
  }
  return value / loops;
}

//handles the corridor navigation
void corridorNavigation(int Kp)
{
  shrtF = average(SFSensor, 5);
  shrtL = average(SLSensor, 5);
  shrtR = average(SRSensor, 5);

  shrtF = computeDistance_SIR(shrtF);
  shrtL = computeDistance_SIR(shrtL);
  shrtR = computeDistance_SIR(shrtR);

  errorF = SET_PT - shrtF; //error from FRONT
  errorL = SET_PT - shrtL; //error from LEFT
  errorR = SET_PT - shrtR; //error from RIGHT

  
  gainF = errorF * Kp;
  gainL = errorL * Kp;
  gainR = errorR * Kp; 

  if(shrtF > 6) //check front wall to know to keep going forward
  {
    if(shrtR < 6) //too close to right wall
    {
      lVel = 93 - gainR;
      rVel = 85 + gainR;
    }else if(shrtL < 6) //too close to left wall
    {
      lVel = 94 - gainL;
      rVel = 88 + gainL;
    }else if(shrtL == 5 && shrtR == 5) //align
    {
      lVel = 90 - gainF;
      rVel = 90 + gainF;
    }
  } else if(shrtF <= 6)//decision to make right turn
  {
    lVel = 97 - gainF;
    rVel = 89 + gainF;
  }
  

  follow_vel(lVel, rVel);
}
void follow_vel(int lVel, int rVel)
{
  if(lVel > 100) lVel = 100;
    else if(lVel < 90) lVel = 90; //prevent go backward

   //check for saturation in right wheel
   if(rVel < 81) rVel = 81;
        else if(rVel > 90) rVel = 90;

    myMover.cmd_vel(lVel, rVel);

    Serial.print("lVel:");
    Serial.print(lVel);
    Serial.print("\trVel");
    Serial.print(rVel);
    Serial.print("\n");
}
  

void printLCD(int shrtF, int shrtL, int shrtR, int lVel, int rVel)
{

  if( shrtF != -1)
  {
     lcd.setCursor(0,1);
     lcd.print("F: ");
     lcd.print(shrtF);
     lcd.print(" ");
  }
  if(shrtL != -1)
  {
    lcd.setCursor(6,1);
    lcd.print("L: ");
    lcd.print(shrtL);
    lcd.print(" ");
  }
  if(shrtR != -1)
  {
    lcd.setCursor(11,1);
    lcd.print("R: ");
    lcd.print(shrtR);
    lcd.print(" ");
  }

  if(lVel != 90)
  {
    lcd.setCursor(0,0);
    lcd.print("lV: ");
    lcd.print(lVel);
  }

  if(rVel != 90)
  {
    lcd.setCursor(6, 0);
    lcd.print("rV: ");
    lcd.print(rVel);
  }
}

