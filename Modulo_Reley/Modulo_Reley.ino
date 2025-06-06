/*
	Capitulo 8 de Arduino desde cero en Español
	Programa que permite verificar el funcionamiento de un modulo de rele, simple o
	doble activandolo a intervalos de 5 segundos.

	Autor: bitwiseAr  

*/

int RELE = 2;			// pin IN de modulo a pin digital 2 de Arduino


void setup(){
  pinMode(RELE, OUTPUT);	// pin 2 como salida
}

void loop(){
  digitalWrite(RELE, LOW);	// activacion del modulo de rele con un nivel bajo
  delay(2000);			// demora de 5 seg.
  digitalWrite(RELE, HIGH);	// apagado del modulo de rele con un nivel alto
  delay(2000);			// demora de 5 seg.
}