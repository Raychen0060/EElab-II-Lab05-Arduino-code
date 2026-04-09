// 實驗三區域
const int pinE = 9;
const int pinDP = 6;

// 呼吸燈區域
const int pinC = 11;
const int pinD = 10;

const int upButtonPin = 2;
const int downButtonPin = 3;

int brightnessLevel = 0; // 0, 1, 2, 3, 4
int pwmValues[5] = {0, 64, 127, 191, 255}; // brightness value

// Debounce variable
int upState, lastUpState = HIGH;
int downState, lastDownState = HIGH;
unsigned long lastUpTime = 0, lastDownTime = 0;
const unsigned long debounceDelay = 50;

int brightness = 0;
int fadeAmount = 5;
unsigned long previousMillis = 0;

void setup() {
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinDP, OUTPUT);
  
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);

  updateBrightness();// initial brightness 
}

void loop() {
  // 1. 呼吸燈 (C, D)
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 30) { // 每30ms就更新一次
  	previousMillis = currentMillis;
  
  	brightness = brightness + fadeAmount;

  	if (brightness <= 0 || brightness >= 255) {
    	fadeAmount = -fadeAmount;
  	}
  }
  analogWrite(pinC, brightness);
  analogWrite(pinD, brightness);
  
  // 2. 實驗三控制 (E, DP)
  handleButtons();
}
  

void handleButtons(){
  int upReading = digitalRead(upButtonPin);
  int downReading = digitalRead(downButtonPin);

  // --- Up Button Debounce ---
  if (upReading != lastUpState) lastUpTime = millis();
  if ((millis() - lastUpTime) > debounceDelay) {
    if (upReading != upState) {
      upState = upReading;
      if (upState == LOW) { // if upButtonPin is 0 or 1 if press need to be consider
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
      if (downState == LOW) { // if upButtonPin is 0 or 1 if press need to be consider
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
  analogWrite(pinE, val);
  analogWrite(pinDP, val);
}
