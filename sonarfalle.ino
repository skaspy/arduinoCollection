
// Standardausgabe: Blink-LED
#define LED 13 // LED an Pin 13: Objekt nähert sich.
#define LED2 7 // LED an Pin 7: Objekt entfernt sich.

// spezieller Ultraschallsensor
#include <NewPing.h>

#define TRIGGER_PIN  9  // Arduino Pin liegt an Trigger Pin des Sensors.
#define ECHO_PIN     8  // Arduino Pin liegt an Echo Pin des Sensors.
#define MAX_DISTANCE 200 // Maximale Distanz zum Pingen.

// Instanzierung des Ultraschallsensors
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Variablen des Programms

unsigned int pingSpeed = 100; // Abstand der Messungen: 30 oder 50 oder 100?
unsigned long pingTimer;     // Zeitpunkt der nächsten Messung

// Messwerte

unsigned long time;          // aktuelle Zeit
unsigned long last_time;     // Zeitpunkt der letzten Messung

int dist;                    // aktuelle Distanz
int last_dist;               // Distanz bei der letzten Messung

int ds;                      // Differenz des Wegs
int dt;                      // Differenz der Zeit

float v;                     // Geschwindigkeit
float MAX = 50/3.6;          // Maximale Geschwindigkeit innerorts

//// spezielles LCD-Display
//#include <LiquidCrystal.h>

//// Instanzierung des LCD-Displays
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Einmal Geräte und Variablen initalisieren.

void setup() {                
  
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
 // lcd.begin(16, 2);

  time = millis();
  pingTimer = time + pingSpeed;
  dist = 0;
  serial_out(time, dist, 0.0);
}

// Endlos-Schleife
void loop() {
  
  if (time >= pingTimer){

    dt = time - last_time;
    dist = sonar.ping_cm();
    ds = ( last_dist - dist ) * 10; // Faktor 10 wegen Einheitswechsel: mm/ms statt cm/ms
    v = (float)ds / dt; 
    
    come_or_go(v);
    
    if (pingTimer <= 10000){ // Begrenzung, wegen Übertragung der Werte im Serial Monitor 
      serial_out(time, dist, v); 
    } 
    
    // lcd_out(time, dist, v);
    
    // blitz(v);
      
    // Merken der letzten Werte für die nächste Messung
    last_dist = dist;
    last_time = time;
    pingTimer = time + pingSpeed; // ca. Zeitpunkt der nächsten Messung
    
  }
  time = millis();    
}

void serial_out(long _t, int _d, float _v){

    Serial.print( _t ); // Zeit in ms
    Serial.print(' ');
    Serial.print( _d ); // Distanz in cm * 10
    Serial.print(' ');
    Serial.println( _v ); // Geschwindigkeit in cm * 10 / ms = m/s
}

void come_or_go(float _v){
    if (_v > 0){  // Objekt nähert sich
      digitalWrite(LED, HIGH);
      digitalWrite(LED2, LOW);
    }
    else if (_v < 0) { // Objekt entfernt sich
      digitalWrite(LED, LOW);
      digitalWrite(LED2, HIGH);
    }
    else{               // Objekt bleibt am Ort
      digitalWrite(LED, LOW);
      digitalWrite(LED2, LOW);      
    }
}

void blitz(float _v){
  if (_v >= MAX ){
     digitalWrite(LED, HIGH);
     digitalWrite(LED2, HIGH);          
  }
}

/*
void lcd_out(long _t, int _d, float _v){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print( _t ); // Zeit in ms
    lcd.print(' ');
    lcd.setCursor(0, 1);
    lcd.print( _d );  // Distanz in cm
    lcd.print(' ');
    lcd.println( _v ); 
}
*/


