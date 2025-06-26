#include <stdio.h>
#include "manipulacao.h"

FILE *manipulacao_arquivos(char nome_arquivo[25], char tipo_abertura[5]){
    FILE *p;
    p = fopen(nome_arquivo, tipo_abertura);
    if(p == NULL){
        //printf("Erro na criacao");
    }else{
//        fclose(p);
        //printf("Criado com sucesso");
    }
    return p;

}
