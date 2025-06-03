#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// LCD I2C 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

// LoRa serial (SoftwareSerial)
SoftwareSerial LoRaSerial(D2, D1); // RX, TX para LoRa

// Sensor de humedad
const int pinHumedad = A0;

void setup() {
  Serial.begin(115200);

  // Iniciar LCD (con SDA en GPIO12, SCL en GPIO13)
  Wire.begin(12, 13);
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando ESP8266");

  // Iniciar LoRa
  LoRaSerial.begin(115200);
  delay(3000);

  lcd.setCursor(0, 1);
  lcd.print("Config LoRa...");

  LoRaSerial.println("AT+ADDRESS=1");
  delay(500);
  LoRaSerial.println("AT+NETWORKID=5");
  delay(500);
  LoRaSerial.println("AT+PARAMETER=12,7,1,4");
  delay(500);
  LoRaSerial.println("AT+BAND=915000000");
  delay(500);

  lcd.setCursor(0, 2);
  lcd.print("Listo para enviar");
}

void loop() {
  int humedadValor = analogRead(pinHumedad);
  int humedadPct = map(humedadValor, 1023, 300, 0, 100); // Ajusta si es necesario

  // Construir mensaje
  String mensaje = "Humedad: " + String(humedadPct) + "%";
  String comando = "AT+SEND=2," + String(mensaje.length()) + "," + mensaje;

  // Enviar por LoRa
  LoRaSerial.println(comando);
  Serial.println("Enviado: " + mensaje);

  // Mostrar en pantalla
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humedad suelo:");
  lcd.setCursor(0, 1);
  lcd.print(humedadPct);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("TX LoRa OK -> ESP32");

  delay(5000);
}
