#include <IRremote.h>

// NEC - 32 bits
// RC5 - 12 bits
// RC6 - 20 bits
// SONY - 20 bits
// UNKNOWN - 0

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
unsigned int teclaB[] = {1250,450, 1250,400, 450,1250, 1250,450, 1250,450, 400,1250, 450,1250, 450,1250, 450,1250, 450,1250, 1250,450, 400};

void setup()
{
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  digitalWrite(9, LOW);
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Valor Decimal: ");
    Serial.println(results.value, DEC);
    ircode   (&results);
    encoding (&results);
    dumpInfo (&results);
    dumpRaw  (&results);
    dumpCode (&results);
    irrecv.resume();
  }

   if(Serial.read() == 'a') {
    for (int i = 1; i < 15; i++) {

    irsend.sendRaw(teclaB, sizeof(teclaB) / sizeof(teclaB[0]), 38 );
    irsend.sendNEC(0x143226DB, 32);
    irsend.sendRC5(0x143226DB, 32);
    // irsend.sendRC6(0x143226DB, 36);
    irsend.sendSony(0x143226DB, 32);
    // irsend.sendPanasonic(0x143226DB, 12);
    // irsend.sendJVC(0x143226DB, 12);
    irsend.sendSAMSUNG(0x143226DB, 32);
    irsend.sendWhynter(0x143226DB, 32);
    Serial.println("Enviando Tecla A");
    delay(1000);
     }
   }




}

void dump(decode_results *results) {
  
  int count = results->rawlen;
  Serial.print("Decodificação: ");
  if (results->decode_type == UNKNOWN) {
    Serial.println("Desconhecida");

  }
  else if (results->decode_type == NEC) {
    Serial.print("NEC");
  }
  else if (results->decode_type == SONY) {
    Serial.print("SONY");
  }
  else if (results->decode_type == RC5) {
    Serial.print("RC5");
  }
  else if (results->decode_type == RC6) {
    Serial.print("RC6");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("LG");
  }
  else if (results->decode_type == JVC) {
    Serial.print("JVC");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Whynter");
  }
  Serial.print("Valor Hexadecimal: ");
  Serial.println(results->value, HEX);
  Serial.print("Qtd bits: ");
  Serial.print(results->bits, DEC);
  Serial.println(" bits");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  
  for (int i = 1; i < count; i++) {
    // if (i & 1) {
    //   Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    // }
    // else {
    //   Serial.write('-');
    //   Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    // }
    Serial.write(',');
    Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
  Serial.println("#####################################################################");
  Serial.println();
}