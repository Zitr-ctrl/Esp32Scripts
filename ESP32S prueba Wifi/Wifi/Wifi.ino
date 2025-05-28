#include <WiFi.h>

// Reemplaza con el nombre y contraseña de tu red Wi-Fi
const char* ssid     = "FAMILIA_ORTIZ";
const char* password = "Familiaortiz";

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  // Conectar a Wi-Fi
  WiFi.begin(ssid, password);

  // Esperar hasta que se conecte
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Mostrar IP al conectarse
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Aquí puedes hacer otras cosas con la conexión
}
