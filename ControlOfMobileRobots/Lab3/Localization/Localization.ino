#include <robotMover.h>
//#include <Wire.h>
//#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>
//#include <Arduino.h>
//#include <Servo.h>
#include <irDist.h>

//#define RED 0x1
//#define YELLOW 0x3
//#define GREEN 0x2
//#define TEAL 0x6
//#define BLUE 0x4
//#define VIOLET 0x5
//#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


const int SFSensor = A0;
const int SLSensor = A1;
const int SRSensor = A2;
const int LFSensor = A3;

int go = 0; //signals the beginning of robot execution

//SENSOR READINGS
int shrtF = 0; //short front reading
int shrtL = 0; //short left reading

/*
 * Definition in the robotMover class definition
 */
//typedef struct orientation {
//  char mDirection;
//  int color;
//} orientation;

orientation mOrientation[4];

uint8_t buttons;

int toCell = 13;

char grid[4][4] = {'X'};
char updatedDirection = 'E'; //global variable to update direction

robotMover myMover;

void setup() {
  // put your setup code here, to run once:
  myMover.attach_servos();
  myMover.cmd_vel(90, 90);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(RED);
  //lcd.print("Localization");
  lcd.setCursor(0, 0);

  cnfgOrientations(mOrientation);
  for (int i = 0; i <= 16; ++i) {
    updateCellStatus(i, 'X');
  }
}

//assume our starting position is at cell 13 pointing East
void loop()
{
  // put your main code here, to run repeatedly:
  buttons = lcd.readButtons();

  if (buttons)
  {
    delay(200);
    if (buttons & BUTTON_SELECT)
    {
      if (go == 0)
        Localization();
    }
  }
}
//******************************************

void print2DigitPayLoad(int payLoad, int startPos)
{
  //print the cell that it's CURRENTLY in
  if (toCell >= 10)
  {
    lcd.setCursor(startPos, 1);
    lcd.print(payLoad);
  } else {
    lcd.setCursor(startPos, 1);
    lcd.print(" ");
    lcd.print(payLoad);
  }
}

void Localization()
{
  //Localization Variables
  //always starting East in block 13
  int indexDirection = 1; //default index for EAST
  char crrntRobotDir = mOrientation[indexDirection].mDirection;
  lcd.setBacklight(RED);

  //toCell - going to this cell

  //  assign the new cell respectively
  /*  Going:
      East  --> +1
      South --> -4
      West  --> -1
      North --> +4
  */


  // 13 14 15 16
  //  9 10 11 12
  //  5  6  7  8
  //  1  2  3  4

  int lngF; //long Front value
  bool cornerFlg = false;
  bool leftTrnFlg = false;

  int counter = 40;
  int wfCntr = 0;
  int dumShrtF = 0;
  
  while (1)
  {
    ++counter;
    dumShrtF = trueDist(SFSensor, 20);
    if (dumShrtF != 0)
    {
      shrtF = dumShrtF;
    }
    else
    {
      myMover.moveForwardALittle(100);
      continue;
    }
    shrtL = trueDist(SLSensor, 10);

    //Marks off cells that are visited
    if (counter == 97)
    {
      counter = 0;
      updateCellStatus(toCell, '0');

      toCell = whereTo(crrntRobotDir, toCell);
      print2DigitPayLoad(toCell, 10);
    }

    print2DigitPayLoad(counter, 14);
    
    if (shrtL < 9)
    {
      myMover.wallFollow(&wfCntr, &counter, shrtL);
      if (cornerFlg)
      {
        myMover.stopRobot();
        myMover.moveForwardALittle(200);
        if (isAWall(shrtF))
        {
          myMover.rightTurn(&indexDirection, &crrntRobotDir);
          updateDirection('r', &indexDirection, &crrntRobotDir, mOrientation);

          counter = 40; //RIGHT turn middle of CELL
        }
        cornerFlg = false;
        continue;
      } else
      {
        cornerFlg = isAWall(shrtF);
        continue;
      }
    } else if (shrtL >= 9)
    {
      //suspect that it is time for a LEFT turn sequence
      if (leftTrnFlg)
      {
        if(counter > 90)
        {
          toCell = whereTo(crrntRobotDir, toCell);
        }
        myMover.leftTurn(&indexDirection, &crrntRobotDir);
        updateDirection('l', &indexDirection, &crrntRobotDir, mOrientation);
        updateCellStatus(toCell, '0');
        toCell = whereTo(crrntRobotDir, toCell);
        counter = 20;
        leftTrnFlg = false;
        continue;
      } else
      {
        myMover.stopRobot();
        leftTrnFlg = true;

        continue;
      }
    }

  }
  return;
}

