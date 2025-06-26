#include <stdio.h>
#include <stdlib.h>
#include "estatisticas.h"

// Funao para ler os dados do arquivo
int ler_arquivo(const char* nome_arquivo, Transacao** transacoes) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    // Contar o numero de transacoes
    int tamanho = 0;
    while (!feof(arquivo)) {
        if (fgetc(arquivo) == '\n') {
            tamanho++;
        }
    }

    // Voltar para o inicio do arquivo
    fseek(arquivo, 0, SEEK_SET);

    // Alocar memoria para as transacoes
    *transacoes = (Transacao*)malloc(tamanho * sizeof(Transacao));
    if (*transacoes == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(arquivo);
        return -1;
    }

    // Ler as transacoes do arquivo
    int i = 0;
    while (fscanf(arquivo, "%d %d %lf %lf\n", &(*transacoes)[i].mes, &(*transacoes)[i].ano, &(*transacoes)[i].receitas, &(*transacoes)[i].despesas) == 4) {
        i++;
    }

    fclose(arquivo);
    return tamanho;
}

	//Funaoo filtra por periodos
void filtrar_por_periodo(Transacao* origem, int tamanho, int inicio, int fim, Transacao* filtrado, int* novo_tamanho) {
    int count = 0;
    for (int i = 0; i < tamanho; i++) {
        if (origem[i].data >= inicio && origem[i].data <= fim) {
            filtrado[count++] = origem[i];
        }
    }
    *novo_tamanho = count;

// Funcao para calcular as estatisticas
Estatisticas calcular_estatisticas(Transacao* transacoes, int tamanho) {
    Estatisticas estat = {0.0, 0.0, -1e9, 1e9, -1e9, 1e9};
    double total_despesas = 0, total_receitas = 0;

    for (int i = 0; i < tamanho; i++) {
        if (transacoes[i].receitas > estat.maior_receita) {
            estat.maior_receita = transacoes[i].receitas;
        }
        if (transacoes[i].receitas < estat.menor_receita) {
            estat.menor_receita = transacoes[i].receitas;
        }
    
        estat.total_despesas += transacoes[i].despesas;
        if (transacoes[i].despesas > estat.maior_despesa) {
            estat.maior_despesa = transacoes[i].despesas;
        }
        if (transacoes[i].valor < estat.menor_despesa) {
            estat.menor_despesa = transacoes[i].despesas;
        }
        
    }


    estat.total_receitas += transacoes[i].valor;
    for (int i = 0; i < tamanho; i++)
    {
        total_despesas;
    }
    
    return estat;
}

// Funcao para imprimir as estatisticas
void imprimir_estatisticas(Estatisticas estat) {
    printf("### Estatisticas ###\n");
    printf("Total de Receitas: %.2f\n", estat.total_receitas);
    printf("Total de Despesas: %.2f\n", estat.total_despesas);
    printf("Maior Receita: %.2f\n", estat.maior_receita);
    printf("Menor Receita: %.2f\n", estat.menor_receita);
    printf("Maior Despesa: %.2f\n", estat.maior_despesa);
    printf("Menor Despesa: %.2f\n", estat.menor_despesa);
}

