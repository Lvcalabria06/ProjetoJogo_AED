#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Carta {
    char *naipe;
    char *valorTexto;
    int valor; // para contagem no blackjack
} Carta;

typedef struct No {
    Carta carta;
    struct No *prox;
    struct No *ant;
} No;

typedef struct {
    Carta cartas[12];
    int total;
    int pontuacao;
} Mao;

typedef struct {
    No *inicio;
    int tamanho;
} Baralho;

// Declaração das funções
void inicializarBaralho(Baralho *baralho);
void embaralhar(Baralho *baralho);
Carta comprarCarta(Baralho *baralho);
void distribuir(Baralho *baralho, Mao *jogador, Mao *dealer);

#endif
