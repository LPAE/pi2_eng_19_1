# Projeto Integrador II - 2019/01

Instituto Federal de Santa Catarina - Disciplina do projeto integrador 2 do curso de Engenharia Eletrônica.

Alunos:

Kevin Jahn - engkevinn@gmail.com

Clóvis Kuhn - 97clovis97@gmail.com



_________________________________________________________________________



# Briefing

Briefing é um conjunto de informações, uma coleta de dados para o desenvolvimento de um projeto. É um documento contendo a descrição da situação de forma resumida, afim de levantar o objeto de estudo e os objetivos a serem alcançados.

Através dos conceitos estudados de indústria 4.0, foi proposto o desenvolvimento de um sistema de controle e qualidade de produção de uma garrafa de suco de uva ao passar por uma esteira industrial. Alguns requisitos foram impostos pelo "cliente" e a partir destes, os projetistas deverão desenvolver uma solução para tal questão.

Os requisitos do cliente foram:

* Verificação de rotulagem;

* Controle de nível de envase;

* Leitura OCR de lote e validade;

* Análise de cores de matéria prima;

* Inspeção e testes;

  

Para fins de organização dos projetistas, o projeto proposto foi dividido em 4 etapas(CDIO), sendo estas: 

* **Concepção**: Definição de requisitos do projeto, compreensão do contexto, busca do conhecimento sobre as tecnologias a serem empregadas, etc;
* **Design**: Especificar componentes, assim como a quantidade de cada. Elaborar um esquemático para cada circuito empregado e orçar o preço do projeto. 
* **Implementação**: Construir os circuitos eletrônicos, desenvolver os algoritmos necessários, desenvolver métodos de testes e simulações, integrar os circuitos e algoritmos;
* **Operacionalizar**: Fazer testes e ajustes, executar o projeto.

Estas etapas serão descritas de forma detalhada ao longo deste artigo. 

# Introdução

Após as duas primeiras revoluções industriais, iniciando pela máquina a vapor, e em seguida, um alto desenvolvimento industrial pós-guerra, introduzindo a metalúrgica, a siderúrgica e a química como ascendentes da indústria, tivemos a terceira revolução. Esta possui um foco tecnológico e mão de obra especializada. A inserção dos computadores, a biotecnologia, a microeletrônica e a informática vieram a ser os pilares desta revolução e da indústria. 

Agora, nos deparamos com a quarta mudança, numa tendência à automatização total das fábricas. Iniciou-se na Alemanha em 2013, com o projeto de tornar a produção de suas empresas totalmente independente da mão de obra humana.

Através da integração de dispositivos de internet das coisas (IoT) e à computação na nuvem, nos deparamos com um sistema de indústria, onde as máquinas se comunicam entre si e são capazes de tomar decisões e cooperar, entre máquinas e humanos. Através de banco de dados e compartilhamento de informações, as fabricas se tornam autossuficientes em boa parte dos processos de produção. 

Gerencia de qualidade de produto, estoque, reparos e aviso de erros são vantagens da indústria 4.0. A integração de nanotecnologia, neurotecnologias, robôs, inteligência artificial, biotecnologia, sistemas de armazenamento de energia, drones e impressoras 3D, tornam a realidade da indústria 4.0 possível. 

Desta maneira, este projeto, apresentado neste artigo, tem em vista projetar uma solução simulada a um processo industrial, se baseando na indústria 4.0. Isto será feito, integrando sensores inteligentes, IoT e banco de dados.  

# Concepção

Nesta etapa do projeto, como foi dito no briefing, os desenvolvedores deverão se apropriar do contexto, definir os requisitos e meios para alcançar seus objetivos.

Com fins didáticos, um tablado de madeira, que poderá ser modificado pelos projetistas livremente, servirá como esteira industrial. As tecnologias empregadas são de escolha dos projetistas, estes dependem de recursos financeiros e da logística de compra e recebimento de matérias, para finalização do projeto em tempo hábil. Os projetistas deverão fornecer uma solução para os seguintes requisitos:

* Verificação de rotulagem;
* Controle de nível de envase;
* Análise de cores de matéria prima;
* Leitura OCR de lote e validade;
* Inspeção e teste;

Dito isto, abaixo estarão descritas de forma detalhada as tecnologias escolhidas pelos projetistas.

## Tecnologias a serem empregadas

O processo industrial tem em seu núcleo para integração dos sensores, controle e comunicação, um microcontrolador, Arduino Mega. Também, será utilizado um smartphone e um notebook para leitura de imagens. 

