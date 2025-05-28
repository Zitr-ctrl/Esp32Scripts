// Definir el pin del LED en el ESP32. Suele ser el pin 2, pero puedes verificar en las especificaciones de tu placa.
#define LED_BUILTIN 2

// la función setup se ejecuta una vez cuando reinicias o enciendes la placa
void setup() {
  // inicializar el pin LED_BUILTIN como salida
  pinMode(LED_BUILTIN, OUTPUT);
}

// la función loop se ejecuta en bucle continuamente
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // encender el LED
  delay(1000);                      // esperar un segundo
  digitalWrite(LED_BUILTIN, LOW);   // apagar el LED
  delay(1000);                      // esperar otro segundo
}
