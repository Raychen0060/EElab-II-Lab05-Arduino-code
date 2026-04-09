// Pin Order： A, B, C, D, E, F
const int segPins[7] = {13,12,11,10,9,8};

const int Button = 4; // connect to pin 4

unsigned long previousMillis = 0;
const long interval = 500;

int count = 0;

// Pin Order： A, B, C, D, E, F
byte digits[7][6] = {
  {0,1,1,1,1,1}, // 0
  {1,0,1,1,1,1}, // 1
  {1,1,0,1,1,1}, // 2
  {1,1,1,0,1,1}, // 3
  {1,1,1,1,0,1}, // 4
  {1,1,1,1,1,0}, // 5
  {0,0,0,0,0,0} // reset state
};

void setup(){
  pinMode(Button,INPUT_PULLUP);
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  displayDigit(count); // initial 7-seg as 0
}

void loop(){
  unsigned long currentMillis = millis();
  int Reading = digitalRead(Button);
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    displayDigit(count);
    count = (count == 5) ? 0 : count + 1;
  }

  if (Reading == LOW) {
    // --- 當按鈕被按下時(持久判定) --- //
    count = 0;
    displayDigit(6); 
  }
}


// display function
void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}
