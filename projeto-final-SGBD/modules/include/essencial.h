#ifndef ESSENCIAL_H
#define ESSENCIAL_H

// Variáveis Globais
char nomeTabela[100];
char nomeColuna[100];


typedef struct {
    char nome[100];
    int numColunas;
    int tipos[30];
    char colunas[30][30];
    char linhas[30][30][100];
}Tabela;

typedef struct {
    Tabela tabelas[30];
} bancoDados;

// Estrutura global
bancoDados banco;

void salvar_arquivos();

void carregar_arquivos();

int verificarChavePrimaria(int indice, char* valor);

int VerificarNomeColuna(int indice, char* nomeColuna);

int verificarNomeTabela(char* nomeTabela);

int pegarSlotVazio();

int pegarProxLinhaVazia(int indice);

char* tipoVariavel(int tipo);

int detectarTiposs(char* string, int tipo);

#endif