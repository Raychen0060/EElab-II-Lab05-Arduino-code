// Pin Order： A, B, C, D, E, F, G
const int segPins[7] = {13,12,11,10,9,8,7};
bool down = 0; 

unsigned long previousMillis = 0;
const long interval = 1000;

int count = 0;

// Pin Order： A, B, C, D, E, F, G
byte digits[16][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}, // 9
  {1,1,1,0,0,1,0}, // 10
  {1,1,0,0,1,1,0}, // 11
  {1,0,1,1,1,0,0}, // 12
  {0,1,1,0,1,0,0}, // 13
  {1,1,1,0,0,0,0}, // 14
  {1,1,1,1,1,1,1}  // 15
};

void setup(){
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  displayDigit(count); // initial 7-seg as 0
}

void loop(){
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    count = down ? count - 1 : count + 1;
    
    if (count == 15) down = 1;
    if (count == 0) down = 0;
    displayDigit(count);
  }
  
}


// display function
void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}
