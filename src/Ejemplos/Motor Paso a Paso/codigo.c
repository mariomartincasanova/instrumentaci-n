#include <Stepper.h>

const int stepsPerRevolution = 2048; // Pasos por revolución completa
const int rolePerMinute = 15;        // 15 RPM

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(rolePerMinute);
  Serial.println("Control Motor Paso a Paso");
}

void loop() {
  Serial.println("Girando sentido horario");
  myStepper.step(stepsPerRevolution);
  delay(500);
  
  Serial.println("Girando sentido antihorario");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}