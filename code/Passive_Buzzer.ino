/*
 * Passive Buzzer Demonstrations
 * Pin 8 ---[100Ω]--- BUZZER(+) --- GND
 */

const int BUZZER_PIN = 8;

// Musical note frequencies (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define REST     0

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Buzzer Demonstrations");
}

void loop() {
  Serial.println("\n=== Demo 1: Alarm Patterns ===");
  demo1_AlarmPatterns();
  delay(2000);
  
  Serial.println("\n=== Demo 2: Musical Scale ===");
  demo2_MusicalScale();
  delay(2000);
  
  Serial.println("\n=== Demo 3: Simple Melody ===");
  demo3_Melody();
  delay(3000);
  
  Serial.println("\n=== Demo 4: Frequency Sweep ===");
  demo4_FrequencySweep();
  delay(2000);
}

// ============================================
// DEMO 1: Various Alarm/Alert Patterns
// ============================================
void demo1_AlarmPatterns() {
  // Pattern 1: Simple beep
  Serial.println("Pattern 1: Single Beep");
  tone(BUZZER_PIN, 1000, 200);
  delay(500);
  
  // Pattern 2: Double beep
  Serial.println("Pattern 2: Double Beep");
  tone(BUZZER_PIN, 1500, 100);
  delay(150);
  tone(BUZZER_PIN, 1500, 100);
  delay(500);
  
  // Pattern 3: Triple beep (notification)
  Serial.println("Pattern 3: Triple Beep");
  for(int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 2000, 50);
    delay(100);
  }
  delay(500);
  
  // Pattern 4: Warbling alarm
  Serial.println("Pattern 4: Warbling Alarm");
  for(int i = 0; i < 5; i++) {
    tone(BUZZER_PIN, 800, 200);
    delay(200);
    tone(BUZZER_PIN, 1200, 200);
    delay(200);
  }
  
  // Pattern 5: Rising alarm
  Serial.println("Pattern 5: Rising Alarm");
  for(int freq = 500; freq <= 2000; freq += 100) {
    tone(BUZZER_PIN, freq, 100);
    delay(100);
  }
  
  // Pattern 6: Siren
  Serial.println("Pattern 6: Siren");
  for(int cycle = 0; cycle < 3; cycle++) {
    for(int freq = 800; freq <= 1500; freq += 50) {
      tone(BUZZER_PIN, freq, 50);
      delay(50);
    }
    for(int freq = 1500; freq >= 800; freq -= 50) {
      tone(BUZZER_PIN, freq, 50);
      delay(50);
    }
  }
}

// ============================================
// DEMO 2: Musical Scale (C Major)
// ============================================
void demo2_MusicalScale() {
  int scale[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, 
                 NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
  String notes[] = {"C", "D", "E", "F", "G", "A", "B", "C"};
  
  // Ascending scale
  Serial.println("Ascending scale:");
  for(int i = 0; i < 8; i++) {
    Serial.print(notes[i]);
    Serial.print(" ");
    tone(BUZZER_PIN, scale[i], 400);
    delay(500);
  }
  Serial.println();
  
  delay(500);
  
  // Descending scale
  Serial.println("Descending scale:");
  for(int i = 7; i >= 0; i--) {
    Serial.print(notes[i]);
    Serial.print(" ");
    tone(BUZZER_PIN, scale[i], 400);
    delay(500);
  }
  Serial.println();
}

// ============================================
// DEMO 3: Simple Melody (Twinkle Twinkle)
// ============================================
void demo3_Melody() {
  // Melody: Twinkle Twinkle Little Star
  int melody[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, REST,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, REST
  };
  
  // Note durations: 4 = quarter note, 8 = eighth note, etc.
  int durations[] = {
    4, 4, 4, 4, 4, 4, 2, 4,
    4, 4, 4, 4, 4, 4, 2, 4
  };
  
  Serial.println("Playing: Twinkle Twinkle Little Star");
  
  for(int i = 0; i < 16; i++) {
    // Calculate note duration (1000ms = 1 second / note duration)
    int noteDuration = 1000 / durations[i];
    
    if(melody[i] != REST) {
      tone(BUZZER_PIN, melody[i], noteDuration);
      Serial.print("♪");
    } else {
      Serial.print("_");
    }
    
    // Pause between notes (note duration + 30%)
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // Stop the tone
    noTone(BUZZER_PIN);
  }
  Serial.println("\nMelody complete!");
}

// ============================================
// DEMO 4: Frequency Sweep Analysis
// ============================================
void demo4_FrequencySweep() {
  Serial.println("Frequency sweep from 100 Hz to 5000 Hz");
  Serial.println("Listen for resonant frequency (loudest point)");
  
  // Slow sweep to identify resonance
  for(int freq = 100; freq <= 5000; freq += 100) {
    tone(BUZZER_PIN, freq);
    Serial.print(freq);
    Serial.print(" Hz ");
    
    // Print bar graph of frequency
    int bars = map(freq, 100, 5000, 1, 20);
    for(int b = 0; b < bars; b++) Serial.print("=");
    Serial.println();
    
    delay(100);
  }
  
  noTone(BUZZER_PIN);
  Serial.println("Sweep complete!");
  
  delay(500);
  
  // Play resonant frequency (typically 2-4 kHz)
  Serial.println("Playing resonant frequency (2.5 kHz):");
  tone(BUZZER_PIN, 2500, 2000);
  delay(2500);
}

// ============================================
// BONUS: Morse Code Function
// ============================================
void playMorseCode(String message) {
  message.toUpperCase();
  
  for(int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    
    if(c == ' ') {
      delay(700); // Word space (7 units)
    } else {
      String morse = charToMorse(c);
      for(int j = 0; j < morse.length(); j++) {
        if(morse.charAt(j) == '.') {
          tone(BUZZER_PIN, 1000, 100); // Dit (1 unit)
          delay(100);
        } else if(morse.charAt(j) == '-') {
          tone(BUZZER_PIN, 1000, 300); // Dah (3 units)
          delay(300);
        }
        delay(100); // Inter-element space (1 unit)
      }
      delay(300); // Letter space (3 units total, 1 already waited)
    }
  }
}

String charToMorse(char c) {
  switch(c) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    default: return "";
  }
}

/*
 * CIRCUIT CONNECTIONS:
 * 
 * Buzzer  ->  Arduino
 * +       ->  Pin 8 (through 100Ω resistor)
 * -       ->  GND
 * 
 * The 100Ω resistor protects the Arduino pin and
 * reduces inductive kickback from the buzzer.
 */
