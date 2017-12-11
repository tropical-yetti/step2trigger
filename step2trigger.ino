/* 
 *  ANDRE SOARES DAS NEVES
 *  ansone@gmail.com
 *  07/2017
 *  
 *  Programa para eliminação de inconsistências de leitura de sensor e aleatorização de trigger
 *  
 *  Condições de aleatorização:
 *    Não deve haver a ocorrência de dois estados altos consecutivos
 *    Não deve haver a ocorrência de mais que quatro repetições de estado baixo
 * 
 * 
 * Implementações desta versão:
 *  (x) Independência de atrasos, sistema adaptável a diferentes ritmos de caminhada.
 *  (x) Ativação orientada à pisada: Um detector de borda de subida (detector de pisada) para ativação do trigger.
 *  (x) Aleatorização do trigger em tempo de execução e sem o uso de switch/case.
 *  (x) Um filtro passa-baixa de 50 amostras para amenizar inconsistências na leitura do footswitch.
 *  (x) Duas saídas adicionais aleatorizadas, porém condicionadas à ativação do trigger de Teste.
 *  (-) Possibilidade de habilitar 
 * 
 */
#define T 6 //Pin do trigger de Teste
#define C1 4 //Pin do triger de Condicionamento 1
#define C2 2 //Pin do trigger de Condicionamento 2
#define teste_EN 8 //Chave para ativação do trigger de Teste
#define F_LENGTH 50 //Tamanho do filtro em número de amostras (+F_LENGTH -> -sensibilidade do filtro)
#define LIMIAR 307 //A sensibilidade do sistema em relação à tensão lida no sensor

int sensor; //Valor lido analógicamente no footswitch


boolean trigger = 0; // O valor da saída do trigger
boolean sensState, old_sensState;



byte t[] = {0, 0, 0, 1, 0};
//long v;


void setup() {
  
}


void loop() {
    /*DETECTOR LENTO (um filtro de médias de tamanho 50)
    A média das 50 últimas amostras com Ts = 200us
    Acrescenta, na pior das hipóteses, 14ms
    0 0 0 1 1 -> Não detecta após 4ms
    1 1 1 1 1 -> Detecta após 10ms
  */
  float VALOR = 0;
  
  for (int i=0; i<=F_LENGTH; i++){
    VALOR += analogRead(sensor);
    delayMicroseconds(200);
  }
  
  VALOR = VALOR/F_LENGTH; //Media das F_LENGTH ultimas amostras


//Detector de pisada
  if (VALOR > LIMIAR){ 
    old_sensState = sensState;
    sensState = 1;
  }
  else { //
   sensState = 0;      
  }

  teste_EN ? ( trigger = triggerState(analogRead(5)) ) : ( trigger = 0 );

/*
 * (sensState - old_sensState) = 0 é patamar
 * (sensState - old_sensState) = -1 é borda de descida
 * (sensState - old_sensState) = 1 é borda de subida
 */
  
  if ( (old_sensState - sensState)==-1){ //Então é borda de subida
      digitalWrite(T, trigger);
      digitalWrite(C1, ( (teste_EN & trigger) ^(byte)(random()%2)) );
      digitalWrite(C2, ( (teste_EN & trigger) ^(byte)(random()%2)) );
      delay(1); //Um pulso para o NIHON
      digitalWrite(T, LOW);
      digitalWrite(C2, LOW);
      digitalWrite(C2, LOW);
      
    }
  
}


/* FUNÇÕES CRIADAS PARA O PROGRAMA */

byte triggerState(int ruido)  {

  for (int i=0; i<=4; i++){
    t[i] = t[i+1];
  } //Rotate left

  int n=4;
  if ( t[n-1] == 1 ){
    t[n] = 0; //Se o anterior foi um, o atual será zero;
    return LOW;
  } else if ( !(t[n-1]||t[n-2]||t[n-3]||t[n-4]) ) { //A primeira condição verifica se o indice é 4 ou mais, e a segunda se houve sequência de 4 zeros.
    t[n] = 1; //Se os 4 últimos forem zero, o atual será um.
    return HIGH;
  } else {
    randomSeed(ruido);
    t[n] = byte (random()%2); //Do contrário (o anterior foi zero e não há 4 repetições, então o atual será aleatório.
    return t[n];
  }
}
