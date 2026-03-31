// Pin Order： A, B, C, D, E, F, G
const int segPins[7] = {13,12,11,10,9,8,7};

const int upButtonPin = 2; // connect to pin 2
const int downButtonPin = 3; // connect to pin 3

int count = 0;

// Pin Order： A, B, C, D, E, F, G
byte digits[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}  // 9
};

int upState, lastUpState = HIGH;
int downState, lastDownState = HIGH;
unsigned long lastUpTime = 0, lastDownTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  displayDigit(count); // initial 7-seg as 0
}

void loop() {
  int upReading = digitalRead(upButtonPin);
  int downReading = digitalRead(downButtonPin);

  // --- Up Button Debounce ---
  if (upReading != lastUpState) lastUpTime = millis();
  if ((millis() - lastUpTime) > debounceDelay) {
    if (upReading != upState) {
      upState = upReading;
      if (upState == LOW) { // if upButtonPin is 0 or 1 if press need to be consider
        count++;
        if (count > 9) count = 0;
        displayDigit(count);
      }
    }
  }
  lastUpState = upReading;

  // --- Down Button Debounce ---
  if (downReading != lastDownState) lastDownTime = millis();
  if ((millis() - lastDownTime) > debounceDelay) {
    if (downReading != downState) {
      downState = downReading;
      if (downState == LOW) { // if downButtonPin is 0 or 1 if press need to be consider
        count--;
        if (count < 0) count = 9;
        displayDigit(count);
      }
    }
  }
  lastDownState = downReading;
}

// display function
void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}
