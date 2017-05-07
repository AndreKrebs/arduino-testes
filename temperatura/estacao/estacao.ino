//#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// Pino conectado ao pino de dados do sensor
#define DHTPIN 11

// Sensor DHT 22  (AM2302)
#define DHTTYPE DHT22   

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Definicoes do sensor : pino, tipo
DHT dht(DHTPIN, DHTTYPE);

int portaLed = 10; // Porta a ser utilizada para ligar o led  

int portaLDR = A5; // Porta analógica utilizada pelo LDR
int portaXd28 = A0; // Porta analógica sensor de solo

// variaveis com dados dos sensores
float temp = 0;
float humid = 0;

void setup() {
  Serial.begin(9600); 

  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  
  pinMode(portaLed, OUTPUT); //Define a porta do Led como saída  
  pinMode(portaXd28, INPUT); // Define porta de entrada do sensor de solo
  
  Serial.println("Aguardando dados...");
  // Iniclaiza o sensor DHT
  dht.begin();
  
}

void loop() {
  
  
  // Leitura da umidade
  humid = dht.readHumidity();
  // Leitura da temperatura (Celsius)
  temp = dht.readTemperature();

  // Verifica se o sensor esta respondendo
  if (isnan(humid) || isnan(temp))
  {
    Serial.println("Falha ao ler dados do sensor DHT !!!");
    return;
  }

  
  /*Serial.println("-----------------------");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" C");
  
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.println(" %");*/

  sensorLight();
  sensorSoilHumidity();

  printLcd();

  // Aguarda segundos entre as medicoes
  delay(5000);

}

void sensorLight() {

  int state = analogRead(portaLDR);  //Lê o valor fornecido pelo LDR  
  
  Serial.print("Current Light: ");
  Serial.println(state);
  
      
  // Caso o valor lido na porta analógica seja maior do que 
  if (state > 300)    
  {  
    digitalWrite(portaLed, HIGH);
    Serial.print("Lumin:Off\r\n");
  }  
  else  //Caso contrário, apaga o led  
  {  
    digitalWrite(portaLed, LOW);  
    Serial.print("Lumin:On\r\n");
  }  
  
  
}

void sensorSoilHumidity() {
  // Le o valor do pino A0 do sensor
  int valor_analogico = analogRead(portaXd28);
  
  //Solo umido
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println("Solo: umido\r\n");
  }
 
  //Solo com umidade moderada
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println("Solo: umidade moderada\r\n");
  }
 
  //Solo seco
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println("Solo: seco\r\n");
  }
} 

void printLcd() {
  //Limpa a tela
  lcd.clear();

  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0, 0);
  lcd.print("AR ");

  // imprime a temperatura
  lcd.setCursor(3, 0);
  lcd.print(temp);
  lcd.setCursor(8, 0);
  lcd.print("C");

  lcd.setCursor(10, 0);
  lcd.print(humid);
  lcd.setCursor(15, 0);
  lcd.print("%");
  
}

/*void printLcd() {
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("KREBSCODE!");
  lcd.setCursor(3, 1);
  lcd.print(" LCD 16x2");
  //delay(5000);
   
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
}*/