Para controle de etapa e validação, foi utilizado quatro sensores de presença por infravermelho, TCR5000, e um algoritmo controlado por máquina de estado para garantia da conclusão de cada estágio. Cada estágio terá seu controle de qualidade e testes, podendo invalidar o produto em questão.

A seguir estão descritos os estados da máquina de estado:

1. **Verificação de rotulagem e controle de qualidade**

   Nesta etapa, após a garrafa estar localizada em frente ao sensor de presença, uma interrupção externa ocorre devido a mudança de estado lógico no pino do Arduino de alto para baixo, indicando estar no estágio 1. 

   Neste estágio, teremos a medição da temperatura do liquido, para garantir a qualidade do produto. Após o sensor medir a temperatura, a informação é armazenada em uma variável no código, validando ou não este estágio, conforme os padrões de qualidade de temperatura do liquido, estipulados pelo cliente. 

   A verificação de rotulagem por sua vez, é um processo um pouco manual, devido as dificuldades encontradas durante o projeto, que serão comentados numa seção mais afrente. Como solução para esta etapa, os projetistas fazem uso de um aplicativo OCR, para Smartphones, que faz a leitura de uma imagem, utilizando a câmera do celular, e converte em arquivo .TXT. Este arquivo é compartilhado via bluetooth para um notebook. Um código em linguagem de programação C, será executado e converterá este arquivo .TXT para uma planilha de Excel, onde poderá servir de controle pelo cliente.

2. **Controle de nível de envase e controle de qualidade**

   Um sensor de distância por ultrassom HC-SR04 será posto no bocal da garrafa. As medidas de distancia do liquido, através do sensor, será coletada e armazenada no código, e exibida no display LCD. 

   Com a distancia do liquido, podemos através de uma equação matemática calcular o volume do liquido. Uma função de calculo de volume foi implementada e será explicada mais afrente. 

3. **Analise de cor de matéria prima e controle de qualidade**

   Um sensor de cor, TCS230, será posto no bocal da garrafa para identificar se este é ou não um suco de uva.  As componentes RGB serão mostradas no display para o usuário.

   Esta etapa, como as outras, possui um controle de qualidade. Caso não seja a cor do suco de uva, uma mensagem indicando que é outo liquido será exposta no display LCD. 

4. **Leitura OCR e Validade**

   Nesta etapa, como na primeira, será utilizado um aplicativo OCR, um smartphone e um notebook. Será realizado o mesmo processo do estagio um de leitura de rótulo e embalagem.

   A imagem da tampa será coletada e transformada em .TXT, para poder ser manipulada por um código em C e fazer o armazenamento numa planilha Excel. 

Desta maneira, finalizamos a parte de concepção e idealização do projeto. A seguir, será visto a etapa de Design do projeto.

# Design

Após a concepção e apropriação do objetivo final, a etapa de design é necessária para escolha de sensores, orçamento do projeto e materiais necessário para execução da concepção. Foi escolhido os sensores que seriam necessários para realização de cada etapa mencionadas acima, suas quantidades e custo. Nesta etapa, foi desenhado a estrutura que suportaria os sensores e o arduino, e com qual material seria feito esta estrutura.

O valor aproximado do projeto, desconsiderando o smartphone e notebook, é de R$ 181,90. 

1. Tablado de madeira

   Cada estágio possui sensores em localizações diferentes. Os sensores de cor, ultrassônico, temperatura, lote e validade, precisam estar acima da garrafa para a medição poder ser feita. Já os sensores de presença precisam estar de tal maneira que detectem a garrafa em sua parte mais larga, afim de reduzir erros. 

   Primeiramente, foi pensado em utilizar isopor para fazer a estrutura, porém devido a fragilidade, aspectos estéticos e de segurança, onde os fios ficariam expostos, foi decidido utilizar uma estrutura de cano PVC. 

   Valor desta etapa: R$ 21,70.

2. Sensores:

   1. Quatro sensores TCR5000. Preço: R$ 2,00 cada;
   2. Um sensor TCS230. Preço: R$ 39,90;
   3. Um sensor HC-SR04. Preço: R$ 7,50;
   4. Um sensor de temperatura;

3. Smartphone com bluetooth;

4. Notebook com bluetooth e pacote Office;

5. Arduino Mega. Preço: R$ 79,90;

6. Fios para conexão entre sensores e arduino. Preço: R$ 14,90;

7. Placas universais. Preço: R$ 10,00;

   

# Implementação

Nesta etapa do projeto, foi implementado o algoritmo para leitura e tratamento de dados dos sensores, assim como a soldagem dos sensores em placas universais. O código foi escrito em linguagem C++ para parte que envolve o arduino e sensores, e em C para transformação do conteúdo .TXT em um banco de dados numa planilha Excel.  

