#include "estrutura.h"

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

void inicializarBaralho(Baralho *baralho) {
    char *naipes[] = {"Copas", "Ouros", "Espadas", "Paus"};
    char *valores[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int valoresNumericos[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    baralho->inicio = NULL;
    baralho->tamanho = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            No *novo = (No*)malloc(sizeof(No));
            novo->carta.naipe = naipes[i];
            novo->carta.valorTexto = valores[j];
            novo->carta.valor = valoresNumericos[j];
            if (baralho->inicio == NULL) {
                baralho->inicio = novo;
                novo->prox = novo;
                novo->ant = novo;
            } else {
                No *ultimo = baralho->inicio->ant;
                ultimo->prox = novo;
                novo->ant = ultimo;
                novo->prox = baralho->inicio;
                baralho->inicio->ant = novo;
            }
            baralho->tamanho++;
        }
    }
}

void embaralhar(Baralho *baralho) {
    srand(time(NULL));
    for (int i = 0; i < baralho->tamanho * 3; i++) {
        int passos = rand() % baralho->tamanho;
        No *p = baralho->inicio;
        for (int j = 0; j < passos; j++) p = p->prox;

        // troca cartas entre baralho->inicio e p
        Carta temp = p->carta;
        p->carta = baralho->inicio->carta;
        baralho->inicio->carta = temp;
    }
}

Carta comprarCarta(Baralho *baralho) {
    Carta carta = baralho->inicio->carta;

    No *remover = baralho->inicio;
    if (baralho->tamanho == 1) {
        baralho->inicio = NULL;
    } else {
        remover->ant->prox = remover->prox;
        remover->prox->ant = remover->ant;
        baralho->inicio = remover->prox;
    }
    free(remover);
    baralho->tamanho--;
    return carta;
}


void distribuir(Baralho *baralho, Mao *jogador, Mao *dealer) {
    jogador->total = dealer->total = 0;
    jogador->cartas[jogador->total++] = comprarCarta(baralho);
    dealer->cartas[dealer->total++] = comprarCarta(baralho);
    jogador->cartas[jogador->total++] = comprarCarta(baralho);
    dealer->cartas[dealer->total++] = comprarCarta(baralho);
}
