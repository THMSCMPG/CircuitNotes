// Position Counter with Direction Display
const int PIN_A = 2;
const int PIN_B = 3;
const int PIN_SW = 4;
const int LED_CW = 9;    // Green - Clockwise
const int LED_CCW = 10;  // Red - Counter-clockwise
const int LED_ZERO = 11; // Blue - At zero position

volatile long encoderCount = 0;
volatile int lastEncoded = 0;
volatile unsigned long lastInterrupt = 0;
volatile int lastDirection = 0;  // 1=CW, -1=CCW, 0=stopped

void setup() {
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(LED_CW, OUTPUT);
  pinMode(LED_CCW, OUTPUT);
  pinMode(LED_ZERO, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(PIN_A), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), updateEncoder, CHANGE);
  
  Serial.begin(9600);
  Serial.println("Position Counter Ready");
  Serial.println("Press button to reset position");
}

void loop() {
  // Update display
  static long lastCount = -999;
  if(encoderCount != lastCount) {
    displayPosition();
    lastCount = encoderCount;
  }
  
  // Update direction LEDs
  if(lastDirection > 0) {
    digitalWrite(LED_CW, HIGH);
    digitalWrite(LED_CCW, LOW);
  } else if(lastDirection < 0) {
    digitalWrite(LED_CW, LOW);
    digitalWrite(LED_CCW, HIGH);
  } else {
    digitalWrite(LED_CW, LOW);
    digitalWrite(LED_CCW, LOW);
  }
  
  // Zero indicator
  digitalWrite(LED_ZERO, encoderCount == 0 ? HIGH : LOW);
  
  // Reset button
  if(digitalRead(PIN_SW) == LOW) {
    delay(50);
    if(digitalRead(PIN_SW) == LOW) {
      encoderCount = 0;
      Serial.println("\n*** POSITION RESET TO ZERO ***\n");
      delay(200);
    }
  }
  
  delay(100);
}

void updateEncoder() {
  unsigned long interruptTime = micros();
  if(interruptTime - lastInterrupt < 1000) return;
  lastInterrupt = interruptTime;
  
  int MSB = digitalRead(PIN_A);
  int LSB = digitalRead(PIN_B);
  int encoded = (MSB < 1) | LSB;
  int sum = (lastEncoded < 2) | encoded;
  
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderCount++;
    lastDirection = 1;
  }
  else if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderCount--;
    lastDirection = -1;
  }
  
  lastEncoded = encoded;
}

void displayPosition() {
  // Calculate degrees (assuming 20 PPR encoder)
  float degrees = (encoderCount % 80) * 4.5;
  int revolutions = encoderCount / 80;
  
  Serial.print("Count: ");
  Serial.print(encoderCount);
  Serial.print(" | Rev: ");
  Serial.print(revolutions);
  Serial.print(" | Angle: ");
  Serial.print(degrees, 1);
  Serial.print("° | Dir: ");
  Serial.println(lastDirection > 0 ? "CW" : (lastDirection < 0 ? "CCW" : "STOP"));
}
