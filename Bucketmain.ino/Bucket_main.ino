// Bibliotecas dos sensores
#include <OneWire.h>
#include <DallasTemperature.h>

// Biblioteca Bluetooth do ESP32
#include "BluetoothSerial.h"

// Cria o objeto Bluetooth
BluetoothSerial SerialBT;

// Pinos dos sensores
#define ONE_WIRE_BUS 2
#define SOIL_SENSOR_PIN 4

// Inicializa o DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Valores de calibração
const int SOLO_SECO = 3200;
const int SOLO_UMIDO = 1500;

void setup() {

  // Monitor Serial
  Serial.begin(115200);

  // Inicia o Bluetooth
  SerialBT.begin("ESP32_Composteira");

  // Inicializa o sensor de temperatura
  sensors.begin();

  Serial.println("Bluetooth iniciado!");
}

void loop() {

  // Leitura da temperatura
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  // Leitura da umidade do solo
  int leitura = analogRead(SOIL_SENSOR_PIN);

  int umidadeSolo = map(leitura, SOLO_SECO, SOLO_UMIDO, 0, 100);
  umidadeSolo = constrain(umidadeSolo, 0, 100);

  // ===== Monitor Serial =====
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade do Solo: ");
  Serial.print(umidadeSolo);
  Serial.println(" %");

  // ===== Bluetooth =====
  SerialBT.print("Temperatura: ");
  SerialBT.print(temperatura);
  SerialBT.println(" °C");

  SerialBT.print("Umidade do Solo: ");
  SerialBT.print(umidadeSolo);
  SerialBT.println(" %");

  SerialBT.println("-----------------------");

  delay(2000);
}