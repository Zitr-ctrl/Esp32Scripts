#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configurar LCD 20x4 con dirección 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4); 

void setup() {
  // Iniciar la comunicación I2C en los pines GPIO12 (SDA), GPIO13 (SCL)
  Wire.begin(12, 13);

  // Iniciar LCD
  lcd.begin(20, 4);
  lcd.backlight();

  // Mostrar mensajes de prueba
  lcd.setCursor(0, 0);
  lcd.print("Mi Preciosa");

  lcd.setCursor(0, 1);
  lcd.print("Vas a ser una");

  lcd.setCursor(0, 2);
  lcd.print("Gran Licenciada");

  lcd.setCursor(0, 3);
  lcd.print("Te Amo <3");
}

void loop() {
  // Nada en el loop (solo pantalla estática)
}
