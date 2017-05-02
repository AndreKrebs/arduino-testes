/**
 * Exemplo do site arduinoecia, 
 */
#include "ESP8266.h"
#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial minhaSerial(2 , 3); 

// Define que o modulo ira utilizar a serial minhaSerial
ESP8266 wifi(minhaSerial);

// Configuracao ID e senha da rede Wireless
#define SSID        "nome_da_rede"
#define PASSWORD    "senha"


void setup()
{
    Serial.begin(19200);
    // no exemplo do site não tem essa linha e isso causa erro
    minhaSerial.begin(19200);

    // uma function pra coisa ficar um pouco mais organizada
    start8266();
}

void start8266() {
  Serial.print("Inicializando modulo\r\n");
  Serial.print("Versao do firmware: ");
  Serial.print(wifi.getVersion().c_str());
  // Define modo de operacao como STA (station)
  if (wifi.setOprToStation()) {
      Serial.print("Modo STA ok\r\n");
  } else {
      Serial.print("Erro ao definir modo STA !r\n");
  }

  // Conexao a rede especificada em SSID
  if (wifi.joinAP(SSID, PASSWORD)) {
      Serial.print("Conectado com sucesso a rede wireless\r\n");
      Serial.print("IP: ");       
      Serial.println(wifi.getLocalIP().c_str());
  } else {
      Serial.print("Erro ao conectar rede wireless !!!\r\n");
  }
  
  Serial.print("*** Fim ***\r\n");

}

void loop(void)
{
    
}
