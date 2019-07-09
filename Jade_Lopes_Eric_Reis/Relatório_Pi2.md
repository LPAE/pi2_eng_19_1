Instituto Federal de Santa Catarina

Curso de Engenharia de Eletrônica

Disciplina: Projeto Integrador II

Equipe: Eric Monteiro dos Reis e Jade Dutra Lopes

# Monitoramento dos processos de produção de uma garrafa de suco de uva

## 1. Introdução
Este projeto surgiu com o propósito de unir os conceitos da nova Indústria 4.0 com a disciplina, desenvolvendo assim um protótipo integrado de monitoramento da produção de uma garrafa de suco de uva.

A ideia base era que encima do tablado fornecido pelos professores haveria um estágio de checagem de 4 informações da garrafa de suco:

 - A cor do líquido;
 - O volume de líquido na garrafa;
 - A temperatura do líquido;
 - A leitura do rótulo da garrafa.
 
 Para o então desenvolvimento dessa ideia, foi nos fornecido os seguintes materiais pelos professores da disciplina:
 
 - Sensor Ultrassônico JSN-SR04T;
 - Sensor de cor TCS3200;
 - Sensor de temperatura infravermelho  MLX90614;
 - Sensor de presença FC-51;
 - Tablado de madeira;
 - Garrafa de suco;
 - Canos PVC.

Além dessa lista (onde todos sensores foram obtidos no Laboratório de Pesquisa Avançada em Eletrônica - LPAE), a equipe utilizou também um Arduino Uno, um sensor de temperatura e umidade ambiente DHT 22 e um módulo Raspberry Pi para a leitura do rótulo.

## 2. Desenvolvimento
### 2.1 A Estrutura

Após obter os sensores para o monitoramento, iniciou-se então a discussão da equipe para decidir o design do projeto. Para este, levou-se em conta que este monitoramento faria parte de um processo maior da produção da garrafa de suco, logo,  que desenvolveríamos apenas uma etapa deste processo encima do tablado. Com essa conclusão, a equipe discutiu em como seria feita a estrutura responsável pela captura de dados da garrafa.

Após refletir sobre diversos exemplos diferentes de materiais e montagens, decidiu-se por utilizar canos PVC para a estrutura, devido à facilidade de manuseio e custo acessível para este projeto. A escolha dos canos facilitou também a montagem do protótipo, uma vez que era possível trabalhar em etapas, apenas os desmontando e fazendo todo o cabeamento dos sensores por dentro deles.