## Sensor de Presença - TCR5000

Para separação em etapas, uma maquina de estado foi implementada, utilizando interrupção externa do arduino. Abaixo está uma forma reduzida, para fins didáticos, do código do sensor de presença e máquina de estado, lembrando que o código completo pode ser encontrado no repositório do GitHub.

O sensor TCR5000 muda do estado lógico alto para baixo quando algo está em sua frente, esta mudança de estado é percebida pelo pino do Arduino que ocasionará em uma interrupção externa.

A detecção por nível de descida nos pinos *Detectx* é ativada, gerando a interrupção externa. A interrupção externa levará a funções especificas que alteram a variável *state_x* para controle da maquina de estado.

<pre>
<font color="#434f54">&#47;&#47;Pinos de conexao dos sensores TCRT5000</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">detect1</font> <font color="#434f54">=</font> <font color="#000000">2</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">detect2</font> <font color="#434f54">=</font> <font color="#000000">3</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">detect3</font> <font color="#434f54">=</font> <font color="#000000">18</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">detect4</font> <font color="#434f54">=</font> <font color="#000000">19</font><font color="#000000">;</font>

<font color="#00979c">volatile</font> <font color="#00979c">int</font> <font color="#000000">state_0</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#00979c">volatile</font> <font color="#00979c">int</font> <font color="#000000">state_1</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">detect1</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;Pino ligado ao coletor do fototransistor estagio 1</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">detect2</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;Pino ligado ao coletor do fototransistor estagio 2</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">detect3</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;Pino ligado ao coletor do fototransistor estagio 3</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">detect4</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;Pino ligado ao coletor do fototransistor estagio 4</font>
 &nbsp;&nbsp;
 &nbsp;<font color="#d35400">attachInterrupt</font><font color="#000000">(</font><font color="#d35400">digitalPinToInterrupt</font><font color="#000000">(</font><font color="#000000">detect1</font><font color="#000000">)</font><font color="#434f54">,</font> <font color="#000000">sensor_1</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">attachInterrupt</font><font color="#000000">(</font><font color="#d35400">digitalPinToInterrupt</font><font color="#000000">(</font><font color="#000000">detect2</font><font color="#000000">)</font><font color="#434f54">,</font> <font color="#000000">sensor_2</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">attachInterrupt</font><font color="#000000">(</font><font color="#d35400">digitalPinToInterrupt</font><font color="#000000">(</font><font color="#000000">detect3</font><font color="#000000">)</font><font color="#434f54">,</font> <font color="#000000">sensor_3</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">attachInterrupt</font><font color="#000000">(</font><font color="#d35400">digitalPinToInterrupt</font><font color="#000000">(</font><font color="#000000">detect4</font><font color="#000000">)</font><font color="#434f54">,</font> <font color="#000000">sensor_4</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;
<font color="#5e6d03">switch</font> <font color="#000000">(</font><font color="#000000">state_0</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#5e6d03">case</font> <font color="#000000">1</font><font color="#434f54">:</font> <font color="#434f54">&#47;&#47;estagio 1</font>
 &nbsp;&nbsp;&nbsp;<font color="#5e6d03">case</font> <font color="#000000">2</font><font color="#434f54">:</font> <font color="#434f54">&#47;&#47;estagio 2</font>
<font color="#000000">}</font>
<font color="#5e6d03">switch</font> <font color="#000000">(</font><font color="#000000">state_1</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;<font color="#5e6d03">case</font> <font color="#000000">1</font><font color="#434f54">:</font> <font color="#434f54">&#47;&#47;estagio 3</font>
 &nbsp;<font color="#5e6d03">case</font> <font color="#000000">2</font><font color="#434f54">:</font> <font color="#434f54">&#47;&#47;estagio 4</font>
<font color="#000000">}</font>

<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">sensor_1</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">state_0</font> <font color="#434f54">=</font> <font color="#000000">1</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">state_1</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">sensor_2</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">state_0</font> <font color="#434f54">=</font> <font color="#000000">2</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">state_1</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">sensor_3</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">state_0</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">state_1</font> <font color="#434f54">=</font> <font color="#000000">1</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">sensor_4</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#000000">state_0</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">state_1</font> <font color="#434f54">=</font> <font color="#000000">2</font><font color="#000000">;</font>
<font color="#000000">}</font>

</pre>

## Sensor Ultrassônico - JSN-SR04T

Nesta etapa, estado 2, é realizado o calculo do volume do liquido. O sensor nos retornará a distancia do liquido em relação ao sensor. 

