/**
 * Exemplo da lib ESP8266.h adaptado
 * para funcionar nas portas 2 e 3
 */
#include "ESP8266.h"
#include "SoftwareSerial.h"

// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial minhaSerial(2 , 3); 
ESP8266 wifi(minhaSerial);

#define SSID        "nome_da_rede"
#define PASSWORD    "senha"


void setup(void)
{
    Serial.begin(19200);
    minhaSerial.begin(19200);
    Serial.print("setup begin\r\n");

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());
    
    
    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } else {
        Serial.print("to station err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    Serial.print("setup end\r\n");
}

void loop(void)
{
}
