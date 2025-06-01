#include <Servo.h>

Servo myservo;
int servoPin = 9;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  Serial.println("Control Servomotor");
}

void loop() {
  // Movimiento automático 0 a 180 grados
  for (int pos = 0; pos <= 180; pos += 15) {
    myservo.write(pos);
    Serial.print("Posición: ");
    Serial.println(pos);
    delay(15);
  }
  
  delay(1000);
  
  // Retorno de 180 a 0 grados
  for (int pos = 180; pos >= 0; pos -= 15) {
    myservo.write(pos);
    Serial.print("Posición: ");
    Serial.println(pos);
    delay(15);
  }
  
  delay(1000);
}
