/*
 * 7-Segment Display and DIP Switch Demonstrations
 */

// ============================================
// DEMO 1: Simple Counter on 7-Segment Display
// ============================================

// Segment pins (Common Cathode)
const int SEG_A = 2;
const int SEG_B = 3;
const int SEG_C = 4;
const int SEG_D = 5;
const int SEG_E = 6;
const int SEG_F = 7;
const int SEG_G = 8;
const int SEG_DP = 9;

// Segment encoding for digits 0-9 and A-F
// Order: A B C D E F G DP
const byte DIGITS[16] = {
  0b11111100,  // 0
  0b01100000,  // 1
  0b11011010,  // 2
  0b11110010,  // 3
  0b01100110,  // 4
  0b10110110,  // 5
  0b10111110,  // 6
  0b11100000,  // 7
  0b11111110,  // 8
  0b11110110,  // 9
  0b11101110,  // A
  0b00111110,  // b
  0b10011100,  // C
  0b01111010,  // d
  0b10011110,  // E
  0b10001110   // F
};

void setup() {
  // Initialize segment pins
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("7-Segment Display Counter");
}

void loop() {
  // Count from 0 to F (hexadecimal)
  for(int digit = 0; digit < 16; digit++) {
    displayDigit(digit);
    
    if(digit < 10) {
      Serial.print("Displaying: ");
      Serial.println(digit);
    } else {
      Serial.print("Displaying: ");
      Serial.println((char)('A' + digit - 10));
    }
    
    delay(1000);
  }
  
  // Flash decimal point
  Serial.println("Flashing DP");
  for(int i = 0; i < 5; i++) {
    digitalWrite(SEG_DP, HIGH);
    delay(200);
    digitalWrite(SEG_DP, LOW);
    delay(200);
  }
}

void displayDigit(int digit) {
  if(digit < 0 || digit > 15) {
    clearDisplay();
    return;
  }
  
  byte pattern = DIGITS[digit];
  
  // Write each segment
  digitalWrite(SEG_A, (pattern >> 7) & 1);
  digitalWrite(SEG_B, (pattern >> 6) & 1);
  digitalWrite(SEG_C, (pattern >> 5) & 1);
  digitalWrite(SEG_D, (pattern >> 4) & 1);
  digitalWrite(SEG_E, (pattern >> 3) & 1);
  digitalWrite(SEG_F, (pattern >> 2) & 1);
  digitalWrite(SEG_G, (pattern >> 1) & 1);
  digitalWrite(SEG_DP, (pattern >> 0) & 1);
}

void clearDisplay() {
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP, LOW);
}

// ============================================
// DEMO 2: DIP Switch Binary Reader
// ============================================

/*
// DIP Switch configuration (8 switches)
const int DIP_PINS[8] = {10, 11, 12, 13, A0, A1, A2, A3};

void setup() {
  // Initialize DIP switch pins with internal pull-ups
  for(int i = 0; i < 8; i++) {
    pinMode(DIP_PINS[i], INPUT_PULLUP);
  }
  
  Serial.begin(9600);
  Serial.println("DIP Switch Binary Reader");
  Serial.println("Switch ON = 1, OFF = 0");
}

void loop() {
  int value = readDIPSwitches();
  
  Serial.print("Binary: ");
  printBinary(value, 8);
  Serial.print(" | Decimal: ");
  Serial.print(value);
  Serial.print(" | Hex: 0x");
  Serial.println(value, HEX);
  
  delay(500);
}

int readDIPSwitches() {
  int value = 0;
  
  for(int i = 0; i < 8; i++) {
    // Read switch (inverted because of pull-up: LOW = ON)
    if(digitalRead(DIP_PINS[i]) == LOW) {
      value |= (1 << i);
    }
  }
  
  return value;
}

void printBinary(int value, int bits) {
  for(int i = bits - 1; i >= 0; i--) {
    Serial.print((value >> i) & 1);
    if(i % 4 == 0 && i != 0) Serial.print(" ");
  }
}
*/

// ============================================
// DEMO 3: Combined - DIP Switch to 7-Segment
// ============================================

/*
// 7-Segment pins
const int SEGMENTS[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// DIP Switch pins (4-bit for hex 0-F)
const int DIP_PINS[4] = {10, 11, 12, 13};

void setup() {
  // Initialize 7-segment
  for(int i = 0; i < 8; i++) {
    pinMode(SEGMENTS[i], OUTPUT);
  }
  
  // Initialize DIP switches
  for(int i = 0; i < 4; i++) {
    pinMode(DIP_PINS[i], INPUT_PULLUP);
  }
  
  Serial.begin(9600);
  Serial.println("DIP Switch to 7-Segment Hex Display");
}

void loop() {
  // Read 4-bit value from DIP switches
  int value = 0;
  for(int i = 0; i < 4; i++) {
    if(digitalRead(DIP_PINS[i]) == LOW) {
      value |= (1 << i);
    }
  }
  
  // Display on 7-segment
  displayDigit(value);
  
  // Print to serial
  static int lastValue = -1;
  if(value != lastValue) {
    Serial.print("DIP Switches: ");
    for(int i = 3; i >= 0; i--) {
      Serial.print((value >> i) & 1);
    }
    Serial.print(" | Value: ");
    Serial.print(value);
    Serial.print(" | Display: ");
    if(value < 10) {
      Serial.println(value);
    } else {
      Serial.println((char)('A' + value - 10));
    }
    
    lastValue = value;
  }
  
  delay(100);
}

void displayDigit(int digit) {
  byte pattern = DIGITS[digit];
  
  for(int i = 0; i < 8; i++) {
    digitalWrite(SEGMENTS[i], (pattern >> (7-i)) & 1);
  }
}
*/

/*
 * CIRCUIT CONNECTIONS:
 * 
 * 7-Segment Display (Common Cathode):
 * Pin 2 ---[220Ω]---> Segment A
 * Pin 3 ---[220Ω]---> Segment B
 * Pin 4 ---[220Ω]---> Segment C
 * Pin 5 ---[220Ω]---> Segment D
 * Pin 6 ---[220Ω]---> Segment E
 * Pin 7 ---[220Ω]---> Segment F
 * Pin 8 ---[220Ω]---> Segment G
 * Pin 9 ---[220Ω]---> Segment DP
 * Common Cathode ---> GND
 * 
 * DIP Switch (4 or 8 position):
 * Switch 1 --+---> Pin 10
 *            |
 *           GND
 * Switch 2 --+---> Pin 11
 *            |
 *           GND
 * (etc...)
 * 
 * Use INPUT_PULLUP mode for switches
 */
