

**De onde veio isso?** 
Uma metodologia de controle de qualidade nos conceitos da indústria 4.0
por Daniel Nunes.

**Introdução** 

A indústria 4.0 é um movimento de origem alemã que teoriza a evolução dos métodos de produção industrial em consequência de movimentos sociais e desenvolvimento tecnológico da última década. O termo foi cunhado em 2011 nomeando uma iniciativa do governo alemão para o desenvolvimento do seu, já consolidado, mercado industrial (1).
	Tendo em mente o conceito de rastreabilidade que tem ganho crescente destaque nos processos industriais, este projeto busca desenvolver uma metodologia de coleta de dados qualitativos para controle de qualidade interno. A partir desta possível coleta de dados, tem-se como tangível um cenário em que o cliente final, estimulado por uma cultura de consumo superficialmente mais consciente, possa verificar as condições que  seu produto adquirido deixou a linha de produção. 

**Desenvolvimento** 

​	Atendendo aos requisitos de projeto solicitados, concebeu-se o projeto com quatro estágios de aquisição de dados: leitura de código de barras, verificação do nível do líquido, medição da temperatura do líquido e captura da cor do líquido. Para que estas medições possam acontecer, foram empregadas as tecnologias descritas as seguir. Para cada módulo, serão detalhadas as etapas da metodologia CDIO, empregada como diretriz para organização do desenvolvimento do projeto. 

**Medição da temperatura do conteúdo** 

​	Tratando-se de um produto alimentício, tem-se como primordial a implementação de um controle de qualidade eficiente na medicação da temperatura do líquido no interior da embalagem. Para isto, utilizou-se um sensor de temperatura de modelo MLX90614,  já adquirido pela equipe pedagógica da disciplina.
​	Além da pronta disponibilidade, um parâmetro que levou-se em consideração foi sua fácil implementação através de bibliotecas, exemple e documentação de fácil acesso.
​	Com sua documentação em mãos, necessitou-se apenas alguns testes para atingir pleno funcionamento do sensor, que utilizou-se no modo de sensoriamento de temperatura direcional de um objeto, porém o módulo conta ainda com com um modo de medição de temperatura ambiente. 

 <img src="https://uploads.filipeflop.com/2018/05/4MD58_1.jpg"
figcaption="Imagem do sensor de temperatura utilizado no projeto." width="300"/>

​	Como é pode observar-se na imagem acima, o sensor possui um foco direcional bastante evidente, facilitando o posicionamento do mesmo de forma coaxial ao gargalo da garrafa a ser inspecionada aberta, apontado diretamente para o conteúdo desta.

**Medição da cor do conteúdo** 

​	De forma análoga à temperatura, o expecto do produto na embalagem pode ser considerado um bom indicador qualitativo. Neste projeto esta análise do expecto é figurada pelo sensoriamento da luz refletida à um sensor ótico que instalou-se, também apontado diretamente para o conteúdo da garrafa, sobre esta.     	Também já tendo-se disponível para utilização, optou-se por empregar um módulo TCS320. Este sensor possibilita a mensurar a intensidade de luz que é capturada por cada um dos seus quatro tipos de componentes. Três destes componentes sensíveis à luz possuem filtros das cores  primárias do espectro da luz visível (vermelho, verde e azul) e um ultimo tipo de sensor não possui filtro e é destinado a medir a claridade geral refletida em seu foco. Para  este projeto, utilizou-se apenas os sensores filtrados.

