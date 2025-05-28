#include <SoftwareSerial.h>

// Crear el objeto SoftwareSerial en pines 10 (RX) y 11 (TX)
SoftwareSerial BT(10, 11);  // RX, TX

void setup() {
  BT.begin(9600);  // Comunicación serial con HC-06
  Serial.begin(9600);

}

void loop() {
  if(BT.available()){
    Serial.write(BT.read());
  }

  if(Serial.available()){
    BT.write(Serial.read());
  }
}
