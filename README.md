# AutoChill

### Sistema Embarcado para Controle de Temperatura Automático em Refrigeradores Manuais

### Descrição do Projeto

Este projeto tem como objetivo desenvolver um sistema embarcado para controle automático de temperatura em refrigeradores manuais, visando economia de energia e melhor conservação dos alimentos. O sistema utiliza um microcontrolador compatível com o Raspberry Pi Pico e diversos periféricos para leitura de sensores e controle de atuadores.

### Funcionalidades

Ajuste de temperatura via botões.

Detecção do peso por meio de um sensor conectado ao ADC.

Controle de um servo motor para ajuste mecânico baseado na temperatura e peso.

Exibição do nível de temperatura na matriz de LEDs.

### Hardware Utilizado

Microcontrolador: Raspberry Pi Pico ou compatível

Sensores: Sensor de peso (conectado ao ADC)

Atuadores: Servo motor controlado por PWM

Interface: Matriz de LEDs controlada via PIO


### Estrutura do Firmware

O firmware foi desenvolvido utilizando Pico SDK, GCC e Vim, e segue uma estrutura modular com os seguintes arquivos:

main.c: Arquivo principal, onde ocorre a inicialização e o loop principal.

lib.c: Implementação das funções auxiliares e controle do hardware.

lib.h: Cabeçalho contendo definição de macros, bibliotecas e assinaturas das funções.

ws2812.pio: Programa PIO utilizado para controle da matriz de LEDs (não desenvolvido por mim, referenciado na seção de créditos).

[Link para apresentação e demostração do funcionamento na BitDogLab](https://drive.google.com/file/d/1XJIb9zb3lr4dVveIIRlc6OgQWYbgKKJ9/view?usp=sharing)

