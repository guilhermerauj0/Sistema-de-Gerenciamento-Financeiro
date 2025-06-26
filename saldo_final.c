#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saldo_final.h"    //incluindo cabeçalho 

// Função para verificar se o resgistro financeiro está dentro do período desejado
int verificarData(int mesRegistro, int anoRegistro, int idInicial, int anoInicial, int idFinal, int anoFinal){
    if (anoRegistro=anoInicial){
        
        if (mesRegistro>=idInicial){
            return 1;
        }

    } else if (anoRegistro>anoInicial && anoRegistro<anoFinal){
        return 1;
    } else if (anoRegistro=anoFinal){
        
        if (mesRegistro<=idFinal){
            return 1;
        }

    }
    
    return 0;
}


void calculaSaldoPeriodo(const char* nome_arquivo, int mesInicial, int anoInicial, int mesFinal, int anoFinal){
  
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de dados financeiros");
    }

    SaldoConsolidado saldoTemp = {0.0, 0.0, 0.0};
    int mes_temp, ano_temp;
    float receitas_temp, despesas_temp;

    while (fscanf(arquivo, "%d %d %f %f", &mes_temp, &ano_temp, &receitas_temp, &despesas_temp) == 4) {
        if (verificarData(mes_temp, ano_temp, mesInicial, anoInicial, mesFinal, anoFinal)==1) {
            saldoTemp.total_despesas_periodo += despesas_temp;
            saldoTemp.total_receitas_periodo += receitas_temp;
        }

    }

    saldoTemp.saldo_final = saldoTemp.total_receitas_periodo - saldoTemp.total_despesas_periodo;

    // --- APRESENTAÇÃO DO SALDO FINAL (CONSOLIDADO) ---
    printf("====================================================================================\n");
    printf("           » RELATORIO DE SALDO FINAL NO PERÍODO DE %d/%d A %d/%d « \n", mesInicial, anoInicial, mesFinal, anoFinal);
    printf("====================================================================================\n");
    printf("         |   TOTAL RECEITAS   |   TOTAL DESPESAS   |   SALDO FINAL   |");
    printf("\n------------------------------------------------------------------------------------\n");
    printf("VALORES: |    %.2f    |    %.2f    |    %.2f    |", saldoTemp.total_receitas_periodo, saldoTemp.total_despesas_periodo, saldoTemp.saldo_final);
    printf("\n====================================================================================\n");
}