/*********************
//  IMPORTANT

// Before to run this program, you have to install the RGB-LCD library for arduino

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Servo.h>
#include <StandardCplusplus.h>
#include <irDist.h>
#include <robotMover.h>
#include <Graph.h>


Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7


//Servo LServo;
//Servo RServo;

const int SFSensor = A0;
const int SLSensor = A1;
const int SRSensor = A2;
const int LFSensor = A3;
int shrtL;


int Ini =1;
int End =1;
int Dir =0;
int Select=1;
int SetUp=0;

//initialization
robotMover myMover;
Graph myGraph;


void setup() {
// put your setup code here, to run once:
  myMover.attach_servos();
  myMover.cmd_vel(90, 90);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  lcd.print("      USF  2016");
  lcd.setCursor(1, 6);
  
  lcd.setBacklight(GREEN);
//    LServo.attach(2);
  //RServo.attach(3);
  //LServo.write(90); 
  //RServo.write(90); 
  

}
  
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
if (SetUp == 0){
    SetParam();
}


if (SetUp == 1)
{
  //LServo.write(91); 
  //RServo.write(89); 

//  Ini = 1;
//  End = 13;
//  Dir = 1;
  
  lcd.setCursor(0, 1);
  lcd.print(Ini);
  lcd.print(' ');
  lcd.print(End);
  lcd.print(' ');
  lcd.print(Dir);
  lcd.print(' ');

  //setup the maze and start and end position
  myGraph.makeGraph(3); //maze 1
  myGraph.setStartEnd(Ini,End);
  myGraph.findPath();
  myGraph.setPath();
  stack <int> tempPath = myGraph.getPath();
  printPath(tempPath); //print the planned path after BFS traversal
  
  char myDirection;
  if (Dir==0) myDirection = 'N';
  if (Dir==1) myDirection = 'E';
  if (Dir==2) myDirection = 'S';
  if (Dir==3) myDirection = 'W';
  goToGoal(Ini,tempPath,myDirection);//start cell, path, orientation
  }
}

void goToGoal(int startCell, stack<int> tempPath, char myDirection)//navigation to the goal
{
  int currentCell = startCell;
  int nextCell;
  char orientation = 'N';
  int wfThresh = 110;
  
  //int frwdTime = 3800;
  int halfTime = 1800;
  lcd.clear();
  bool isfirstTime = true;
  bool islastTime = tempPath.empty();

  //start in correct Dir
  orientation = getOrientation(currentCell,nextCell);
//  adjRbtDir(orientation, myDirection);
  
  while(!(islastTime))
  {
    lcd.setBacklight(WHITE);
    nextCell = tempPath.top();
    tempPath.pop();
    islastTime = tempPath.empty();    
    /*
			New changes 30 Apr 2016
		*/
 
    for(int i = 0; i < 2; ++i)
    {
      if(isfirstTime)
      {
        isfirstTime = false;
        i = 1;
      }

      if(i == 1)
      {
        lcd.setCursor(8,0);
        lcd.print("   ");
        //adj rbt orientation in the middle of the cell
        //obtain the direction and assert the robot is in that direction
        orientation = getOrientation(currentCell,nextCell);
        adjRbtDir(orientation, myDirection);
        printLCD(currentCell, myDirection, nextCell, orientation);
        //myMover.cmd_vel(90,90);
      }
			shrtL = trueDist(SLSensor, 10);
		  if(shrtL < 8) // we think there is a wall here
		  {
				//WALL FOLLOW for half a cell and retry
		    int cellCntr = 0;
		    int wfCntr = 0;
        lcd.setBacklight(RED);
        lcd.setCursor(13, 0);
        lcd.print("WF");
        delay(500);
		    while(cellCntr < wfThresh)
		    {
          printVal(cellCntr);
					shrtL = trueDist(SLSensor, 10);
		      myMover.wallFollow(&wfCntr, &cellCntr, shrtL);
		      ++cellCntr;  
		    }
       
		  }else if(shrtL > 8)
		  {
        lcd.setBacklight(BLUE);
        lcd.setCursor(13,0);
        lcd.print("BL");
        delay(500);
        myMover.moveForwardALittle(halfTime);
		  }
     myMover.stopRobot();
     myMover.moveForwardALittle(200);
    }

    lcd.setCursor(8, 0);
    lcd.print("NC!");
    lcd.setCursor(13,0);
    lcd.print("  ");
    currentCell = nextCell;
    myMover.stopRobot();

		/*********************
			End new changes 30 Apr 2016
		*/
  }

  //move to the last cell
  shrtL = trueDist(SLSensor, 10);
  if(shrtL <= 8) // we think there is a wall here
  {
    //WALL FOLLOW for half a cell and retry
    int cellCntr = 0;
    int wfCntr = 0;
    lcd.setBacklight(RED);
    lcd.setCursor(13, 0);
    lcd.print("WF");
    delay(500);
    while(cellCntr < wfThresh)
    {
      printVal(cellCntr);
      shrtL = trueDist(SLSensor, 10);
      myMover.wallFollow(&wfCntr, &cellCntr, shrtL);
      ++cellCntr;  
    }
  }else if(shrtL > 8)
  {
    lcd.setBacklight(BLUE);
    lcd.setCursor(13,0);
    lcd.print("BL");
    delay(500);
    myMover.moveForwardALittle(halfTime);
  }
  myMover.moveForwardALittle(300);
  myMover.cmd_vel(90,90);
  lcd.clear();
  lcd.setBacklight(GREEN);
  lcd.print("Done. Suckas.");
  while(1);
}

