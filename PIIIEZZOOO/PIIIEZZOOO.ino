const int trigPin = 40;
const int echoPin = 42;
const int piezoPin = 2;
// defines variables
long duration;
int distance = 9999;
int target = 11;
int preventFalsePositive = 0;
bool played = false;

const int dotDuration = 200; // duration of a dot
const int dashDuration = dotDuration * 3; // duration of a dash
const int letterSpace = dotDuration * 3; // space between letters
const int wordSpace = dotDuration * 7; // space between words

const char *morseCodeTable[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
  "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void setup() {
  pinMode(piezoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); 
}

void loop() {
  // Check distances only if target is not reached
  if (distance > 11 || preventFalsePositive < 50) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    // DEBUG
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.print("FalsePositive check:");
    Serial.println(preventFalsePositive);

    digitalWrite(piezoPin, LOW);

    if (distance <= 11) {
      preventFalsePositive++;
    }
    else
      preventFalsePositive = 0;
  }
  else{
    playMorseCode("FUOCO");
    delay(5000);
  }
}

void playMorseCode(const char *message) {
  for (int i = 0; message[i] != '\0'; i++) {
    if (message[i] == ' ') {
      delay(wordSpace); // space between words
    } else {
      playMorseCharacter(message[i]);
      delay(letterSpace); // space between letters
    }
  }
}

void playMorseCharacter(char character) {
  if (character >= 'A' && character <= 'Z') {
    playMorseString(morseCodeTable[character - 'A']);
  } else if (character >= '0' && character <= '9') {
    playMorseString(morseCodeTable[character - '0' + 26]);
  }
}

void playMorseString(const char *morseString) {
  for (int i = 0; morseString[i] != '\0'; i++) {
    if (morseString[i] == '.') {
      tone(piezoPin, 500, dotDuration); // play dot
      delay(dotDuration);
    } else if (morseString[i] == '-') {
      tone(piezoPin, 500, dashDuration); // play dash
      delay(dashDuration);
    }
    delay(dotDuration); // space between dots and dashes
  }
}
//tara 24-25
//to 11 