#define LDR_PIN A0
#define REF_PIN A1  // Potenciómetro de referencia

// Pines de los 5 LEDs
int ledsPin[] = {2, 3, 4, 5, 6};
int numLeds = 5;

void setup() {
  Serial.begin(9600);
  
  // Configurar LEDs como salida
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledsPin[i], OUTPUT);
  }
  
  // Configurar referencia analógica externa
  analogReference(EXTERNAL);
  
  Serial.println("Control 5 LEDs con LDR y referencia ajustable");
}

void loop() {
  int valorLDR = analogRead(LDR_PIN);
  
  // Calcular cuántos LEDs encender (0 a 5)
  int ledsAEncender = map(valorLDR, 0, 1023, numLeds, 0);
  
  // Controlar LEDs
  for (int i = 0; i < numLeds; i++) {
    if (i < ledsAEncender) {
      digitalWrite(ledsPin[i], HIGH);
    } else {
      digitalWrite(ledsPin[i], LOW);
    }
  }
  
  Serial.print("LDR: ");
  Serial.print(valorLDR);
  Serial.print(" - LEDs activos: ");
  Serial.println(ledsAEncender);
  
  delay(200);
}