/*
 * 128x64 OLED Display Demonstrations
 * Requires: Adafruit_SSD1306 and Adafruit_GFX libraries
 * 
 * Install via Arduino Library Manager:
 * - Adafruit SSD1306
 * - Adafruit GFX Library
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin (-1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // Common I2C address (or 0x3D)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Loop forever
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
  
  Serial.println("OLED Display Ready");
}

void loop() {
  // Demo 1: Text Display
  demo1_TextDisplay();
  delay(3000);
  
  // Demo 2: Graphics and Animations
  demo2_Graphics();
  delay(3000);
  
  // Demo 3: Real-time Data Display
  demo3_DataDisplay();
  delay(5000);
}

// ============================================
// DEMO 1: Text Display with Multiple Sizes
// ============================================
void demo1_TextDisplay() {
  display.clearDisplay();
  
  // Title (size 2)
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("OLED Demo");
  
  // Line separator
  display.drawLine(0, 18, 127, 18, SSD1306_WHITE);
  
  // Size 1 text
  display.setTextSize(1);
  display.setCursor(0, 24);
  display.println("Text Size 1");
  display.println("128x64 pixels");
  display.println("Monochrome");
  
  // Small status at bottom
  display.setCursor(0, 56);
  display.print("Demo 1/3");
  
  display.display();
}

// ============================================
// DEMO 2: Graphics Primitives
// ============================================
void demo2_Graphics() {
  display.clearDisplay();
  
  // Draw shapes
  display.drawRect(0, 0, 30, 20, SSD1306_WHITE);  // Rectangle
  display.fillRect(35, 0, 30, 20, SSD1306_WHITE); // Filled rectangle
  display.drawCircle(80, 10, 10, SSD1306_WHITE);  // Circle
  display.fillCircle(110, 10, 8, SSD1306_WHITE);  // Filled circle
  
  // Draw line patterns
  for(int i = 0; i < 128; i += 10) {
    display.drawLine(0, 25, i, 64, SSD1306_WHITE);
  }
  
  display.display();
  delay(2000);
  
  // Bouncing ball animation
  int x = 64, y = 32;
  int dx = 2, dy = 2;
  int radius = 5;
  
  for(int frame = 0; frame < 100; frame++) {
    display.clearDisplay();
    
    // Update position
    x += dx;
    y += dy;
    
    // Bounce off walls
    if(x - radius <= 0 || x + radius >= SCREEN_WIDTH) dx = -dx;
    if(y - radius <= 0 || y + radius >= SCREEN_HEIGHT) dy = -dy;
    
    // Draw ball
    display.fillCircle(x, y, radius, SSD1306_WHITE);
    
    // Draw borders
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    
    display.display();
    delay(20);
  }
}

// ============================================
// DEMO 3: Real-time Sensor Data Display
// ============================================
void demo3_DataDisplay() {
  for(int i = 0; i < 50; i++) {
    display.clearDisplay();
    
    // Simulate sensor readings
    int temperature = random(20, 30);
    int humidity = random(40, 60);
    int lightLevel = analogRead(A0);
    
    // Title bar
    display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(2, 2);
    display.print("SENSOR DASHBOARD");
    display.setTextColor(SSD1306_WHITE);
    
    // Temperature
    display.setCursor(0, 18);
    display.setTextSize(1);
    display.print("Temp:");
    display.setTextSize(2);
    display.setCursor(40, 16);
    display.print(temperature);
    display.print("C");
    
    // Humidity
    display.setTextSize(1);
    display.setCursor(0, 36);
    display.print("Humid:");
    display.setTextSize(2);
    display.setCursor(40, 34);
    display.print(humidity);
    display.print("%");
    
    // Light level bar graph
    display.setTextSize(1);
    display.setCursor(0, 54);
    display.print("Light:");
    int barWidth = map(lightLevel, 0, 1023, 0, 70);
    display.drawRect(48, 54, 72, 8, SSD1306_WHITE);
    display.fillRect(49, 55, barWidth, 6, SSD1306_WHITE);
    
    display.display();
    delay(100);
  }
}

/*
 * CIRCUIT CONNECTIONS (I2C):
 * 
 * OLED Display  ->  Arduino Uno
 * VCC           ->  5V (or 3.3V depending on module)
 * GND           ->  GND
 * SCL           ->  A5 (SCL)
 * SDA           ->  A4 (SDA)
 * 
 * Note: Most OLED modules work with both 3.3V and 5V
 * I2C address is usually 0x3C or 0x3D (check with I2C scanner)
 */
