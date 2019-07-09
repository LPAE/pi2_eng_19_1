/* This code works with JSN SR04 T ultrasound module
 * It measures the distance and shows it on the Serial monitor
 * Refer to www.SurtrTech. com or SurtrTech YT channel for more informations 
 */

//Bibliotecas
#include <DHT.h>;                   //biblioteca do sensor dht22
#include <Adafruit_MLX90614.h>      //biblioteca do sensor temperatura infravermelho
//Defines
 
// Pinos TCS
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12
 
// Pinos distância
#define TRIG 2  
#define ECHO 3  
 
// Pinos presença
#define PS_1 4  //Sensor de presenca 1
#define PS_2 5  //Sensor de presenca 2
#define PS_3 13 //Sensor de presenca 3

// Pinos umidade/temp. ambiente
#define DHTPIN 7
#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Defines
#define BUZZER 6
#define INITIAL_STAGE 1
#define COLOR_STAGE   2
#define VOLUME_STAGE  3
#define TEMP_STAGE    4
#define WAITING_STAGE 99

// Configuracao dos sensores com bibliotecas disponibilizadas na plataforma arduino
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
DHT dht(DHTPIN, DHTTYPE); 

// Inicializacao de variaveis

//variável responsável pela troca entre os sensores, ela é inicializada no estágio inicial
unsigned int position_counter = INITIAL_STAGE;

//variável para a obtenção dos valores de umidade e temp. ambiente
float hum;  
float temp; 

//variáveis para a obtenção das cores
int frequency_red = 0;
int frequency_blue = 0;
int frequency_green = 0;

//variáveis pré definidas baseado na cor do suco de uva, caso seja desejado outro parâmetro é necessário a modificação nas variáveis max_xxx abaixo
int max_red = 42;    
int max_green = 74;
int max_blue = 62;

//variáveis com os valores máximos de temperatura e o valor da margem de erro da cor 
unsigned int temp_max = 28;
float color_margin = 0.15;

//variável da temperatura infravermelho do objeto desejado.
double temp_obj;

