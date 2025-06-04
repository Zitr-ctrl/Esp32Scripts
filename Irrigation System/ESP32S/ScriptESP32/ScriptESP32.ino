
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
    String linea = LoRaSerial.readStringUntil('\n');
    linea.trim(); // Elimina saltos de línea y espacios

    Serial.println("Mensaje recibido: " + linea);

    // Verifica si es una línea con datos reales
    if (linea.startsWith("+RCV=")) {
      // Formato esperado: +RCV=1,6,1:91:%,-26,11
      int primerComa = linea.indexOf(',');               // después de +RCV=
      int segundoComa = linea.indexOf(',', primerComa + 1);
      int tercerComa = linea.indexOf(',', segundoComa + 1);

      if (segundoComa != -1 && tercerComa != -1) {
        String payload = linea.substring(segundoComa + 1, tercerComa);
        payload = linea.substring(segundoComa + 1, tercerComa);
        payload.trim(); // Esto será algo como "1:91:%"

        Serial.println("Payload limpio: " + payload);

        int sep1 = payload.indexOf(':');
        int sep2 = payload.indexOf(':', sep1 + 1);

        if (sep1 > 0 && sep2 > sep1) {
          String sensor_id = payload.substring(0, sep1);
          String valor = payload.substring(sep1 + 1, sep2);
          String unidad = payload.substring(sep2 + 1);

          String postData = "sensor_id=" + sensor_id + "&valor=" + valor + "&unidad=" + unidad;

          if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.begin("http://192.168.100.8:3000/api/insertar_lectura");
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");

            int httpResponseCode = http.POST(postData);

            if (httpResponseCode > 0) {
              String response = http.getString();
              Serial.println("Respuesta servidor: " + response);
            } else {
              Serial.println("Error en POST: " + String(httpResponseCode));
            }

            http.end();
          } else {
            Serial.println("WiFi no conectado.");
          }
        } else {
          Serial.println("Formato inválido en payload: " + payload);
        }
      }
    } else {
      Serial.println("Mensaje de control ignorado: " + linea);
    }
  }
}

