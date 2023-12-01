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


// Teclas
unsigned int teclaA[] = {1300 ,400 ,1250 ,400 ,450 ,1250 ,1300 ,400 ,1300 ,400 ,450 ,1250 ,400 ,1250 ,450 ,1250 ,450 ,1250 ,450 ,1250 ,1300 ,400 ,450};
// Ligar ventilador
unsigned int teclaB[] = {1300,400, 1250,450, 400,1300, 1250,400, 1300,400, 450,1250, 400,1300, 400,1250, 450,1250, 450,1250, 1300,400, 450 };
unsigned int teclaC[] = {1300,450, 1250,400, 450,1300, 1250,400, 1250,400, 450,1300, 400,1250, 450,1300, 400,1250, 450,1250, 1250,450, 400};
// Ligar TV
unsigned int teclaD[] = {8900,4500, 550,550, 550,600, 550,1700, 550,600, 550,600, 550,600, 500,600, 550,600, 550,1700, 550,1700, 550,600, 550,1700, 550,1700, 550,1700, 550,1700, 550,1700, 550,700, 500,1750, 500,600, 550,600, 550,600, 550,600, 500,600, 550,600, 550,1700, 550,600, 550,1800, 550,1700, 550,1700, 550,1750, 500,1750, 500,1750, 550};

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

  // Testar qual a frequência que o dispositivo responde
  //  if(Serial.read() == 'a') {
  //   for(int i = 1; i < 1000; i++) {
  //     irsend.sendRaw(teclaC, sizeof(teclaC) / sizeof(teclaC[0]), i);
  //     Serial.println("Enviando Tecla A");
  //     Serial.println(i);
  //     delay(500);
  //   }

  if(Serial.read() == 'a') {
    irsend.sendRaw(teclaC, sizeof(teclaC) / sizeof(teclaC[0]), 38);
    Serial.println("Enviando Tecla A");
    delay(500);
  }

  if(Serial.read() == 'b') {

  Serial.println("Enviando Tecla B");
  irsend.sendNEC(0x1E6AFF13, 32);
  delay(1000);
  }
}
