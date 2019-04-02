## Introdução

Atualmente a indústria como um todo tem domínio praticamente nulo sobre os processos de produção de suas fabricas. Muitas informações são perdidas, omitidas e processos de melhorias muitas vezes estão defasados ou se distorcem da realidade da produção. Para obtermos redução de custo, qualidade, estoque saudável e não desperdiçar suprimentos é preciso coletar dados do processo como um todo. Precisamos validar as informações coletadas, agrupa-las e então pensar numa solução para determinado problema. 

Com o surgimento da indústria 4.0, a coleta e analise de dados em determinado processo ficou fácil, precisa e confiável. Com a atuação de sensores, internet das coisas, inteligência artificial na produção das empresas obteve-se um grande avanço na engenharia da qualidade, logística, administração, gestão e etc. Houve grande redução na perda de produtos, aumento da qualidade final, controle de estoque, redução de gastos e atrasos de lotes. A produção ficou mais rápida e eficaz, pois ao encontrar um defeito, maquinas com inteligência artificial se comunicam e trazem soluções. 

Sem a implementação da indústria 4.0 é necessário contar com a agilidade, eficácia, honestidade e raciocínio lógico dos seres humanos quando se trata de processos produtivos. Desta forma, muitas vezes encontra-se barreiras, como a falha de comunicação e relacionamentos que gestores se deparam todos os dias em seus sistemas de funcionários. Também, sistemas produtivos são mais lentos e muitos dados importantes não são levantados sem o uso do conceito da indústria 4.0. Logo, analise e implementação de melhorias acabam sendo infrutíferas.

## Concepção 

O projeto em questão é uma simulação de um processo produtivo industrial de uma garrafa de suco de uva. Temos como premissa, entregar ao cliente um produto pronto que verificará a rotulagem durante a produção, controlar o nível de envase, analisar a cor da matéria prima, fazer a leitura OCR do lote e validade, e inspecionar e fazer alguns testes para garantir a qualidade do produto. 

A leitura do rotulo garantirá que um rótulo foi impresso, contendo a quantidade de litros contido na garrafa, o tipo de suco e código de barras. Será feito utilizando câmeras externas e a ferramenta Tesseract, esta converte a imagem em uma string, para manipulação e analise via código e microcontrolador. 

O controle do nível de envase será feito com a utilização de sensores ultrassônicos, que enviarão a informação da altura que o liquido se encontra na garrafa para o microcontrolador. Este, através de formulas matemáticas, retornará o valor do volume contido na garrafa. 

A analise da cor da matéria prima, neste caso, suco de uva, será feita utilizando sensor de cor e um microcontrolador. Está etapa servirá de teste de qualidade e inspeção para garantirmos a cor do suco contido. 

A leitura do lote e validade será feita com uma câmera externa focada na tampa do produto. A ferramenta Tesseract, já mencionada, converterá as informações em string. Validaremos, via código, se é um lote válido e no período da validade desejada. 

Garantiremos a qualidade através das inspeções e testes, mencionados anteriormente, e acrescentaremos dois sensores de temperatura, interno e externo, para garantir que não ultrapasse o valor desejado durante o processo produtivo, não danificando o suco em questão. Todas as etapas serão escritas num display LCD para que o usuário possa acompanhar o resultado de cada uma. 