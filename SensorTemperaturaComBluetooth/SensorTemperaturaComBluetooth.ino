#include <DHT.h>; //INCLUSÃO DE BIBLIOTECA
#include <Timing.h>

#define DHTPIN 7 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
#define tempoEsperaVerificacao 300000

DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
Timing minutosDeEsperaParaVerificar;
Timing timerContador;

int  state = 0;
int temperaturaAmbiente = 27; // Temperatura desejada para o ambiente
int toleranciaDeTemperatura = 2; // Faixa que a temperatura não será alterada
boolean sinalAutomatico = true;
int contador;

void setup()
{
  Serial.begin(9600);  
  Serial.println("O bluetooth está ativo. Conecte-se ao HC-05 a partir de qualquer outro dispositivo Bluetooth com 1234 como chave de emparelhamento!");
  dht.begin(); //INICIALIZA A FUNÇÃO
  contador = tempoEsperaVerificacao/1000;
  minutosDeEsperaParaVerificar.begin(0);
  delay(1000); // 1 SEGUNDO ANTES DE INICIAR 
}
 
void loop() {

  delay(1000); 

  if(Serial.available()  > 0){ 
      state = Serial.read();  // Ler o dado na porta serial
      Serial.println(state);
  }

  if (state == 'a') {
    Serial.println("Ligando o ar-condicionado!");
    // Código que mandará o sinal para o ar
  }

  if (state == 'b') {
    Serial.println("Desligando o ar-condicionado!");
    // Código que mandará o sinal para o ar
  }

  if (state == 'c') {
    Serial.println("Aumentando a temperatura do ar");
    // Código que mandará o sinal para o ar
  }

  if (state == 'd') {
    Serial.println("Diminuindo a temperatura do ar");
    // Código que mandará o sinal para o ar
  }

  if (state == 'e') {
    if(sinalAutomatico == true){
      Serial.println("Controle automático do ar-condicionado parado!");
      sinalAutomatico = false;
    } else {
      Serial.println("Controle automático do ar-condicionado iniciado!");
      sinalAutomatico = true;
    }
    contador = tempoEsperaVerificacao/1000; // Contagem reiniciando com o tempo total até desligar (para evitar que retome o tempo anterior)
  }


  // Se sinalAutomatico for verdadeiro, o controle do ar-condicionado será feito automaticamente
  if(sinalAutomatico == true) {

    if(contador % 10 == 0) {

      Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
      Serial.print(dht.readHumidity()); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
      Serial.print("%"); //IMPRIME O TEXTO NA SERIAL 
      Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
      Serial.print(dht.readTemperature()); //IMPRIME NA SERIAL O VALOR DE TEMPERATURA MEDIDO E REMOVE A PARTE DECIMAL
      Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL

    }

    //Imprime a contagem regressiva no monitor serial a cada 1 segundo 
    Serial.println((contador > 1) ? --contador : contador = tempoEsperaVerificacao/1000);
    
    if (minutosDeEsperaParaVerificar.onTimeout(tempoEsperaVerificacao)){
 
      // O +1 serve pra quando estiver na faixa de temperatura escolhida ele não mudar
      if (dht.readTemperature() > temperaturaAmbiente + toleranciaDeTemperatura) {
        Serial.println("Sensor deve abaixar mais a temperatura!");
      } else if (dht.readTemperature() < temperaturaAmbiente - toleranciaDeTemperatura) {
        Serial.println("Sensor deve aumentar mais a temperatura!");
      }
    }
  }
  
  state = 0;
}
