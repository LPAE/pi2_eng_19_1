CURSO DE ENGENHARIA ELETRÔNICA

PROJETO INTEGRADOR II

NOMES: Matheus Rodrigues e Ueslei Marian

MACRO 1 - Contextualização da indústria 4.0

O surgimento da indústria 4.0 está alterando o protagonismo da indústria, com novas tecnologias e novos métodos de fabricação em grande escala. Os avanços tecnológicos proporcionados pela quarta revolução industrial demonstram grandes avanços na área da robótica e da inteligência artificial.

As primeiras revoluções industriais expandiram a produção em massa de produtos, nas linhas de montagem, na eletricidade e na tecnologia de semicondutores revolucionaram e expandiram a renda dos trabalhadores fazendo à tecnologia ser o cerne do desenvolvimento econômico mundial. A quarta revolução industrial, que terá um impacto mais profundo, irá mudar o mundo no contexto físico e digital.

A próxima revolução industrial irá alterar o modo de produção atual, e aumentará a demanda pela capacidade de operação, existindo uma união entre o homem e a máquina, sendo a máquina o ponto de evolução. Esse futuro proposto pela quarta revolução industrial sediará uma nova era no mundo moderno produzindo novos postos de trabalho que deverão ser atribuídos a funcionários com funções amplas e generalistas.

Todo país desenvolvido tecnologicamente tende a sair na frente na corrida tecnológica, e isso vai ser explorado por países que já possuem um escopo grande no mercado mundial.

MACRO 2 - CONCEPÇÃO DO PROJETO:

O projeto que será desenvolvido pela nossa equipe tem como objetivo ampliar o leque de conhecimentos tecnológicos, com a utilização de diversos tipos de sensores será possível mostrar como essas ferramentas podem ser usadas em diversas aplicações do cotidiano, realizaremos testes de diversas formas a fim de obter o melhor resultado possível. Esses testes realizados em cada sensor mostrarão como cada sensor se comporta com as influências do ambiente.

Foi passado a equipe informações referentes a tecnologias que poderiam servir como um ponto de partida para o desenvolvimento do projeto. Tudo que foi informado pelo corpo docente da disciplina irá servir como motivação para a equipe no transcorrer do desenvolvimento do projeto como um todo.

Com a união entre outras equipes de desenvolvimento do projeto, e esforços entre outros departamentos será possível realizar o projeto com êxito. A ajuda proposta do departamento de design é mais um ponto positivo que servirá para evoluirmos o produto em sua estrutura física externa.

Por fim, o projeto tem como objetivo mostrar aplicações do cotidiano de uma indústria, e com essas informações será possível aperfeiçoar ferramentas para futuros projetos de outras equipes.

 

​       2.Concepção (C)

2.1 Requisitos do Projeto

 

|    Requisitos do Projeto    |         Tecnologias         | Quantidades |
| :-------------------------: | :-------------------------: | :---------: |
|  Verificação de Rotulagem   |           Celular           |      1      |
| Verificação de Temperatura  |       Sensor MLX90614       |      1      |
|     Sensor Ultrassônico     |       Sensor JSN0R04        |      1      |
|     Verificação da Cor      |    Sensor de Cor TCS230     |      1      |
| Apresentação dos Resultados |   Aplicativo Desenvolvido   |      1      |
|   Verificação da Presença   | Sensor de Presença TCRT5000 |      4      |

​                                              

​                                              

3.3 Especificar e Orçar



Arduino Uno: Uma plataforma de prototipagem que é destinada para o uso em projeto de de pequeno porte.

Display LCD + I2c:  Permite o interface do display com o arduino. 

Obs: (O Display LCD + I2c não foi utilizado no projeto final devido a utilização do aplicativo como interface).

MLX90614: Sensor que permite medir temperatura. Utilizamos no projeto para a medição da temperatura do líquido 

HC-05: Módulo Bluetooth que utilizamos para a comunicação entre o aplicativo e o arduino. Toda a troca de informação dos sensores como o envio de código de barra da garrafa foi feita por meio do Bluetooth.

JSN - SR04T: Sensor de distância que utilizamos para medirmos o volume da garrafa.

TCRT5000: Sensor que verifica a proximidade de um determinado objeto a curto alcance (menos que 2cm).

Tablado de Madeira: Cedido pelo LPAE e utilizado para simular uma esteira de fábrica por onde passaria a garrafa de suco.

Garrafa de Vidro: Objeto a ser estudado e apresentados os dados obtidos através dos sensores.

 

| Nome da Tecnologia |         Projeto         | Quantidades |  Custo  | Cedido Por: |
| :----------------: | :---------------------: | :---------: | :-----: | :---------: |
|    Arduino Uno     | Processador do Circuito |      1      | R$35,00 |             |
| Display LCD + I2c  |         Display         |      1      | Cedido  |    LPAE     |
|      MLX90614      |  Sensor de Temperatura  |      1      | Cedido  |    LPAE     |
|       HC-05        |    Módulo  Bluetooth    |      1      | R$25,00 |             |
|    JSN – SR04T     |   Sensor de Distância   |      1      | Cedido  |    LPAE     |
|      TCRT5000      |  Sensor de   Presença   |      3      | Cedido  |    LPAE     |
| Tablado de Madeira | Sustentação do Projeto  |      1      | Cedido  |    LPAE     |
|  Garrafa de Vidro  |  Objeto para   Análise  |      1      | Cedido  |    LPAE     |

 

 

 

