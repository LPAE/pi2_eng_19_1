# Projeto Integrado 2 - Engenharia Eletrônica
Autores: Guilherme Camargo Valese e Jéssica Ramos Ribeiro

## 1 Introdução

A Indústria 4.0 é considerada como a Quarta Revolução Industrial. A primeira envolveu utilização de máquinas, a segunda linhas de montagem e produção em massa, a terceira empregou automação e a quarta envolve máquinas que se comunicam entre si. Enquanto as outras revoluções industriais foram marcadas pelo crescimento das linhas de produção, popularização de máquinas e produção em massa, a indústria 4.0 caracteriza-se pela forma de se unir diversas tecnologias que permitam a fusão do mundo físico, digital e biológico (ABDI). Isso inclui sistemas físico-cibernéticos, internet das coisas, computação na nuvem e computação cognitiva. Um sistema físico-cibernético visa a integração de processos físicos e computacionais. Ou seja, os computadores e redes podem monitorar o processo físico de fabricação em um determinado processo. O uso destas tecnologias permite a operação modular e descentralizada das fábricas, podendo inclusive serem controladas a distância por meio da internet. Sensores posicionados ao longo da cadeia produtiva realizam a análise dos processos e por meio da IA (Inteligência Artificial), podem tomar decisões sem a intervenção humana (JORNAL DA GLOBO, 2018). Segundo a ABDI (Agência Brasileira de Desenvolvimento Industrial) “a estimativa anual de redução de custos industriais no Brasil, a partir da migração da indústria para o conceito 4.0, será de, no mínimo, R$ 73 bilhões/ano.” As rápidas mudanças nas tecnologias de informação e comunicação romperam os limites entre a realidade virtual e o mundo real. A ideia por trás da Indústria 4.0 é criar uma rede social onde as máquinas possam se comunicar umas com as outras, chamada Internet of Things( IoT) e com as pessoas, Internet of People (IoP). A Internet das coisas é o que permite que objetos e máquinas, ou sensores, se comuniquem uns com os outros, assim como os seres humanos. A integração dessa tecnologia permite que os objetos funcionam e resolvam problemas de forma independente. Naturalmente, isso não o que realmente acontece, uma vez que os seres humanos podem intervir. Celulares, tablets, laptops, televisores e até mesmo relógios estão se tornando cada vez mais interconectados. Os serviços de Internet visam criar um ambiente que simplifique todos os dispositivos conectados para poder tirar o máximo proveito destes produtos e assim simplificar o processo. A Indústria 4.0 é definitivamente uma abordagem revolucionária para as técnicas de fabricação. O conceito levará fabricantes a um nível de otimização e produtividade superiores. As recompensas econômicas são imensas.

## 2 Concepção

![](imagens/fluxograma_funcionamento.jpg)

#### Quadro 1

| Delimitadores Tecnológicos      | Tecnologias     | Quantidade(s)       |
| --------------------------------|-----------------|---------------------|
|Verificação do Rótulos (OCR)     |Em análise       |                     |
|Temperatura                      |MLX90614         | 1                   |
|Cor                              |TSC 3200         | 1                   |
|Ultrassônico                     |JSN-SR04T        | 1                   |
|Posição                          |TCRT5000         | 4                   |
|LCD                              |HD44780          | 1                   |

Para a realização do projeto foram utilizados os sensores listados acima. Cada um deles possui sua importância. Os sensores de posição verificam a posição da garrafa ao longo de todo o processo. O sensor de cor verifica se a cor do líquido dentro da garrafa está normal. O sensor ultrassônico é utilizado para a verificação da altura do líquido dentro da garrafa, calculando assim o volume total de líquido dentro da mesma. Por fim, o leitor OCR verifica validade e lote da garrafa! Como critério de escolha de cada sensor, foi pesquisado a lista de sensores disponíveis no laboratório. Para o sensor ultrassônico, por exemplo, haviam dois sensores disponíveis sendo um deles com diâmetro menor do que o diâmetro da  garrafa a qual será utilizada no projeto e o outro sua dimensão ultrapassa a da garrafa. O sensor ultrassônico escolhido foi o JSN-SR04T devido suas dimensões serem compatíveis para a garrafa.  
Para todas as verificações que forem positivas, o processo continuará de onde estava. Porém quando a mesma obtiver um valor fora do esperado, a garrafa será retirada do processo e a próxima garrafa iniciará o processo do início.









