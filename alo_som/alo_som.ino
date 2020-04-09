//esp8266
#define timeout 5500
#define esp8266gpio0 12
#define esp8266gpio2 13
#define esp8266chpd 8
#define esp8266tx 6
#define esp8266rx 5
#define esp8266rst 7
String rede = "marilia";
String senha = "guilherme";
#include <SoftwareSerial.h>
SoftwareSerial esp8266(esp8266rx, esp8266tx);

//som
#define sensorSom 3
#define silencio 1
#define delayfinal 10       //Valor representa um tempo em milissegundos, esse tempo é aguardado pelo programa para que se inicie novamente o loop.
int numLeitura = 200;         //Valor representa a quantidade de leituras segidas para se determinar o ruído

//métodos
void setup() {
  Serial.begin(115200);//9600);
  
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
  boolean atrst = false;
  boolean at = false;
  boolean cmd = false;
  int i = 0;
  while (!atrst or !at or i < 1) {
    atrst = esp8266cmd("AT+RST",2000);
    delay(500);
    at = esp8266cmd("AT",1000);
    i += 1;
  }
  cmd = esp8266cmd("AT+GMR",1000);
  Serial.println ("Iniciou");
  String conncmd = "AT+CWJAP=" + rede + "," + senha;
  cmd = esp8266cmd(conncmd,1000);
  if (cmd) {
    Serial.println("Conectado!");
  } else {
    Serial.println("Tente outra vez");
  }
}

void loop() {
  int sinal = digitalRead(sensorSom);
  if (sinal < silencio){
    int db = mede_som();
    //envia_som
    if (db > 40) {
      //envia som
      //Serial.println(db);
    }
  }
  delay(delayfinal);
}

int mede_som(){
  int soma = 0;
  for (int i=0; i < numLeitura; i++){
    int sinal = digitalRead(sensorSom);
    soma = soma + sinal;
  }
  double db = 0.361809*soma; //número que cheguei com determinado ajuste do potenciômetro e um app "decibelímetro" para Android.
  return db;
}

boolean esp8266cmd(String comando,int atraso){
  boolean b = false;
  Serial.println(comando);
  esp8266.println(comando);
  //delay(atraso);

  unsigned long limite = millis() + timeout + atraso;
  String s = "";
  while (millis() < limite) {
    while (esp8266.available()) {
      char c = esp8266.read();
      s = s + c;
    }
  }
  if (s.indexOf("OK") > 0) {
    Serial.println(s + "!");
    b = true;
  } else {
    Serial.println(s + ";");
  }
  return b;
}

//funciona mas não quero usar :P
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
