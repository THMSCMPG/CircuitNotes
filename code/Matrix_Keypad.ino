/*
 * 4x4 Matrix Keypad Demonstrations
 * Requires: Keypad library by Mark Stanley, Alexander Brevig
 * Install via Arduino Library Manager: "Keypad"
 */

#include <Keypad.h>

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;

// Define the keymap (standard 4x4 layout)
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad ROW pins to these Arduino pins
byte rowPins[ROWS] = {9, 8, 7, 6};

// Connect keypad COLUMN pins to these Arduino pins
byte colPins[COLS] = {5, 4, 3, 2};

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("====================================");
  Serial.println("   4x4 Keypad Demonstrations");
  Serial.println("====================================");
  Serial.println();
}

void loop() {
  // Demo selection menu
  Serial.println("Select a demo:");
  Serial.println("1 - Simple Key Detection");
  Serial.println("2 - PIN Code Entry");
  Serial.println("3 - Calculator");
  Serial.println("4 - Menu Navigation");
  Serial.println();
  
  // Wait for demo selection
  char selection = waitForKey();
  Serial.println();
  
  switch(selection) {
    case '1':
      demo1_KeyDetection();
      break;
    case '2':
      demo2_PINEntry();
      break;
    case '3':
      demo3_Calculator();
      break;
    case '4':
      demo4_MenuNavigation();
      break;
    default:
      Serial.println("Invalid selection!");
      delay(1000);
  }
  
  Serial.println();
  Serial.println("Press any key to return to menu...");
  waitForKey();
  Serial.println("\n\n");
}

// ============================================
// DEMO 1: Simple Key Detection with Events
// ============================================
void demo1_KeyDetection() {
  Serial.println("=== Demo 1: Key Detection ===");
  Serial.println("Press keys to see events");
  Serial.println("Press * to exit\n");
  
  unsigned long startTime = millis();
  int keyCount = 0;
  
  while(true) {
    char key = keypad.getKey();
    
    if(key) {
      keyCount++;
      
      Serial.print("Key pressed: ");
      Serial.print(key);
      Serial.print(" | Count: ");
      Serial.print(keyCount);
      Serial.print(" | Time: ");
      Serial.print((millis() - startTime) / 1000.0, 1);
      Serial.println("s");
      
      if(key == '*') {
        Serial.println("\nExiting demo...");
        delay(500);
        break;
      }
    }
  }
}

// ============================================
// DEMO 2: PIN Code Entry System
// ============================================
void demo2_PINEntry() {
  Serial.println("=== Demo 2: PIN Entry System ===");
  
  const String correctPIN = "1234";
  const int MAX_ATTEMPTS = 3;
  int attempts = 0;
  
  while(attempts < MAX_ATTEMPTS) {
    Serial.println("\nEnter 4-digit PIN:");
    Serial.print("Attempt ");
    Serial.print(attempts + 1);
    Serial.print(" of ");
    Serial.println(MAX_ATTEMPTS);
    
    String enteredPIN = "";
    
    while(enteredPIN.length() < 4) {
      char key = waitForKey();
      
      if(key >= '0' && key <= '9') {
        enteredPIN += key;
        Serial.print("*");  // Display asterisk for security
      } else {
        Serial.println("\nInvalid input! Use digits 0-9 only.");
        enteredPIN = "";
        Serial.println("Try again:");
      }
    }
    
    Serial.println();
    
    if(enteredPIN == correctPIN) {
      Serial.println("✓ ACCESS GRANTED!");
      Serial.println("PIN correct!");
      delay(2000);
      return;
    } else {
      attempts++;
      Serial.println("✗ INCORRECT PIN");
      
      if(attempts < MAX_ATTEMPTS) {
        Serial.println("Try again...");
      }
    }
  }
  
  Serial.println("\n*** LOCKED OUT ***");
  Serial.println("Too many failed attempts!");
  delay(3000);
}

