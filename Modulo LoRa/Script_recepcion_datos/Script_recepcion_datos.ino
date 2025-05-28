#include <HardwareSerial.h>
HardwareSerial LoRaSerial(2);  // UART2

void setup() {
  Serial.begin(115200);
  LoRaSerial.begin(115200, SERIAL_8N1, 21, 22);  // RX = 21, TX = 22
  delay(3000);

  Serial.println("Configurando módulo LoRa (ESP32 receptor)");

  // Configurar como receptor (ADDRESS 2)
  LoRaSerial.println("AT+ADDRESS=2");
  delay(500);
  LoRaSerial.println("AT+NETWORKID=5");
  delay(500);
  LoRaSerial.println("AT+PARAMETER=12,7,1,4");
  delay(500);
  LoRaSerial.println("AT+BAND=915000000");
  delay(500);

  Serial.println("Esperando mensajes desde ESP8266...");
}

void loop() {
  if (LoRaSerial.available()) {
    String mensaje = LoRaSerial.readStringUntil('\n');
    Serial.println("Mensaje recibido: " + mensaje);
  }
}