Foi dividido a garrafa em duas partes, para facilitar o calculo do volume. A primeira, consideramos uma aproximação de um hiperbolóide de uma folha e a segunda em um cilindro. Temos uma altura fixa do sensor até a garrafa e com a distancia do liquido até o sensor conseguimos calcular através de alguns valores fixos, de raio, diâmetro, etc., e pela formula de calculo de volume das duas partes, o volume final do liquido.

Como na parte superior da garrafa temos diversos valores de diâmetro, para facilitar o calculo matemático do volume, na parte do hiperbolóide de uma folha, foi setorizado e dividido alguns valores fixos para o diâmetro. Conforme a altura que o liquido se encontra, terá um valor fixo para o diâmetro nesta parte, que foi encontrado através de medidas feitas na garrafa. Portanto, está função só será valida para esta garrafa e caso queira utilizar outra, deverá alterar os valores fixos.

Abaixo há um código exemplo de utilização do sensor ultrassônico, retirado do código original. Vale lembrar novamente que é necessário todo o conjunto do código para funcionamento adequado, e este é apenas um exemplo didático.



 <pre>
<font color="#434f54">&#47;&#47;Carrega a biblioteca do sensor ultrassonico</font>
<font color="#5e6d03">#include</font> <font color="#434f54">&lt;</font><font color="#000000">Ultrasonic</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>

<font color="#434f54">&#47;&#47;Define os pinos para o trigger e echo do sensor ultrassonico</font>
<font color="#5e6d03">#define</font> <font color="#000000">pino_trigger</font> <font color="#000000">12</font>
<font color="#5e6d03">#define</font> <font color="#000000">pino_echo</font> <font color="#000000">13</font>

