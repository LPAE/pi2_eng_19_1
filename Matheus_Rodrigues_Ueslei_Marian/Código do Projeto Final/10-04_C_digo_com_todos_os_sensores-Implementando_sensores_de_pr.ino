#include <Arduino.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>


#define TRIGGER_PIN  7  // Pino definido para utilização do sensor de distancia
#define ECHO_PIN     6  // Pino definido para utilização do sensor de distancia
#define MAX_DISTANCE 450 // Distancia maxima para leitura do sensor de distância(Utilizado pela biblioteca)
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Configurações dos pinos 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//declaração das funções 
void color();
void envia_dados();
String leStringSerial();
float ler_temperatura();
void chegada_sensor();
void saida_sensor();
float calculo_volume(float);


//Pinos de conexao do modulo TCS230  
const int s0 = 8;  
const int s1 = 9;  
const int s2 = 12;  
const int s3 = 11;  
const int out = 10;

//Variaveis do sensor de presença
const int parada1 = 2;   
const int parada2 = 3;   
const int parada3 = 4; 

//Pino do buzzer para sinalização 
const int buzzer = 5;   

//Variáveis para armazenar as etapas de cada tipo de verificação
int p1 = 0;   
int p2 = 0;   
int p3 = 0;   
  
    
//Variaveis que armazenam o valor das cores  
int red = 0;  
int green = 0;  
int blue = 0;
int clear_filter = 0;
int r;
int g;
int b;

String cod_produto = ""; //Codigo de barras da garrafa
float temperatura = 0;
float volume = 0;
float volume1 = 0;

  
    
void setup()   
{  
  mlx.begin();

  //Nivel lógico baixo = objeto detectado
  pinMode(parada1, INPUT);  //Pino ligado ao coletor do fototransistor    
  pinMode(parada2, INPUT);  //Pino ligado ao coletor do fototransistor    
  pinMode(parada3, INPUT);  //Pino ligado ao coletor do fototransistor    

  pinMode(buzzer, OUTPUT);  //Pino ligado ao buzzer 


  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);  
  Serial.begin(9600);  //Definição para comunicação por bluetooth
  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);
  digitalWrite(buzzer, LOW);  

} 
    
void loop() 
{ 
/*
  Como o objetivo do projeto era poder armazenar todas as informações de alguma forma na garrafa, fizemos um código que só habilita o reconhecimento dos sensores
a partir do momento que é feito o registro do código de barras da garrafa atravez do aplicativo.
O código fica em loop até receber uma linha de texto formatada por um padrão. Após isso, ele registra o código de barras e habilita o registro de cada sensor para esta garrafa. 
*/
  if (Serial.available() > 0){
    // Lê toda string recebida
    String cod_produto = leStringSerial();
    if(cod_produto!=""){
      while(cod_produto!=""){
        if(digitalRead(parada1) == LOW &&p1==0){
          chegada_sensor();
          color();// Chama rotina para ler valores das cores
          saida_sensor();
          p1=1; //Set variavel como 1 para informar que ja foi feito a medida necessária
        }
        if(digitalRead(parada2)==LOW &&p2==0){
          chegada_sensor();
          ler_volume(); //Chama rotina para ler distancia do líquido
          saida_sensor();
          p2=1;//Set variavel como 1 para informar que ja foi feito a medida necessária
        }
        if(digitalRead(parada3)==LOW &&p3==0){
          chegada_sensor();
          ler_temperatura();  //Chama rotina para ler temperatura do liquido
          saida_sensor();
          p3=1; //Set variavel como 1 para informar que ja foi feito a medida necessária
        }
        if(p1==1&&p2==1&&p3==1){
          Serial.print(cod_produto);
          envia_dados();
          cod_produto="";
          temperatura=0;
          red = 0;
          green = 0;
          blue = 0;
          p1=0;
          p2=0;
          p3=0; 
        }
      }
    }
  }
}

