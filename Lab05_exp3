// Pin declaration
const int pinC = 11;
const int pinD = 10;
const int pinE = 9;
const int pinDP = 6;

const int upButtonPin = 2;
const int downButtonPin = 3;

int brightnessLevel = 0; // 0, 1, 2, 3, 4
int pwmValues[5] = {0, 64, 127, 191, 255}; // brightness value

// Debounce variable
int upState, lastUpState = LOW;
int downState, lastDownState = LOW;
unsigned long lastUpTime = 0, lastDownTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinDP, OUTPUT);
  
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);

  updateBrightness();// initial brightness 
}

void loop() {
  int upReading = digitalRead(upButtonPin);
  int downReading = digitalRead(downButtonPin);

  // --- Up Button Debounce ---
  if (upReading != lastUpState) lastUpTime = millis();
  if ((millis() - lastUpTime) > debounceDelay) {
    if (upReading != upState) {
      upState = upReading;
      if (upState == HIGH) { // if upButtonPin is 0 or 1 if press need to be consider
        if (brightnessLevel < 4) {
          brightnessLevel++;
          updateBrightness();
        }
      }
    }
  }
  lastUpState = upReading;

  // --- Down Button Debounce ---
  if (downReading != lastDownState) lastDownTime = millis();
  if ((millis() - lastDownTime) > debounceDelay) {
    if (downReading != downState) {
      downState = downReading;
      if (downState == HIGH) { // if upButtonPin is 0 or 1 if press need to be consider
        if (brightnessLevel > 0) {
          brightnessLevel--;
          updateBrightness();
        }
      }
    }
  }
  lastDownState = downReading;
}

// update brightness
void updateBrightness() {
  int val = pwmValues[brightnessLevel];
  analogWrite(pinC, val);
  analogWrite(pinD, val);
  analogWrite(pinE, val);
  analogWrite(pinDP, val);
}