![Estrutura](http://oi64.tinypic.com/2vd5ipw.jpg)

### 2.2 Sensoriamento
A estrutura foi montada tendo em mente que precisaríamos ter 3 sensores posicionados encima da garrafa aberta: o sensor de cor (TCS3200), de temperatura infravermelho (MLX90614) e o sensor ultrassônico (JSN-SR04T).

Dividimos o processo em 3 etapas: checagem da cor do líquido, checagem do volume e checagem da temperatura do líquido, respectivamente. Para cada etapa, foi implementado um sensor de presença posicionado muito próximo à garrafa. Só seria realizado o sensoriamento de cada etapa se o sensor de presença detectasse a garrafa na posição correta.

O código feito para este projeto em etapas foi basicamente uma máquina de estados utilizando a lógica *switch case*, em que para ir ao próximo estado, era preciso que o sensor de presença estivesse funcionando corretamente. A leitura dos resultados foi feita pelo monitor serial do Arduino. Foi também implementado um buzzer que indicava ao usuário se a leitura feita na garrafa estava incorreta.

Quando o programa começa a rodar, o sensor DHT 22 nos informa na primeira linha a temperatura e a umidade do ambiente.

#### 2.2.1 Etapa 1 - Checagem de cor
Após vários testes e relatos de colegas, chegamos à conclusão que o sensor de cor TCS3200 não apresentava resultados muito precisos, devido à ruídos provenientes da luz do ambiente e pela distância (mesmo que curta) que ele estava da abertura da garrafa de suco.

Sendo assim, estabelecemos uma margem de erro de 15% para um valor máximo médio que estipulamos com base nos resultados que o sensor apresentava dependendo do local onde estava posicionado. Para o ambiente onde foi feita a defesa do projeto, alteramos o código da seguinte maneira:

    int max_red = 42;    
    int max_green = 74;
    int max_blue = 62;
    float color_margin = 0.15;

Assim, foi feita uma lógica para identificar se a cor que o sensor estava lendo se encaixava na faixa de cor que a equipe estipulou para o funcionamento:

    if((frequency_red < (max_red * (1 + color_margin))) && (frequency_red > (max_red * (1-color_margin))) && (frequency_green < (frequency_green * (1+color_margin))) && (frequency_green > (max_green*(1-color_margin))) && (frequency_blue < (max_blue * (1+color_margin))) && (frequency_blue > (max_blue * (1-color_margin)))){
          Serial.print("\nObjeto identificado corretamente\n");
        }
        else{
          Serial.print("Coloração incorreta\n");
          digitalWrite(BUZZER, LOW);
          delay(500);
          digitalWrite(BUZZER, HIGH); 
          delay(500); 

![Etapa 1 - Cor](http://oi65.tinypic.com/suvjgz.jpg)

#### 2.2.2 Etapa 2 - Checagem de volume
O sensor ultrassônico JSN-SR04T necessita de uma distância miníma do objeto de aproximadamente 25 cm. Por esse motivo foi feito uma parte da estrutura mais comprida.

Nos testes, para garantir que o sensor estava nos dando uma leitura correta, foi feita uma checagem simples: a equipe marcou na garrafa até onde o líquido deveria ir, e assim, com o uso de uma fita métrica, foi medida a distância do líquido até o sensor. Com isso verificou-se que o sensor estava correto.

Para a nossa estrutura, a distância que o sensor deveria mostrar era de 35 cm. Isso indica que o volume da garrafa está correto. Caso contrário, o buzzer iria apitar, informando que o sensor está medindo outro valor, como mostrado a seguir:

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

 ![Etapa 2 - Volume](http://oi65.tinypic.com/qxa2d1.jpg)

#### 2.2.3 Etapa 3 - Checagem da temperatura do líquido

Nesta terceira e última etapa, a garrafa era posicionada embaixo de sensor MLX90614. Quando nesta etapa, nos era mostrado a temperatura do líquido. A equipe estipulou que esta temperatura não deveria passar de 28 ºC. Caso ultrapasse este valor, o usuário era alertado via buzzer e pela mensagem no monitor que o objeto deveria ser checado, como mostra a seguir:

    if(temp_obj > temp_max){  //Compara a temperatura com o valor máximo pré estabelecido e sinaliza caso esteja inadequado o valor
          Serial.print("\nTemperatura do liquido superior ao adequado, verificar o objeto \n");
          digitalWrite(BUZZER, LOW);
          delay(500);
          digitalWrite(BUZZER, HIGH); 
          delay(500); 
        }
![Etapa 3 - Temperatura](http://oi64.tinypic.com/17via9.jpg)
## 3. Conclusão
Ao fim da montagem e testes, obtivemos resultados de acordo com o esperado, considerando o fato que já sabíamos que alguns sensores, como o sensor de cor, não obteria resultados tão precisos.

Uma das maiores dificuldades do projeto foi a integração da estrutura com os sensores. Devido à quantidade de fios que todos os sensores utilizaram, passamos por problemas de mal contato e de rompimento de cabos dentro da estrutura. Isso acabou custando à equipe muito tempo que poderia ter sido utilizado para melhorar outras partes do projeto.

Também devido à falta de tempo, não foi possível implementar a câmera para realizar o processamento de imagem do rótulo da garrafa. A equipe discutiu e decidiu que seria melhor focar em outras partes mais importantes do projeto. Assim, a estrutura não possui a etapa de leitura do rótulo.

Todo o projeto foi construído em torno da ideia que a garrafa estaria se movimentando através de um esteira. O uso de três sensores de presença acabou nos beneficiando, uma vez que percebemos que para uma montagem futura, esses três sensores não deixariam que alguma garrafa passasse despercebida pelas etapas de checagem.

Por fim, este projeto nos proporcionou a chance de trabalharmos livremente dentro do tema proposto. Foi possível assim analisar e discutir diferentes formas de montagem e sensoriamento, e no final conseguímos escolher a melhor no nosso ponto de vista. Foi interessante também a chance de apresentar nosso projeto como um produto futuro, uma vez que trabalhando nessa estrutura, conseguímos pensar em formas de melhorar a mesma em outras oportunidades.
