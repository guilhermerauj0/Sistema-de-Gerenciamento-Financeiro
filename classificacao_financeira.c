#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incluindo o cabeçalho para garantir consistência entre declaração e definição.
#include "classificacao_financeira.h"

#define CAPACIDADE_INICIAL_REGISTROS 10

// --- Implementação das Funções do Módulo ---

RegistroFinanceiro* carregar_registros_financeiros(const char* nome_arquivo, int* num_registros) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de dados financeiros");
        *num_registros = 0;
        return NULL;
    }

    RegistroFinanceiro* registros = NULL;
    int capacidade = 0;
    *num_registros = 0;

    int id_temp, ano_temp;
    double receitas_temp, despesas_temp;

    while (fscanf(arquivo, "%d %d %lf %lf", &id_temp, &ano_temp, &receitas_temp, &despesas_temp) == 4) {
        if (*num_registros >= capacidade) {
            int nova_capacidade = (capacidade == 0) ? CAPACIDADE_INICIAL_REGISTROS : capacidade * 2;
            RegistroFinanceiro* temp_registros = realloc(registros, nova_capacidade * sizeof(RegistroFinanceiro));

            if (temp_registros == NULL) { // CORREÇÃO: Verificação direta de !temp_registros para NULL
                perror("Erro ao realocar memória para os registros");
                liberar_registros_financeiros(registros, *num_registros);
                fclose(arquivo);
                *num_registros = 0;
                return NULL;
            }
            // CORREÇÃO CRÍTICA: As duas linhas abaixo estavam faltando!
            // Sem elas, 'registros' nunca era atualizado após a realocação.
            registros = temp_registros;
            capacidade = nova_capacidade;
        }
        // As atribuições abaixo agora funcionam corretamente porque 'registros' foi atualizado.
        registros[*num_registros].id_periodo = id_temp;
        registros[*num_registros].ano = ano_temp;
        registros[*num_registros].total_receitas = receitas_temp;
        registros[*num_registros].total_despesas = despesas_temp;
        registros[*num_registros].saldo = 0.0;
        registros[*num_registros].classificacao = NULL;
        (*num_registros)++;
    }

    if (ferror(arquivo)) {
        fprintf(stderr, "Erro de leitura no meio do arquivo.\n"); // CORREÇÃO: Melhor mensagem de erro
        liberar_registros_financeiros(registros, *num_registros);  // CORREÇÃO: Evita vazamento de memória
        *num_registros = 0;
        fclose(arquivo);
        return NULL; // CORREÇÃO: Retorna NULL em caso de erro de leitura
    }
    
    fclose(arquivo);

    // CORREÇÃO CRÍTICA: Faltava o retorno da função no caminho de sucesso.
    return registros;
}

void classificar_um_registro(RegistroFinanceiro* registro) {
    if (registro == NULL) return; // Boa prática: verificar se o ponteiro não é nulo

    registro->saldo = registro->total_receitas - registro->total_despesas;

    if (registro->classificacao) {
        free(registro->classificacao);
        registro->classificacao = NULL;
    }
    // CORREÇÃO: Strings com acento (Superavitário, Deficitário) para consistência
    if (registro->saldo > 1e-6) {
        registro->classificacao = strdup("Superavitário");
    } else if (registro->saldo < -1e-6) {
        registro->classificacao = strdup("Deficitário");
    } else {
        registro->classificacao = strdup("Equilibrado");
    }
    // Boa prática: verificar se strdup (alocação) funcionou
    if (registro->classificacao == NULL) {
        perror("Falha ao alocar memória para string de classificação");
    }
}

void classificar_registros_financeiros(RegistroFinanceiro* registros, int num_registros) {
    if (registros == NULL) return; // Boa prática: verificar ponteiro nulo
    for (int i = 0; i < num_registros; i++) {
        classificar_um_registro(&registros[i]);
    }
}

void informar_deficit_superavit_por_periodo(const RegistroFinanceiro* registros, int num_registros) {
    if (!registros) {
        printf("Nenhum registro para informar.\n");
        return;
    }

    printf("\n--- Relatorio Detalhado por Periodo ---\n"); // CORREÇÃO: Typo "Detalahado"
    printf("------------------------------------------------------------------------------------------\n");
    printf("| ID Periodo | Ano  | Total Receitas | Total Despesas |     Saldo     | Classificacao   |\n"); // CORREÇÃO: Alinhamento do cabeçalho
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_registros; i++) {
        // CORREÇÃO: Formatação de double é com %f. Também ajustei espaçamentos para melhor alinhamento.
        printf("| %-10d | %-4d | %14.2f | %14.2f | %13.2f | %-15s |\n",
               registros[i].id_periodo,
               registros[i].ano,
               registros[i].total_receitas,
               registros[i].total_despesas,
               registros[i].saldo,
               registros[i].classificacao ? registros[i].classificacao : "Indefinido");
    }
    // CORREÇÃO CRÍTICA: Esta linha estava DENTRO do loop, agora está fora.
    printf("------------------------------------------------------------------------------------------\n");
}

