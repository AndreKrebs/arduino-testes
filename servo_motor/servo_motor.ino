#include <Servo.h>
 
Servo motor1;
Servo motor2;

int totalExec = 0;

void setup() 
{ 
 motor1.attach(3);

 Serial.begin(19200);
} 
void loop() 
{ 
    int cont, aux;

    int regServo1 = 13;

    int posIni1 = 90;

    if(totalExec==1 || totalExec==0) {

      motor1.write(270+regServo1); 
//      motor1.write(0+regServo1); 
      delay(4000);

      leftRightServo(posIni1, regServo1);

//      backAndForth(180+regServo1, 90+regServo1);
//      backAndForth(0+regServo1, 90+regServo1);

      if(totalExec==1){ totalExec++; }

    }
} 

void leftRightServo(int posIni1, int regServo1) {
  

  for(int aux=0; (posIni1+aux)<=180; aux+=1) {

    // imprime posição
    Serial.print("POS: ");
    Serial.print((posIni1+regServo1)+aux);
    Serial.print(" - ");
    
    motor1.write((posIni1+regServo1)+aux);
    delay(700);

    // imprime posição
    Serial.print((posIni1-regServo1)-aux);
    Serial.println();
    
    motor1.write((posIni1-regServo1)-aux); 
    delay(700);
  }
  Serial.println("Fim...\n\n");
  delay(2000);
}

void backAndForth(int go, int back) {

  motor1.write(go);
  delay(700);
  motor1.write(go);
  delay(1000);
  
}

