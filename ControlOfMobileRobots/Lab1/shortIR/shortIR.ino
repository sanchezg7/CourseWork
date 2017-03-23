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
const int SLSensor = A1;  
const int SRSensor = A2;  
const int LFSensor = A3;

 
 int SValueSF=0; //Short Front
 int SValueSR=0; //Short Right
 int SValueSL=0; //Short Left

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.print("ShortIR");
  //lcd.setCursor(1,6);
  lcd.setBacklight(WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0); //(position, line)

  
  //read Short IR values
  SValueSF = analogRead(SFSensor);
  delay(100);
  SValueSL = analogRead(SLSensor);
  delay(100);
  SValueSR = analogRead(SRSensor);
  delay(100);

  //compute the distance based on the digital value
  Serial.print("Front");
  SValueSF = computeDistance_SIR(SValueSF);
  Serial.print("Left");
  SValueSL = computeDistance_SIR(SValueSL);
  Serial.print("Right");
  SValueSR = computeDistance_SIR(SValueSR);
 
  printLCD(SValueSF, SValueSL, SValueSR);  
  
  delay(200); //0.5 seconds
  
}

void printLCD(int SValueSF, int SValueSL, int SValueSR){

  if(SValueSF != -1)
  {
    lcd.setCursor(8, 0);
    lcd.print("SF:");
    lcd.print(SValueSF);
    lcd.print("\"");
  }
  if(SValueSL != -1)
  {
    lcd.setCursor(0, 1);
    lcd.print("SL:");
    lcd.print(SValueSL);
    lcd.print("\"");
  }
  if(SValueSR != -1)
  {
    lcd.setCursor(6, 1);
    lcd.print("SR:");
    lcd.print(SValueSR);
    lcd.print("\"");
  }

  

  //Short right
  //Short left
}


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
                    else if(value < 100) distance = 10; //10 inches

  Serial.print(" sensor: ");
  Serial.print(distance);
  Serial.print(" dValue: ");
  Serial.print(value);
  Serial.print("\n");
                                                  
  return distance;
}




/*
int SF_Function(int dValue){
  
  int distance = 0;
  //distance = (dValue - 558.43);
  //distance /= -22.622;
  //consider ceiling/floor
  if(dValue < 370 && dValue > 175){
      distance = (12.592 * exp(-0.004 * dValue));  
  } else{
    if(dValue < 100){
      distance = (12.592 * exp(-0.004 * dValue)) - 1;  
    } else{
      distance = 1+ (12.592 * exp(-0.004 * dValue));  
    }
  }
  
  
  Serial.print("Front sensor: ");
  Serial.print(distance);
  Serial.print(" dValue: ");
  Serial.print(dValue);
  Serial.print("\n");
  return distance;
}*/
