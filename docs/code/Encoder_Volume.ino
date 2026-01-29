// Rotary Encoder Volume Control
const int PIN_A = 2;      // CLK
const int PIN_B = 3;      // DT
const int PIN_SW = 4;     // Switch (button)

volatile int encoderPos = 50;  // Start at 50% volume
volatile int lastEncoded = 0;
volatile unsigned long lastInterrupt = 0;

int volume = 50;  // 0-100%
bool muted = false;

void setup() {
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);
  
  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_A), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), updateEncoder, CHANGE);
  
  Serial.begin(9600);
  Serial.println("Volume Control Ready");
  printVolume();
}

void loop() {
  // Update volume from encoder position
  static int lastPos = encoderPos;
  if(encoderPos != lastPos) {
    volume = constrain(encoderPos, 0, 100);
    lastPos = encoderPos;
    printVolume();
  }
  
  // Check for button press (mute/unmute)
  static bool lastButton = HIGH;
  bool currentButton = digitalRead(PIN_SW);
  
  if(lastButton == HIGH && currentButton == LOW) {
    delay(50); // Debounce
    if(digitalRead(PIN_SW) == LOW) {
      muted = !muted;
      Serial.print("MUTED: ");
      Serial.println(muted ? "ON" : "OFF");
    }
  }
  lastButton = currentButton;
  
  delay(10);
}

void updateEncoder() {
  // Debouncing
  unsigned long interruptTime = micros();
  if(interruptTime - lastInterrupt < 1000) return;
  lastInterrupt = interruptTime;
  
  // Read current state
  int MSB = digitalRead(PIN_A);
  int LSB = digitalRead(PIN_B);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  
  // Determine direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderPos++;
  }
  else if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderPos--;
  }
  
  lastEncoded = encoded;
}

void printVolume() {
  Serial.print("Volume: ");
  Serial.print(volume);
  Serial.print("% ");
  
  // Visual bar
  Serial.print("[");
  for(int i = 0; i < 20; i++) {
    if(i < volume / 5) Serial.print("=");
    else Serial.print(" ");
  }
  Serial.println("]");
}
