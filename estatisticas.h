#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H


typedef struct {
    int data; 
    double valor;
    char tipo;
} Transacao;

void filtrar_por_periodo(Transacao* origem, int tamanho, int inicio, int fim, Transacao* filtrado, int* novo_tamanho);
double calcular_total(Transacao* transacoes, int tamanho, char tipo);
double encontrar_maior(Transacao* transacoes, int tamanho, char tipo);
double encontrar_menor(Transacao* transacoes, int tamanho, char tipo);

#endif

