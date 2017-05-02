#include <Servo.h>
 
Servo servo1;

void setup() {
  servo1.attach(3);
  Serial.begin(19200);
}

void loop() {
  int angle = analogRead(0); // Lê o valor do potenciômetro
  
  Serial.println(angle); // imprime valor do potenciometro
  
  angle=map(angle, 0, 600, 0, 180); // Mapeia os valores de 0 a 180 graus

  servo1.write(angle); // informa o valor para o servo

  delay(15); // delay para dar tempo ao servo  

}
