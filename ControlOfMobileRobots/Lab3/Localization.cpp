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
const int LFSensor = A3;

int go = 0; //signals the beginning of robot execution

//SENSOR READINGS
int shrtF = 0; //short front reading
int shrtL = 0; //short left reading


typedef struct orientation {
  char mDirection;
  int color;
} orientation;

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

  cnfgOrientations();
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
      {
        Localization();
      }
    }
  }
}
//******************************************

int whereTo(const char cardinalDir, int tempToCell)
{
  /*  Going:
      East  --> +1
      South --> -4
      West  --> -1
      North --> +4
  */
  int toCell = tempToCell;
  switch (cardinalDir)
  {
    case 'N':
      toCell += 4;
      break;
    case 'E':
      toCell += 1;
      break;
    case 'S':
      toCell -= 4;
      break;
    case 'W':
      toCell -= 1;
      break;
  }

  //avoid going out of bounds
  if (toCell > 16)
  {
    toCell = tempToCell;
  } else if (toCell < 1)
  {
    toCell = tempToCell;
  }

  //print the cell that it's CURRENTLY in
  if (toCell >= 10)
  {
    lcd.setCursor(10, 1);
    lcd.print(toCell);
  } else {
    lcd.setCursor(10, 1);
    lcd.print(" ");
    lcd.print(toCell);
  }

  return toCell;


}

void Localization()
{
  //Localization Variables
  //always starting East in block 13
  int indexDirection = 1; //default index for EAST
  char crrntRobotDir = mOrientation[indexDirection].mDirection;
  lcd.setBacklight(RED);


  //after a certain count has been reached, we are in a NEW cell respective to the direction (fromCell to NewCell) assign a new cell
  //the old cell will be marked visited on the LCD
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

  //cell numbers


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
      moveForwardALittle(100);
      continue;
    }
    shrtL = trueDist(SLSensor, 10);

    //Marks off cells that are visited
    if (counter == 97)
    {
      counter = 0;
      updateCellStatus(toCell, '0');

      toCell = whereTo(crrntRobotDir, toCell);
    }

    if (counter >= 10)
    {
      lcd.setCursor(14, 1);
      lcd.print(counter);
    } else {
      lcd.setCursor(14, 1);
      lcd.print(" ");
      lcd.print(counter);
    }

    if (shrtL < 9)
    {
      wallFollow(&wfCntr, &counter, shrtL);
      if (cornerFlg)
      {
        stopRobot();
        moveForwardALittle(200);
        if (isAWall(shrtF))
        {
          rightTurn(&indexDirection, &crrntRobotDir);

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
        leftTurn(&indexDirection, &crrntRobotDir);
        updateCellStatus(toCell, '0');
        toCell = whereTo(crrntRobotDir, toCell);
        counter = 20;
        leftTrnFlg = false;
        continue;
      } else
      {
        stopRobot();
        leftTrnFlg = true;

        continue;
      }
    }

  }
  return;
}

void wallFollow(int* wfCntr, int* cellCntr, const int shrtL)
{
  int threshold = 4;
  if (shrtL > threshold)
  {
    //Left Wall is in range, follow it accordingly.
    ++*wfCntr;
    moveCloserToWall();
    if (*wfCntr == 5)
    {

      *wfCntr = 0;
      *cellCntr -= 1;
      //offset the movement by moving in the opposite direction
      moveAwayFromWall();

    }
  } else if (shrtL < threshold)
  {
    //The robot is too close to wall. Move away.
    ++*wfCntr;
    moveAwayFromWall();
    if (*wfCntr == 5)
    {
      *wfCntr = 0;
      *cellCntr -= 1;
      moveCloserToWall();
    }
  } else if (shrtL == threshold)
  {
    *wfCntr = 0;
    alignWithWall();
  }
  return;
}

void leftTurn(int* indexDir, char* rbtDir)
{
  moveForwardALittle(1200);

  stopRobot();

  //perform the left turn!
  int mlVel = 86;//previously 90
  int mrVel = 84;//previously 80
  myMover.cmd_vel(mlVel, mrVel);
  delay(800); //Apr 8 turns too wide, decreased from 1300ms

  updateDirection('l', indexDir, rbtDir);
  moveForwardALittle(1300);
}

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

