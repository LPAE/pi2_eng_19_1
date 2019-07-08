#include <Arduino.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define v_max 1.6   //Limite máximo do volume da garrafa
#define v_min 1.4   //Limite mínimo do volume da garrafa


#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

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

//Pino buzzer  
const int buzzer = 5;   

int p1 = 0;   
int p2 = 0;   
int p3 = 0;   
int p4 = 0;
   
    
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

  //Nivel lógico alto = objeto detectado
  pinMode(parada1, INPUT);  //Pino ligado ao coletor do fototransistor    
  pinMode(parada2, INPUT);  //Pino ligado ao coletor do fototransistor    
  pinMode(parada3, INPUT);  //Pino ligado ao coletor do fototransistor    

  pinMode(buzzer, OUTPUT);  //Pino ligado ao coletor do fototransistor    A

  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);
 
  pinMode(out, INPUT);  
  Serial.begin(9600);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);

  digitalWrite(buzzer, LOW);  

}  
    
void loop() 
{ 

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
                  //write_disp(temperatura)
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
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  while(Serial.available() > 0){ 
  //Serial.print("Serial available: ");
  //Serial.println(Serial.available());
    // Lê byte da serial
    if(Serial.peek()== '*'){
      //Serial.println(Serial.peek());
      //Serial.print("Serial available depois de *: ");
      //Serial.println(Serial.available());

      while(Serial.available() > 0){ 
        caractere = Serial.read();
        //Serial.println(caractere);
     
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
 * Função que lê uma string da Serial
 * e retorna-a
 */
void envia_dados(){
  
  //  Serial.print("#");
    Serial.print(",");
    Serial.print(red,DEC);
    Serial.print(","); // Por definição, foi usado a virgula como separador de variaveis
    Serial.print(green,DEC);
    Serial.print(",");
    Serial.print(blue,DEC);
    Serial.print(",");
    Serial.print(temperatura,2);
    Serial.print(",");
    Serial.print(volume1,2);
    Serial.print(",");
  //  Serial.print("#");
   // Serial.print(",");
    // Implementar codido de segurança para confirmar o envio correto dos dados
  return ;
}
float ler_temperatura(){
   int i=0;
      while(i<10){
        temperatura = temperatura + (mlx.readObjectTempC());
        i++;  
      }
    temperatura = temperatura/10;
}
float ler_volume(){
  int i=0;
  volume=0;
    while(i<10){
      unsigned int o = sonar.ping(); 
      if(o!= 0){
        volume = volume +( o / 56.1);
        i++;  
        //Serial.print("I=");
        //Serial.print(i); // Convert ping time to distance in cm and print result (0 = outside set distance range)
      }  
    }
    volume = volume/10;
    Serial.println(volume,2);
    volume1= calculo_volume(volume);
    Serial.println(volume1,2);

    return ;

}
void chegada_sensor(){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);  
    delay(2000);
    return ;
}
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

float calculo_volume(float distancia) {

  int altura_total = 54;//fixo
  float altura_liq = altura_total - distancia;
  Serial.println(altura_liq);
  float parte_cil = 15.0; //fixo cilindro
  float raio_cil = 5.05; //fixo
  float cheio = 24.0; //fixo altura quando está cheio
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
    vol = (parte_cil * 3.1415 * (raio_cil * raio_cil));
    vol2= ((3.1415 * (altura_liq - 15) * (2 * (diam * diam) + (raio_cil * raio_cil)))/3);
    Serial.println(vol2);
    return (vol+vol2);
    //return volume = (parte_cil * 3.1415 * (raio_cil * raio_cil)) + (((1 / (3 * 3.1415)) * (altura_liq-15) * (2 * ((diametro1 * diametro1) + (d2 * d2)))) / 2);
  }
}