<font color="#434f54">&#47;&#47;Inicializa o sensor ultrassonico e o display nos pinos e bibliotecas definidas acima</font>
<font color="#000000">Ultrasonic</font> <font color="#000000">ultrasonic</font><font color="#000000">(</font><font color="#000000">pino_trigger</font><font color="#434f54">,</font> <font color="#000000">pino_echo</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;<font color="#5e6d03">switch</font><font color="#000000">(</font><font color="#000000">state_0</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;<font color="#5e6d03">case</font> <font color="#000000">2</font><font color="#434f54">:</font>

 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">println</font><font color="#000000">(</font><font color="#005c5f">&#34;Estágio 2: Detecção de nível do líquido&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">clear</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">setCursor</font><font color="#000000">(</font><font color="#000000">0</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;ESTAGIO 2&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">setCursor</font><font color="#000000">(</font><font color="#000000">0</font><font color="#434f54">,</font> <font color="#000000">1</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;NÍVEL ENVASE&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">delay</font><font color="#000000">(</font><font color="#000000">3000</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">clear</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47;Le as informacoes do sensor, em cm-----------------------------------------</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#00979c">float</font> <font color="#000000">cmMsec</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#00979c">long</font> <font color="#000000">microsec</font> <font color="#434f54">=</font> <font color="#000000">ultrasonic</font><font color="#434f54">.</font><font color="#000000">timing</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">cmMsec</font> <font color="#434f54">=</font> <font color="#000000">ultrasonic</font><font color="#434f54">.</font><font color="#000000">convert</font><font color="#000000">(</font><font color="#000000">microsec</font><font color="#434f54">,</font> <font color="#000000">Ultrasonic</font><font color="#434f54">:</font><font color="#434f54">:</font><font color="#000000">CM</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#00979c">String</font> <font color="#000000">cmMsecString</font> <font color="#434f54">=</font> <font color="#00979c">String</font><font color="#000000">(</font><font color="#000000">cmMsec</font><font color="#434f54">,</font> <font color="#000000">2</font><font color="#000000">)</font><font color="#000000">;</font> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; A variavel que armazena os valores em centimetros e no segundo argumento (&#34;2&#34;) serve para dizer que quero 2 casas decimais.</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#00979c">String</font> <font color="#000000">cmMsecStringFinal</font> <font color="#434f54">=</font> <font color="#000000">cmMsecString</font> <font color="#434f54">+</font> <font color="#005c5f">&#34;cm&#34;</font><font color="#000000">;</font> &nbsp;<font color="#434f54">&#47;&#47; Valor = STRING em CENTIMETROS</font>

 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Print a message to the LCD.</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">setCursor</font><font color="#000000">(</font><font color="#000000">0</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;Distancia&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">setCursor</font><font color="#000000">(</font><font color="#000000">10</font><font color="#434f54">,</font> <font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#000000">cmMsecStringFinal</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">setCursor</font><font color="#000000">(</font><font color="#000000">0</font><font color="#434f54">,</font> <font color="#000000">1</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#005c5f">&#34;Volume&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">setCursor</font><font color="#000000">(</font><font color="#000000">8</font><font color="#434f54">,</font> <font color="#000000">1</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47;Calculo do volume ---------------------------------------------------------</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">lcd</font><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#000000">volume_func</font><font color="#000000">(</font><font color="#000000">cmMsec</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">delay</font><font color="#000000">(</font><font color="#000000">500</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#5e6d03">break</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">}</font>
<font color="#000000">}</font>

<font color="#00979c">float</font> <font color="#000000">volume_func</font><font color="#000000">(</font><font color="#00979c">float</font> <font color="#000000">altura_sensor</font><font color="#000000">)</font> <font color="#000000">{</font>

 &nbsp;<font color="#00979c">int</font> <font color="#000000">altura_total</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font><font color="#434f54">&#47;&#47;fixo</font>
 &nbsp;<font color="#00979c">float</font> <font color="#000000">altura_liq</font> <font color="#434f54">=</font> <font color="#000000">altura_total</font> <font color="#434f54">-</font> <font color="#000000">altura_sensor</font><font color="#000000">;</font>
 &nbsp;<font color="#00979c">int</font> <font color="#000000">parte_cil</font> <font color="#434f54">=</font> <font color="#000000">10</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;fixo cilindro</font>
 &nbsp;<font color="#00979c">int</font> <font color="#000000">raio_cil</font> <font color="#434f54">=</font> <font color="#000000">4</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;fixo</font>
 &nbsp;<font color="#00979c">int</font> <font color="#000000">cheio</font> <font color="#434f54">=</font> <font color="#000000">20</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;fixo altura quando está cheio</font>
 &nbsp;<font color="#00979c">float</font> <font color="#000000">volume</font><font color="#000000">;</font>
 &nbsp;<font color="#00979c">float</font> <font color="#000000">diametro1</font><font color="#434f54">,</font> <font color="#000000">d2</font> <font color="#434f54">=</font> <font color="#000000">8</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47;d2, fixo</font>
 &nbsp;<font color="#434f54">&#47;&#47;altura do liquido * pi*r^2</font>

 &nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&lt;=</font> <font color="#000000">parte_cil</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#5e6d03">return</font> <font color="#000000">volume</font> <font color="#434f54">=</font> <font color="#000000">altura_liq</font> <font color="#434f54">*</font> <font color="#000000">3.1415</font> <font color="#434f54">*</font> <font color="#000000">(</font><font color="#000000">raio_cil</font> <font color="#434f54">*</font> <font color="#000000">raio_cil</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#000000">}</font> <font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&gt;</font> <font color="#000000">parte_cil</font><font color="#000000">)</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&lt;=</font> <font color="#000000">cheio</font><font color="#000000">)</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&gt;=</font> <font color="#000000">11</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">altura_liq</font> <font color="#434f54">&lt;=</font> <font color="#000000">12</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">diametro1</font> <font color="#434f54">=</font> <font color="#000000">5.5</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font> <font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&gt;</font> <font color="#000000">12</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">altura_liq</font> <font color="#434f54">&lt;=</font> <font color="#000000">13</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">diametro1</font> <font color="#434f54">=</font> <font color="#000000">4.5</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font> <font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&gt;</font> <font color="#000000">13</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">altura_liq</font> <font color="#434f54">&lt;=</font> <font color="#000000">14</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">diametro1</font> <font color="#434f54">=</font> <font color="#000000">3.5</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font> <font color="#5e6d03">else</font> <font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">altura_liq</font> <font color="#434f54">&gt;</font> <font color="#000000">14</font> <font color="#434f54">&amp;&amp;</font> <font color="#000000">altura_liq</font> <font color="#434f54">&lt;=</font> <font color="#000000">15</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">diametro1</font> <font color="#434f54">=</font> <font color="#000000">2.5</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">}</font>

 <font color="#5e6d03">return</font> volume = (parte_cil * 3.1415 * (raio_cil * raio_cil)) + (1/3 * 3.1415 * (altura_liq-15) * (2 * (diametro1 * diametro1) + (raio_cil * raio_cil)));
 &nbsp;<font color="#000000">}</font>
<font color="#000000">}</font>

</pre>

## Sensor de Cor - TCS230

Esta é a etapa 3 do processo. Neste estágio, o sensor de cor transmite o valor RGB (vermelho, azul e verde) para o arduino. O sensor TCS230 baseia-se em uma matriz de fotodiodos, combinados com um conversor corrente-frequência. Sob esse conjunto de fotodiodos incide a luz refletida pelos objetos ao alcance do sensor. Os fotodiodos geram uma corrente de saída de acordo com a intensidade da luz refletida e também de acordo com seus filtros. Há uma tabela de seleção de filtros e escala de frequência, que pode ser observada em seu datasheet.

