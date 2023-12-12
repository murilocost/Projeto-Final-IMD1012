#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "essencial.h"
#include "criar.h"

void criaTabela(){
    int qntColunas, tipo, indice = pegarSlotVazio();

    printf("Digite o nome da tabela: ");
    scanf("%s", nomeTabela);

    while(verificarNomeTabela(nomeTabela) != -1){
        printf("Nome de tabela já existente!\n");
        printf("Digite o nome da tabela novamente: ");
        scanf("%s", nomeTabela);
    }

    strcpy(banco.tabelas[indice].nome, nomeTabela);
    printf("Digite o número de colunas: ");
    scanf("%i", &banco.tabelas[indice].numColunas);

    // Não permite que a quantidade de colunas seja menor que 1
    while(banco.tabelas[indice].numColunas < 1){
        printf("Número inválido de colunas! Insira novamente: ");
        scanf("%i", &banco.tabelas[indice].numColunas);
    }

    printf("Digite o nome da chave primaria: ");
    scanf("%s", nomeColuna);
    strcpy(banco.tabelas[indice].colunas[0], nomeColuna);
    banco.tabelas[indice].tipos[0] = 1;

    fflush(stdin); // Limpa o buffer da entrada

    for (int i = 1; i < banco.tabelas[indice].numColunas; i++) {
        printf("Digite o nome da coluna %i: ", i);
        scanf("%s", nomeColuna);

        while(verificarNomeColuna(indice, nomeColuna) == 1){
            printf("Nome de coluna já existente!\n");
            printf("Digite o nome da coluna novamente: ");
            scanf("%s", nomeColuna);
        }
        strcpy(banco.tabelas[indice].colunas[i], nomeColuna);

        printf("Digite o número do tipo da coluna:\n"
               "0 - INT\n"
               "1 - CHAR\n"
               "2 - FLOAT\n"
               "3 - DOUBLE\n"
               "4 - STRING\n");
        scanf("%d", &tipo);
        while(tipo < 0 || tipo > 4){
            printf("Tipo inválido! Digite novamente: ");
            scanf("%d", &tipo);
        }
        banco.tabelas[indice].tipos[i] = tipo;
    }


    salvar_arquivos(); // Realiza o save do arquivo
    printf("\nTabela criada!\n"); // Constata e confirma a criação da tabela e seu save
}

void criaLinha(){
    salvar_arquivos();

    char* valorColuna = malloc(20 * sizeof(char));
    int indice = -1;
    int numLinhas = 1;

    while(indice == -1){
        printf("\nDigite o nome da tabela: ");
        scanf("%s", nomeTabela);
        indice = verificarNomeTabela(nomeTabela);
        // Caso a tabela exista, sairá do loop com o indice igual ao indice na tabela no array, senão fica no loop caso o usuário digite o nome de uma tabela não existente
    }

    int linhaLivre = pegarProxLinhaVazia(indice);
    printf("Quantas linhas deseja inserir? ");
    scanf("%i", &numLinhas);

    while(numLinhas < 1){
        printf("O minímo é uma linha! Insira novamente a quantidade: ");
        scanf("%i", &numLinhas);
    }
    
    for(int i = linhaLivre; i < linhaLivre + numLinhas; i++){
        printf("///////////// Linha %i /////////////\n", i);

        for(int j = 0; j < banco.tabelas[indice].numColunas; j++){
            printf("Digite os dados da coluna %s (%s)- ", banco.tabelas[indice].colunas[j], tipoVariavel(banco.tabelas[indice].tipos[j]));
            scanf("%s", valorColuna);

            while(detectarTipos(valorColuna, banco.tabelas[indice].tipos[j]) != 1){
                printf("Você inseriu um valor diferente do tipo! Tipo válido: %s\nInsira novamente: ", tipoVariavel(banco.tabelas[indice].tipos[j]));
                scanf("%s", valorColuna);
            }

            if(j == 0){
                while(verificarChavePrimaria(indice, valorColuna) == 1){
                    printf("Valor duplicado! Insira outro valor: ");
                    scanf("%s", valorColuna);
                }
            }

            strcpy(banco.tabelas[indice].linhas[i][j], valorColuna);
        }
    }
    printf("\nLinha(s) inserida(s) com sucesso!");
}
