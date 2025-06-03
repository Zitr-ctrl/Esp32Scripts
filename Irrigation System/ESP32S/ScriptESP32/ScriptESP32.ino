ESP32:
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "FAMILIA_ORTIZ";
const char* password = "Familiaortiz";

HardwareSerial LoRaSerial(2);  // UART2

void setup() {
  Serial.begin(115200);
  LoRaSerial.begin(115200, SERIAL_8N1, 21, 22);
  
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a la red WiFi");

  // Configuración LoRa
  delay(3000);
  Serial.println("Configurando módulo LoRa (ESP32 receptor)");

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

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin("http://192.168.100.8/api/insertar_lectura");  // Cambia a la URL de tu API

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Supongamos que el mensaje tiene formato: "sensor_id:valor:unidad"
      // Ejemplo: "1:55.3:%"
      int separator1 = mensaje.indexOf(':');
      int separator2 = mensaje.indexOf(':', separator1 + 1);
      if (separator1 > 0 && separator2 > separator1) {
        String sensor_id = mensaje.substring(0, separator1);
        String valor = mensaje.substring(separator1 + 1, separator2);
        String unidad = mensaje.substring(separator2 + 1);

        String postData = "sensor_id=" + sensor_id + "&valor=" + valor + "&unidad=" + unidad;
        int httpResponseCode = http.POST(postData);

        if (httpResponseCode > 0) {
          String response = http.getString();
          Serial.println("Respuesta servidor: " + response);
        } else {
          Serial.println("Error en POST: " + String(httpResponseCode));
        }
      } else {
        Serial.println("Formato de mensaje incorrecto.");
      }
      http.end();
    } else {
      Serial.println("WiFi no conectado.");
    }
  }
}