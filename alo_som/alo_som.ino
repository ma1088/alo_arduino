//esp8266
#define esp8266gpio0 6
#define esp8266gpio2 7
#define esp8266chpd 8
#define esp8266tx 9
#define esp8266rx 10
#define esp8266rst 11
#define rede "Marilia"
#define senha "guilherme!"
#include <SoftwareSerial.h>
SoftwareSerial esp8266(esp8266tx, esp8266rx);

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
  Serial.println("Inicialização ESP-8266");
  digitalWrite(esp8266gpio0,HIGH);
  digitalWrite(esp8266gpio2,HIGH);
  digitalWrite(esp8266chpd,HIGH);
  digitalWrite(esp8266rst,LOW);
  delay(1000);
  digitalWrite(esp8266rst,HIGH);
  delay(1500);
  esp8266.begin(115200);
  esp8266.setTimeout(5000);
  while (!esp8266resposta()) {
    Serial.println("Reset");
    esp8266.println("AT+RST");
  }
  Serial.println("Teste");
  esp8266.println("AT");
  if (esp8266resposta()){
    esp8266.println("AT+GMR");
    boolean b = esp8266resposta();
    b = esp8266resposta();
  }
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

boolean esp8266resposta(){
  Serial.println("Resposta: ");
  int limite = 5500;
  unsigned long chegada = millis();
  boolean continuar = true;
  boolean resposta = false;
  String S = "";
  unsigned long ultimoChar = 0;
  while (continuar) {
    if (esp8266.available()) {
      char c = esp8266.read();
      ultimoChar = millis();
      Serial.print (c);
      S = S + c;
      if (c == 10) { //LF
        byte p = S.indexOf(13);
        String S1 = S.substring(0,p);
        if ((S1 == "OK") or (S1 == "ready")) {
          continuar = false;
          resposta = true;
        }
        if ((S1 == "no change") or (S1 == "ERROR")) {
          continuar = false;
          resposta = false;
        }
        S="";
      }
    }else {
      if (millis() - chegada > limite) {
        continuar = false;
        resposta = false;
      }
    }
  }
  Serial.println(".");
  return resposta;
}
