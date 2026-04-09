// Pin Order： A, B, C, D, E, F, G
const int segPins[7] = {13,12,11,10,9,8,7};
const int Button = 4; // connect to pin 4

unsigned long previousMillis = 0;
const long interval = 500;

int count = 0;

int State, lastState = HIGH;
unsigned long lastTime = 0;
unsigned long debounceDelay = 50;

const int myID[9] = {1,1,3,5,1,1,0,8,1};

// Marquee (A-F)
byte marqueeDigits[6][7] = {
  {0,1,1,1,1,1,1}, // A
  {1,0,1,1,1,1,1}, // B
  {1,1,0,1,1,1,1}, // C
  {1,1,1,0,1,1,1}, // D
  {1,1,1,1,0,1,1}, // E
  {1,1,1,1,1,0,1}  // F
};

// Digit
byte numDigits[10][7] = {
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

void setup(){
  pinMode(Button,INPUT_PULLUP);
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
}

void loop(){
  unsigned long currentMillis = millis();
  int Reading = digitalRead(Button);
  
  // Marquee
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for (int i = 0; i < 7; i++) digitalWrite(segPins[i], marqueeDigits[count][i]);
    count = (count == 5) ? 0 : count + 1;
  }
  
  // --- Button Debounce ---
  if (Reading != lastState) lastTime = millis();
  if ((millis() - lastTime) > debounceDelay) {
    if (Reading != State) {
      State = Reading;
      if (State == LOW) {
        displayID();
        count = 0;
      }
    }
  }
  lastState = Reading;
}

// display function
void displayID() {
  for (int i = 0; i < 9; i++) {
    int currentNum = myID[i];
    // 輸出對應數字
    for (int j = 0; j < 7; j++) digitalWrite(segPins[j], numDigits[currentNum][j]);
    delay(1000); // 每一位數字停留 1 秒
  }
  // 學號播完後，先熄滅或全亮作為結束訊號
  for (int i = 0; i < 7; i++) digitalWrite(segPins[i], 1);
  delay(200);
}