Em síntese, as cores são filtradas e a informação é gerada no pino OUT, que vai enviar os dados ao microcontrolador. Os pinos S0 e S1 ditam a frequência de saída, e os pinos S2 e S3 o nível de cor detectado.

O código abaixo é um exemplo para saber se é suco de uva (avermelhado) ou não. Para mais detalhes, acessar código completo do projeto.

<pre>
<font color="#434f54">&#47;&#47;Pinos de conexao do modulo TCS230</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">s0</font> <font color="#434f54">=</font> <font color="#000000">7</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">s1</font> <font color="#434f54">=</font> <font color="#000000">8</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">s2</font> <font color="#434f54">=</font> <font color="#000000">11</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">s3</font> <font color="#434f54">=</font> <font color="#000000">10</font><font color="#000000">;</font>
<font color="#00979c">const</font> <font color="#00979c">int</font> <font color="#000000">out</font> <font color="#434f54">=</font> <font color="#000000">9</font><font color="#000000">;</font>

<font color="#434f54">&#47;&#47;Variaveis que armazenam o valor das cores</font>
<font color="#00979c">int</font> <font color="#000000">red</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">green</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#00979c">int</font> <font color="#000000">blue</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">s0</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">s1</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">s2</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">s3</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">out</font><font color="#434f54">,</font> <font color="#00979c">INPUT</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">digitalWrite</font><font color="#000000">(</font><font color="#000000">s0</font><font color="#434f54">,</font> <font color="#00979c">HIGH</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">digitalWrite</font><font color="#000000">(</font><font color="#000000">s1</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;<font color="#5e6d03">switch</font><font color="#000000">(</font><font color="#000000">state_1</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#5e6d03">case</font> <font color="#000000">1</font><font color="#434f54">:</font>

​	  Serial.println("Estágio 3: Detecção da cor do suco");
​      lcd.clear();
​      lcd.setCursor(0, 0);
​      lcd.print("ESTAGIO 3");
​      lcd.setCursor(0, 1);
​      lcd.print("COLOR LIQUIDO");
​      delay(4000);
​      lcd.clear();
​      color(); //Chama a rotina que le as cores
​      //Mostra no serial monitor os valores detectados
​      Serial.print("Vermelho :");
​      Serial.print(red);
​      Serial.print(" Verde : ");
​      Serial.print(green);
​      Serial.print(" Azul : ");
​      Serial.print(blue);
​      Serial.println();

