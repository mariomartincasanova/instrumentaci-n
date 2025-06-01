#define ENABLE_M1 9   // PWM
#define DIRA_M1 8
#define DIRB_M1 7

void setup() {
  Serial.begin(9600);
  pinMode(ENABLE_M1, OUTPUT);
  pinMode(DIRA_M1, OUTPUT);
  pinMode(DIRB_M1, OUTPUT);
  
  Serial.println("Control Motor DC L293D");
  Serial.println("Comandos: horario, antihorario, parar, velocidad");
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readString();
    comando.trim();
    
    if (comando == "horario") {
      motorHorario();
    }
    else if (comando == "antihorario") {
      motorAntihorario();
    }
    else if (comando == "parar") {
      motorParar();
    }
    else if (comando == "velocidad") {
      testVelocidades();
    }
  }
}

void motorHorario() {
  digitalWrite(ENABLE_M1, HIGH);
  digitalWrite(DIRA_M1, HIGH);
  digitalWrite(DIRB_M1, LOW);
  Serial.println("Girando sentido horario");
}

void motorAntihorario() {
  digitalWrite(ENABLE_M1, HIGH);
  digitalWrite(DIRA_M1, LOW);
  digitalWrite(DIRB_M1, HIGH);
  Serial.println("Girando sentido antihorario");
}

void motorParar() {
  digitalWrite(ENABLE_M1, LOW);
  digitalWrite(DIRA_M1, LOW);
  digitalWrite(DIRB_M1, LOW);
  Serial.println("Motor detenido");
}

void testVelocidades() {
  for (int velocidad = 255; velocidad >= 0; velocidad -= 51) {
    analogWrite(ENABLE_M1, velocidad);
    digitalWrite(DIRA_M1, HIGH);
    digitalWrite(DIRB_M1, LOW);
    Serial.print("Velocidad: ");
    Serial.println(velocidad);
    delay(1000);
  }
  motorParar();
}