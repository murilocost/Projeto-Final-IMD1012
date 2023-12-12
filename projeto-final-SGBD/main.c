#include "apagar.h"
#include "essencial.h"
#include "criar.h"
#include "listar.h"

#include <stdio.h>

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

int main(int argc, char const *argv[]){
  carregar_arquivos();
 
  printf("__________________________________\n");
  printf("| Sistema                        |\n");
  printf("|     Gerenciador de             |\n");
  printf("|        Banco de Dados          |\n");
  printf("|                                |\n");
  printf("|                            ITP |\n");
  printf("__________________________________\n");
 
  int op = 1;

  while (op != 0){
    fflush(stdin);

    interface();

    printf("\nOpção desejada: ");
    scanf("%d", &op);

    fflush(stdin); // Limpa do buffer de entrada (teclado)

    switch (op) {
    case 1:
      criaTabela();
      break;
    case 2:
      listarTabelas();
      break;
    case 3:
      criaLinha();
      break;
    case 4:
      listarDadosTabela();
      break;
    case 5:
      apagaLinhaTabela();
      break;
    case 6:
      apagaTabela();
      break;
    case 0:
      printf("Saindo...\n");
      salvar_arquivos();
      break;
    default:
      printf("Opçăo inválida! Selecione uma das opçőes:\n");
      interface();
      break;
    }
  }

  return 0;

}
