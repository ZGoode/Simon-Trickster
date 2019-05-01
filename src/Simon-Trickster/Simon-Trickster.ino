/***********************************************
   RED - 2
   BLUE - 3
   GREEN - 4
   YELLOW - 5

   RED_BUTTON - 6
   BLUE_BUTTON - 7
   GREEN_BUTTON - 8
   YELLOW_BUTTON - 9

   NEOPIXEL - 10
   SPEAKER - 11
   SPEAKER ON/OFF - 12
 ***********************************************/

#include <Tone.h>
#include <Adafruit_NeoPixel.h>

const int redled = 2;
const int blueled = 3;
const int greenled = 4;
const int yellowled = 5;

const int redbutton = 6;
const int bluebutton = 7;
const int greenbutton = 8;
const int yellowbutton = 9;

const int tonePin = 10;
const int PIN = 11;
const int toneOnOff = 12;

int Stage = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

//max score is 50 per level
//each level gets faster and faster
//number of levels is 10
const int maxscore = 50;
const int maxlevel = 10;

const int delaytime = 2500;
const int ontime = 500;

int level = 1;

int pattern[maxscore];

int patternLength = 0;

void setup() {

  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(yellowled, OUTPUT);

  digitalWrite(redled, OUTPUT);
  digitalWrite(blueled, OUTPUT);
  digitalWrite(greenled, OUTPUT);
  digitalWrite(yellowled, OUTPUT);

  pinMode(redbutton, INPUT);
  pinMode(bluebutton, INPUT);
  pinMode(greenbutton, INPUT);
  pinMode(yellowbutton, INPUT);

  pinMode(tonePin, INPUT);
  pinMode(toneOnOff, INPUT);

  strip.begin();
  strip.show();

  playMusic(0);
}

void loop() {
  if (Stage == 0) {
    if ((digitalRead(redbutton) == HIGH) || (digitalRead(bluebutton) == HIGH) || (digitalRead(yellowbutton) == HIGH) || (digitalRead(greenbutton) == HIGH)) {
      Stage = 1;
      playMusic(1);
    }
  } else if (Stage == 1) {
    continuePattern();
    playPattern();
    playGame();
  } else if (Stage == 2) {
    endGame();
    playMusic(2);
    Stage = 0;
  }
}

void continuePattern () {
  if (patternLength < maxscore) {
    randomSeed(millis());
    pattern[patternLength] = random(0, 3);
    patternLength++;
  } else {
    level++;
    winLevel();
    patternLength = 0;
  }
}

void playPattern () {
  for (int i = 0; i < patternLength; i++) {
    if (pattern[i] == 0) {
      digitalWrite(redled, HIGH);
      playMusic(6);
      digitalWrite(redled, LOW);
    } else if (pattern[i] == 1) {
      digitalWrite(blueled, HIGH);
      playMusic(7);
      digitalWrite(blueled, LOW);
    } else if (pattern[i] == 2) {
      digitalWrite(yellowled, HIGH);
      playMusic(8);
      digitalWrite(yellowled, LOW);
    } else if (pattern[i] == 3) {
      digitalWrite(greenled, HIGH);
      playMusic(9);
      digitalWrite(greenled, LOW);
    }

    if ((i - 1) < patternLength) {
      delay(delaytime / level);
    }
  }
}

void playGame () {
  for (int i = 0; i < patternLength; i++) {
    while ((digitalRead(redbutton) == LOW) && (digitalRead(bluebutton) == LOW) && (digitalRead(greenbutton) == LOW) && (digitalRead(yellowbutton) == LOW)) {
      delay(1);
    }

    if (digitalRead(redbutton) == HIGH) {
      if (pattern[i] == 0) {
        digitalWrite(redled, HIGH);
        playMusic(6);
        digitalWrite(redled, LOW);
      } else {
        Stage = 2;
        endGame();
        return;
      }
    } else if (digitalRead(bluebutton) == HIGH) {
      if (pattern[i] == 1) {
        digitalWrite(blueled, HIGH);
        playMusic(7);
        digitalWrite(blueled, LOW);
      } else {
        Stage = 2;
        endGame();
        return;
      }
    } else if (digitalRead(yellowbutton) == HIGH) {
      if (pattern[i] == 2) {
        digitalWrite(yellowled, HIGH);
        playMusic(8);
        digitalWrite(yellowled, LOW);
      } else {
        Stage = 2;
        endGame();
        return;
      }
    } else if (digitalRead(greenbutton) == HIGH) {
      if (pattern[i] == 3) {
        digitalWrite(greenled, HIGH);
        playMusic(9);
        digitalWrite(greenled, LOW);
      } else {
        Stage = 2;
        endGame();
        return;
      }
    }
  }
}

void endGame () {
  Stage = 0;
  playMusic(5);
}

void winLevel () {
  playMusic(3);
  if (level >= maxlevel) {
    Stage = 0;
    playMusic(4);
  }
}

void playMusic (int x) {
  if (digitalRead(toneOnOff) == HIGH) {
    if (x == 0) {
      /*music that plays on turn on*/
    } else if (x == 1) {
      /*music that plays on game start*/
    } else if (x == 2) {
      /*end game music*/
    } else if (x == 3) {
      /*win level music*/
    } else if (x == 4) {
      /*win game music*/
    } else if (x == 5) {
      /*lose game music*/
    } else if (x == 6) {
      /*red tone/music*/
    } else if (x == 7) {
      /*blue tone/music*/
    } else if (x == 8) {
      /*yellow tone/music*/
    } else if (x == 9) {
      /*green tone/music*/
    } else {
      return;
    }
  }
}
