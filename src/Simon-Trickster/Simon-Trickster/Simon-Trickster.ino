/***********************************************
   CS - 10
   SCK - 13
   MOSI - 11
   MISO - 12
   VCC - 5V
   GND - GND

   SPEAKER - 9

   RED - 0
   BLUE - 1
   GREEN - 2
   YELLOW - 3

   RED_BUTTON - 4
   BLUE_BUTTON - 5
   GREEN_BUTTON - 6
   YELLOW_BUTTON - 7

   SD/TONE TOGGLE - 8
 ***********************************************/

#include <SD.h>
#define SD_ChipSelectPin 10
#include <TMRpcm.h>
#include <SPI.h>
#include <tone.h>
#include <AFArray.h>

const int redled = 0;
const int blueled = 1;
const int greenled = 2;
const int yellowled = 3;

const int redbutton = 4;
const int bluebutton = 5;
const int greenbutton = 6;
const int yellowbutton = 7;

const int SDTONE_TOGGLE = 8;

boolean ToneWav = false;
boolean continueGame = false;

AFArray<int> pattern;

void setup() {
  tmrpcm.speakerPin = 9;

  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(yellowled, OUTPUT);

  pinMode(redbutton, INPUT);
  pinMode(bluebutton, INPUT);
  pinMode(greenbutton, INPUT);
  pinMode(yellowbutton, INPUT);
  pinMode(SDTONE_TOGGLE, INPUT);

  if (SD.begin(SD_ChipSelectPin)) {
    if (digitalRead(SDTONE_TOGGLE) == HIGH) {
      ToneWav = false;
    } else {
      ToneWav = true;
    }
  }

  if (ToneWav == true) {
    tmrpcm.play("intro");
  }
}

void loop() {

}
