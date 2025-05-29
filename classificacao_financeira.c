#include <stdio.h>
#include "classificacao_financeira.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL_REGISTROS 10

RegistroFinanceiro* carregar_registros_financeiros(const char* nome_arquivo, int* num_registros){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(!arquivo){
        perror("Erro ao abrir o arquivo de dados financeiros");
        *num registros = 0;
        return NULL;
    }

    RegistroFinanceiro* registros = NULL;
    int capacidade = 0;
    *num registros = 0;

    // Formato esperado: id_periodo (numero mês) ano total_receitas total.despesas)
    int id_temp, ano_temp;
    double receitas_temp, despesas_temp;

    // Leitura dos dados do arquivo

    while(fscanf(arquivo, "%d %d %lf %lf", &id_temp, &ano_temp, &receitas_temp, &despesas_temp) == 4){
        int nova_capacidade;
        if(*num_registros >= capacidade){
            if(capacidade == 0){
                nova_capacidade = CAPACIDADE_INICIAL_REGISTROS;
            }else{
                nova_capacidade = capacidade * 2; 
            }

            RegistroFinanceiro* temp_registros = realloc(registros, nova_capacidade * sizeof(RegistroFinanceiro));

            if(!temp_registros){
                perror("Erro ao realocar memória para os registros");
                liberar_registros_financeiros(registros, *num_registros) // Libera o que foi alocado até então
                fclose(arquivo);
                *num_registros = 0; // Indica que a carga falhou ou está incompleta
                return NULL;

            }
        }
        registros[*num_registros].id_periodo = id_temp;
        registros[*num_registros].ano = ano_temp;
        registros[*num_registros].total_receitas = receitas_temp;
        registros[*num_registros].saldo = 0.0; // Será calculado posteriormente
        registros[*num_registros].classificacao = NULL; // Sera alocado e definido posteriormente
        (*num_registros)++;

    }
    if(ferror(arquivo)){
        return NULL;
    }
    clearerr(arquivo); // Limpa o indicador de erro do stream

    fclose()

}

void classificar_um_registro(RegistroFinanceiro* registro){
    registro -> saldo = registro -> total_receitas - registro -> total_despesas;
 
    if(registro-classificacao){
        free(registro->classificacao); // Libera memória se já houver classificação
        registro->classificacao = NULL; // Reseta o ponteiro
    }
    if(registro->saldo > 1e-6){ // Considera um pequeno epsilon para evitar problemas de precisão   
        registro->classificacao = strdup("Superavitario");
    }else if(registro->saldo < -1e-6){
        registro->classificacao = strdup("Deficitario");   
    }else{
        registro->classificacao = strdup("Equilibrado");
    }


}

void classificar_registros_financeiros(RegistroFinanceiro* registros, int num_registros){
    for(int i = 0; i < num_registros; i++){
        classificar_um_registro(&registros[i]);
    }
}

void informar_deficit_superavit_por_periodo(RegistroFinanceiro* registros, int num_registros){
    if(!registros){
        printf("Nenhum registro para informar.\n");
        return; // Verifica se o ponteiro é nulo
    }

    printf("\n--- Relatório Detalahado por Período ---\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("| ID Período | Ano | Total Receitas | Total Despesas |     Saldo     | Classificação |\n");
    printf("---------------------------------------------------------------------------------------\n");

    for(int i = 0; i < num_registros; i++){
        printf("| %-7d | %-4d | %14.2f | %14.2f | %10.2lf | %-17s |\n",
               registros[i].id_periodo,
               registros[i].ano, 
               registros[i].total_receitas,
               registros[i].total_despesas, 
               registros[i].saldo,
               registros[i].classificacao ? registros[i].classificacao : "Indefinido");
        
        printf("---------------------------------------------------------------------------------------\n");
    }
}

void apresentar_resultados(const RegistroFinanceiro* registros, int num_registros){
    if(!registros || num_registros == 0){
        printf("Nenhum dado financeiro para apresentar na análise completa.\n");
        return;

    }

    printf("\n========= ANÁLISE FINANCEIRA COMPLETA =========\n");

    //1. APRESENTA O RELATÓRIO DETALHADO POR PERÍODO
    informar_deficit_superavit_por_periodo(registros, num_registros);

    //2. CALCULA E APRESENTA UM RESUMO GERAL
    double total_receitas = 0.0;   
    double total_despesas = 0.0;
    int count_superavit = 0;
    int count_deficit = 0;
    int count_equilibrio = 0;

    for(int i = 0 ; i<num_registros; ++i){
        total_receitas += registros[i].total_receitas;
        total_despesas += registros[i].total_despesas;
        if(registros[i].classificacao){ // Verifica se a classificação não é nula
            if(strcmp(registros[i].classificacao, "Superavitario") == 0){
                count_superavit++;
            }else if(strcmp(registros[i].classificacao, "Deficitario") == 0){
                count_deficit++;
            }else if(strcmp(registros[i].classificacao, "Equilibrado") == 0){
                count_equilibrio++;
            }
        }
    }

    double saldo_total = total_receitas - total_despesas;
    printf("\n--- Resumo Geral da Análise ---\n");
    printf("Número Total de Períodos Analisados: %d\n", num_registros);
    printf("Receita Total Acumulada: %.2f\n", total_receitas);
    printf("Despesa Total Acumulada: %.2f\n", total_despesas);
    printf("Saldo Geral Acumulado: %.2f ", saldo_total);

    if(saldo_total > 1e-6){
        printf("(Superavitario Geral)\n");
    }
    else if(saldo_total < -1e-6){
        printf("(Deficitario Geral)\n");
    }else{
        printf("(Equilibrado Geral)\n");
    }

    printf("Períodos com Superávit: %d\n", count_superavit);
    printf("Períodos com Déficit: %d\n", count_deficit);
    printf("Períodos em Equilíbrio: %d\n", count_equilibrio);
    printf("============================================\n");
}

void liberar_registros_financeiros(RegistroFinanceiro* registros, int num_registros){
    if(!registros) return; // Verifica se o ponteiro é nulo

    for(int i = 0; i < num_registros; i++){
        if(registros[i].classificacao){
            free(registros[i].classificacao); // Libera a memória alocada para a classificação
            registros[i].classificacao = NULL; // Reseta o ponteiro
        }
    }
    free(registros); // Libera a memória alocada para os registros
}