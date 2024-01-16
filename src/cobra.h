#ifndef __COBRA__
#define __COBRA__

#include <jogo.h>
#include <input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Rafael Carvalho Avidago Geraldo
#define MAX_SEGMENTOS 1000
#define TAM_SEGMENTO 20


typedef struct
{
    int x;
    int y;
} Segmento;

typedef struct
{
    Segmento segmentos[MAX_SEGMENTOS];
    int direcao;
    int tamanho;
} Cobra;

Cobra *cria_cobra();

void atualiza_cobra(Cobra *cobra);

void desenha_cobra(Cobra *cobra);


#endif