void color(){  
  //Rotina que le o valor das cores  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  red = map (red, 15 , 250 , 255 , 0 ) ;
  red = constrain(red, 0, 254);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  blue = constrain(blue, 0, 254);  
  blue = map (blue, 15 , 250 , 255 , 0 ) ;
  blue = constrain(blue, 0, 254);  
//
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  green = constrain(green, 0, 254);
  green = map (green, 15 , 250 , 255 , 0 ) ;
  green = constrain(green, 0, 254);
 
  digitalWrite(s3, LOW);  
  //count OUT, pClear, CLEAR  
  clear_filter = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);   
}
/**
 * Função que lê uma string formatada da serial:
 * Por padrão, utilizamos essa função que habilita a leitura da 
 * string somente após receber um caracter inicial.
 * 
 * Definimos esse caracter como "*". Precisamos utilizar essa função pois o modulo bluetooth faz o envio
 * de alguns dados para confirmar que ele conseguiu fazer a conexão.
 *  */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  while(Serial.available() > 0){ //verifica caracter por caracter até encontrar o "*"
    if(Serial.peek()== '*'){ //Quando encontra o "*", faz a leitura dos caracteres restantes
      while(Serial.available() > 0){ 
        caractere = Serial.read();  
        // Ignora caractere de quebra de linha
        if ((caractere != '\n')&& (caractere != '*' )){
          // Concatena valores
          conteudo.concat(caractere);
        }
        // Aguarda buffer serial ler próximo caractere
        delay(10);
      }
    }
    caractere = Serial.read();
  }
return conteudo;
}


/**
 * Função que envia pela serial todos os dados armazenados pelos sensores;
 * Aqui utilizamos um formato especifico para podermos separar as informações no aplicativo.
 */
void envia_dados(){
    Serial.print(cod_produto);
    Serial.print(","); // Por definição, usamos a virgula como separador de variaveis
    Serial.print(red,DEC);
    Serial.print(","); 
    Serial.print(green,DEC);
    Serial.print(",");
    Serial.print(blue,DEC);
    Serial.print(",");
    Serial.print(temperatura,2);
    Serial.print(",");
    Serial.print(volume1,2);
    Serial.print(",");
  return ;
}

//Função para leitura de temperatura
float ler_temperatura(){
   int i=0;
      while(i<10){ //Para evitar maiores erros de leitura, fizemos a media de 10 leituras de cada sensor
        temperatura = temperatura + (mlx.readObjectTempC());
        i++;  
      }
    temperatura = temperatura/10;
}

//Função para leitura da distancia do líquido utilizando o sensor ultrassônico
float ler_volume(){
  int i=0;
  volume=0;
    while(i<10){
      unsigned int o = sonar.ping(); 
      if(o!= 0){
        volume = volume +( o / 56.1);
        i++;  
      }  
    }
  volume = volume/10;
  volume1= calculo_volume(volume);
  return ;
}

/* função para sinalização de reconhecimento do sensor de presença.
    Nessa função fizemos o buzzer apitar uma vez para sabermos que o sensor de presença está ativo.
*/
void chegada_sensor(){
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);  
  delay(2000);
  return ;
}
/* Função que sinaliza o fim da etapada da leitura do sensor.
    Nessa função fizemos o buzzer apitar duas vezes para sabermos que terminou a etapa de leitura do sensor;
*/
void saida_sensor(){
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);                
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW); 
  return ;
}
/* Função que calcula o volume de líquido da garrafa de suco do Projeto integrador 2 da Engenharia Eletrônica 2019/01
*/
float calculo_volume(float distancia) {

  int altura_total = 54; //Fixo devido nossa estrutura ser fixa
  float altura_liq = altura_total - distancia;
  float parte_cil = 15.0; //fixo cilindro
  float raio_cil = 5.05; //fixo
  float cheio = 24.0; //Altura màxima do líquido quando a garrafa está cheia
  float vol;
  float vol2=0;
  float diam;
  float d2 = 10.20; //d2, fixo

  if (altura_liq <= parte_cil) {
    return vol = altura_liq * 3.1415 * (raio_cil * raio_cil);
  } else if ((altura_liq > parte_cil) && (altura_liq <= cheio)) {
    if (altura_liq >= 15.0 && altura_liq <= 17.0) {
      diam = 5.5;
    } else if (altura_liq > 17.0 && altura_liq <= 19.0) {
      diam = 4.5;
    } else if (altura_liq > 19.0 && altura_liq <= 20.0) {
      diam = 3.5;
    } else if (altura_liq > 20.0 && altura_liq <= 22.0) {
      diam = 2.5;
    } else if (altura_liq > 22.0 && altura_liq < 28.0) {
      diam = 2.25;
    }
    vol = (parte_cil * 3.1415 * (raio_cil * raio_cil)); //Cálculo do volume da parte cilindrica da garrafa 
    vol2= ((3.1415 * (altura_liq - 15) * (2 * (diam * diam) + (raio_cil * raio_cil)))/3); //Cálculo do volume do restante da garrafa 
    return (vol+vol2);
  }
}
