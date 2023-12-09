#include <IRremote.h>

int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

void ircode   (decode_results *results);
void encoding (decode_results *results);
void dumpInfo (decode_results *results);
void dumpRaw  (decode_results *results);
void dumpCode (decode_results *results);


// Ligar
unsigned int teclaA[] = {3400,1800, 350,1350, 350,1350, 450,400, 350,400, 400,400, 400,1350, 350,400, 350,500, 350,1350, 350,1400, 350,400, 400,1350, 400,400, 350,400, 400,1350, 350,1400, 350,400, 400,1350, 350,1350, 350,400, 400,400, 400,1350, 350,400, 350,450, 400,1400, 300,400, 400,400, 400,400, 350,400, 400,450, 350,400, 300,500, 350,450, 350,400, 400,400, 350,400, 350,450, 400,400, 350,400, 350,450, 400,400, 300,450, 400,1350, 400,400, 400,400, 400,1350, 350,400, 450,400, 350,1350, 400,1350, 350,450, 400,400, 350,1350, 350,1350, 450};
// Desligar
unsigned int teclaB[] = {3400,1800, 350,1350, 350,1350, 400,400, 350,400, 400,400, 350,1350, 350,400, 400,400, 350,1350, 400,1350, 350,400, 350,1400, 350,400, 350,400, 400,1350, 350,1400, 350,400, 350,1350, 350,1400, 350,400, 350,400, 400,1350, 350,400, 350,450, 350,1350, 350,400, 400,400, 350,400, 350,400, 400,400, 350,400, 350,450, 350,400, 350,400, 400,400, 350,400, 350,400, 400,400, 350,400, 400,400, 350,400, 350,400, 400,1350, 350,400, 400,400, 350,1350, 350,400, 400,400, 350,1350, 400,1350, 350,400, 400,400, 350,1350, 350,1350, 400};
// Aumentar
unsigned int teclaC[] = {1300,450, 1250,400, 450,1300, 1250,400, 1250,400, 450,1300, 400,1250, 450,1300, 400,1250, 450,1250, 1250,450, 400};
// Diminuir
unsigned int teclaD[] = {8900,4500, 550,550, 550,600, 550,1700, 550,600, 550,600, 550,600, 500,600, 550,600, 550,1700, 550,1700, 550,600, 550,1700, 550,1700, 550,1700, 550,1700, 550,1700, 550,700, 500,1750, 500,600, 550,600, 550,600, 550,600, 500,600, 550,600, 550,1700, 550,600, 550,1800, 550,1700, 550,1700, 550,1750, 500,1750, 500,1750, 550};

unsigned int teclaE[] = {8950,4450, 550,550, 550,550, 550,1650, 550,600, 550,550, 550,550, 550,550, 550,600, 500,1700, 550,1650, 550,550, 550,1700, 550,1650, 550,1650, 550,1700, 550,1650, 550,550, 550,550, 550,600, 550,1650, 550,550, 550,550, 550,600, 500,600, 550,1650, 550,1650, 550,1700, 550,550, 550,1650, 550,1700, 550,1650, 550,1650, 550};
void setup()
{
  Serial.begin(9600);
  irsend.begin(3);
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
    dumpInfo (&results);
    dumpCode (&results);
    Serial.println();
    irrecv.resume();
  }

   //Testar qual a frequência que o dispositivo responde
    //if(Serial.read() == 'a') {
    //  for(int i = 1; i < 1000; i++) {
    //    irsend.sendRaw(teclaA, sizeof(teclaA) / sizeof(teclaA[0]), 38);
    //    Serial.println("Enviando Tecla A");
    //    //Serial.println(i);
    //    delay(1000);
    //  }
    //}

  // Ligar o Ar-condicionado
  if(Serial.read() == 'a') {
    irsend.sendRaw(teclaA, sizeof(teclaA) / sizeof(teclaA[0]), 38);
    Serial.println("Enviando Tecla A");
    delay(500);
  }

  // Desligar o Ar-condicionado
  if(Serial.read() == 'b') {
    irsend.sendRaw(teclaB, sizeof(teclaB) / sizeof(teclaB[0]), 38);
    Serial.println("Enviando Tecla B");
    delay(500);
  }

  // Aumentar temperatura do Ar-condicionado
  if(Serial.read() == 'c') {
    irsend.sendRaw(teclaC, sizeof(teclaC) / sizeof(teclaC[0]), 38);
    Serial.println("Enviando Tecla C");
    delay(500);
  }

  // Diminuir temperatura do Ar-condicionado
  if(Serial.read() == 'd') {
    irsend.sendRaw(teclaD, sizeof(teclaD) / sizeof(teclaD[0]), 38);
    Serial.println("Enviando Tecla D");
    delay(500);
  }

  // ????
  if(Serial.read() == 'e') {
    irsend.sendRaw(teclaE, sizeof(teclaE) / sizeof(teclaE[0]), 38);
    Serial.println("Enviando Tecla E");
    delay(500);
  }


  if(Serial.read() == 'f') {

  Serial.println("Enviando Tecla F");
  irsend.sendNEC(0x1E6AFF13, 32);
  delay(1000);
  }
}
