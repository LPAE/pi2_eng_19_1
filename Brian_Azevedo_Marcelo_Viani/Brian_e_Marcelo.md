# Campus Florianópolis

Departamento Acadêmico de Eletrônica

Curso de Engenharia Eletrônica

Projeto Integrador II

Alunos:
Brian Azevedo
Marcelo Viani

### INTRODUÇÃO

A necessidade de produção em grandes escalas, decorrente do aumento populacional e da migração das pessoas do campo para as cidades, levou, há anos atrás, uma mudança na forma em que eram produzidos os produtos, deixando de ser feitos de forma artesanal e passando a ser produzidos em larga escala por indústrias equipadas com máquinas e funcionários que as operavam. Assim foi o começo da primeira revolução industrial, que após anos de evolução, chegou à quarta revolução, chamada também de indústria 4.0.

A indústria 4.0 em muito se difere da primeira revolução, tendo em sua estrutura atual de organização máquinas que utilizam eletricidade e estão “conectadas”, tanto entre si, quanto na rede, onde podem receber e enviar informações do que fazem. Assim as máquinas que antes eram movidas a vapor e precisavam de operários, agora podem até ter autocontrole, fazendo o processo de fabricação completa de um produto sem interferência humana, com uma velocidade superior e já controlando a qualidade do que é feito.

O controle de linhas de montagens também pode ser feito de forma remota, onde uma pessoa pode monitorar e resolver problemas técnicos em outro continente. Como acontece com uma fábrica alemã instalada no Brasil, que visualiza o que é feito e da assistência diretamente da Alemanha, aumentando assim a eficiência e qualidade, sem aumentar custos.

Outra aplicação que está ainda começando a ser feita nas indústrias é a utilização do Machine Learning, que é, com uma programação inicial, a máquina fazer determinados serviços e a cada vez que executa novamente ela aprende e aprimora o que faz. Uma forma de fazer uso do Machine Learning é ao se colocar sensores numa linha industrial, ela ser capaz de ver, em mínimas diferenças, qual a melhor temperatura e velocidade devem ser aplicadas para gerar a melhor eficiência possível. Esses aspectos analisados são apenas alguns do que se é e ainda pode ser aplicado na indústria, com a inserção da tecnologia na indústria, visando ter uma melhor qualidade, agilidade, menos gastos e assim, no fim, gerando um maior lucro.



### CONCEPÇÃO
A concepção é a etapa do projeto em que serão conhecidos os requisitos do projeto e propostas as soluções para atender os requisitos exigidos.
O projeto consiste no controle da produção industrial de uma garrafa de 1,5L de suco. O processo de verificação é dividido em 4 etapas.

#### 1° Etapa - Medição de temperatura
O processo de medição da temperatura ambiente e do líquido é realizado atráves do sensor MLX90614.

#### 2° Etapa - Controle do nível de envase
Um sensor ultrassônico JSN-SR04T vai ser utilizado para verificar a altura do líquido da garrafa.

#### 3° Etapa - Análise de cor da matéria-prima
O sensor TCS230 vai analisar a cor do líquido contido na garrafa.

#### 4° Etapa - Leitura OCR
Utiliza-se uma webcam para a leitura do código de barras da garrafa.

### DESIGN
Nesta fase do projeto é definida a disposição dos sensores e a estrutura de apoio dos sensores e do módulo arduino que irá controlar o sistema completo.
Para definir como seria a estrutura, foi pensado em como seria feita a disposição dos sensores. Como o MLX90614(temperatura) e o TCS230(cor) precisam estar próximos ao que vai ser medido e o JSN-SR04T tem uma distância mínima de 25cm, foi utilizado uma placa que seria o teto, em que ficaria o arduino em cima e os sensores embaixo desse teto, com colunas para os sensores que precisam ficar mais próximos e para os sensores de presença foi feito um "piso" mais elevado visto que ele precisa estar na altura do rótulo.

### IMPLEMENTAÇÃO
Para implementar os sensores no arduino é necessário entender seu funcionamento e adaptar os códigos já disponíveis por isso será dada uma breve explicação dos sensores.

#### TCRT5000 - Sensor de presença
É um sensor composto por um emissor e um fototransistor. Quando algum objeto é colocado em frente sensor, o sinal infravermelho é refletido para o fototransistor. Quando isso acontece a saída vai para nível lógico baixo, sendo possível assim controlar os outros sensores utilizando o sinal recebido pelo TRCT5000.

#### MLX90614 - Sensor de temperatura
Este sensor detecta a temperatura absorvendo as ondas infravermelhas emitidas pelo objeto que está em sua direção. O sensor deve estar localizado próximo do objeto que se deseja a temperatura.

