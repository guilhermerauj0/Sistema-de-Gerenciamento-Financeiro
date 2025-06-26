#ifndef SALDO_FINAL_H
#define SALDO_FINAL_H

typedef struct {
    float total_receitas_periodo;
    float total_despesas_periodo;
    float saldo_final;
} SaldoConsolidado;


/**
 * @brief Verifica se uma data de registro está dentro de um período específico.
 * * A função compara o ano e o ID do registro com os valores iniciais e finais
 * de um período para determinar se o registro pertence a esse intervalo.
 * * @param idRegistro O ID do registro a ser verificado.
 * @param anoRegistro O ano do registro a ser verificado.
 * @param idInicial O ID inicial do período.
 * @param anoInicial O ano inicial do período.
 * @param idFinal O ID final do período.
 * @param anoFinal O ano final do período.
 * @return int Retorna 1 se a data do registro estiver dentro do período, caso contrário, retorna 0.
 */
int verificarData(int idRegistro, int anoRegistro, int idInicial, int anoInicial, int idFinal, int anoFinal);


/**
 * @brief Calcula o saldo consolidado (receitas - despesas) para um determinado período.
 * A função lê um arquivo de dados financeiros, filtra os registros que
 * pertencem ao período especificado e calcula o total de receitas, despesas e o saldo final.
 * @param idInicial O ID inicial do período para o filtro.
 * @param anoInicial O ano inicial do período para o filtro.
 * @param idFinal O ID final do período para o filtro.
 * @param anoFinal O ano final do período para o filtro.
 * @param cont Um ponteiro para uma variável inteira que contará o número de registros no período.
 * @return SaldoConsolidado Retorna uma estrutura com os totais de receitas, despesas e o saldo final do período analisado.
 */
SaldoConsolidado calculaSaldoPeriodo(int idInicial, int anoInicial, int idFinal, int anoFinal, int* cont);


#endif