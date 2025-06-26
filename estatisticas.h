#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

typedef struct {
    int mes;   // A data da transacao
    int ano;
    double receitas;
    double despesas;
    double valor;
} Transacao;

typedef struct {
    double total_receitas;
    double total_despesas;
    double maior_receita;
    double menor_receita;
    double maior_despesa;
    double menor_despesa;
} Estatisticas;

// Funcao para ler os dados do arquivo
int ler_arquivo(const char* nome_arquivo, Transacao** transacoes);

//Funcao para filtrar por periodos
void filtrar_por_periodo(Transacao* origem, int tamanho, int inicio, int fim, Transacao* filtrado, int* novo_tamanho);

// Funcao para calcular as estat�sticas
Estatisticas calcular_estatisticas(Transacao* transacoes, int tamanho);

// Funcao para imprimir as estat�sticas
void imprimir_estatisticas(Estatisticas estat);

#endif // ESTATISTICAS_H

