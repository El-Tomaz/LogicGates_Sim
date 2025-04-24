# LogicGate Sim


As portas lógicas estão na base de toda a tecnologia digital que usamos no dia a dia, de celulares e computadores a sistemas embarcados e automação residencial. Compreender como elas funcionam é essencial para quem deseja seguir nas áreas de tecnologia, eletrônica e sistemas embarcados.

Nesta atividade, foram colocados em prática os conhecimentos de programação e lógica digital n um simulador físico de portas lógicas usando a placa BitDogLab. 

## Objetivos:

1. Praticar o desenvolvimento de aplicações embarcadas na BitDogLab;

1. Ter uma experiência prática com o comportamento das portas lógicas, aplicando entradas com botões e visualizando a saída com LED;
        
1. Ser capaz de modelar o comportamento das portas lógicas na linguagem C;

## Requisitos do projeto:

1. O sistema deve simular o funcionamento das seguintes portas lógicas (7 ao total): AND, OR, NOT, NAND, NOR, XOR e XNOR.

1. Entradas: utilize os botões A e B da BitDogLab como entradas binárias (1 (não pressionado) ou 0 (pressionado)), simulando os sinais de entrada da porta lógica selecionada. 

1. Saída: use o LED RGB da placa, ele deverá indicar o resultado da operação, acendendo vermelho (0) ou verde (1), de acordo com a lógica da porta.

1. Seleção da porta lógica: a escolha da porta a ser simulada deve ser feita por meio do joystick da placa. A cada mudança, o display OLED deverá exibir o nome (ou símbolo) da porta lógica atualmente selecionada.

1. Para a porta NOT, utilizar apenas uma entrada (botão A), desconsiderando o botão B.

## Arquitetura

| menu | <-> |main + logica|