3.4 Documentar Resultados

O arduino uno é uma placa para o desenvolvimento de sistemas automatizados, sendo assim, ele possui diversas funcionalidades para a produção de um projeto. Com a utilização do arduino uno  foi possível unir todos os sensores que foram trabalhados no projeto.

Foram utilizados 6 sensores para o desenvolvimento do projeto, sendo esses sensores calibrados e testados para atender os requisitos do projeto realizado na disciplina de projeto integrador 2 do curso de Engenharia Eletrônica do IFSC (INSTITUTO FEDERAL DE SANTA CATARINA). 

Nesse relatório iremos expor de forma clara e objetiva as funcionalidades de cada sensor e como cada sensor foi aplicado para a melhor desempenho possível. 

O sensor de presença TCRT5000 como o próprio nome diz, verifica se há ou não presença de um objeto em seu entorno, e assim é possível relacionar essas informações na outra parte do código  e produzir informações constantes.  

O sensor de cor escolhido pela equipe o foi o TCS230, esse sensor verifica a intensidade das cores RGB (Vermelho,  verde e azul). Nossa ideia era apresentar esses três níveis de cores na tela do aplicativo para termos uma gama maiores de cores, não limitando apenas a verificação se a cor do líquido está correta ou não.  Após alguns testes, observamos que o sensor era bem limitado, pois tínhamos muita interferência da luminosidade externa e também da distância entre o sensor e o líquido.

Com o avanço do projeto foi verificado algumas objeções em relação a distância do objeto. Nosso sensor era limitado a uma distância mínima de 23cm, então precisamos mudar nossa estrutura para que o sensor ficasse com uma altura de 56cm do tablado.



Como já comentamos anteriormente, foi desenvolvido um aplicativo no site [http://ai2.appinventor.mit.edu](http://ai2.appinventor.mit.edu/) para servir como interface para o usuário. Nesse aplicativo utilizamos algumas funções disponíveis para integrar no nosso projeto. As principais funções utilizadas no aplicativo foram: Bluetooth, leitor de código de barras, temporizador, notificação, botões e rótulos.

A primeira função foi o Bluetooth. Todo o aplicativo foi baseado para a comunicação com o arduino por bluetooth. No primeiro momento, seguimos um tutorial para criação do app (http://mundoprojetado.com.br/modulo-bluetooth-criando-aplicativo-parte-2/) onde pudemos utilizar boa parte da programação lógica e principalmente as ideias do controle de erro para a conexão bluetooth.

Outra função disponível no app inventor é o leitor de código de barras e QRCode. Com ele faremos o envio e registro do código de barras para o arduino.

Próximo passo foi criar a tela do aplicativo para mostrar todas as informações necessária. Após criado a tela, precisamos programar o restante da lógica para a comunicação do app com o arduino. 

Como nosso intuito era poder registrar a garrafa primeiramente para só depois disso o arduino fazer a leitura de cada sensor, criamos uma lógica em que ao fazer a leitura do código de barras pelo APP, mandamos esse mesmo código como uma *string* pelo bluetooth caso o arduino estivesse conectado. Criamos um botão "REGISTRAR GARRAFA" que quando é pressionado, o APP abre o leitor de código de barras e faz o envio pelo bluetooth. Nos primeiros testes tivemos muitos problemas pois quando o módulo bluetooth faz a conexão com o celular, ele envia alguns dados na porta serial informando que está conectado, estão precisamos fazer uma lógica pra ignorar essa informação. A nossa solução foi fazer o envio do código de barras sempre com um caractere de início de *string*. Utilizamos o "*" para isso.  

No código do arduino, temos uma função que faz o tratamento desses dados e só recebe a informação quando o código de barras tem no início o "*".



Para o recebimento das informações, também foi necessário criar uma lógica para tratar os dados. Após a leitura dos sensores, o arduino faz o envio de 6 dados, onde cada um é separado por vírgula para que pudéssemos separar no aplicativo e utilizar da maneira correta. Para mostrar as informações na tela, criamos um botão "INFORMAÇÕES" que quando pressionado, faz a separação de todos os dados recebidos e mostra na tela. A possibilidade de mostrar as cores do líquido na tela do celular foi muito importante para o projeto, pois apesar do líquido sempre ter a cor roxa, nosso projeto possibilita a leitura de outras cores.

Para fazer todas as conexões de maneira mais eficiente e mais organizada, fizemos um shild para conectar diretamente no arduino.







Conclusão.

Foi de extrema importância a implementação desse projeto para integrar as disciplinas até a quarta fase do curso superior de Engenharia Eletrônica. Apesar das limitações de alguns sensores, conseguimos obter os resultados desejados.







Referências:

 http://mundoprojetado.com.br/modulo-bluetooth-criando-aplicativo-parte-2/

<https://randomnerdtutorials.com/arduino-color-sensor-tcs230-tcs3200/>

<https://www.filipeflop.com/>