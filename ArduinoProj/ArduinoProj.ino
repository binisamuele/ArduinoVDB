#include <Keypad.h>
#include "SevSeg.h"
SevSeg sevseg; //Inizia un oggetto controller a sette segmenti


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String currNum = "";
unsigned long previousMillis = 0;
const long interval = 500; // interval at which to blink (milliseconds)
bool displayState = true; // true to display the number, false to hide it
int blinkCount = 0;
bool blinking = false;

void setup(){
    byte numDigits = 4;  
    byte digitPins[] = {45, 43, 41, 39};
    byte segmentPins[] = {52, 51, 29, 23, 22, 53, 27, 25};
    bool resistorsOnSegments = 0; 
    
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
    Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  unsigned long currentMillis = millis();

  if (key){
    Serial.println(key);
    if (key == 'C')
    {
      currNum = "";
      sevseg.setChars(currNum.c_str());
    }
    if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') {
      if (currNum.length() < 4) { // Ensure we don't exceed the number of digits
        currNum += key;
      }
      sevseg.setChars(currNum.c_str());
    }
  }
  if (currNum == "1234" && !blinking) {
    blinking = true;
    blinkCount = 0;
    previousMillis = millis();
  }

  if (blinking) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      displayState = !displayState;
      
      if (displayState) {
        sevseg.setChars(currNum.c_str());
      } else {
        sevseg.blank();
      }

      blinkCount++;
      if (blinkCount >= 8) { // 8 intervals for 4 blinks (on and off each count as 1 interval)
        blinking = false;
        currNum = "A1C2";
        sevseg.setChars(currNum.c_str());
      }
    }
  }
  sevseg.refreshDisplay(); // Must run repeatedly
}