void adjRbtDir(char orientation, char& myDirection)
{
  int leftDelay = 900;
  int rightDelay = 900;
  //lcd.clear();
  lcd.setCursor(12,1);
  lcd.print(myDirection);
  lcd.print("->");
  lcd.print(orientation);
  lcd.setBacklight(YELLOW);
  delay(500);
  if(!(orientation == myDirection))
    {
      myMover.stopRobot();
      switch(myDirection){
        case 'N':
          if(orientation == 'S') { for(int i = 0; i < 2; ++i) myMover.rightTurn(rightDelay);}
          if(orientation == 'E') myMover.rightTurn(rightDelay); 
          if(orientation == 'W') 
          {
            lcd.setBacklight(VIOLET);
            myMover.leftTurn(leftDelay); 
          }
          break;
        case 'E':
          if(orientation == 'N') myMover.leftTurn(leftDelay); 
          if(orientation == 'S') myMover.rightTurn(rightDelay); 
          if(orientation == 'W') {for(int i = 0; i < 2; ++i) myMover.rightTurn(rightDelay); }
          break;
        case 'S':
          if(orientation == 'W') myMover.rightTurn(rightDelay); 
          if(orientation == 'N') {for(int i = 0; i < 2; ++i) myMover.rightTurn(rightDelay); }
          if(orientation == 'E') myMover.leftTurn(leftDelay); 
          break;
        case 'W':
          if(orientation == 'N') myMover.rightTurn(rightDelay); 
          if(orientation == 'E') {for(int i = 0; i < 2; ++i) myMover.rightTurn(rightDelay);} 
          if(orientation == 'S') myMover.leftTurn(leftDelay);
          break;
      } 
    }
    myMover.cmd_vel(90,90);
    myDirection = orientation;
}

void printVal(int val)
{
  lcd.setCursor(5,1);
  if(val < 10)
  {
    lcd.print(val);
  }else if(val >=10)
  {
    lcd.print(val);
  }
}

void printLCD(int currentCell, char mDirection, int nextCell, char orientation)
{
     if(currentCell < 10)
    {
      lcd.setCursor(0,0);
      lcd.print(" ");
      lcd.print(currentCell);
      
    }else if(currentCell >= 10)
    {
      lcd.setCursor(0,0);
      lcd.print(currentCell);
    }
    if(nextCell < 10){
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.print(nextCell);
    } else if(nextCell >= 10)
    {
      lcd.setCursor(0, 1);
      lcd.print(nextCell);
    }
    lcd.print(orientation);
}

void printPath(stack <int> tempPath)
{
  int lcd_cursor = 0;
  int lcd_line = 0;
  int pathVal;
  lcd.clear();
  int cnt = 0;
  while (!(tempPath.empty()))
  {
    
    //pop and print to the lcd respective spot
    pathVal = tempPath.top();
    tempPath.pop();
    //lcd.setCursor(lcd_cursor, lcd_line);
    
    lcd.print(pathVal);
    lcd.print(" ");
    cnt += 1;
    
    if(cnt == 5) 
    { 
      lcd.setCursor(0,1);
    } 
  }
  lcd.setBacklight(WHITE);
  delay(2000);
  
}

void SetParam(){

 delay(100);
 lcd.clear();
  uint8_t buttons = lcd.readButtons();
  if (Select==1){
        lcd.setCursor(0, 0);
        lcd.print("Starting Locat.");
        lcd.setCursor(0, 1);
        lcd.print(Ini);
        
    }

  if (Select==2){
        lcd.setCursor(0, 0);
        lcd.print("Ending Locat.");
        lcd.setCursor(0, 1);
        lcd.print(End);
        
    }

  if (Select==3){
        lcd.setCursor(0, 0);
        lcd.print("Orientation");
        lcd.setCursor(0, 1);
        if (Dir==0) lcd.print("North");
        if (Dir==1) lcd.print("East");
        if (Dir==2) lcd.print("South");
        if (Dir==3) lcd.print("West");
        
   }

  if (Select==4){
        lcd.setCursor(0, 0);
        lcd.print("Exit");
        lcd.setCursor(0, 1);
       
    }


  if (buttons) {
    delay(100);
    
    if (buttons & BUTTON_UP) {
      
      if (Select==1) Ini=Ini+1; 
      if (Select==2) End=End+1;
      if (Select==3) Dir=Dir+1; 
      if (Ini>16) Ini=1;
      if (Ini<1) Ini=16;
      if (End>16) End=1;
      if (End<1) End=16;
      if (Dir>4) Dir=1;
      if (Dir<1) Dir=4;
      }
      
    if (buttons & BUTTON_DOWN) {
      if (Select==1) Ini=Ini-1;
      if (Select==2) End=End-1;
      if (Select==3) Dir=Dir-1;
      if (Ini>16) Ini=1;
      if (Ini<1) Ini=16;
      if (End>16) End=1;
      if (End<1) End=16;
      if (Dir>3) Dir=0;
      if (Dir<0) Dir=3;
      }
      }
    if (buttons & BUTTON_LEFT) {
      if (Select==1){
        Select=4;
      }
      else {
        Select=Select-1;
        
      }
      
    }
    if (buttons & BUTTON_RIGHT) {
      if (Select==4){
        Select=1;
      }
      else {
        Select=Select+1;
        }
        
          }
    if (buttons & BUTTON_SELECT) {
    
      if (Select==4) 
        {
        SetUp=1;
        lcd.print("Set Up Done");
        }
      
      else 
        {
          SetUp=0;
        }
        
    }  
}

