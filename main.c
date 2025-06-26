#include <stdio.h>
#include <stdlib.h>
#include "manipulacao.h"
#include "usuario.h"


#include "classificacao_financeira.h"
#include "estatisticas.h"

#include "structs.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
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
	
	//		Arthur
	const char* nome_do_arquivo = "dados_financeiros.txt";

    RegistroFinanceiro* registros = NULL;
    int num_registros = 0;
	//
	
	
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
	while(r2 == 's'){
		printf("Voce deseja inserir/visualizar os dados de que mes: ");
		scanf("%d", &mes);
		printf("E de qual ano: ");
		scanf("%d", &ano);
		
		while(r == 'n'){
			printf("[1] - Visualizar saldo\n[2] - Inserir Despesas\n[3] - Inserir Receitas\n[4] - Analise Financeira\n");
			printf("Escolha: ");
			scanf("%d", &opcao);
			
			if(opcao == 1){
				//visualizar o saldo
			}else if(opcao == 2){
				printf("\nComo voce classificaria sua despesa: \n");
				printf("[1] - Alimentacao\n[2] - Moradia\n[3] - Saude\n[4] - Transporte\n[5] - Lazer\n\n");
				printf("Escolha: ");
				scanf("%d", &opcao);
				if(opcao == 1){
					printf("Qual foi o valor: R$");
					scanf("%f", &alimentacao.valor);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &alimentacao.data[0], &alimentacao.data[1], &alimentacao.data[2]);
					soma_despesa += alimentacao.valor;
					//j = manipulacao_arquivos("despesa.txt", "a+");
				//	fprintf(j, "%.2f %d %d %d\n", alimentacao.valor, alimentacao.data[0], alimentacao.data[1], alimentacao.data[2]);
				//	fclose(j);
					
				}
				else if(opcao == 2){
					printf("Qual foi o valor: R$");
					scanf("%f", &moradia.valor);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &moradia.data[0], &moradia.data[1], &moradia.data[2]);
					soma_despesa += moradia.valor;
					//j = manipulacao_arquivos("despesa.txt", "a+");
					//fprintf(j, "%.2f %d %d %d\n", moradia.valor, moradia.data[0], moradia.data[1], moradia.data[2]);
					//fclose(j);
				}
				else if(opcao == 3){
					printf("Qual foi o valor: R$");
					scanf("%f", &saude.valor);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &saude.data[0], &saude.data[1], &saude.data[2]);
					soma_despesa += saude.valor;
					//j = manipulacao_arquivos("despesa.txt", "a+");
					//fprintf(j, "%.2f %d %d %d\n", saude.valor, saude.data[0], saude.data[1], saude.data[2]);
					//fclose(j);
				}
				else if(opcao == 4){
					printf("Qual foi o valor: R$");
					scanf("%f", &transporte.valor);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &transporte.data[0], &transporte.data[1], &transporte.data[2]);
					soma_despesa+= transporte.valor;
					
					//j = manipulacao_arquivos("despesa.txt", "a+");
					//fprintf(j, "%.2f %d %d %d\n", transporte.valor, transporte.data[0], transporte.data[1], transporte.data[2]);
					//fclose(j);
				}
				else if(opcao == 5){
					printf("Qual foi o valor: R$");
					scanf("%f", &lazer.valor);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &lazer.data[0], &lazer.data[1], &lazer.data[2]);
					soma_despesa+= lazer.valor;
					
					//j = manipulacao_arquivos("despesa.txt", "a+");
					//fprintf(j, "%.2f %d %d %d\n", lazer.valor, lazer.data[0], lazer.data[1], lazer.data[2]);
					//fclose(j);
				}
			}else if(opcao == 3){
				printf("\nComo voce classificaria sua receita: \n");
				printf("[1] - Trabalho\n[2] - Extra\n\n");
				printf("Escolha: ");
				scanf("%d", &opcao);
				if(opcao == 1){
					printf("Qual foi o valor: R$");
					scanf("%f", &trabalho.renda);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &trabalho.data[0], &trabalho.data[1], &trabalho.data[2]);
					soma_receita+= trabalho.renda;
					
					//j = manipulacao_arquivos("receita.txt", "a+");
					//fprintf(j, "%.2f %d %d %d\n", trabalho.renda, trabalho.data[0], trabalho.data[1], trabalho.data[2]);
					//fclose(j);
				}
				else if(opcao == 2){
					printf("Qual foi o valor: R$");
					scanf("%f", &extra.renda);
				//	printf("Qual foi a data(dd/mm/aaaa): ");
				//	scanf("%d/%d/%d", &extra.data[0], &extra.data[1], &extra.data[2]);
					soma_receita+=extra.renda;
					
					//j = manipulacao_arquivos("receita.txt", "a+");
					//fprintf(j, "%.2f %d %d %d\n", extra.renda, extra.data[0], extra.data[1], extra.data[2]);
					//fclose(j);
				}
			
			}else if(opcao == 4){
				fflush(stdin);
	
				j = manipulacao_arquivos("dados_financeiros.txt", "a+");
				fprintf(j, "%d %d %.2f %.2f\n", mes, ano, soma_receita, soma_despesa);
				
				fclose(j);
				registros = carregar_registros_financeiros(nome_do_arquivo, &num_registros);

				if (registros == NULL && num_registros == 0) {
					fprintf(stderr, "ERRO: Nao foi possivel carregar os registros financeiros.\n");
					fprintf(stderr, "Verifique se o arquivo '%s' existe e esta formatado corretamente.\n", nome_do_arquivo);
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
				printf("=> Memoria liberada. Programa encerrado com sucesso.\n");
				

				
			}
			
			else{
				printf("Opcao nao encontrada.");
			}
			
			fflush(stdin);
			printf("\n\n\n");
			printf("Deseja encerrar a insercao/visualizacao do fluxo de caixa desse mes[s/n] : ");
			scanf("%c", &r);
		
			
		}
		
		printf("Deseja inserir/visualizar os dados de mais algum outro mes[s/n]: ");
		scanf("%c", &r2);
		if(r2 == 's'){
			r = 'n';
			soma_receita = 0;
			soma_despesa = 0;
		}
		
		
	}
	
	return 0;
}