![TCS230 TCS3200 Color Sensor Photodiodes Filters How It Works](https://howtomechatronics.com/wp-content/uploads/2016/05/TCS230-TCS3200-Color-Sensor-Photodiodes-Filters-How-It-Works.jpg)	

​	A imagem acima,  retirada de um tutorial para  implementação do módulo (2), ilustra os quatro tipos de sensores presentes, assim como a composição do mesmo.
​	Por também possuir uma vasta documentação disponível, sua aplicação fez-se simples e rápida: para cada um dos três tipos de sensores, o módulo de controle recebe uma série de leituras, das quais é feita uma média aritmética simples. Para uma coerência na aplicação como método de controle de qualidade, este valor médio é então comparado com um valor pré-estabelescido do que pode-se considerar aceitável para o produto e, desta comparação, é obtida um erro percentual. Estes três valores de desvios são então agregados para, por fim, resultar em um valor percentual de proximidade do que mede-se em relação à condição ideal configurada.
​	Com essa metodologia de aplicação, possibilita-se a criação de uma regra de reprovação. Por exemplo, se uma determinada garrafa possui um líquido que apresente uma cor menos que 90% compatível com o esperado, esta garrafa deve ser reprovada no teste de qualidade.

**Verificação do nível de conteúdo** 

​	Em uma terceira etapa de medida, implementou-se a verificação do volume de líquido contido no recipiente e, para que isto fosse possível, algumas características da embalagem precisam ser prioritariamente levadas em consideração. Primeiramente, é necessário que esta averiguação da quantidade de líquido seja feita de forma não invasiva, ou seja, fizera-se necessário a medição de forma perpendicular à superfície do líquido e não de forma paralela como intuía-se fazer a princípio. Esta condição criaria ainda outro problema: a medição deveria ser feita através do gargalo da garrafa, limitando a escolha de sensores à módulos ultrassônicos construídos de forma a ter seu sensor e emissor posicionados de forma coaxial. Para suprir estas necessidades, elegeu-se o módulo JSN-SR04T que, além de ter seus atuadores posicionados de forma satisfatória, possui o hardware de tratamento de sinal separado destes atuadores, facilitando um futuro posicionamento na estrutura do protótipo.
​	Novamente a documentação técnica para este sensor mostrou-se de fácil acesso e compreensão facilitando a integração do sensor ao módulo de controle. Porém, com esta documentação em mãos, constatou-se que a distância mínima requerida pelo sensor (20cm) em conjunto com sua grande abertura de foco (75°) impossibilitaria a medição caso a garrafa e o sensor não estivessem perfeitamente alinhados. Devido a escassez de tempo hábil e restrição orçamental para alterar o sensor utilizado, decidiu-se implementar este sensor no protótipo deste projeto, levando em consideração essas limitações e tomando nota para uma futura substituição por um modelo de sensor que adeque-se melhor às necessidades da aplicação.
​	Apesar destes contratempos, o módulo foi implementado em conjunto com o sistema de controle e a medição do volume de líquido na embalagem foi feita aproximando, matematicamente, o recipiente ao formato de um cilindro, averiguando a linha de preenchimento da garrafa quando esta continha o volume esperado (1500ml) e comparando este valore ao então medido pelo sensor.

**Leitura do código de barras** 

​	Imaginando-se uma aplicação real para este projeto de análise qualitativa de um produto destinado ao consumo final, é possível contemplar uma situação de erro na linha de produção deste bem resultando em um produto diferente sendo testado para em relação aos parâmetros do objeto à que este projeto destina-se. Uma forma comtemplada para evitar este cenário seria a leitura do código de barras do produto a ser inspecionado e, assim, certificar-se de que este mesmo é compatível com os testes a serem empregados. 	Assim sendo, solicitou-se à equipe pedagógica da disciplina a compra de um módulo leitor de códigos de barra do tipo 1D (unidirecional). Pretendia-se que este módulo fosse afixado ao conjunto do projeto posicionado na altura regular de onde espera-se encontrar o código de barras da embalagem.
​	Com o módulo adquirido em mãos, a implementação deste mostrou-se mais dispendiosa de tempo que o esperado. Em grande parte isso deve-se à falta de uma identificação clara do módulo e, consequentemente, à dificuldade aumentada em localizar documentação técnica para o mesmo. Ainda assim,  tentou-se basear a implementação do módulo de acordo com a esparsa documentação disponível _on-line_ para produtos semelhantes ao adquirido, mas sem muito sucesso. Ao fim do tempo hábil para desenvolvimento deste projeto, consegui-se apenas a verificação de uma conexão válida entre o sensor e o módulo de controle.

**Unidade de controle** 

​	A unidade de controle implementou-se com um módulo Arduino Uno devido sua praticidade e vasta gama de documentação de aplicações utilizando este. Ainda vale ressaltar a compatibilidade entre a tecnologia deste módulo com a dos sensores  periféricos que elegeu-se para  utilização neste projeto.

**Display** 

​	Apesar de ser imaginado para uma implementação automatizada em uma linha de produção, equipou-se o protótipo com com um display LCD para interface com o usuário. Por este meio, fez-se possível exibir as  medições realizadas pelo conjunto de  sensores e verificar o funcionamento do projeto sem a dependência de um meio proibitivo como um computador.

**Estrutura de Fixação**

​	Por ser imaginado como uma parte de uma linha de produção, a construção de uma estrutura para posicionamento dos sensores mostrou-se imprescindível. Esta estrutura deveria seguir os seguintes critérios:

* Leveza. O longo período de execução deste projeto e a quantidade de membros da disciplina utilizando o espaço restrito da instituição restringe a possibilidade de uma instalação permanente e fixa, sendo então necessária a movimentação da estrutura.
* Custo. Apesar de o projeto ser financiado, em sua maioria, pelos recursos destinados à disciplina, estra estrutura seria custeada pelo projetista.
* Modularidade. Sendo um projeto concebido e construído a partir de módulos, é evidente a necessidade de uma estrutura física que reflita esta característica.
* Tamanho. Mais do que apenas para contribuir com a portabilidade, o tamanho reduzido da estrutura possibilitaria o armazenamento facilitado desta quando não em uso.

​	A partir destes critérios, desenhou-se e construiu-se uma estrutura gradeada a partir de canos de PVC destinados à instalações  hidráulicas, distanciando as hastes de fixação dos sensores apenas o suficiente para a livre manipulação da garrafa entre os estágios de medição. A estrutura montada com os sensores fixados é ilustrada na figura abaixo.

![Estrutura](C:\Users\danie\Desktop\Estrutura.png)

​	Obedecendo-se o requisito de mobilidade, construiu-se esta estrutura com seus quatro apoios retráteis, de forma que, quando completamente "fechada" a estrutura possui apenas 25cm de altura (46cm de largura e 55cm de comprimento). Ainda observa-se na imagem a fixação dos módulos sensores de temperatura, cor e volume (direita para esquerda), além de uma  haste reservada para a instalação do módulo para leitura de código de barras. No canto inferior direito da imagem figura o módulo de controle fixado à uma _protoboard_, assim como o _display_ LCD e as conexões do projeto. Para o cabeamento dos sensores ao módulo de controle utilizou-se cabos flexíveis em conjuntos de quatro vias.

**Referências**

1 - https://online-journals.org/index.php/i-jim/article/download/7072/4532 

2 - https://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/

https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home#!ultrasonic-sensors

https://www.robocore.net/tutoriais/primeiros-passos-com-modulo-i2c.html

