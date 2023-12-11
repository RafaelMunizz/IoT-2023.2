#include <IRremote.h>

int RECV_PIN = 8;  // Pino do arduino
int state = 0;     // Entrada de dados recebida
IRsend irsend;
decode_results results;

// MAC ESP: CC:DB:A7:5B:B2:B2  

IRrecv irrecv(RECV_PIN);

void ircode(decode_results *results);
void encoding(decode_results *results);
void dumpInfo(decode_results *results);
void dumpRaw(decode_results *results);
void dumpCode(decode_results *results);

// Ligar
unsigned int ligarAr[] = { 3400, 1800, 350, 1350, 350, 1350, 450, 400, 350, 400, 400, 400, 400, 1350, 350, 400, 350, 500, 350, 1350, 350, 1400, 350, 400, 400, 1350, 400, 400, 350, 400, 400, 1350, 350, 1400, 350, 400, 400, 1350, 350, 1350, 350, 400, 400, 400, 400, 1350, 350, 400, 350, 450, 400, 1400, 300, 400, 400, 400, 400, 400, 350, 400, 400, 450, 350, 400, 300, 500, 350, 450, 350, 400, 400, 400, 350, 400, 350, 450, 400, 400, 350, 400, 350, 450, 400, 400, 300, 450, 400, 1350, 400, 400, 400, 400, 400, 1350, 350, 400, 450, 400, 350, 1350, 400, 1350, 350, 450, 400, 400, 350, 1350, 350, 1350, 450 };
// Desligar
unsigned int desligarAr[] = { 3400, 1800, 350, 1350, 350, 1350, 400, 400, 350, 400, 400, 400, 350, 1350, 350, 400, 400, 400, 350, 1350, 400, 1350, 350, 400, 350, 1400, 350, 400, 350, 400, 400, 1350, 350, 1400, 350, 400, 350, 1350, 350, 1400, 350, 400, 350, 400, 400, 1350, 350, 400, 350, 450, 350, 1350, 350, 400, 400, 400, 350, 400, 350, 400, 400, 400, 350, 400, 350, 450, 350, 400, 350, 400, 400, 400, 350, 400, 350, 400, 400, 400, 350, 400, 400, 400, 350, 400, 350, 400, 400, 1350, 350, 400, 400, 400, 350, 1350, 350, 400, 400, 400, 350, 1350, 400, 1350, 350, 400, 400, 400, 350, 1350, 350, 1350, 400 };
// Aumentar
unsigned int aumentarAr[] = { 1300, 450, 1250, 400, 450, 1300, 1250, 400, 1250, 400, 450, 1300, 400, 1250, 450, 1300, 400, 1250, 450, 1250, 1250, 450, 400 };
// Diminuir
unsigned int diminuirAr[] = { 8900, 4500, 550, 550, 550, 600, 550, 1700, 550, 600, 550, 600, 550, 600, 500, 600, 550, 600, 550, 1700, 550, 1700, 550, 600, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 550, 700, 500, 1750, 500, 600, 550, 600, 550, 600, 550, 600, 500, 600, 550, 600, 550, 1700, 550, 600, 550, 1800, 550, 1700, 550, 1700, 550, 1750, 500, 1750, 500, 1750, 550 };

//unsigned int teclaE[] = {8950,4450, 550,550, 550,550, 550,1650, 550,600, 550,550, 550,550, 550,550, 550,600, 500,1700, 550,1650, 550,550, 550,1700, 550,1650, 550,1650, 550,1700, 550,1650, 550,550, 550,550, 550,600, 550,1650, 550,550, 550,550, 550,600, 500,600, 550,1650, 550,1650, 550,1700, 550,550, 550,1650, 550,1700, 550,1650, 550,1650, 550};

void setup() {
  Serial.begin(38400);
  Serial.println("O bluetooth está ativo. Conecte-se ao HC-05 a partir de qualquer outro dispositivo Bluetooth com 1234 como chave de emparelhamento!");
  irsend.begin(3);
  irrecv.enableIRIn();
  delay(500);
}

void loop() {

  delay(1000);
 
  // Leitura se o bluetooth está recebendo dados
  if (Serial.available() > 0) {
    state = Serial.read();  // Ler o dado na porta serial
    Serial.println(state);
  }

  // Leitura se o receptor infra está recebendo dados
  if (irrecv.decode(&results)) {
    dumpInfo(&results);
    dumpCode(&results);
    //Serial.println();
    irrecv.resume();
  }

  // Testar qual a frequência que o dispositivo responde
  // for(int i = 1; i < 1000; i++) {
  //   irsend.sendRaw(ligarAr, sizeof(ligarAr) / sizeof(ligarAr[0]), 38);
  //   Serial.println("Enviando sinal!");
  //   //Serial.println(i);
  //   delay(1000);
  // }

  // Ligar o Ar-condicionado
  if (state == 'a') {
    Serial.println("Ligando o ar-condicionado!");
    irsend.sendRaw(ligarAr, sizeof(ligarAr) / sizeof(ligarAr[0]), 38);
    delay(500);
  }

  // Desligar o Ar-condicionado
  if (state == 'b') {
    Serial.println("Desligando o ar-condicionado!");
    irsend.sendRaw(desligarAr, sizeof(desligarAr) / sizeof(desligarAr[0]), 38);
    delay(500);
  }

  // Aumentar temperatura do Ar-condicionado
  if (state == 'c') {
    Serial.println("Aumentando a temperatura do ar");
    irsend.sendRaw(aumentarAr, sizeof(aumentarAr) / sizeof(aumentarAr[0]), 38);
    delay(500);
  }

  // Diminuir temperatura do Ar-condicionado
  if (state == 'd') {
    Serial.println("Diminuindo a temperatura do ar");
    irsend.sendRaw(diminuirAr, sizeof(diminuirAr) / sizeof(diminuirAr[0]), 38);
    delay(500);
  }

  // if(state == 'f') {

  //   Serial.println("Enviando Tecla F");
  //   irsend.sendNEC(0x1E6AFF13, 32);
  //   delay(1000);
  // }

  state = 0;  // Zerando o armazenamento do dado recebido
}