void setup() { 
  
//Configuração do terminal serial
  Serial.begin(9600); // Serial monitoring
  Serial.print("Link Start\n\n");
  delay(2000);
  //Configuração dos pinos. 
  pinMode(TRIG, OUTPUT); //configuracao dos pinos TRG e ECHo 
  pinMode(ECHO, INPUT_PULLUP);
  pinMode(PS_1, INPUT);  //configuracao dos sensores de presenca  
  pinMode(PS_2, INPUT);
  pinMode(PS_3, INPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //Inicializacao do sensor de humidade/temp. ambiente e temperatura infra-vermelho
  
  dht.begin();
  mlx.begin();

  //Inicializando o buzzer para que não apite sem entrar nos casos de erro.
  digitalWrite(BUZZER, HIGH);
  //Configuração da frequência do sensor de cor para 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
    
}
   
void loop() { 
  //Definição e inicialização das variáveis  
  unsigned int distance;
  unsigned int flag_dht22 = 1;
  switch(position_counter){
    case INITIAL_STAGE:
        if(flag_dht22 == 1){
            Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
            Serial.print(dht.readHumidity()); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
            Serial.print("%"); //IMPRIME O TEXTO NA SERIAL 
            Serial.print(" / Temperatura ambiente: "); //IMPRIME O TEXTO NA SERIAL
            Serial.print(dht.readTemperature(), 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
            Serial.println("ºC"); //IMPRIME O TEXTO NA SERIAL
            delay(2000); //INTERVALO DE 2 SEGUNDOS * NÃO DIMINUIR ESSE VALOR
        }
        position_counter = WAITING_STAGE;
        break;
    case WAITING_STAGE:
      //faz uma comparação com as 3 posições pra garantir que só seja possivel uma leitura ser feita por vez e dependendo de qual sensor é acionado ativa o sensor adequado
      if((digitalRead(PS_1) == LOW) && (digitalRead(PS_2) == HIGH) && (digitalRead(PS_3) == HIGH)){   //as condições estão sendo feitas em comparação com os 3 sensores de presença pra evitar erros de ruido
        position_counter = COLOR_STAGE;
      }
      if((digitalRead(PS_1) == HIGH) && (digitalRead(PS_2) == HIGH) && (digitalRead(PS_3) == LOW)){   
        position_counter = VOLUME_STAGE;
      }
      if((digitalRead(PS_1) == HIGH) && (digitalRead(PS_2) == LOW) && (digitalRead(PS_3) == HIGH)){   
        position_counter = TEMP_STAGE;
      }
      break;
    case COLOR_STAGE:
    
        // Configurando para pegar a cor vermelha
        digitalWrite(S2,LOW);
        digitalWrite(S3,LOW);
        // Leitura da frequência de saída
        frequency_red = pulseIn(sensorOut, LOW);

        //Mostrando o valor da cor lido pelo sensor
        Serial.print("R= ");
        Serial.print(frequency_red);
        Serial.print("  ");
        delay(100);
       
       
        //Configurando para pegar a cor verde
        digitalWrite(S2,HIGH);
        digitalWrite(S3,HIGH);
        // Leitura da frequência de saída
        frequency_green = pulseIn(sensorOut, LOW);
        
        //Mostrando o valor da cor lido pelo sensor
        Serial.print("G= ");
        Serial.print(frequency_green);
        Serial.print("  ");
        delay(100);
       
       
        //Configurando para pegar a cor azul
        digitalWrite(S2,LOW);
        digitalWrite(S3,HIGH);
        //Leitura da frequência de saída
        frequency_blue = pulseIn(sensorOut, LOW);

        //Mostrando o valor da cor lido pelo sensor
        Serial.print("B= ");
        Serial.print(frequency_blue);
        Serial.println("  ");
        //Condição onde ele checa se a cor do objeto está dentro do valor especificado, para alterar a margem de erro a alteração deve ser feito na variável "color_margin".
        if((frequency_red < (max_red * (1 + color_margin))) && (frequency_red > (max_red * (1-color_margin))) && (frequency_green < (frequency_green * (1+color_margin))) && (frequency_green > (max_green*(1-color_margin))) && (frequency_blue < (max_blue * (1+color_margin))) && (frequency_blue > (max_blue * (1-color_margin)))){
          Serial.print("\nobjeto identificado corretamente\n");
        }
        else{
          Serial.print("Coloração incorreta\n");
          digitalWrite(BUZZER, LOW);
          delay(500);
          digitalWrite(BUZZER, HIGH); 
          delay(500);          
        }
        delay(3500);
        position_counter = WAITING_STAGE;
        break;
    case VOLUME_STAGE:
      // Configuração dos pulsos do trigger necessários para uma leitura e depois a leitura do pino ECHO
      digitalWrite(TRIG, LOW);  
      delayMicroseconds(2); 
    
      digitalWrite(TRIG, HIGH); 
      delayMicroseconds(20); 
    
      digitalWrite(TRIG, LOW); 
      distance = pulseIn(ECHO, HIGH,26000); //Leitura do valor em pulsos
    
      distance= distance/58; //Conversão do valor para cm
                           
      if(distance == 35){
        Serial.print("Volume correto");
      }
     else{   //caso o volume esteja incorreto ele avisa na serial e ativa o buzzer para sinalização
        Serial.print("Volume incorreto");
        digitalWrite(BUZZER, LOW);
        delay(500);
        digitalWrite(BUZZER, HIGH); 
        delay(500); 
      }

      /*
      Serial.print("Distance ");
      Serial.print(distance);
      Serial.println("cm");
      */
      Serial.print("\n\n\n");
      delay(1000);
      delay(50);
      position_counter = WAITING_STAGE;    
      break;
    case TEMP_STAGE:
        //leitura do objeto com a função mlx.readObjectTempC() e depois imprime o valor adequado
        temp_obj = mlx.readObjectTempC();
        Serial.print("Objeto = ");
        Serial.print(temp_obj); Serial.println("ºC");
        delay(2000);
        if(temp_obj > temp_max){  //Compara a temperatura com o valor máximo pré estabelecido e sinaliza caso esteja inadequado o valor
          Serial.print("\nTemperatura do liquido superior ao adequado, verificar o objeto \n");
          digitalWrite(BUZZER, LOW);
          delay(500);
          digitalWrite(BUZZER, HIGH); 
          delay(500); 
        }
        position_counter = WAITING_STAGE;
      break;
    default:
      //parte padrão caso o código encontre algum problema
      Serial.print("HOUVE UM ERRO NO SISTEMA");
      digitalWrite(BUZZER, LOW);
      delay(500);
      digitalWrite(BUZZER, HIGH); 
      delay(500); 
      position_counter = WAITING_STAGE;
      break;
       
  }
  
}

  