//LEFT Turn Function Here

//********** Localization Specific Functions ****************
bool isMazeTraverseComplete()
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; i < 3; ++i)
    {
      if (grid[i][j] == 'X')
      {
        //there is an unvisited cell, return FALSE
        return false;
      }
    }
  }

  return true; //all cells are VISITED
}


//from the updateDirection(char turn, int* indxDir, char* rbtDir) function
void updateLCDColor(int* indxDir, char* rbtDir)
{
  lcd.setBacklight(mOrientation[*indxDir].color);
  lcd.setCursor(15,0);
  lcd.print(*rbtDir);
}


void updateCellStatus(int cellNumber, char status) 
{
 // 13 14 15 16
//  9 10 11 12
//  5  6  7  8
//  1  2  3  4
  //char status is only one character to update the status

  switch (cellNumber) {
    case 1:
      lcd.setCursor(5, 1);
      lcd.print(status);
      grid[3][0] = '0';
      break;
    case 2:
      lcd.setCursor(6, 1);
      lcd.print(status);
      grid[3][1] = '0';
      break;
    case 3:
      lcd.setCursor(7, 1);
      lcd.print(status);
      grid[3][2] = '0';
      break;
    case 4:
      lcd.setCursor(8, 1);
      lcd.print(status);
      grid[3][3] = '0';
      break;
    case 5:
      lcd.setCursor(5, 0);
      lcd.print(status);
      grid[2][0] = '0';
      break;
    case 6:
      lcd.setCursor(6, 0);
      lcd.print(status);
      grid[2][1] = '0';
      break;
    case 7:
      lcd.setCursor(7, 0);
      lcd.print(status);
      grid[2][2] = '0';
      break;
    case 8:
      lcd.setCursor(8, 0);
      lcd.print(status);
      grid[2][3] = '0';
      break;
    case 9:
      lcd.setCursor(0, 1);
      lcd.print(status);
      grid[1][0] = '0';
      break;
    case 10:
      lcd.setCursor(1, 1);
      lcd.print(status);
      grid[1][1] = '0';
      break;
    case 11:
      lcd.setCursor(2, 1);
      lcd.print(status);
      grid[1][2] = '0';
      break;
    case 12:
      lcd.setCursor(3, 1);
      lcd.print(status);
      grid[1][3] = '0';
      break;
    case 13:
      lcd.setCursor(0, 0);
      lcd.print(status);
      grid[0][0] = '0';
      break;
    case 14:
      lcd.setCursor(1, 0);
      lcd.print(status);
      grid[0][1] = '0';
      break;
    case 15:
      lcd.setCursor(2, 0);
      lcd.print(status);
      grid[0][2] = '0';
      break;
    case 16:
      lcd.setCursor(3, 0);
      lcd.print(status);
      grid[0][3] = '0';
      break;
  }

  print2DigitPayLoad(cellNumber, 10);
}

//******** Navigation Specific Functions ***********


//bool isAWall();
//void moveCloserToWall();
//void moveAwayFromWall();
//void alignWithWall();
//moveForwardALittle();
//Stop Robot();
//int trueDist(int sensor, int loops);




