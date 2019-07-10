//Include the module so we don't
//have to use the default Serial
//so the Arduino can be plugged in
//to a computer and still use bluetooth
#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

// Pinos BLUETOOTH
#define RX_PIN        3 // Resistor ligado ao segundo pino do HC
#define TX_PIN        2 // Terceiro pino do HC

//Pinos DISTANCIA
#define TRIGGER_PIN   4
#define ECHO_PIN      5 
#define MAX_DISTANCE  500

// Pinos COR
#define S0            8
#define S1            9
#define S2            12
#define S3            11
#define S_OUT         10

// Pinos TEMPERATURA
// Pinos analógicos 1 e 2
// SCL: A5 (primeiro de baixo)
// SDA: A4 (segundo de baixo)

// Pinos PRESENÇA
#define PRESEN_1     6
#define PRESEN_2     7

// Pinos gastos:
// 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12

// Pinos livres:
// 1, 13

/*
 * Pinagem de todos os componentes:
 * 
 * BLUETOOTH: 2, 3
 * DISTANCIA: 
 * COR:       8, 9, 10, 11, 12
 * TEMPERAT.: 1, 2 (analog.) (I2C)
 * 
 * 
 */
struct cor_t {
  int vermelho;
  int verde;
  int azul;
};

 // Setups Iniciais:
// Setup BLUETOOTH
SoftwareSerial bluetooth(TX_PIN, RX_PIN);
// Setup DISTANCIA
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
// Setup TEMPERATURA
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Variáveis globais utilizadas no programa
char l = 'A';
int i, j;
bool wait, failed;
String stringnum[6];

cor_t  cor;
long   dist_microsec;
double temp_amb;
double temp_obj;
unsigned long started_waiting_at;

void setup()
{
  dist_microsec = 1500;
  cor.vermelho = 20;
  cor.verde = 30;
  cor.azul = 40;
  temp_amb = 10.01;
  temp_obj = 15.55;
  // Setup COR:
  pinMode(S0, OUTPUT);  
  pinMode(S1, OUTPUT);  
  pinMode(S2, OUTPUT);  
  pinMode(S3, OUTPUT);  
  pinMode(S_OUT, INPUT);  
  digitalWrite(S0, HIGH);  
  digitalWrite(S1, LOW);

  // Setup PRESENÇA
  pinMode(PRESEN_1, INPUT);
  pinMode(PRESEN_2, INPUT);

  // Setup TEMPERATURA
  mlx.begin();  
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Serial ready"); 
  bluetooth.begin(9600);
  Serial.println("Bluetooth ready");
}

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Enviando S - aguardando resposta para inicio do processo...");
  wait = true;
  while(wait){
    bluetooth.print('S');
    //bluetooth.flush();
    l = 'A';
    while(bluetooth.available()){
      l = bluetooth.read(); 
    }
    if(l == 'S'){
      // Se a letra recebida for S, sai do while
      // e parte pra próxima etapa
      Serial.println("Recebido S - aguardando garrafa..."); 
      wait = false;
    }else{
      //Serial.print("Recebido outro caractere: "); 
      //Serial.println(l); 
    }
    delay(5);
  }
  digitalWrite(LED_BUILTIN, HIGH);

  wait = true;
  while(wait){
    // Leitura de chegada da garrafa
    i = digitalRead(PRESEN_1);
    if(i == 0){
      delay(2000);
      // Leitura de confirmação
      i = digitalRead(PRESEN_1);
      if(i == 0){
        wait = false;
      }
    }
  }
  
  delay(200);
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Garrafa detectada no primeiro estagio!"); 
  // A garrafa está na posição para realizar as medições
  
  dist_microsec = get_dist(); 
  get_cor(&cor);
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();

  Serial.println("Medicoes feitas, aguardando chegada da garrafa no segundo estágio..."); 
  wait = true;
  while(wait){
    // Leitura de chegada da garrafa
    i = digitalRead(PRESEN_2);
    if(i == 0){
      delay(2000);
      // Leitura de confirmação
      i = digitalRead(PRESEN_2);
      if(i == 0){
        wait = false;
      }
    }
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Garrafa detectada no segundo estagio!"); 

  // Empacotamento dos dados no conjunto de Strings
  if(dist_microsec > 9999)
    stringnum[0] = "0000";
  else
    stringnum[0] = String(dist_microsec);
  
  stringnum[1] = String(cor.vermelho, DEC);
  if(stringnum[1].length() < 3)
    stringnum[1] = "0" + stringnum[1];
  if(stringnum[1].length() < 3)
    stringnum[1] = "0" + stringnum[1];
  
  stringnum[2] = String(cor.verde, DEC);
  if(stringnum[2].length() < 3)
    stringnum[2] = "0" + stringnum[2];
  if(stringnum[2].length() < 3)
    stringnum[2] = "0" + stringnum[2];
  
  stringnum[3] = String(cor.azul, DEC);
  if(stringnum[3].length() < 3)
    stringnum[3] = "0" + stringnum[3];
  if(stringnum[3].length() < 3)
    stringnum[3] = "0" + stringnum[3];

  // Vai ter problema se a temperatura for maior que 99 *C
  // ou abaixo de 1 *C
  stringnum[4] = String(temp_amb,2);
  if(temp_amb < 10)
    stringnum[4] = "0" + stringnum[4];
  
  stringnum[5] = String(temp_obj,2);
  if(temp_obj < 10)
    stringnum[5] = "0" + stringnum[5];
  
  Serial.println("Enviando pacotes para o notebook..."); 
  // Enviar protocolo pro notebook!
  do{
    bluetooth.flush();
    bluetooth.print('F');
    bluetooth.print(stringnum[0]);  // 4 bytes - Distancia
    bluetooth.print(stringnum[1]);  // 3 bytes - Vermelho
    bluetooth.print(stringnum[2]);  // 3 bytes - Verde
    bluetooth.print(stringnum[3]);  // 3 bytes - Azul
    bluetooth.print(stringnum[4]);  // 5 bytes - Temp. Amb.
    bluetooth.print(stringnum[5]);  // 5 bytes - Temp. Obj.
    bluetooth.print('C');
    bluetooth.flush();
    while(bluetooth.available()){
      l = bluetooth.read(); 
    }
  }while(l != 'S');
  
  wait = true;
  Serial.println("Dados de medicoes enviados para o notebook."); 
  while(wait){
    l = 'A';
    while(bluetooth.available()){
      l = bluetooth.read(); 
    }
    if(l == 'S'){
      // Se a letra recebida for S, sai do while
      // e parte pra próxima etapa
      Serial.println("Recebido S - reiniciando processo."); 
      wait = false;
    }else{
      //Serial.print("Recebido outro caractere: "); 
      //Serial.println(l); 
    }
  }
}

