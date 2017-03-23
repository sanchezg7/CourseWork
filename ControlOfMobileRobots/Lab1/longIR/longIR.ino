#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <math.h>


Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

const int SFSensor = A0;
const int LFSensor = A3;


int LValueF = 0; //Long Front
int SValueSF = 0; //Short Front IR
int rawShortDistance = 0;
int rawLongDistance = 0;
int sDistance = 0;
int lDistance = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("IR Long");
  lcd.setCursor(0, 1);
  //lcd.print("Distance Sensor");

  lcd.setBacklight(GREEN);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0); //(position, line)

  //read Short IR value
  SValueSF = analogRead(SFSensor);
  //delay(100); //delay to minimize noise from reading
  delay(100);
  //read Long IR value
  LValueF = analogRead(LFSensor);

  //compute the distance based on the digital value

  sDistance = computeShortDistance(SValueSF);
  lDistance = computeLongDistance(LValueF);
  //Serial.print("distance: ");
  //Serial.print(sDistance);
  //Serial.print("\t");


  if (sDistance != -1 || SValueSF > 120)
  {
    //found a valid range
    if (sDistance <= 8 && sDistance >= 2)
    {
      printLCD(sDistance); //display the desired distance
    }
  } else if (lDistance != -1) {
    //found a valid range
    if (lDistance >= 9 && lDistance <= 59)
    {
      printLCD(lDistance);
    }
  }

  delay(1000); //2
  //Serial.print("here");
}

void printLCD(int value)
{
  //lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(value);
  lcd.print("\"");
}


int computeShortDistance(int SValueF)
{

  double distance = -1; //-1 signals that it did not qualify as a new distance

  //assign a distance to the respective threshold if the Short IR digital value qualifies in the valid range
  if ( SValueF > 473 && SValueF < 530)  distance = 2; //2 inches

  else if ( SValueF > 335 && SValueF < 366) distance = 3; //3 inches

  else  if (SValueF > 246 && SValueF < 268) distance = 4; //4 inches

  else if (SValueF > 195 && SValueF < 229) distance = 5; //5 inches

  else if (SValueF > 175 && SValueF < 191) distance = 6; //6 inches

  else if ( SValueF > 143 && SValueF < 167) distance = 7; //7 inches

  else if (SValueF > 121 && SValueF < 136) distance = 8; //149 causes an overlap with 7 & 8 inches, changed to 136

  //Serial.print("Short Value: ");
  //Serial.print(SValueF);
  //Serial.print("\t");
//  Serial.print("SDistance:");
//  Serial.print(distance);
//  Serial.print("\t");


  return (int)distance;
}


int computeLongDistance(int LValueF)
{
  int distance = -1;

  //if (LValueF > 235 && LValueF < 520)
  if(LValueF > 280 && LValueF < 520)
  {
    //distance = ((7E-05) * LValueF * LValueF) - (0.0942 * LValueF) + 36.943; //8 to 20 inches
    //distance = ceil(distance) + 1;
    distance = ((-.0397) * LValueF) + 28.146; //good from 9-17
  
  } else if (LValueF > 160 && LValueF <= 240){ // 21 to 30
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
  
  
  
  
  /*else if (LValueF > 227 && LValueF < 280)
  {
    distance = ((-0.0738) * LValueF) + 37.516;
  }
  else if (LValueF > 151 && LValueF < 227) {

    distance = (-0.1468 * LValueF) + 51.391; //21 to 30 inches
    distance += 2;

  } else if (LValueF > 112 && LValueF < 144 ) {

    distance = (-0.3046 * LValueF) + 74.086; //31 to 40 inches

  } else if (LValueF > 86 && LValueF < 109) {

    distance = (-0.3336 * LValueF) + 77.7777; // 41 to 50 inches
  } else if (LValueF > 60 && LValueF < 86 ) {

    distance = (-0.392 * LValueF) + 84.866; //50 to 59 inches
  }*/
  Serial.print("L value: ");
  Serial.print(LValueF);
  Serial.print("\tLDistance:");
  Serial.print(distance);
  Serial.print("\n");

  return (int) distance;
}


