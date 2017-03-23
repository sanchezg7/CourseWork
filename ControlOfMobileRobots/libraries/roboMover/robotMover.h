#ifndef __roboMoverMotion_h
#define __robotMoverMotion_h
#include <Servo.h>
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_RGBLCDShield.h>



typedef struct orientation {
  char mDirection;
  int color;
} orientation;

//Helper functions
int whereTo(const char cardinalDir, int tempToCell);
void updateDirection(char turn, int* indxDir, char* rbtDir, orientation mOrientation[]);
void cnfgOrientations(orientation* mOrientation);
char getOrientation(int currentCell, int nextCell);
int getDifferenceOfCell(int nextCell, char orientation);

class robotMover{
private:
	Servo LServo;
	Servo RServo;
	
public:
	robotMover();
	void cmd_vel(int left, int right);
	void move_fwd(int time);
	void move_bkwd(int time);
	void spin_cntclkwse();
	void spin_clkwse();
	void attach_servos();
	void circle_20(int time);
	void cnt_circle_20(int time);
	void fig8_circle_20(int time);
	void fig8_cnt_circle_20(int time);
	void follow_vel(int lVel, int rVel);
	void basic_right();
	void basic_left();
	void leftTurn(int* indexDir, char* rbtDir);
	void rightTurn(int* indexDir, char* rbtDir);
	void rightTurn(int mDelay);
	void leftTurn(int mDelay);
	void moveForwardALittle(int mDelay);
	void stopRobot();
	void wallFollow(int* wfCntr, int* cellCntr, const int shrtL);
	void moveCloserToWall();
	void moveAwayFromWall();
	void alignWithWall();
	
	

};

#endif