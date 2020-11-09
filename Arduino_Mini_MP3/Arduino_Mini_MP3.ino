#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <DFRobot_Gesture.h>
#include <Wire.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int testPin= 7;
unsigned char cmd;

DFRobot_Gesture myGesture;

void setup()
{   
  Wire.begin();        // join i2c bus (address optional for master)
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30               
  myDFPlayer.play(7); 
}

void loop()
{
  if(digitalRead(testPin)==0)
  {
     
   myGesture.I2C1_MasterRead(md.buf,26,0x42); //The address is:0x42
   cmd = myGesture.mgcProcMsg();     //process the message
          if(cmd != GI_NOGESTURE )
            {
                switch(cmd)
                {
                 
                    case GI_FLICK_R:
                      Serial.println("RIGHT");
                        myDFPlayer.play(7); 
                        break;

                    case GI_FLICK_L:
                        Serial.println("LEFT");
                        myDFPlayer.play(9);
                        break;

                    case GI_FLICK_D:
                     Serial.println("DOWN");
                       myDFPlayer.play(11); 
                        break;

                    case GI_FLICK_U:
                       Serial.println("UP");
                         myDFPlayer.play(13);
                        break;
                    case GI_AIRWHEEL_CW://Clockwise in circles
                     Serial.println("CW");
                       myDFPlayer.play(3);
                        break;

                    case GI_AIRWHEEL_CCW://Counterclockwise circles
                       Serial.println("CCW");
                         myDFPlayer.play(1);
                        break;

                    default: break;
                }
            }
  }
  
 else  {};

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
