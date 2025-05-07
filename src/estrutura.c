#include "estrutura.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void inicializarBaralho(Baralho *baralho) {
    char *naipes[] = {"Copas", "Ouros", "Espadas", "Paus"};
    char *valores[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int valoresNumericos[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    baralho->head = NULL;
    baralho->tamanho = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Node *Novo = (Node*)malloc(sizeof(Node));
            Novo->carta.naipe = naipes[i];
            Novo->carta.valorTexto = valores[j];
            Novo->carta.valor = valoresNumericos[j];
            if (baralho->head == NULL) {
                baralho->head = Novo;
                Novo->next = Novo;
                Novo->prev = Novo;
            } else {
                Node *ultimo = baralho->head->prev;
                ultimo->next = Novo;
                Novo->prev = ultimo;
                Novo->next = baralho->head;
                baralho->head->prev = Novo;
            }
            baralho->tamanho++;
        }
    }
}

void embaralhar(Baralho *baralho) {
    srand(time(NULL));
    for (int i = 0; i < baralho->tamanho * 3; i++) {
        int passos = rand() % baralho->tamanho;
        Node *p = baralho->head;
        for (int j = 0; j < passos; j++) p = p->next;

        // troca cartas entre baralho->head e p
        Carta temp = p->carta;
        p->carta = baralho->head->carta;
        baralho->head->carta = temp;
    }
}

Carta comprarCarta(Baralho *baralho) {
    Carta carta = baralho->head->carta;

    Node *remover = baralho->head;
    if (baralho->tamanho == 1) {
        baralho->head = NULL;
    } else {
        remover->prev->next = remover->next;
        remover->next->prev = remover->prev;
        baralho->head = remover->next;
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


int contarPontos(Mao *mao){
    int soma = 0, ases = 0;

    for(int i=0; i < mao->total; i++){
        if(mao->cartas[i].valorTexto == 'A'){
            ases++;
        }
        else{
            soma += mao->cartas[i].valor;
        }
    }

    while(soma + (ases*11) > 21 && ases > 0){
        soma += 1;
        ases--;
    }

    /** talvez tenha um erro no caso de o jogador/dealer ter um às valendo 11 
     * e outra carta (ex.:8) e comprar uma nova carta e ela vir às novamente.
     * Verificar depois
     */
    soma += ases * 11;
}