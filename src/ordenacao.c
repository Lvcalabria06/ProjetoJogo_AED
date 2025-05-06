#include "ordenacao.h"

// Insertion Sort para ordenar as cartas na mão por valor
void ordenarMao(Mao *mao) {
    for (int i = 1; i < mao->total; i++) {
        Carta chave = mao->cartas[i];
        int j = i - 1;

        while (j >= 0 && mao->cartas[j].valor > chave.valor) {
            mao->cartas[j + 1] = mao->cartas[j];
            j--;
        }

        mao->cartas[j + 1] = chave;
    }
}