// ============================================
// DEMO 3: Simple Calculator
// ============================================
void demo3_Calculator() {
  Serial.println("=== Demo 3: Simple Calculator ===");
  Serial.println("Format: NUM1 OP NUM2 #");
  Serial.println("Operations: A(+) B(-) C(x) D(÷)");
  Serial.println("Press # to calculate");
  Serial.println("Press * to exit\n");
  
  while(true) {
    String input = "";
    
    Serial.print("Enter: ");
    
    while(true) {
      char key = waitForKey();
      
      if(key == '*') {
        Serial.println("\nExiting calculator...");
        delay(500);
        return;
      }
      
      if(key == '#') {
        Serial.println();
        break;
      }
      
      input += key;
      Serial.print(key);
    }
    
    // Parse and calculate
    if(input.length() >= 3) {
      int num1 = 0;
      int num2 = 0;
      char operation = ' ';
      int opIndex = -1;
      
      // Find operation
      for(int i = 1; i < input.length() - 1; i++) {
        if(input[i] == 'A' || input[i] == 'B' || 
           input[i] == 'C' || input[i] == 'D') {
          operation = input[i];
          opIndex = i;
          break;
        }
      }
      
      if(opIndex > 0) {
        num1 = input.substring(0, opIndex).toInt();
        num2 = input.substring(opIndex + 1).toInt();
        
        float result = 0;
        bool valid = true;
        
        switch(operation) {
          case 'A':
            result = num1 + num2;
            Serial.print(num1);
            Serial.print(" + ");
            Serial.print(num2);
            break;
          case 'B':
            result = num1 - num2;
            Serial.print(num1);
            Serial.print(" - ");
            Serial.print(num2);
            break;
          case 'C':
            result = num1 * num2;
            Serial.print(num1);
            Serial.print(" × ");
            Serial.print(num2);
            break;
          case 'D':
            if(num2 != 0) {
              result = (float)num1 / num2;
              Serial.print(num1);
              Serial.print(" ÷ ");
              Serial.print(num2);
            } else {
              Serial.println("ERROR: Division by zero!");
              valid = false;
            }
            break;
          default:
            Serial.println("ERROR: Invalid operation!");
            valid = false;
        }
        
        if(valid) {
          Serial.print(" = ");
          Serial.println(result);
        }
      } else {
        Serial.println("ERROR: No operation found!");
      }
    } else {
      Serial.println("ERROR: Invalid input format!");
    }
    
    Serial.println();
  }
}

// ============================================
// DEMO 4: Menu Navigation
// ============================================
void demo4_MenuNavigation() {
  Serial.println("=== Demo 4: Menu System ===");
  Serial.println("Use keys to navigate:");
  Serial.println("2 = UP, 8 = DOWN");
  Serial.println("5 = SELECT, * = BACK\n");
  
  String menuItems[] = {
    "1. System Info",
    "2. Settings",
    "3. Sensors",
    "4. About",
    "5. Exit"
  };
  
  int menuSize = 5;
  int selectedItem = 0;
  
  while(true) {
    // Display menu
    Serial.println("--- MAIN MENU ---");
    for(int i = 0; i < menuSize; i++) {
      if(i == selectedItem) {
        Serial.print("> ");
      } else {
        Serial.print("  ");
      }
      Serial.println(menuItems[i]);
    }
    Serial.println("-----------------");
    
    // Wait for input
    char key = waitForKey();
    
    switch(key) {
      case '2':  // UP
        selectedItem--;
        if(selectedItem < 0) selectedItem = menuSize - 1;
        break;
      case '8':  // DOWN
        selectedItem++;
        if(selectedItem >= menuSize) selectedItem = 0;
        break;
      case '5':  // SELECT
        Serial.print("\nSelected: ");
        Serial.println(menuItems[selectedItem]);
        
        if(selectedItem == 4) {  // Exit option
          Serial.println("Exiting menu...");
          delay(1000);
          return;
        }
        
        Serial.println("(Feature not implemented in demo)");
        Serial.println("\nPress any key to continue...");
        waitForKey();
        break;
      case '*':  // BACK
        Serial.println("\nExiting menu system...");
        delay(500);
        return;
    }
    
    Serial.println();
  }
}

// ============================================
// Helper Function: Wait for Key Press
// ============================================
char waitForKey() {
  char key = 0;
  while(key == 0) {
    key = keypad.getKey();
  }
  return key;
}

/*
 * CIRCUIT CONNECTIONS:
 * 
 * Keypad to Arduino:
 * Row 1 ---> Pin 9
 * Row 2 ---> Pin 8
 * Row 3 ---> Pin 7
 * Row 4 ---> Pin 6
 * Col 1 ---> Pin 5
 * Col 2 ---> Pin 4
 * Col 3 ---> Pin 3
 * Col 4 ---> Pin 2
 * 
 * How Matrix Keypad Works:
 * - 4 row pins and 4 column pins = 16 keys
 * - Rows are set LOW one at a time
 * - Columns are read
 * - If column reads LOW, key at (row, col) is pressed
 * - Scanning happens continuously
 */
