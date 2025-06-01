# Sistema de Control Climático con Arduino


> **Actividad 2**: Sistema de control y actuación en función del clima - Colección completa de ejemplos para instrumentación programable con Arduino.

##  Tabla de Contenidos

- [Descripción del Proyecto](#-descripción-del-proyecto)
- [Características](#-características)
- [Ejemplos Incluidos](#-ejemplos-incluidos)
- [Instalación y Configuración](#-instalación-y-configuración)
- [Guía de Uso](#-guía-de-uso)
- [Diagramas de Conexión](#-diagramas-de-conexión)
- [Troubleshooting](#-troubleshooting)


##  Descripción del Proyecto

Este repositorio contiene una colección completa de ejemplos Arduino para crear un **sistema de control climático inteligente**. El proyecto simula una boya climática que monitorea y controla temperatura, humedad e iluminación usando sensores, actuadores y algoritmos de control.

### Objetivos Funcionales
- 🌡️ **Control de Temperatura**: Mantener las baterías a 25°C ±3°C
- 💡 **Control de Iluminación**: Ajustar iluminación artificial al 80%
- 📊 **Monitoreo en Tiempo Real**: Display LCD con información del sistema
- 🔧 **Actuación Automática**: Respuesta inteligente según condiciones climáticas

##  Características

- **🎮 8 Ejemplos Independientes**: Desde básicos hasta sistemas integrados
- **🔌 Compatible con WOKWI**: Simulación online sin hardware físico
- **📚 Documentación Completa**: Código comentado y diagramas incluidos
- **🛠️ Modular**: Cada ejemplo puede usarse independientemente
- **📈 Escalable**: Fácil integración y expansión del sistema

##  Ejemplos Incluidos

| # | Ejemplo | Descripción | Componentes Principales | Dificultad |
|---|---------|-------------|------------------------|------------|
| **01** | [Control de Temperatura](#01-control-de-temperatura) | Algoritmo discontinuo 3 posiciones | DHT22, LEDs, LCD |
| **02** | [Motor DC con L293D](#02-motor-dc-con-l293d) | Control velocidad y dirección | L293D, Motor DC | 
| **03** | [Servomotor](#03-servomotor) | Control de posición angular | Servo SG90 | 
| **04** | [Motor Paso a Paso](#04-motor-paso-a-paso) | Control preciso de movimiento | 28BYJ-48, ULN2003A | 
| **05** | [8 LEDs con 74HC595](#05-8-leds-con-74hc595) | Expansión de salidas digitales | 74HC595, 8 LEDs | 
| **06** | [Control LDR-LED PWM](#06-control-ldr-led-pwm) | Iluminación automática básica | LDR, LED PWM | 
| **07** | [5 LEDs Graduales](#07-5-leds-graduales) | Control iluminación por niveles | LDR, 5 LEDs, Potenciómetro | 
| **08** | [Sistema Integrado](#08-sistema-integrado) | Control climático completo | Todos los anteriores |

##  Instalación y Configuración

### Prerrequisitos

**Para Simulación (WOKWI):**
- Navegador web moderno
- Cuenta gratuita en [WOKWI](https://wokwi.com/)

**Para Hardware Real:**
- Arduino IDE 2.0+
- Librerías requeridas (ver sección de librerías)

### Librerías Necesarias

```cpp
// Instalar desde el Library Manager de Arduino IDE
#include <DHT.h>              // DHT sensor library by Adafruit
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C by Frank de Brabander
#include <Servo.h>            // Servo library (incluida con Arduino)
#include <Stepper.h>          // Stepper library (incluida con Arduino)
```

### Instalación Rápida

1. **Clonar el repositorio:**
   ```bash
   git clone https://github.com/tu-usuario/sistema-control-climatico-arduino.git
   cd sistema-control-climatico-arduino
   ```

2. **Abrir en Arduino IDE:**
   - Abrir Arduino IDE
   - File > Open > Seleccionar el archivo `.ino` deseado

3. **Para WOKWI:**
   - Ir a [wokwi.com](https://wokwi.com/)
   - Crear nuevo proyecto Arduino Uno
   - Copiar código del ejemplo
   - Agregar componentes según diagrama

##  Guía de Uso

### 01. Control de Temperatura

**🎯 Objetivo:** Mantener temperatura constante usando algoritmo discontinuo de 3 posiciones.

**📋 Componentes WOKWI:**
```
- Arduino Uno
- DHT22 (Temperatura/Humedad)
- LCD 16x2 I2C
- 2x LED (Rojo/Azul)
- 2x Resistencia 220Ω
```

*** Conexiones:**
```cpp
DHT22    -> Pin 2
LED Rojo -> Pin 3 (Calentar)
LED Azul -> Pin 4 (Enfriar)
LCD I2C  -> SDA: A4, SCL: A5
```

*** Funcionamiento:**
- Mide temperatura cada 500ms
- Activa calentamiento si T < 22°C
- Activa enfriamiento si T > 28°C
- Zona muerta: 22°C - 28°C (sin acción)

---

### 02. Motor DC con L293D

*** Objetivo:** Control bidireccional de motor DC con velocidad variable.

*** Componentes WOKWI:**
```
- Arduino Uno
- CI L293D
- Motor DC
- Fuente externa 9V
- Potenciómetro 10kΩ
```

*** Conexiones:**
```cpp
L293D Enable -> Pin 9 (PWM)
L293D DIRA   -> Pin 8
L293D DIRB   -> Pin 7
```

*** Comandos Serie:**
- `horario` - Giro sentido horario
- `antihorario` - Giro sentido antihorario
- `parar` - Detener motor
- `velocidad` - Test de velocidades

---

### 03. Servomotor

*** Objetivo:** Control preciso de posición angular.

*** Componentes WOKWI:**
```
- Arduino Uno
- Servomotor SG90
```

*** Conexiones:**
```cpp
Servo -> Pin 9 (PWM)
```

*** Funcionamiento:**
- Movimiento automático 0° a 180°
- Incrementos de 15°
- Retorno automático a posición inicial

---

### 04. Motor Paso a Paso

*** Objetivo:** Control preciso de movimiento rotacional por pasos.

*** Componentes WOKWI:**
```
- Arduino Uno
- Motor 28BYJ-48
- Driver ULN2003A
- Fuente externa 5V
```

*** Conexiones:**
```cpp
ULN2003A -> Pines 8, 9, 10, 11
```

*** Especificaciones:**
- 2048 pasos/revolución
- Velocidad: 15 RPM
- Movimiento bidireccional

---

### 05. 8 LEDs con 74HC595

*** Objetivo:** Expandir salidas digitales usando registro de desplazamiento.

*** Componentes WOKWI:**
```
- Arduino Uno
- CI 74HC595
- 8x LED
- 8x Resistencia 220Ω
```

*** Conexiones:**
```cpp
74HC595 Data  -> Pin 2
74HC595 Latch -> Pin 3
74HC595 Clock -> Pin 4
```

*** Efectos Incluidos:**
- Secuencia progresiva
- Secuencia regresiva
- Patrones alternos

---

### 06. Control LDR-LED PWM

*** Objetivo:** Iluminación automática compensada por luz ambiente.

*** Componentes WOKWI:**
```
- Arduino Uno
- LDR (Fotorresistor)
- Resistencia 10kΩ
- LED
- Resistencia 220Ω
```

*** Conexiones:**
```cpp
LDR -> Pin A0 (con divisor de tensión)
LED -> Pin 5 (PWM)
```

*** Lógica:**
- Menos luz ambiente = Mayor intensidad LED
- Control proporcional inverso
- Respuesta en tiempo real

---

### 07. 5 LEDs Graduales

*** Objetivo:** Control de iluminación por niveles discretos.

*** Componentes WOKWI:**
```
- Arduino Uno
- LDR
- Resistencia 1kΩ
- Potenciómetro 10kΩ (referencia)
- 5x LED
- 5x Resistencia 220Ω
```

*** Conexiones:**
```cpp
LDR           -> Pin A0
Potenciómetro -> Pin A1
LEDs          -> Pines 2, 3, 4, 5, 6
```

*** Características:**
- Referencia ajustable con potenciómetro
- 5 niveles de iluminación
- Adaptación automática al ambiente

---

### 08. Sistema Integrado

*** Objetivo:** Sistema completo de control climático.

*** Componentes WOKWI:**
```
- Arduino Uno
- DHT22 (Temperatura/Humedad)
- LDR (Luz ambiente)
- LCD 16x2 I2C
- 2x LED control temperatura
- 74HC595 + 8 LEDs iluminación
- Resistencias varias
```

*** Conexiones:**
```cpp
DHT22     -> Pin 2
LDR       -> Pin A0
LEDs Temp -> Pines 3, 4
74HC595   -> Pines 5, 6, 7
LCD I2C   -> A4 (SDA), A5 (SCL)
```

*** Parámetros de Control:**
- **Temperatura objetivo:** 25°C ±3°C
- **Iluminación objetivo:** 80%
- **Actualización:** Cada 1 segundo
- **Display:** Información en tiempo real

## Diagramas de Conexión

### Esquema Sistema Integrado

```
    Arduino Uno
    ┌─────────────┐
    │         D2  │◄── DHT22 (Temp/Humedad)
    │         D3  │──► LED Rojo (Calentar)
    │         D4  │──► LED Azul (Enfriar)
    │         D5  │──► 74HC595 Data
    │         D6  │──► 74HC595 Latch
    │         D7  │──► 74HC595 Clock
    │         A0  │◄── LDR (Luz)
    │         A4  │◄─► LCD SDA
    │         A5  │◄─► LCD SCL
    │         GND │──► Común
    │         5V  │──► Alimentación
    └─────────────┘
```

### Conexión 74HC595 para LEDs

```
    74HC595          8 LEDs
    ┌─────────┐      ┌─────┐
    │     Q0  │──────│ LED1│
    │     Q1  │──────│ LED2│
    │     Q2  │──────│ LED3│
    │     Q3  │──────│ LED4│
    │     Q4  │──────│ LED5│
    │     Q5  │──────│ LED6│
    │     Q6  │──────│ LED7│
    │     Q7  │──────│ LED8│
    └─────────┘      └─────┘
```

##  Troubleshooting

### Problemas Comunes

*** Error: DHT sensor no responde**
```cpp
// Solución: Verificar conexiones y agregar delay en setup()
void setup() {
  dht.begin();
  delay(2000); // Esperar inicialización DHT
}
```

*** Error: LCD no muestra nada**
```cpp
// Solución: Verificar dirección I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Probar 0x3F si no funciona
```

*** Error: LEDs no encienden con 74HC595**
```cpp
// Solución: Verificar secuencia de envío
digitalWrite(LATCH_PIN, LOW);   // Primero LOW
shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data);
digitalWrite(LATCH_PIN, HIGH);  // Luego HIGH para activar
```

*** Error: Servo se mueve erráticamente**
```cpp
// Solución: Agregar delays apropiados
myservo.write(pos);
delay(15); // Mínimo 15ms entre movimientos
```

### Debug con Monitor Serie

```cpp
// Activar debug verbose
#define DEBUG 1

void debugPrint(String mensaje) {
  #if DEBUG
    Serial.println(mensaje);
  #endif
}
```

##  Expansiones Sugeridas

###  Mejoras de Hardware
- Agregar sensor de calidad del aire (MQ-135)
- Implementar conexión WiFi (ESP32)
- Añadir almacenamiento SD para datos históricos
- Integrar RTC para timestamp

###  Mejoras de Software  
- Algoritmo PID para control más suave
- Interface web para monitoreo remoto  
- Logging de datos con análisis estadístico
- Alertas por SMS/Email

###  Mejoras de Interface
- Display OLED para mejor visualización
- Control por app móvil (Bluetooth)
- Dashboard web en tiempo real
- Gráficos históricos


### Código de Conducta
- Código limpio y bien comentado
- Seguir convenciones de nomenclatura Arduino
- Documentar cambios en README
- Probar en WOKWI antes de enviar PR

