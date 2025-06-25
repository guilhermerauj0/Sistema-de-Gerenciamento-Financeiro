#include "estatisticas.h"

void filtrar_por_periodo(Transacao* origem, int tamanho, int inicio, int fim, Transacao* filtrado, int* novo_tamanho) {
    int count = 0;
    for (int i = 0; i < tamanho; i++) {
        if (origem[i].data >= inicio && origem[i].data <= fim) {
            filtrado[count++] = origem[i];
        }
    }
    *novo_tamanho = count;
}

double calcular_total(Transacao* transacoes, int tamanho, char tipo) {
    double total = 0.0;
    for (int i = 0; i < tamanho; i++) {
        if (transacoes[i].tipo == tipo) {
            total += transacoes[i].valor;
        }
    }
    return total;
}

double encontrar_maior(Transacao* transacoes, int tamanho, char tipo) {
    double maior = -1e9;
    for (int i = 0; i < tamanho; i++) {
        if (transacoes[i].tipo == tipo && transacoes[i].valor > maior) {
            maior = transacoes[i].valor;
        }
    }
    return maior;
}

double encontrar_menor(Transacao* transacoes, int tamanho, char tipo) {
    double menor = 1e9;
    for (int i = 0; i < tamanho; i++) {
        if (transacoes[i].tipo == tipo && transacoes[i].valor < menor) {
            menor = transacoes[i].valor;
        }
    }
    return menor;
}

