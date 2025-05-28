#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// LCD 20x4 en dirección I2C 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);

// LoRa: RX = D2 (GPIO4), TX = D1 (GPIO5)
SoftwareSerial LoRaSerial(D2, D1);

void setup() {
  Serial.begin(115200);

  // Iniciar LCD (con SDA = GPIO12, SCL = GPIO13)
  Wire.begin(12, 13);
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando ESP8266");

  // Iniciar LoRa
  LoRaSerial.begin(115200);
  delay(3000);

  lcd.setCursor(0, 1);
  lcd.print("Configurando LoRa");

  LoRaSerial.println("AT+ADDRESS=1");
  delay(500);
  LoRaSerial.println("AT+NETWORKID=5");
  delay(500);
  LoRaSerial.println("AT+PARAMETER=12,7,1,4");
  delay(500);
  LoRaSerial.println("AT+BAND=915000000");
  delay(500);

  Serial.println("Listo para enviar");
  lcd.setCursor(0, 2);
  lcd.print("Listo para enviar...");
}

void loop() {
  String mensaje = "Hola desde ESP8266!";
  String comando = "AT+SEND=2," + String(mensaje.length()) + "," + mensaje;
  LoRaSerial.println(comando);
  Serial.println("Mensaje enviado: " + mensaje);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enviado a ESP32:");
  lcd.setCursor(0, 1);
  lcd.print(mensaje);
  lcd.setCursor(0, 2);
  lcd.print("LoRa: OK");

  delay(5000);
}
