#include <stdio.h>
#include <stdlib.h>
#include "manipulacao.h"
#include "usuario.h"

#include "classificacao_financeira.h"

#include "saldo_final.h"

#include "structs.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	FILE *j;
	int opcao;
	char nome[20];
	d_alimentacao alimentacao;
	d_moradia moradia;
	d_saude saude;
	d_transporte transporte;
	d_lazer lazer;
	
	extra extra;
	trabalho trabalho;
	
	float soma_receita = 0;
	float soma_despesa = 0;
	char r = 'n';
	char r2 = 's';
	int mes, ano;
	int cont = 0;
	
	char* arquivo_base_financeiro = "dados_financeiros.txt";

    RegistroFinanceiro* registros = NULL;
    int num_registros = 0;
	
	
	j = manipulacao_arquivos("usuario.txt", "r");
	
	//cadastrando usuario, se necessario
	if(j == NULL){
		printf("Como deseja ser chamado: ");
		scanf("%s", &nome);
		fclose(j);
		j = manipulacao_arquivos("usuario.txt", "a+");
		fprintf(j, "%s", nome);
		fclose(j);
	}
	j = manipulacao_arquivos("usuario.txt", "r+");
	fscanf(j, "%s", &nome);
	printf("Ola, %s\n\n", nome);
	
	fclose(j);
	
	//Menu e opcoes, com suas respectivas respostas
	while(r2 == 's'){
		printf("Voce deseja inserir/visualizar os dados de que mes: ");
		scanf("%d", &mes);
		printf("E de qual ano: ");
		scanf("%d", &ano);
		
		while(r == 'n'){
			printf("[1] - Inserir Despesas\n[2] - Inserir Receitas\n[3] - Analise Financeira\n[4] - Exibir Saldo Final\n");
			printf("Escolha: ");
			scanf("%d", &opcao);
			fflush(stdin);
			
			if(opcao == 1){
				printf("\nComo voce classificaria sua despesa: \n");
				printf("[1] - Alimentacao\n[2] - Moradia\n[3] - Saude\n[4] - Transporte\n[5] - Lazer\n\n");
				printf("Escolha: ");
				scanf("%d", &opcao);
				if(opcao == 1){
					printf("Qual foi o valor: R$");
					scanf("%f", &alimentacao.valor);
					fflush(stdin);
					soma_despesa += alimentacao.valor;

					
				}
				else if(opcao == 2){
					printf("Qual foi o valor: R$");
					scanf("%f", &moradia.valor);
					fflush(stdin);
					soma_despesa += moradia.valor;
	
				}
				else if(opcao == 3){
					printf("Qual foi o valor: R$");
					scanf("%f", &saude.valor);
					fflush(stdin);
					soma_despesa += saude.valor;

				}
				else if(opcao == 4){
					printf("Qual foi o valor: R$");
					scanf("%f", &transporte.valor);
					fflush(stdin);
					soma_despesa+= transporte.valor;

				}
				else if(opcao == 5){
					printf("Qual foi o valor: R$");
					scanf("%f", &lazer.valor);
					fflush(stdin);

					soma_despesa+= lazer.valor;

				}
			}else if(opcao == 2){
				printf("\nComo voce classificaria sua receita: \n");
				printf("[1] - Trabalho\n[2] - Extra\n\n");
				printf("Escolha: ");
				scanf("%d", &opcao);
				if(opcao == 1){
					printf("Qual foi o valor: R$");
					scanf("%f", &trabalho.renda);
					soma_receita+= trabalho.renda;

				}
				else if(opcao == 2){
					printf("Qual foi o valor: R$");
					scanf("%f", &extra.renda);
					soma_receita+=extra.renda;
					
				}
			
			}else if(opcao == 3){
				fflush(stdin);
				registros = carregar_registros_financeiros(arquivo_base_financeiro, &num_registros);

				if (registros == NULL && num_registros == 0) {
					fprintf(stderr, "ERRO: Nao foi possivel carregar os registros financeiros.\n");
					fprintf(stderr, "Verifique se o arquivo '%s' existe e esta formatado corretamente.\n", arquivo_base_financeiro);
					return 1;
				}
				
				if (num_registros == 0) {
					printf("O arquivo de dados esta vazio. Nada a processar.\n");
					liberar_registros_financeiros(registros, num_registros);
					return 0;
				}
				classificar_registros_financeiros(registros, num_registros);
				printf("=> Classificacao concluida.\n");

				apresentar_analise_financeira(registros, num_registros);
				liberar_registros_financeiros(registros, num_registros);
				printf("=> Memoria liberada.\n");
				
			}else if(opcao == 4){
				int mes_ini, ano_ini;
				int mes_fim, ano_fim;
				int contador_Meses=0;

				printf("\n Insira o mes inicial do periodo desejado para calculo do saldo: ");
				scanf("%d", &mes_ini);
				fflush(stdin);

				printf("\n Insira o ano inicial do periodo desejado para calculo do saldo: ");
				scanf("%d", &ano_ini);
				fflush(stdin);

				printf("\n Insira o mês final do periodo desejado para calculo do saldo: ");
				scanf("%d", &mes_fim);
				fflush(stdin);

				printf("\n Insira o ano final do periodo desejado para calculo do saldo: ");
				scanf("%d", &ano_fim);
				fflush(stdin);


				calculaSaldoPeriodo(arquivo_base_financeiro, mes_ini, ano_ini, mes_fim, ano_fim);

			}
			
			
			else{
				printf("Opcao nao encontrada.");
			}
			
			fflush(stdin);
			printf("\n\n");
			printf("Deseja encerrar a insercao/visualizacao do fluxo de caixa desse mes[s/n] : ");
			scanf("%c", &r);
		
			
		}
		fflush(stdin);
		
		j = manipulacao_arquivos(arquivo_base_financeiro, "a+");
		fprintf(j, "%d %d %.2f %.2f\n", mes, ano, soma_receita, soma_despesa);
		
		fclose(j);
		
		printf("Deseja inserir/visualizar os dados de mais algum outro mes[s/n]: ");
		scanf("%c", &r2);
		fflush(stdin);
		if(r2 == 's'){
			r = 'n';
			soma_receita = 0;
			soma_despesa = 0;
		}
		
	}
	
	return 0;
}




