#include <SoftwareSerial.h>

// RX = D2 (GPIO4), TX = D1 (GPIO5)
SoftwareSerial LoRaSerial(D2, D1);  // RX, TX para LoRa

void setup() {
  Serial.begin(115200);
  LoRaSerial.begin(115200);
  delay(3000);

  Serial.println("Configurando módulo LoRa (ESP8266)");

  // Configurar como emisor (ADDRESS 1)
  LoRaSerial.println("AT+ADDRESS=1");
  delay(500);
  LoRaSerial.println("AT+NETWORKID=5");
  delay(500);
  LoRaSerial.println("AT+PARAMETER=12,7,1,4");
  delay(500);
  LoRaSerial.println("AT+BAND=915000000");
  delay(500);

  Serial.println("Listo para enviar mensajes al ESP32...");
}

void loop() {
  String mensaje = "Hola desde ESP8266!";
  String comando = "AT+SEND=2," + String(mensaje.length()) + "," + mensaje;
  LoRaSerial.println(comando);
  Serial.println("Mensaje enviado: " + mensaje);
  delay(5000);
}
