
#include <Servo.h>

Servo servoBottom; //unterer Motor von 0 bis 180 Grad
Servo servoMiddle; //mittlerer Motor  von ca. 35 bis 180 Grad
Servo servoTop; //oberer Motor von 110 (offen) bis 180 (geschlossen)

int potPin0 = 0; //Potentiometer für BOTTOM an A0
int potPin1 = 1; //Potentiometer für MIDDLE an A1
int potPin2 = 2; //Potentiometer für TOP an A2

int val0 = 0;
int val1 = 0;
int val2 = 0;

void setup() {
  servoBottom.attach(11);
  servoMiddle.attach(10);
  servoTop.attach(9);
}

void loop() {
  val0 = analogRead(potPin0);
  val1 = analogRead(potPin1);
  val2 = analogRead(potPin2);
  
  //Umwandlung der Potiwerte auf die Range der Servos
  val0 = map(val0, 0, 1023, 0, 180); 
  val1 = map(val1, 0, 1023, 35, 180);
  val2 = map(val2, 0, 1023, 115, 180); 
  
  servoBottom.write(val0); 
  servoMiddle.write(val1);
  servoTop.write(val2);
  
  delay(50);
}