void apresentar_resultados(const RegistroFinanceiro* registros, int num_registros) {
    if (!registros || num_registros == 0) {
        printf("Nenhum dado financeiro para apresentar na analise completa.\n");
        return;
    }

    printf("\n========= ANÁLISE FINANCEIRA COMPLETA =========\n");

    informar_deficit_superavit_por_periodo(registros, num_registros);

    double total_receitas = 0.0;
    double total_despesas = 0.0;
    int count_superavit = 0;
    int count_deficit = 0;
    int count_equilibrio = 0;

    for (int i = 0; i < num_registros; ++i) {
        total_receitas += registros[i].total_receitas;
        total_despesas += registros[i].total_despesas;
        if (registros[i].classificacao) {
             // CORREÇÃO: Comparar com as strings corretas com acentos
            if (strcmp(registros[i].classificacao, "Superavitário") == 0) {
                count_superavit++;
            } else if (strcmp(registros[i].classificacao, "Deficitário") == 0) {
                count_deficit++;
            } else if (strcmp(registros[i].classificacao, "Equilibrado") == 0) {
                count_equilibrio++;
            }
        }
    }

    double saldo_total = total_receitas - total_despesas;
    printf("\n--- Resumo Geral da Analise ---\n");
    printf("Numero Total de Periodos Analisados: %d\n", num_registros);
    printf("Receita Total Acumulada: %.2f\n", total_receitas);
    printf("Despesa Total Acumulada: %.2f\n", total_despesas);
    printf("Saldo Geral Acumulado: %.2f ", saldo_total);

    if (saldo_total > 1e-6) {
        printf("(Superavitario Geral)\n"); // CORREÇÃO: Strings sem acento podem causar inconsistência
    } else if (saldo_total < -1e-6) {
        printf("(Deficitario Geral)\n");
    } else {
        printf("(Equilibrado Geral)\n");
    }

    printf("Periodos com Superavit: %d\n", count_superavit);
    printf("Periodos com Deficit: %d\n", count_deficit);
    printf("Periodos em Equilibrio: %d\n", count_equilibrio);
    printf("============================================\n");
}

void liberar_registros_financeiros(RegistroFinanceiro* registros, int num_registros) {
    if (!registros) return;

    for (int i = 0; i < num_registros; i++) {
        if (registros[i].classificacao) {
            free(registros[i].classificacao);
            registros[i].classificacao = NULL;
        }
    }
    free(registros);
}

// --- Função Principal para Teste ---

int main() {
    const char* nome_do_arquivo = "dados_financeiros.txt";

    printf("Iniciando o programa de gerenciamento financeiro...\n");
    printf("Tentando carregar dados do arquivo: %s\n\n", nome_do_arquivo);

    RegistroFinanceiro* registros = NULL;
    int num_registros = 0;

    registros = carregar_registros_financeiros(nome_do_arquivo, &num_registros);

    if (registros == NULL && num_registros == 0) {
        fprintf(stderr, "ERRO: Nao foi possivel carregar os registros financeiros.\n");
        fprintf(stderr, "Verifique se o arquivo '%s' existe e esta formatado corretamente.\n", nome_do_arquivo);
        return EXIT_FAILURE;
    }
    
    if (num_registros == 0) {
        printf("O arquivo de dados esta vazio. Nada a processar.\n");
        liberar_registros_financeiros(registros, num_registros);
        return EXIT_SUCCESS;
    }

    printf("=> Dados carregados com sucesso! Total de %d registros encontrados.\n", num_registros);

    printf("\nIniciando a classificacao financeira de todos os registros...\n");
    classificar_registros_financeiros(registros, num_registros);
    printf("=> Classificacao concluida.\n");

    apresentar_resultados(registros, num_registros);

    printf("\nFinalizando o programa e liberando a memoria alocada...\n");
    liberar_registros_financeiros(registros, num_registros);
    printf("=> Memoria liberada. Programa encerrado com sucesso.\n");

    return EXIT_SUCCESS;
}