&nbsp;&nbsp;&nbsp;&nbsp;//Verifica se a cor do suco é a correta
      if (red < 300 && red > 270 && red < green && blue < 315)
      {
        Serial.println("Suco de uva");
        lcd.setCursor(0, 0);
        lcd.print("R");
        lcd.setCursor(2, 0);
        lcd.print(red);
        lcd.setCursor(5, 0);
        lcd.print("G");
        lcd.setCursor(7, 0);
        lcd.print(green);
        lcd.setCursor(10, 0);
        lcd.print("A");
        lcd.setCursor(12, 0);
        lcd.print(blue);
        lcd.setCursor(0, 1);
        lcd.print("!SUCO DE UVA!");
        delay(6000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ESTAGIO VALIDADO");
        delay(4000);
      }
      //Caso contrário define que é outro tipo de líquido detectado no produto
      else
      {
        Serial.println("Outro liquido");
        lcd.setCursor(0, 0);
        lcd.print("R");
        lcd.setCursor(2, 0);
        lcd.print(red);
        lcd.setCursor(5, 0);
        lcd.print("G");
        lcd.setCursor(7, 0);
        lcd.print(green);
        lcd.setCursor(10, 0);
        lcd.print("A");
        lcd.setCursor(12, 0);
        lcd.print(blue);
        lcd.setCursor(0, 1);
        lcd.print("!OUTRO LIQUIDO!");
        delay(6000);
        lcd.clear();
        lcd.setCursor(7, 0);
        lcd.print("ERRO");
        lcd.setCursor(0, 1);
        lcd.print("DESCARTE PRODUTO");
      }
      delay(3000);
      lcd.clear();
      break;
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#000000">color</font><font color="#000000">(</font><font color="#000000">)</font>
<font color="#000000">{</font>
 &nbsp;<font color="#434f54">&#47;&#47;Rotina que le o valor das cores</font>
 &nbsp;<font color="#d35400">digitalWrite</font><font color="#000000">(</font><font color="#000000">s2</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">digitalWrite</font><font color="#000000">(</font><font color="#000000">s3</font><font color="#434f54">,</font> <font color="#00979c">LOW</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#434f54">&#47;&#47;count OUT, pRed, RED</font>
 &nbsp;<font color="#000000">red</font> <font color="#434f54">=</font> <font color="#d35400">pulseIn</font><font color="#000000">(</font><font color="#000000">out</font><font color="#434f54">,</font> <font color="#d35400">digitalRead</font><font color="#000000">(</font><font color="#000000">out</font><font color="#000000">)</font> <font color="#434f54">==</font> <font color="#00979c">HIGH</font> <font color="#434f54">?</font> <font color="#00979c">LOW</font> <font color="#434f54">:</font> <font color="#00979c">HIGH</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">digitalWrite</font><font color="#000000">(</font><font color="#000000">s3</font><font color="#434f54">,</font> <font color="#00979c">HIGH</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#434f54">&#47;&#47;count OUT, pBLUE, BLUE</font>
 &nbsp;<font color="#000000">blue</font> <font color="#434f54">=</font> <font color="#d35400">pulseIn</font><font color="#000000">(</font><font color="#000000">out</font><font color="#434f54">,</font> <font color="#d35400">digitalRead</font><font color="#000000">(</font><font color="#000000">out</font><font color="#000000">)</font> <font color="#434f54">==</font> <font color="#00979c">HIGH</font> <font color="#434f54">?</font> <font color="#00979c">LOW</font> <font color="#434f54">:</font> <font color="#00979c">HIGH</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#d35400">digitalWrite</font><font color="#000000">(</font><font color="#000000">s2</font><font color="#434f54">,</font> <font color="#00979c">HIGH</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;<font color="#434f54">&#47;&#47;count OUT, pGreen, GREEN</font>
 &nbsp;<font color="#000000">green</font> <font color="#434f54">=</font> <font color="#d35400">pulseIn</font><font color="#000000">(</font><font color="#000000">out</font><font color="#434f54">,</font> <font color="#d35400">digitalRead</font><font color="#000000">(</font><font color="#000000">out</font><font color="#000000">)</font> <font color="#434f54">==</font> <font color="#00979c">HIGH</font> <font color="#434f54">?</font> <font color="#00979c">LOW</font> <font color="#434f54">:</font> <font color="#00979c">HIGH</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

</pre>

## OCR

Como dito anteriormente, nesta parte do projeto encontramos dificuldades para resolução e a solução desenvolvida foi utilizar um aplicativo que transforma imagem em .TXT para que, através de um código em C, possamos converter os dados numa planilha Excel. 

O código é simples, abre um arquivo .TXT, lê os dados e armazena em outro arquivo do tipo .csv.

Abaixo se encontra o código em C que fará esta função do projeto.

<pre>
<font color="#5e6d03">#include</font> <font color="#434f54">&lt;</font><font color="#000000">stdio</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>
<font color="#5e6d03">#include</font> <font color="#434f54">&lt;</font><font color="#000000">stdlib</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>


<font color="#00979c">int</font> <font color="#000000">main</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">{</font>
<font color="#00979c">int</font> <font color="#000000">n</font> <font color="#434f54">=</font><font color="#000000">0</font><font color="#434f54">,</font> <font color="#000000">numberOfValues</font> <font color="#434f54">=</font> <font color="#000000">5</font><font color="#434f54">,</font> <font color="#000000">c</font><font color="#000000">;</font>
<font color="#00979c">char</font> <font color="#000000">x</font><font color="#000000">[</font><font color="#000000">]</font> <font color="#434f54">=</font> <font color="#005c5f">&#34;Informações:\n&#34;</font><font color="#000000">;</font>

<font color="#000000">FILE</font> * <font color="#000000">fp</font> <font color="#434f54">=</font> <font color="#d35400">fopen</font><font color="#000000">(</font><font color="#005c5f">&#34;pi.csv&#34;</font><font color="#434f54">,</font> <font color="#005c5f">&#34;w&#34;</font><font color="#000000">)</font><font color="#000000">;</font> &nbsp;
<font color="#000000">FILE</font> <font color="#434f54">*</font> <font color="#000000">fx</font> <font color="#434f54">=</font> <font color="#d35400">fopen</font><font color="#000000">(</font><font color="#005c5f">&#34;pi.txt&#34;</font><font color="#434f54">,</font> <font color="#005c5f">&#34;r&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#d35400">fprintf</font><font color="#000000">(</font><font color="#000000">fp</font><font color="#434f54">,</font> <font color="#005c5f">&#34;%s\n&#34;</font><font color="#434f54">,</font> <font color="#000000">x</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;<font color="#5e6d03">while</font><font color="#000000">(</font><font color="#000000">1</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">c</font> <font color="#434f54">=</font> <font color="#d35400">fgetc</font><font color="#000000">(</font><font color="#000000">fx</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#5e6d03">if</font><font color="#000000">(</font> <font color="#d35400">feof</font><font color="#000000">(</font><font color="#000000">fx</font><font color="#000000">)</font> <font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#5e6d03">break</font> <font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">}</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">fprintf</font><font color="#000000">(</font><font color="#000000">fp</font><font color="#434f54">,</font> <font color="#005c5f">&#34;%c&#34;</font><font color="#434f54">,</font> <font color="#000000">c</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#000000">}</font>
 &nbsp;&nbsp;<font color="#d35400">fclose</font><font color="#000000">(</font><font color="#000000">fx</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#d35400">fclose</font><font color="#000000">(</font><font color="#000000">fp</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#5e6d03">return</font> <font color="#000000">0</font><font color="#000000">;</font>
<font color="#000000">}</font>

</pre>

# Melhorias

Devido ao curto tempo de execução do projeto, disciplina de 36h, algumas aplicações não puderam ser executadas de maneira mais eficiente e outros adicionais não foram acrescentados.

Todos os dados dos sensores poderiam ser comunicados com um módulo WiFi, exemplo ESP8266, que disponibilizaria os dados numa pagina web ou num servidor em nuvem, exemplo ThingSpeak. Podendo ser visualizado de qualquer dispositivo com conexão a internet. Além de podermos comandar o microcontrolador a distancia para executar ajustes ou acionar atuadores.

Com a conexão a internet, nos aproximaríamos mais do conceito da indústria 4.0. Uma aplicação de envio de email ou mensagem poderia ser implementada, para informar o estado, controle de qualidade, entre outros. 

Atuadores poderiam ser inseridos que poderiam ser ativados conforme os dados dos sensores. Por exemplo, LEDs poderiam ser inseridos para informar erro ou necessidade de reparo. 

Outra melhoria, seria adicionar um cartão de memória no Arduino e um dispositivo bluetooth para receber o arquivo .TXT direto no Arduino, armazenando no cartão e fazendo a leitura direto do mesmo, sem ser necessário a utilização de um notebook no processo.

E por ultimo, um sistema de inserção de parâmetros pelo usuário seria necessário para etapas de controle de qualidade, como por exemplo, a temperatura aceitável do liquido ou o volume nominal.  

# Dificuldades

Ao longo do projeto foram encontrados alguns obstáculos, como por exemplo o sensor ultrassônico. Este precisa estar muito bem posicionado no bocal da garrafa para não sofrer interferência externar e retornar apenas o valor exato da distância do liquido. 

Outro problema encontrado foi na equação do calculo do volume na parte do tronco de cone, esta equação precisa do parâmetro do diâmetro do tronco de cone. Porem, a garrafa nesta parte, possui diversos valores e então foi necessário setorizar em algumas faixas de valores. Por exemplo, de 20 cm a 22 cm de distância, teríamos 10 cm de diâmetro. Ou então utilizar uma outra tecnologia.

Na parte de leitura de rótulo e validade, precisaríamos fazer tratamento de imagem, o que seria inviável utilizando um Arduino. Nem um dos projetistas tinha conhecimento suficiente para desenvolver esta aplicação em tempo hábil. 

Os sensores em questão não são facilmente encontrados em simuladores de circuitos eletrônicos, desta forma, dificulta o processo de teste, tendo em vista, que precisa ser feito direto na prática. 

E por ultimo, de dificuldades encontradas, foi percebido que a maquina de estados não funcionava e após muitos testes e metodologias de debug, foi descoberto que o switch case do Arduino só ia de 0 até 2. Portanto, foi necessário dividir a maquina de estado em dois estados, estado_0 e estado_1.



# Referências 

https://www.filipeflop.com/blog/sensor-ultrassonico-hc-sr04-ao-arduino/

http://blogmasterwalkershop.com.br/arduino/arduino-utilizando-o-sensor-reflexivo-tcrt5000/

https://www.filipeflop.com/blog/sensor-de-cor-tcs3200-rgb-arduino/

www.alldatasheet.com <Datasheet encontrados para os sensores>

https://www.arduino.cc/reference/pt/language/functions/external-interrupts/attachinterrupt/

http://www.circuitstoday.com/arduino-mega-pinout-schematics

https://www.significados.com.br/briefing/

https://www.genbeta.com/web/siete-documentales-que-puedes-ver-junio-youtube-mundo-software-desarrollo

Conheça alguns conceitos da indústria 4.0 que já fazem parte do nosso dia a dia - https://www.youtube.com/watch?v=ZqpQbsVdqsU

