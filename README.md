### Segundo Trabalho Prático de AEDS I 

## Objetivo
Implementar o jogo Snake usando a biblioteca `jogo.h`. Exemplo de jogo: [Play Snake](https://playsnake.org/).

## Características
- Solicitar apelido no início.
- Oferecer 3 opções de velocidade: lenta, normal ou rápida.
- Tamanho da tela: mínimo de 640x480.
- Cobra formada por cabeça e segmentos de 10x10.
- Movimentação da cobra em quatro direções.
- Perda do jogo ao colidir com bordas ou próprios segmentos.
- Frutas aleatórias para aumentar segmentos da cobra.
- Placar com frutas coletadas.
- Efeitos sonoros para coleta de frutas e derrota.
- Música de fundo.
- Ranking com as 5 maiores pontuações, mantido entre sessões.

## Requisitos de Código
- Uso de módulos (ex: `cobra.h` e `cobra.c`).
- Obrigatório uso da `jogo.h` para desenho.
- Implementação de segmentos da cobra com alocação dinâmica e uso de `struct`.
