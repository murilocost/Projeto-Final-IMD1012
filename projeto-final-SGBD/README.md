# Projeto-Final-ITP
Sistema de Gerenciamento de Banco de Dados (SGBD) da matéria de Introdução às Técnicas de Programação (ITP), UFRN.

## Funcionalidades Implementadas

1. **Criação de Tabela:**
   - Solicita o nome da tabela, número de colunas e o nome da chave primária.
   - Verifica a unicidade do nome da tabela e da chave primária.
   - Permite a definição do tipo de cada coluna.

2. **Listagem de Tabelas:**
   - Apresenta os nomes das tabelas presentes no banco de dados.

3. **Adição de Linhas à Tabela:**
   - Permite a inserção de uma ou mais linhas em uma tabela existente.
   - Verifica se os valores inseridos correspondem aos tipos definidos para cada coluna.
   - Garante a unicidade da chave primária.

4. **Listagem de Dados da Tabela:**
   - Exibe as colunas e linhas de uma tabela específica.
   - Indica o tipo de cada coluna.

5. **Remoção de Linha da Tabela:**
   - Solicita o valor da chave primária para identificar e apagar a linha correspondente.

6. **Remoção de Tabela:**
   - Remove completamente uma tabela, liberando seu espaço.

## Funcionalidade Extra Implementada

- **Salvamento e Carregamento de Dados:**
   - Implementadas funções para salvar e carregar o estado do banco de dados em um arquivo.
   - O arquivo `bancodados.itp` é utilizado para armazenar os dados persistentemente.

## Uso da Aplicação

1. Execute o programa.

    Para compilar e executar o programa, utilize a linha de comando abaixo:

gcc main.c modules/impl/* -I modules/include

Após a compilação bem-sucedida, um arquivo executável chamado `a.exe` será gerado.

Para executar o programa, utilize o seguinte comando:
./a

2. Escolha a operação desejada digitando o número correspondente.
3. Siga as instruções apresentadas na tela para completar a operação.

## Não foi possível implementar a modularização do programa

## Reflexão sobre o Desenvolvimento

1. **Tratamento de Erros Aprimorado:**
   - Implementaria um sistema robusto de tratamento de erros, utilizando exceções ou retornos de erro mais estruturados. Isso melhoraria a capacidade de diagnóstico de problemas e tornaria o programa mais resiliente.

2. **Utilização de Bibliotecas de Terceiros:**
   - Exploraria o uso de bibliotecas de terceiros para tarefas específicas, como detecção de tipos. Isso poderia simplificar o código e aproveitar soluções testadas pela comunidade.

Autores do Projeto:
Emilly Miller Moreira e Murilo Antonio Lima Da Costa.

### Emilly Miller

- Implementação das funções relacionadas à manipulação e verificação de arquivos (`salvar_arquivos` e `carregar_arquivos`).
- Desenvolvimento das funções para verificar a unicidade da chave primária, da coluna e do nome da tabela (`verificarChavePrimaria`, `verificarNomeColuna` e `verificarNomeTabela`).
- Participação no desenvolvimento da interface do usuário (`interface`).

### Murilo Antonio

- Implementação das funções relacionadas à criação e manipulação de tabelas (`criaTabela`, `apagaTabela`).
- Desenvolvimento das funções para listar tabelas e seus dados (`listarTabelas`, `listarDadosTabela`).
- Implementação das funções para criar e apagar linhas em uma tabela (`criaLinha`, `apagaLinhaTabela`).

   Juntos fizemos a implementação de funções auxiliares, como a detecção de tipos de dados (`detectarTipos`) e na definição da estrutura global do banco de dados.
