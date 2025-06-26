#ifndef CLASSIFICACAO_FINANCEIRA_H
#define CLASSIFICACAO_FINANCEIRA_H

//Estrutura para armazenar os dados financeiros de um período Ex. Mensal
typedef struct{
    int id_periodo;         // Identificador do período (ex: mês 1, 2, 3...)
    int ano;                // Ano correspondente ao período
    double total_receitas;
    double total_despesas;
    double saldo;           // Calculado como: total_receitas - total_despesas
    char* classificacao;    // String alocada dinamicamente: "Superavitário", "Deficitário", "Equilíbrio"

} RegistroFinanceiro;

/**
 * @brief Carrega os registros financeiros de um arquivo de texto.
 * Formato esperado no arquivo (por linha): id_periodo ano total_receitas total_despesas
 * Exemplo: 1 2024 5000.00 4500.00
 *
 * @param nome_arquivo Caminho do arquivo de dados.
 * @param num_registros Ponteiro para int, onde será armazenado o número de registros lidos.
 * @return Ponteiro para um array de RegistroFinanceiro alocado dinamicamente.
 * Retorna NULL em caso de erro crítico (ex: falha ao abrir arquivo, falha de alocação inicial).
 * O chamador é responsável por liberar a memória com liberar_registros_financeiros.
 */
RegistroFinanceiro* carregar_registros_financeiros(const char* nome_arquivo, int* num_registros);

/**
 * @brief Classifica um único registro financeiro.
 * Calcula o saldo (receitas - despesas).
 * Define a string 'classificacao' ("Superavitário", "Deficitário", "Equilíbrio").
 * Aloca memória dinamicamente para a string 'classificacao'.
 *
 * @param registro Ponteiro para o RegistroFinanceiro a ser classificado.
 */
void classificar_um_registro(RegistroFinanceiro* registro);


/**
 * @brief Executa a classificação financeira para todos os registros carregados.
 * Itera sobre o array de registros, chamando classificar_um_registro para cada um.
 *
 * @param registros Array de RegistroFinanceiro.
 * @param num_registros Número de elementos no array de registros.
 */
void classificar_todos_registros(RegistroFinanceiro* registros, int num_registros);


/**
 * @brief Informa (imprime no console) o déficit ou superávit de cada período/mês.
 *
 * @param registros Array de RegistroFinanceiro (já classificados).
 * @param num_registros Número de elementos no array de registros.
 */
void informar_deficit_superavit_por_periodo(const RegistroFinanceiro* registros, int num_registros);


/**
 * @brief Apresenta os resultados completos da análise financeira. Superavitário, Deficitiário e Equilibrado.
 *
 * @param registros Array de RegistroFinanceiro (já classificados).
 * @param num_registros Número de elementos no array de registros.
 */
void apresentar_analise_financeira(const RegistroFinanceiro* registros, int num_registros);

/**
 * @brief Libera toda a memória alocada dinamicamente para os registros financeiros.
 * Isso inclui a string 'classificacao' de cada registro e o próprio array de registros.
 *
 * @param registros Array de RegistroFinanceiro a ser liberado.
 * @param num_registros Número de elementos no array de registros.
 * Se registros for NULL, a função não faz nada.
 */

void liberar_registros_financeiros(RegistroFinanceiro* registros, int num_registros);


/**
 * @brief Apresenta estatísticas detalhadas com base na análise financeira.
 *
 * @param total_receitas Array de RegistroFinanceiro (já classificados).
 * @param total_despesas Número de elementos no array de registros.
 * @param count_superavit Número de elementos no array de registros.
 * @param count_deficit Número de elementos no array de registros.
 * @param count_equilibrio Número de elementos no array de registros.
 */
void apresentar_estatisticas(const int num_registros, const double total_receitas, const double total_despesas, const int count_superavit, const int count_deficit, const int count_equilibrio );


#endif