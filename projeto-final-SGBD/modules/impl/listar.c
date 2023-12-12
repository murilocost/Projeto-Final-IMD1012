#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "essencial.h"
#include "listar.h"

void listarTabelas(){
    printf("------------ Tabelas ------------\n");
    for(int i = 0; i < 10; i++){
        if(strlen(banco.tabelas[i].nome) != 0) printf("- %s -\n", banco.tabelas[i].nome);
		// Verifica os nomes no array, imprindo eles caso não tenha o valor inicializado
    }
    salvar_arquivos();
    printf("\nEssas são as tabelas presentes.\n");
}

void listarDadosTabela(){
    salvar_arquivos();

    int indice = -1; //só pra entrar no WHILE

    printf("------------ Listando valores ------------\n");

    while(indice == -1){
        printf("Digite o nome da tabela: ");
        scanf("%s", nomeTabela);
        indice = verificarNomeTabela(nomeTabela);
    }

    // Printf das colunas
    printf("Colunas: ");
    for(int i = 0; i < banco.tabelas[indice].numColunas; i++){
        if(banco.tabelas[indice].colunas[i]){
            if(i == 0) printf("%s* [PK (Int)]\n", banco.tabelas[indice].colunas[i]);
            else printf("%s (%s) // ", banco.tabelas[indice].colunas[i], tipoVariavel(banco.tabelas[indice].tipos[i]));
        }
    }

    // Printf das linhas
    for(int i = 0; i < 30; i++){
        if(strlen(banco.tabelas[indice].linhas[i][0]) != 0) printf("\nLinha %i: ", i + 1);
        for(int j = 0; j < banco.tabelas[indice].numColunas; j++){ // colunas
            if(strlen(banco.tabelas[indice].linhas[i][0]) != 0) printf("%s // ", banco.tabelas[indice].linhas[i][j]);
        }
    }
}