void updateDirection(char turn, int* indxDir, char* rbtDir)
{ //change our cardinal orientation within the cube

  //  east --> right turn --> south (++1)
  //  east --> left turn --> north (--1)

  switch (turn)
  {
    case 'r':
      *indxDir += 1;
      break;
    case 'l':
      *indxDir -= 1;
      break;
  }

  if (*indxDir <= -1) {
    *indxDir = 3;
  } else
  {
    *indxDir = *indxDir % 4;
  }

  //update the crrntRobotDir variable
  *rbtDir = (mOrientation[*indxDir].mDirection);

  //update LCD color
  lcd.setBacklight(mOrientation[*indxDir].color);
  lcd.setCursor(15, 0);
  lcd.print(*rbtDir);
}


void cnfgOrientations()
{
  //Red - Right
  //Green - Left
  //Blue - Up
  //Yellow - Down

  //north - UP
  mOrientation[0].mDirection = 'N';
  mOrientation[0].color = BLUE;

  //east - RIGHT
  mOrientation[1].mDirection = 'E';
  mOrientation[1].color = RED;

  //south - DOWN
  mOrientation[2].mDirection = 'S';
  mOrientation[2].color = YELLOW;

  //west - LEFT
  mOrientation[3].mDirection = 'W';
  mOrientation[3].color = GREEN;

  return;
}

// 13 14 15 16
//  9 10 11 12
//  5  6  7  8
//  1  2  3  4

void updateCellStatus(int cellNumber, char status) {

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

  //print the cell that it JUST completed
  if (cellNumber >= 10)
  {
    lcd.setCursor(10, 0);
    lcd.print(cellNumber);
  } else {
    lcd.setCursor(10, 0);
    lcd.print(" ");
    lcd.print(cellNumber);
  }
}

//******** Navigation Specific Functions ***********


bool isAWall(int shrtF)
{
  int mythreshold = 6;
  lcd.setCursor(15, 1);
  lcd.print(shrtF);
  return shrtF < mythreshold;
}

void rightTurn(int* indexDir, char* rbtDir)
{
  int mlVel = 95;
  int mrVel = 96;
  myMover.cmd_vel(mlVel, mrVel);
  delay(850); //Apr 6 turns too small, increased from 800ms
  updateDirection('r', indexDir, rbtDir);
}



//too FAR from wall
void moveCloserToWall()
{
  int mlVel = 95;
  int mrVel = 83; //SPEED right up
  myMover.cmd_vel(mlVel, mrVel);
}

//too CLOSE to wall
void moveAwayFromWall()
{
  int mlVel = 97; //SPEED left up
  int mrVel = 86;
  myMover.cmd_vel(mlVel, mrVel);
}

void alignWithWall()
{ //align
  //myMover.cmd_vel(95, 85);
  int mlVel = 95;
  int mrVel = 86; //right motor is weaker
  myMover.cmd_vel(mlVel, mrVel);

}

//Helps prepare for LEFT turn sequence
void moveForwardALittle(int mDelay)
{
  int mlVel = 95;
  int mrVel = 85;
  myMover.cmd_vel(mlVel, mrVel);
  delay(mDelay); //allow the robot to move to the center of the cell to spin to the left
  myMover.cmd_vel(90, 90);
}

void stopRobot()
{
  int mlVel = 90;
  int mrVel = 90;
  myMover.cmd_vel(mlVel, mrVel);
  delay(500);
}
/*
  int trueDist(int sensor, int loops)
  {
  int value = 0;
  for(int i = 0; i < loops; ++i)
  {
    int distance = computeDistance_SIR(analogRead(sensor));
    if(distance != -1)
    {
      value += distance;
    }else
    {
      loops -= 1;
    }

  }
  return value / loops;
  }*/


//new trueDist because if we get a lot of bad values we will get a bad average
int trueDist(int sensor, int loops)
{
  int value = 0;
  int i = 0;
  int c = 0;
  while (i < loops)
  {
    int distance = computeDistance_SIR(analogRead(sensor));
    if (distance != -1)
    {
      value += distance;
    } else
    {
      if (c == 30)
      {
        break;
      }
      if (i == 0)
        i = 0;
      else
        i -= 1;
      ++c;
    }
    ++i;

  }
  return value / loops;
}



