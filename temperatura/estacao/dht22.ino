#include <DHT.h>

// Pino conectado ao pino de dados do sensor
#define DHTPIN 8

// Sensor DHT 22  (AM2302)
#define DHTTYPE DHT22   

// Definicoes do sensor : pino, tipo
DHT dht(DHTPIN, DHTTYPE);

int portaLed = 10; // Porta a ser utilizada para ligar o led  

int portaLDR = A5; // Porta analógica utilizada pelo LDR
int portaXd28 = A0; // Porta analógica sensor de solo

void setup() {
  Serial.begin(9600); 
  
  pinMode(portaLed, OUTPUT); //Define a porta do Led como saída  
  pinMode(portaXd28, INPUT); // Define porta de entrada do sensor de solo
  
  Serial.println("Aguardando dados...");
  // Iniclaiza o sensor DHT
  dht.begin();
  
}

void loop() {
  // Aguarda 2 segundos entre as medicoes
  delay(2000);
  
  // Leitura da umidade
  float h = dht.readHumidity();
  // Leitura da temperatura (Celsius)
  float t = dht.readTemperature();

  // Verifica se o sensor esta respondendo
  if (isnan(h) || isnan(t))
  {
    Serial.println("Falha ao ler dados do sensor DHT !!!");
    return;
  }
  Serial.print("-----------------------\r\n");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" C\r\n\r\n");
  
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %\r\n\r\n");

  sensorLight();
  sensorSoilHumidity();

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

