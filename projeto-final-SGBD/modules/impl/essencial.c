#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "essencial.h"

// Funções para guardar aquivos e verificação
// Variáveis Globais
char nomeTabela[100];
char nomeColuna[100];

// Estrutura global
bancoDados banco;

void salvar_arquivos(){
    FILE* arquivo = fopen ("data/bancodados.itp", "w");

    if (arquivo == NULL){
        printf("ERROR! Erro %s ao carregar os arquivos.", strerror(errno));
        return;
    }

    // Recupera dados e os coloca no banco

    fread(&banco, sizeof(bancoDados), 1, arquivo);
    fclose (arquivo);
}

void carregar_arquivos(){
    FILE* arquivo = fopen("data/bancodados.txt", "r");
    if (arquivo == NULL){
        printf("ERROR! Erro %s ao abrir Banco de Dados.\n", strerror(errno));
        exit(1);
    }

    // Gravar no arquivo

    fwrite(&banco, sizeof(bancoDados), 1, arquivo);

    if(fwrite == 0) printf("Erro ao salvar\n");
    fclose (arquivo);

}

// Verificação de unicidade de chave primária
int verificarChavePrimaria(int indice, char *valor){
    for(int i = 0; i < 30; i++){
        if(strcmp(banco.tabelas[indice].linhas[i][0], valor) == 0) return 1;
    }
    return 0;
}

// Verificação unicidade da coluna
int verificarNomeColuna(int indice, char *nomeColuna){
    for(int i = 0; i < 30; i++){
        if(strcmp(banco.tabelas[indice].colunas[i], nomeColuna) == 0) return 1;
    }
    return 0;
}

// Verificação unicidade da tabela
int verificarNomeTabela(char * nomeTabela){
    for(int i = 0; i < 30; i++){
        if(strcmp(banco.tabelas[i].nome, nomeTabela) == 0) return i;
    }
    return -1;
}

// pegar proximo espaço vazio do banco | pegar próxima tabela/linha vazia (array)
int pegarSlotVazio(){ // obter a index do próximo espaço livre
    for(int i = 0; i < 30; i++){
        if(banco.tabelas[i].numColunas == 0) return i;
    }
    return -1;
}

int pegarProxLinhaVazia(int indice){
    for(int i = 0; i < 10; i++){
        if(strlen(banco.tabelas[indice].linhas[i][0]) == 0) return i;
    }
    return 29;
}

char * tipos[] = {"Int", "Char", "Float", "Double", "String"};
char * tipoVariavel(int tipo){
    return tipos[tipo] ? tipos[tipo] : "Tipo inválido";
}

int detectarTipos(char * string, int tipo){
    int tiposLista[5];
    tiposLista[4] = 1; // Convertendo para String
    if(strlen(string) == 1) tiposLista[1] = 1; // Convertendo para Character
    if(strtof(string, NULL) != 0 && strchr(string, '.')) tiposLista[2] = 1; // Convertendo para Float
    if(strtod(string, NULL) != 0 && strchr(string, '.')) tiposLista[3] = 1; // Conversão para Double
    if(strtol(string, NULL, 10) != 0 && tiposLista[2] != 1 && tiposLista[3] != 1) tiposLista[0] = 1; // Conversão para Inteiro (long)
    
    // A entrada pode ser dois tipos diferentes, returnando um array
    return tiposLista[tipo];
}