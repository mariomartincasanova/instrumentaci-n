#define LDR_PIN A0
#define LED_PIN 5  // Pin PWM

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Control Iluminación LDR-LED");
}

void loop() {
  int valorLDR = analogRead(LDR_PIN);
  
  // Invertir y escalar: menos luz ambiente = más LED
  int intensidadLED = map(valorLDR, 0, 1023, 255, 0);
  
  analogWrite(LED_PIN, intensidadLED);
  
  Serial.print("LDR: ");
  Serial.print(valorLDR);
  Serial.print(" - LED: ");
  Serial.println(intensidadLED);
  
  delay(100);
}