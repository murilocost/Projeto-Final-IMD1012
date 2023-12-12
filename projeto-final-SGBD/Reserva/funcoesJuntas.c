#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Funções para guardar aquivos e verificação
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

struct bancoDados {
    Tabela tabelas[30];
};

// Estrutura global
struct bancoDados banco;

// ABERTURA DO ARQUIVO

void salvar_arquivos(){
    FILE* arquivo = fopen ("data/database.itp", "w");

    if (arquivo == NULL){
        printf("ERROR! Erro %s ao carregar os arquivos.", strerror(errno));
        return;
    }

    // Recupera dados e os coloca no banco

    fread(&banco, sizeof(struct bancoDados), 1, arquivo);
    fclose (arquivo);
}

void carregar_arquivos(){
    FILE* arquivo = fopen("data/database.txt", "r");
    if (arquivo == NULL){
        printf("ERROR! Erro %s ao abrir Banco de Dados.\n", strerror(errno));
        exit(1);
    }

    // Gravar no arquivo

    fwrite(&banco, sizeof(struct bancoDados), 1, arquivo);

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


// FUNÇÕES DO MENU


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

void interface(){
    printf("\n/////////////////////////////////////////////");
    printf("\n/ 1- Criar Tabela                           /");
    printf("\n/ 2- Listar Tabelas                         /");
    printf("\n/ 3- Adicionar valor a tabela               /");
    printf("\n/ 4- Listar Dados da tabela                 /");
    printf("\n/ 5- Apagar linha da tabela                 /");
    printf("\n/ 6- Apagar tabela                          /");
    printf("\n/ 0- Sair                                   /");     
    printf("\n/////////////////////////////////////////////\n\n");

}