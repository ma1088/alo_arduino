//esp8266
#define DEBUG true
#include <SoftwareSerial.h>
SoftwareSerial esp8266(2, 3);

//som
#define sensorSom 5
#define silencio 1
#define delayfinal 10       //Valor representa um tempo em milissegundos, esse tempo é aguardado pelo programa para que se inicie novamente o loop.
int numLeitura = 200;         //Valor representa a quantidade de leituras segidas para se determinar o ruído

//métodos
void setup() {
  Serial.begin(9600);
  
  //som
  pinMode(sensorSom,INPUT);

  //esp8266
  esp8266.begin(115200);
  sendData("AT+RSTrn", 2000, DEBUG);
  delay(1000);
  Serial.println("Versao de firmware");
  delay(3000);
  sendData("AT+GMRrn", 2000, DEBUG);
  sendData("AT+CIOBAUD=19200rn", 2000, DEBUG);
  Serial.println("** Final **");
}

void loop() {
  int sinal = digitalRead(sensorSom);
  if (sinal < silencio){
    int soma = 0;
    for (int i=0; i < numLeitura; i++){
      sinal = digitalRead(sensorSom);
      soma = soma + sinal;
    }
    double db = 0.361809*soma; //número que cheguei com determinado ajuste do potenciômetro e um app "decibelímetro" para Android.
  }
  delay(delayfinal);
}

//métodos esp8266
String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
