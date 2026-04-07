// Pin Order： (A, B, C, D, E, F, G)
const int segPins[7] = {13,12,11,10,9,8,7};

// (D1:十位, D2:個位)
const int digitPins[2] = {2, 3};

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

int count = 0;
unsigned long prevCountMillis = 0;
const long countInterval = 1000;

void setup() {
  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);
  pinMode(digitPins[0], OUTPUT);
  pinMode(digitPins[1], OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - prevCountMillis >= countInterval) {
    prevCountMillis = currentMillis;
    count++;
    if (count > 20) count = 0;
  }

  displayMultiplex(count);
}

void displayMultiplex(int num) {
  int tens = num / 10; // 十位數
  int ones = num % 10; // 個位數

  // 顯示十位數
  if (num >= 10){
    showDigit(0, tens);
    delay(5); // 5ms can fastly scan two 7-seg display 
  }

  // 顯示個位數
  showDigit(1, ones);
  delay(5); // 5ms can fastly scan two 7-seg display 
}

void showDigit(int digitIdx, int val) {
  // 先熄滅所有位數
  digitalWrite(digitPins[0], LOW);
  digitalWrite(digitPins[1], LOW);

  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[val][i]);
  }

  digitalWrite(digitPins[digitIdx], HIGH);
}
