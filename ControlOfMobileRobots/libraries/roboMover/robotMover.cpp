#include <robotMover.h>



	Servo LServo;
	Servo RServo;

robotMover::robotMover()
{
	//constructor
	
}

void robotMover::cmd_vel(int left, int right)
{

  if(left != -1) LServo.write(left);
  if(right != -1) RServo.write(right);
 
}
void robotMover::attach_servos()
{
	LServo.attach(2);
	RServo.attach(3);
	return;

}

void robotMover::move_fwd(int time)
{
    cmd_vel(100, 80);//l & r
    delay(time);
    cmd_vel(90, 90);
}

void robotMover::move_bkwd(int time)
{
  cmd_vel(80, 100); //move the robot backwards
  delay(time);
  cmd_vel(90, 90);
}

void robotMover::spin_cntclkwse()
{
  cmd_vel(90, 80);
  delay(1350);
  cmd_vel(90, 90);
}

void robotMover::spin_clkwse()
{
  cmd_vel(100, 90);
  delay(1250);
  cmd_vel(90,90);
}

void robotMover::cnt_circle_20(int time)
{
	cmd_vel(94, 83);
	delay(time);
	cmd_vel(90,90); //stop the robot
}

void robotMover::circle_20(int time)
{
	cmd_vel(96, 87);	
	delay(time);
	cmd_vel(90,90); //stop the robot
}

void robotMover::fig8_circle_20(int time)
{
	cmd_vel(96, 87);
	delay(time); 
	cmd_vel(90,90);
}

void robotMover::fig8_cnt_circle_20(int time)
{
	cmd_vel(94, 83); //might work
	delay(time); 
	cmd_vel(90,90);
}

void robotMover::basic_right(){
	cmd_vel(100, 100);
}

void robotMover::basic_left(){
	cmd_vel(80,80);
}

void robotMover::follow_vel(int lVel, int rVel)
{
  if(lVel > 100) lVel = 100;
    else if(lVel < 90) lVel = 90; //prevent go backward

   //check for saturation in right wheel
   if(rVel < 81) rVel = 81;
        else if(rVel > 90) rVel = 90;

    cmd_vel(lVel, rVel);
}
//Helps prepare for LEFT turn sequence
void robotMover::moveForwardALittle(int mDelay)
{
  int mlVel = 95;
  int mrVel = 86;
  cmd_vel(mlVel, mrVel);
  delay(mDelay); //allow the robot to move to the center of the cell to spin to the left
  cmd_vel(90, 90);
}

void robotMover::rightTurn( int mDelay)
{
  int mlVel = 95;
  int mrVel = 96;
  cmd_vel(mlVel, mrVel);
  delay(mDelay); //Apr 6 turns too small, increased from 800ms
}

void robotMover::leftTurn(int mDelay)
{
  //perform the left turn!
  int mlVel = 86;//previously 90
  int mrVel = 84;//previously 80
  cmd_vel(mlVel, mrVel);
  delay(mDelay); //Apr 8 turns too wide, decreased from 1300ms
  cmd_vel(90,90);
}

void robotMover::rightTurn(int* indexDir, char* rbtDir)
{
  int mlVel = 95;
  int mrVel = 96;
  cmd_vel(mlVel, mrVel);
  delay(850); //Apr 6 turns too small, increased from 800ms
  cmd_vel(90,90);
}

void robotMover::leftTurn(int* indexDir, char* rbtDir)
{
  moveForwardALittle(1200);

  stopRobot();

  //perform the left turn!
  int mlVel = 86;//previously 90
  int mrVel = 84;//previously 80
  cmd_vel(mlVel, mrVel);
  delay(800); //Apr 8 turns too wide, decreased from 1300ms
  moveForwardALittle(1300);
}

void robotMover::stopRobot()
{
  int mlVel = 90;
  int mrVel = 90;
  cmd_vel(mlVel, mrVel);
  delay(500);
}

void robotMover::wallFollow(int* wfCntr, int* cellCntr, const int shrtL)
{
  int threshold = 5;
  int bufferCoef = 10;
  if (shrtL > threshold)
  {
    //Left Wall is in range, follow it accordingly.
    ++*wfCntr;
    moveCloserToWall();
    if (*wfCntr == bufferCoef)
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
    if (*wfCntr == bufferCoef)
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

//too FAR from wall
void robotMover::moveCloserToWall()
{
  int mlVel = 95;
  int mrVel = 83; //SPEED right up
  cmd_vel(mlVel, mrVel);
}

//too CLOSE to wall
void robotMover::moveAwayFromWall()
{
  int mlVel = 97; //SPEED left up
  int mrVel = 86;
  cmd_vel(mlVel, mrVel);
}

void robotMover::alignWithWall()
{ //align
  //myMover.cmd_vel(95, 85);
  int mlVel = 95;
  int mrVel = 86; //right motor is weaker
  cmd_vel(mlVel, mrVel);

}



///Helper functions
void cnfgOrientations(orientation* mOrientation)
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
void updateDirection(char turn, int* indxDir, char* rbtDir, orientation mOrientation[])
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
}

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
  return toCell;
}

char getOrientation(int currentCell, int nextCell)
{
	int difference = nextCell - currentCell;
	if(difference == 1){
		return 'E';
	} else if(difference == 4){
		return 'N';
	} else if(difference == -4){
		return 'S';
	} else if(difference == -1){
		return 'W';
	} else{
		return 'Z';
	}
}

int getDifferenceOfCell(int nextCell, char orientation)
{
	int difference = 0;
	if(orientation == 'N'){
		difference = nextCell - 1;
	} else if(orientation == 'E'){
		difference = nextCell + 4;
	} else if(orientation == 'S'){
		difference = nextCell + 1;
	} else if(orientation == 'W'){
		difference = nextCell - 4;
	}
	
	if(difference < 0)
	return difference;
}