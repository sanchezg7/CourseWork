#include <robotMover.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <irDist.h>

//lcd colors
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
const int LFSensor = A3;

int go = 0; //go flag for Navigation

//SENSOR Readings
int shrtF = 0;
int shrtL = 0;
int longF = 0;

//SERVOR Velocities
int rVel;
int lVel;

uint8_t buttons;

robotMover myMover;

void setup() 
{
  // put your setup code here, to run once:
  myMover.attach_servos();
  myMover.cmd_vel(90, 90);

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setBacklight(WHITE);
  lcd.print("Navigation");
  lcd.setCursor(0,0);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  buttons = lcd.readButtons();

  if(buttons){
    delay(200); //debounce
    if(buttons & BUTTON_SELECT){
      if(go == 0){
        //start robot moving forward
        lVel = 100;
        rVel = 80;
        go = 1;
        Navigation();
      }
    }
    
  }
  printLCD(trueDist(SFSensor, 20), trueDist(SLSensor, 20), 90, 90);
}


int trueDist(int sensor, int loops)
{
  int value = 0;
  for(int i = 0; i < loops; ++i)
  {
    int distance = computeDistance_SIR(analogRead(sensor));
    if(distance != -1)
    {
      value += distance;  
    }
    
  }
  return value / loops;
}

int longTrueDist(int LongSensor, int loops)
{
  int value = 0;

  for(int i = 0; i < loops; ++i)
  {
    int distance = longComputeDist(analogRead(LongSensor));
    if(distance != -1)
    {
      value += distance;  
    }
  }
  return value / loops;
}


void printLCD(int shrtF, int shrtL, int lVel, int rVel)
{
  if( shrtF != -1)
  {
     lcd.setCursor(0,1);
     lcd.print("F:");
     lcd.print(shrtF);
     lcd.print(" ");
  }
  if(shrtL != -1)
  {
    lcd.setCursor(5,1);
    lcd.print("L:");
    lcd.print(shrtL);
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
    lcd.setCursor(7, 0);
    lcd.print("rV: ");
    lcd.print(rVel);
  }
}

void Navigation()
{
  lcd.clear();
  int lngF; //long Front value
  bool cornerFlg = false;
  bool leftTrnFlg = false;

  int counter = 0;
  int wfCntr = 0;
  while(1)
  {
    shrtF = trueDist(SFSensor, 10);
    shrtL = trueDist(SLSensor, 10);
    //longF = longTrueDist(LFSensor, 20);
    
    printLCD(shrtF, shrtL, lVel, rVel);

    //CORNER case - YELLOW
    //LEFT turn - GREEN
    //too FAR - TEAL
    //too CLOSE - RED

    if(shrtL < 9)
    {
      wallFollow(&wfCntr, shrtL);

      if(cornerFlg)
      {
        stopRobot();
        if(isAWall(shrtF))
        {
          //perform corner turn
          rightTurn();
        }
        cornerFlg = false;
        continue;
      }else 
      {
        cornerFlg = isAWall(shrtF); 
        
      }
      
    }else if(shrtL >= 9)
    {
      //suspect that it is time for a LEFT turn sequence
      if(leftTrnFlg)
      {
        leftTurn();
        leftTrnFlg = false;
        continue;

      }else
      { 
        stopRobot();
        leftTrnFlg = true;
        continue;
      }
        
    }
  }
}

bool isAWall(int shrtF)
{
  return shrtF < 5;
}


void wallFollow(int* wfCntr, const int shrtL)
{
  int threshold = 4;
  if(shrtL > threshold)
  {
    //Left Wall is in range, follow it accordingly.
     ++*wfCntr;   
     moveCloserToWall();
     if(*wfCntr == 5)
     {
        wfCntr = 0;
        //offset the movement by moving in the opposite direction
        moveAwayFromWall();  
     }
   }else if(shrtL < threshold)
   {
      //The robot is too close to wall. Move away.
      ++*wfCntr;
      moveAwayFromWall();
      if(*wfCntr == 3)
      {
        wfCntr = 0;
        moveCloserToWall();
      }
  } else if(shrtL == threshold)
  {
    *wfCntr = 0;
    alignWithWall();
  }
  return;
}

void rightTurn()
{  
  int mlVel = 95;
  int mrVel = 96;
  myMover.cmd_vel(mlVel, mrVel);
  delay(800);
}

void leftTurn()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Left Turn");
  
  moveForwardALittle(1000);
  
  stopRobot(); 
  
  //perform the left turn!  
  int mlVel = 90;
  int mrVel = 80;
  myMover.cmd_vel(mlVel, mrVel);
  delay(1200);

  moveForwardALittle(1000);
}


void moveCloserToWall()
{ //too far from wall 
  //myMover.cmd_vel(93, 85);
  int mlVel = 95; 
  int mrVel = 83; //SPEED right up
  myMover.cmd_vel(mlVel, mrVel);
  //delay(200);  
}

void moveAwayFromWall()
{ //too close to wall
 // myMover.cmd_vel(95, 87);
 int mlVel = 97; //SPEED left up
 int mrVel = 86; 
 myMover.cmd_vel(mlVel, mrVel);
 //delay(200);       
}

void alignWithWall()
{ //align
  //myMover.cmd_vel(95, 85);
  int mlVel = 95;
  int mrVel = 86; //right motor is weaker
  myMover.cmd_vel(mlVel, mrVel);
  
}

void moveForwardALittle(int mDelay)
{ //move forward a little before left turn
  //myMover.cmd_vel(95, 85);//allow robot to move forward a bit before turning left
  int mlVel = 95;
  int mrVel = 85;
  myMover.cmd_vel(mlVel, mrVel);
  delay(mDelay); //allow the robot to move to the center of the cell to spin to the left
}

void stopRobot()
{//stops robot
  //myMover.cmd_vel(90,90);
  int mlVel = 90;
  int mrVel = 90;
  myMover.cmd_vel(mlVel, mrVel);
  delay(500);
}

