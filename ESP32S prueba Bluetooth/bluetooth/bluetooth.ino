#include "BluetoothSerial.h"

// Crear el objeto BluetoothSerial
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);         // Inicializar el monitor serial
  SerialBT.begin("ESP32S-Test"); // Nombre del Bluetooth que aparecerá
  Serial.println("Bluetooth iniciado. Ahora puedes emparejarte.");
}

void loop() {
  if (Serial.available()) {
    // Si mandas algo desde el monitor serial, lo envía por Bluetooth
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available()) {
    // Si recibes algo por Bluetooth, lo muestra en el monitor serial
    Serial.write(SerialBT.read());
  }

  delay(20);
}
