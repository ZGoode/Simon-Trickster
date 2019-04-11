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

//max score is 100

#include <SD.h>
#define SD_ChipSelectPin 10
#include <TMRpcm.h>
#include <SPI.h>
#include <Tone.h>
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

int Stage = 0;

AFArray<int> pattern;
int patternLength = 0;

int patternPosition = 0;

TMRpcm tmrpcm;

void setup() {
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(7);

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
    while (tmrpcm.isPlaying()) {
      delay(1);
    }
  } else {
    tone("choose a satisfying beepy noise or maybe make a song idk yet", "idk");
  }
}

void loop() {
  if (Stage == 0) {
    if ((digitalRead(redbutton) == HIGH) || (digitalRead(bluebutton) == HIGH) || (digitalRead(yellowbutton) == HIGH) || (digitalRead(greenbutton) == HIGH)) {
      Stage = 1;
      if (ToneWav == true) {
        /* Maybe have some kind of song or starting music IDK */
        while (tmrpcm.isPlaying()) {
          delay(1);
        }
      }
    }
  } else if (Stage == 1) {
    continuePattern();
    playPattern();
    playGame();
  } else if (Stage == 2) {
    endGame();
    /* some kind of ending music IDK */
    Stage = 0;
  }
}

void continuePattern () {
  patternLength++;
  pattern.add(random(0, 3));
}

void playPattern () {
  for (int i = 0; i < patternLength; i++) {
    if (pattern[i] == 0) {
      digitalWrite(redled, HIGH);
      if (ToneWav == true) {
        tmrpcm.play("1");
        while (tmrpcm.isPlaying()) {
          delay(1);
        }
      } else {
        tone("choose a satisfying beepy noise or maybe make a song idk yet", "idk");
      }
    } else if (pattern[i] == 1) {
      digitalWrite(blueled, HIGH);
      if (ToneWav == true) {
        tmrpcm.play("2");
        while (tmrpcm.isPlaying()) {
          delay(1);
        }
      } else {
        tone("choose a satisfying beepy noise or maybe make a song idk yet", "idk");
      }
    } else if (pattern[i] == 2) {
      digitalWrite(yellowled, HIGH);
      if (ToneWav == true) {
        tmrpcm.play("3");
        while (tmrpcm.isPlaying()) {
          delay(1);
        }
      } else {
        tone("choose a satisfying beepy noise or maybe make a song idk yet", "idk");
      }
    } else if (pattern[i] == 3) {
      digitalWrite(greenled, HIGH);
      if (ToneWav == true) {
        tmrpcm.play("4");
        while (tmrpcm.isPlaying()) {
          delay(1);
        }
      } else {
        tone("choose a satisfying beepy noise or maybe make a song idk yet", "idk");
      }
    }
  }
}

void playGame () {
  patternPosition = 0;
  for (int i = 0; i < patternLength; i++) {
    while ((digitalRead(redbutton) == LOW) && (digitalRead(bluebutton) == LOW) && (digitalRead(greenbutton) == LOW) && (digitalRead(yellowbutton) == LOW)) {
      delay(1);
    }

    if (digitalRead(redbutton) == HIGH) {
      if (pattern[i] == 0) {
        patternPosition++;
      } else {
        Stage = 2;
        endGame();
        return;
      }
    } else if (digitalRead(bluebutton) == HIGH) {
      if (pattern[i] == 1) {
        patternPosition++;
      } else {
        Stage = 2;
        endGame();
        return;
      }
    } else if (digitalRead(yellowbutton) == HIGH) {
      if (pattern[i] == 2) {
        patternPosition++;
      } else {
        Stage = 2;
        endGame();
        return;
      }
    } else if (digitalRead(greenbutton) == HIGH) {
      if (pattern[i] == 3) {
        patternPosition++;
      } else {
        Stage = 2;
        endGame();
        return;
      }
    }
  }
}

void endGame () {
  pattern.reset();
  Stage = 0;
}

void winGame () {
  /* some kind of victory music idk

  */
  endGame();
  Stage = 2;
}
