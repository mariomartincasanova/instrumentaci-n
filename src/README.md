# Sistema de Control Climático - Arduino

## Descripción

Este proyecto implementa un sistema de control climático automatizado utilizando Arduino. El sistema monitorea y controla diversos parámetros ambientales como temperatura, humedad, iluminación y calidad del aire, proporcionando una respuesta automática para mantener condiciones óptimas.

## Características Principales

- **Control de Temperatura**: Mantiene la temperatura en 25°C ±3°C mediante sistemas de calentamiento y enfriamiento
- **Control de Iluminación**: Sistema de 8 LEDs que complementa la luz ambiente para alcanzar el 80% de iluminación objetivo
- **Panel Solar Inteligente**: Servo motor que orienta el panel solar según la intensidad lumínica
- **Monitoreo Ambiental**: Seguimiento de humedad, calidad del aire y velocidad del viento
- **Sistema de Alertas**: Indicadores LED para condiciones críticas
- **Interfaz LCD**: Display rotativo que muestra información en tiempo real

## Componentes Utilizados

### Hardware Principal
- **Arduino UNO** (o compatible)
- **DHT22** - Sensor de temperatura y humedad
- **LDR** - Sensor de luz (fotoresistor)
- **LCD 16x2 I2C** - Display de información
- **Servo Motor** - Control de panel solar
- **74HC595** - Registro de desplazamiento para control de LEDs

### Componentes Adicionales
- **LEDs indicadores**:
  - LED Rojo (Pin 3): Calentamiento activo
  - LED Azul (Pin 4): Enfriamiento activo  
  - LED Amarillo (Pin 8): Alerta general
- **8 LEDs** - Sistema de iluminación complementaria
- **2 Potenciómetros** - Simulación de sensores de viento y calidad del aire
- **Resistencias y cables** de conexión

## Configuración de Pines

```c
// Sensores
#define DHT_PIN 2          // Sensor DHT22
#define LDR_PIN A0         // Fotoresistor
#define POT_VIENTO_PIN A1  // Potenciómetro viento (simulado)
#define POT_AIRE_PIN A2    // Potenciómetro calidad aire (simulado)

// Actuadores
#define LED_ROJO 3         // LED calentamiento
#define LED_AZUL 4         // LED enfriamiento  
#define LED_ALERTA 8       // LED alerta
#define SERVO_PIN 9        // Servo panel solar

// 74HC595 (Control LEDs iluminación)
#define DATA_PIN 5         // Datos
#define LATCH_PIN 6        // Latch
#define CLOCK_PIN 7        // Clock
```

## Parámetros de Control

| Parámetro | Valor | Descripción |
|-----------|-------|-------------|
| Temperatura Objetivo | 25°C | Temperatura ideal del sistema |
| Tolerancia Térmica | ±3°C | Rango aceptable (22°C - 28°C) |
| Iluminación Objetivo | 80% | Nivel de luz deseado |
| Intervalo de Actualización | 1000ms | Frecuencia de lecturas |

## Funcionalidades del Sistema

### 1. Control de Temperatura
- **Zona de Confort**: 22°C - 28°C (sin acción)
- **Calentamiento**: Activo cuando T < 22°C (LED rojo encendido)
- **Enfriamiento**: Activo cuando T > 28°C (LED azul encendido)

### 2. Sistema de Iluminación
- Medición continua de luz ambiente mediante LDR
- Conversión a escala lux (0-1000)
- Activación progresiva de 8 LEDs para complementar hasta 80%
- Control mediante registro de desplazamiento 74HC595

### 3. Panel Solar Automatizado
- Orientación automática del servo (0° - 90°)
- Posición basada en intensidad lumínica detectada
- Maximización de captación de energía solar

### 4. Sistema de Alertas
Activación del LED de alerta cuando:
- Temperatura > 35°C o < 10°C
- Humedad > 80%
- Calidad del aire > 600 (escala 0-1023)
- Velocidad del viento > 80 km/h

### 5. Interfaz de Usuario (LCD)
Display rotativo cada 3 segundos mostrando:
- **Pantalla 1**: Temperatura, humedad y estado térmico
- **Pantalla 2**: Nivel de luz y LEDs activos
- **Pantalla 3**: Velocidad del viento y calidad del aire
- **Pantalla 4**: Estado general del sistema

## Instalación y Uso

### Requisitos de Software
```c
#include <LiquidCrystal_I2C.h>  // Control LCD I2C
#include <DHT.h>                // Sensor DHT22
#include <Servo.h>              // Control servo motor
```

### Pasos de Instalación
1. Conectar todos los componentes según el diagrama de pines
2. Instalar las librerías requeridas en Arduino IDE
3. Configurar la dirección I2C del LCD (por defecto: 0x27)
4. Cargar el código en la placa Arduino
5. Abrir el monitor serie (9600 baud) para debugging

### Calibración
- **LDR**: Ajustar resistencia de pull-up según condiciones de luz
- **Potenciómetros**: Simular diferentes condiciones de viento y aire
- **Servo**: Verificar rango de movimiento del panel solar

## Monitoreo y Debug

El sistema proporciona información detallada a través de:

### Monitor Serie (cada 5 segundos)
```
=== ESTADO SISTEMA ===
Temp: 24.5°C -> OK
Humedad: 55%
Luz: 450 lx -> LEDs: 3/8
Panel Solar: 40°
Viento: 15 km/h
Aire: 280
=====================
```

### Display LCD (rotativo)
- Información visual en tiempo real
- Estados del sistema claramente identificados
- Valores numéricos y estados cualitativos

## Posibles Mejoras

- Integración con sensores reales de viento y calidad del aire
- Conectividad IoT para monitoreo remoto
- Algoritmos PID para control más preciso de temperatura
- Base de datos para histórico de mediciones
- Interfaz web para configuración remota
- Sistema de backup energético

## Solución de Problemas

### Problemas Comunes
- **DHT22 sin respuesta**: Verificar conexiones y alimentación
- **LCD en blanco**: Comprobar dirección I2C y conexiones
- **Servo errático**: Verificar alimentación suficiente
- **LEDs no encienden**: Revisar conexiones del 74HC595

### Valores por Defecto de Seguridad
- Temperatura: 25°C (si sensor falla)
- Humedad: 50% (si sensor falla)
- Todas las salidas se mantienen en estado seguro

