#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "essencial.h"
#include "apagar.h"


void apagaTabela(){
    salvar_arquivos();
    Tabela aux;
    int indice = -1;

    while(indice == -1){
        printf("Digite o nome da tabela: ");
        scanf("%s", nomeTabela);

        while(verificarNomeTabela(nomeTabela) == -1){
            printf("Essa tabela não existe!\n");
            printf("Digite o nome da tabela novamente: ");
            scanf("%s", nomeTabela);
        }
        indice = verificarNomeTabela(nomeTabela); // Verifica a existência da tabela, retornando um num != -1
    }

    memset(&banco.tabelas[indice], 0, sizeof(aux)); // Anula todos os dados da tabela referida

    printf("Tabela apagada!");
}

void apagaLinhaTabela(){
    salvar_arquivos();

    char *valorPrimaryKey = malloc(20 * sizeof(char));
    int indice = -1;

    while(indice == -1){
        printf("\nDigite o nome da tabela: ");
        scanf("%s", nomeTabela);

        while(verificarNomeTabela(nomeTabela) == -1){
            printf("Nome de tabela inexistente!\n");
            printf("Digite o nome da tabela: ");
            scanf("%s", nomeTabela);
        }

        indice = verificarNomeTabela(nomeTabela);
        // Verificando se a tabela já existe, retornando o indice da tabela no array, caso contrário, ficará no loop
    }

    printf("Digite o valor de %s para apagar: ", banco.tabelas[indice].colunas[0]);
    scanf("%s", valorPrimaryKey);
    // Verifica a linha com base na sua chave primária, para apaga-la

    for(int i = 0; i < 30; i++){
        if(strcmp(banco.tabelas[indice].linhas[i][0], valorPrimaryKey) == 0){
            memset(&banco.tabelas[indice].linhas[i], 0, sizeof(30 * 30 * 30));
            break;
        }
    }

    printf("\nLinha apagada com sucesso!\n");
}