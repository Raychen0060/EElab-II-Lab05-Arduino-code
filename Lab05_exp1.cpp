const int segA = 13; // Pin A connect 13
const int segD = 12; // Pin D connect 12
int segState1 = LOW;
int segState2 = LOW;
unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0;
const long interval1 = 500; // because duty cycle = 50% , 0.5s changes once for 1Hz
const long interval2 = 5; // because duty cycle = 50% , 5ms changes once for 100Hz

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segD, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    segState1 = !segState1;
    digitalWrite(segA, segState1);
  }

  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    segState2 = !segState2;
    digitalWrite(segD, segState2);
  }
}