#### JSN-SR04T - Sensor Ultrassônico
Funciona emitindo ondas sonoras ciclicas que ao colidir com um objeto vai retornar e ter um tempo de resposta, utilizando esse tempo é possível calcular a distância. O sensor deve estar a uma distancia minima de 25cm para o correto funcionamento.

#### TCS230 - Sensor de cor
Vai dar uma onda quadrada de frequencia diretamente proporcional a intensidade de luz. O sensor deve estar o mais próximo possível e com a menor variação possível de iluminação, pois ele é extremamente sensível a luz ambiente, por isso foi colocado um pedaço de papelão para envolver o sensor, possibilitando assim medidas mais precisas.

O código para a implementação dos 4 sensores utilizados está abaixo.
```
#include <Arduino.h>
#include <NewPing.h>
#include <Wire.h>

#include "MLX90615.h"
#include <I2cMaster.h>

#define SDA_PIN A4   //define the SDA pin
#define SCL_PIN A5   //define the SCL pin

SoftI2cMaster i2c(SDA_PIN, SCL_PIN);
MLX90615 mlx90615(DEVICE_ADDR, &i2c);

//  Presença:
int pinoSensor1 = 2; //PINO DIGITAL UTILIZADO PELO SENSOR
int pinoSensor2 = 3; //PINO DIGITAL UTILIZADO PELO SENSOR
int pinoSensor3 = 4; //PINO DIGITAL UTILIZADO PELO SENSOR
int a = 0;


//  Cor:
//  Pinos de conexao do modulo TCS230  
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define OUT 12
  
//  Variaveis que armazenam o valor das cores  
int red, green, blue, clean;
int c_red, c_green, c_blue;

//  Distancia
#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int    h, v = 0;
float  r_cil  = 0.0493, r1_con = 0.0142, r2_con = 0.0347;


void setup() {
  Serial.begin(9600);
  Serial.println("PI II");
  Serial.println("Prototipo de Leitura de dados Industrial");
  Serial.println("Alunos:");
  Serial.println("\tBrian Azevedo");
  Serial.println("\tMarcelo Viani");  
  pinMode(pinoSensor1, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSensor2, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSensor3, INPUT); //DEFINE O PINO COMO ENTRADA

  pinMode (S0, OUTPUT);
  pinMode (S1, OUTPUT);
  pinMode (S2, OUTPUT);
  pinMode (S3, OUTPUT);
  pinMode (OUT, INPUT);

  digitalWrite (S0, LOW);
  digitalWrite (S1, HIGH);

}

void loop() {
  
  if (digitalRead(pinoSensor1) == LOW & digitalRead(pinoSensor2) == HIGH  & digitalRead(pinoSensor3) == HIGH) {
    a = 1;
  } else if (digitalRead(pinoSensor2) == LOW & digitalRead(pinoSensor1) == HIGH & digitalRead(pinoSensor3) == HIGH){
    a = 2;
  } else if (digitalRead(pinoSensor3) == LOW & digitalRead(pinoSensor1) == HIGH & digitalRead(pinoSensor2) == HIGH){
    a = 3;
  }

  if (a == 1){
    
    // Temperatura:
    Serial.println("Leitura da Temperatura:");
    Serial.print("Temperatura do Objeto = "); Serial.print(mlx90615.getTemperature(MLX90615_OBJECT_TEMPERATURE));
    Serial.print("*C\nTemperatura do Ambiente = "); Serial.print(mlx90615.getTemperature(MLX90615_AMBIENT_TEMPERATURE)); 
    Serial.println("*C");
  } else if (a == 2){
    
    // Cor:
      Serial.println("Leitura da Cor:\n");
          if (v == 1500) {
    
          read_color (&red, &green, &blue, &clean);
          c_red = (int)255*1.23*(float)clean/red;
          c_green = (int)255*1.18*(float)clean/green;
          c_blue = (int)255*1.4*(float)clean/blue;
    
          //Serial.print ("COLOR: rgb("); 
          //Serial.print (c_red);
          //Serial.print (", ");
          //Serial.print (c_green);
          //Serial.print (", ");
          //Serial.print (c_blue);
          //Serial.println (")");
          //Serial.println("");
    
      //Verifica se é Puro  
        if (108 < c_red && c_red < 125 && 100 < c_green && c_green < 115 && 115 < c_blue && c_blue < 130)   
        {  
         Serial.println("O Suco está com a Cor Correta");  
        }
      /*
        //Verifica se tem um pouco de agua
        else if (145 < c_red && c_red < 165 && 90 < c_green && c_green < 95 && 90 < c_blue && c_blue < 100)   
        {  
         Serial.println("Um pouco de agua");  
        }  
      
        //Verifica se tem pouco suco
        else if (145 < c_red && c_red < 165 && 80 < c_green && c_green < 90 && 100 < c_blue && c_blue < 120)   
        {  
         Serial.println("Bastante agua");  
        }  
        //Verifica se tem so agua
        else if (120 < c_red && c_red < 130 && 95 < c_green && c_green < 105 && 110 < c_blue && c_blue < 130)   
        {  
         Serial.println("Apenas agua");  
        }  */
        else
        {  
            Serial.println("A Cor do Suco está fora do Padrão");  
        }  
        
            Serial.println("");
        }
        else
            Serial.println("A altura deve estar no Padrão para correta leitura da Coloração");  
  } else if(a == 3){
    
// Distancia:
    unsigned int o,uS = sonar.ping(); 
    o = uS;
    h = o / US_ROUNDTRIP_CM - 3;
  
    if (h >= 23  &&   (h <= 51)) {
        Serial.println("Leitura do Volume:");
        //Serial.print("Distancia: ");
        //Serial.print(h);
        //Serial.println("cm"); 

        if ((h <= 51)  &&   (h > 33)) {           // Cilindro
            //Serial.print("Cilindro");
            h = 51 - h;
            v = M_PI * h * pow(10, -2) * pow(r_cil, 2) * 1000000;
        }
        else if ((h <= 24)  &&   (h >= 23)) {     // Cone
            //Serial.print("Cone");
            h = 51 - h;
            v = 1481 + (((M_PI * (h-26) * pow(10, -2))/3) * (pow(r2_con, 2) + r2_con * r1_con + pow(r1_con, 2))) * 1000000;
        }
        else if ((h <= 33)  &&   (h > 24)) {      // Hiperboloide
            //Serial.print("Hiperboloide");
            switch(h){
                case 33:
                    v = 1332;
                    break;
                case 32:
                    v = 1361;
                    break;
                case 31:
                    v = 1385;
                    break;
                case 30:
                    v = 1405;
                    break;
                case 29:
                    v = 1422;
                    break;
                case 28:
                    v = 1436;
                    break;
                case 27:
                    v = 1449;
                    break;
                case 26:
                    v = 1463;
                    break;
                case 25:
                    v = 1480;
                    break;
            }
        }
        //Serial.println();
        //Serial.print("Volume: ");
        //Serial.print(v);
        //Serial.println("ml"); */

        if (v == 1500) {
            Serial.println("Nivel do Suco está Correto");
            Serial.print("Volume: ");
            Serial.print(v);
            Serial.println("ml"); 
        }
        else {
            Serial.print("Nivel fora do Padrão");
        }
        
    }
  }

  a = 0;
  Serial.println();
  Serial.println();
  delay(1500);
}



void read_color(int* red, int* green, int* blue, int* clean){
  /* Red Filter */
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  *red = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);

  /* Green Filter */
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  *green = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
  
  /* Blue Filter */
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  *blue = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);

  /* Clean Filter */
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  *clean = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
}
```
E para a leitura do código de barras foi utilizado o código open source zbar que está disponível no endereço https://github.com/ZBar/ZBar e a webcam do notebook.

### OPERAÇÃO
Na operação do projeto a garrafa vai transitar nas posições em que estão dispostos os sensores para verificar os requisitos:
* Temperatura
* Volume
* Cor
Para o volume foi feito uma operação binaria, se estiver dentro do padrão(1,5L), vai ser impressa uma mensagem falando que está correto o volume de suco e para volumes menores, vai ter a mensagem que está fora dos padrões. 
Para a cor, foram feitas medições para ver a faixa do código RGB que a cor do suco está e vai aprovar se estiver nesta faixa de cor apenas se o volume também estiver correto, para casos em que a cor está fora do esperado ou o volume não é 1,5L a garrafa não vai ser aprovada.

## Referências bibliográficas
Código para MLX90614 https://github.com/adafruit/Adafruit-MLX90614-Library
Código para JSN-SR04T https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
Leitor de código de barras https://github.com/ZBar/ZBar
As fórmulas para o cálculo do volume utilizadas foram providas pela equipe do Otavio e do Thiago https://github.com/LPAE/pi2_eng_19_1/blob/master/Otavio_Freire_Thiago_Lira/Documento_T%C3%A9cnico_Otavio_Thiago.md