/*
 * Funções de aplicação dos sensores
 * long get_dist(void)  : retorna valor em ms do sensor ultrassom
 * void get_cor(struct_cor_t * cor) : armazena os coeficientes de cor na struct passada
 */
long get_dist(void)
{
  int i = 0;
  long microsec = 0;
  long microsec_vect[10];
  while(i < 10)
  {
    microsec = sonar.ping();
    if(microsec != 0)
    {
      microsec_vect[i] = microsec;
      i++;
    }
    delay(2);   
  }
  microsec = microsec_vect[0] + microsec_vect[1] + microsec_vect[2] + microsec_vect[3] + microsec_vect[4] + microsec_vect[5] + microsec_vect[6] + microsec_vect[7] + microsec_vect[8] + microsec_vect[9];
  microsec /= 10;
  return microsec;
}

void get_cor(cor_t * cor)
{
  //Rotina que lê o valor das cores  
  digitalWrite(S2, LOW);  
  digitalWrite(S3, LOW);  
  //count OUT, pRed, RED  
  cor->vermelho = pulseIn(S_OUT, digitalRead(S_OUT) == HIGH ? LOW : HIGH);  
  digitalWrite(S3, HIGH);  
  //count OUT, pBLUE, BLUE  
  cor->azul = pulseIn(S_OUT, digitalRead(S_OUT) == HIGH ? LOW : HIGH);  
  digitalWrite(S2, HIGH);  
  //count OUT, pGreen, GREEN  
  cor->verde = pulseIn(S_OUT, digitalRead(S_OUT) == HIGH ? LOW : HIGH);

  if(cor->vermelho > 255)
    cor->vermelho = 0;
  else
    cor->vermelho = 255 - cor->vermelho;
    
  if(cor->verde > 255)
    cor->verde = 0;
  else
    cor->verde = 255 - cor->verde;

  if(cor->azul > 255)
    cor->azul = 0;
  else
    cor->azul = 255 - cor->azul;
  
}
