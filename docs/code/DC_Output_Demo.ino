/*
 * Arduino 5V DC Output Demo
 * Simple constant DC voltage output
 * Output Pin: 5V pin or Digital Pin set HIGH
 */

void setup() {
  // Set pin 13 (built-in LED pin) as output for visual confirmation
  pinMode(13, OUTPUT);
  
  // Set a digital pin as HIGH for 5V DC output
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);  // Constant 5V DC output
  
  // Turn on built-in LED to indicate operation
  digitalWrite(13, HIGH);
}

void loop() {
  // Nothing needed in loop - constant DC output
  // The pin remains HIGH continuously
}
