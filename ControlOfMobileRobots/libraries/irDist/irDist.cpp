#include <irDist.h>

int computeDistance_SIR(int value){

  int distance = -1; //-1 signals that it did not qualify as a new distance
  if( value > 473 && value < 530)
  {
    //2 inches
    distance = 2;
  } else if( value > 335 && value < 366) distance = 3; //3 inches
      else  if(value > 246 && value < 268) distance = 4; //4 inches
          else if(value > 195 && value < 229) distance = 5; //5 inches
            else if (value > 175 && value < 191) distance = 6; //6 inches
              else if( value > 143 && value < 167) distance = 7; //7 inches
                else if(value > 121 && value < 136) distance = 8;//149 causes an overlap with 7 & 8 inches, changed to 136
                  else if (value > 107 && value < 135) distance = 9;
                    else if(value < 100) distance = 10; //used to be 10 inches 3-30-2016

/*
  Serial.print(" sensor: ");
  Serial.print(distance);
  Serial.print(" dValue: ");
  Serial.print(value);
  Serial.print("\n"); */
                                                  
  return distance;
}

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


int longComputeDist(int LValueF)
{
	int distance = -1;

  //if (LValueF > 235 && LValueF < 520)
  if(LValueF > 280 && LValueF < 520)
  { 
    distance = ((-.0397) * LValueF) + 28.146; //good from 9-17
  } else if (LValueF > 160 && LValueF <= 240)
  { // 21 to 30
    distance = (-0.1341 * LValueF + 50.624);//y = -0.1341x + 50.624 
  //} //else if(LValueF > 105 && LValueF <= 150){ //31 to 40
    //distance = (-0.2294 * LValueF) + 65 + 1;//y = -0.2294x + 65.054
    //distance = (-0.2334 * LValueF) + 66.127; // y = -0.2334x + 66.127 Worked
  } else if(LValueF > 83 && LValueF <= 115)
  {
    distance = (-0.3079 * LValueF) + 75.64;//y = -0.3079x + 75.64
  } else if (LValueF > 90 && LValueF < 96)
  {
    distance = 50;
  }
  else if (LValueF > 75 && LValueF < 85)
  {
    distance = 55;
  } else if (LValueF > 56 && LValueF < 75)
  {
    distance = 59;
  }

  return (int) distance;
}

bool isAWall(int shrtF)
{
  int mythreshold = 6;
//  lcd.setCursor(15, 1);
//  lcd.print(shrtF);
  return shrtF < mythreshold;
}