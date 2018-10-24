/**
 * Gerencia e chama as funções relacionadas ao caça palavras, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 */

#include "interfaceWH.h"

// Imprime a matriz carregada, em uma tabela estilizada
void _printCurrentMatrix(char **matrix, int lines, int columns) {
    if (matrix == NULL) return cprintf(YELLOW, "A matriz atual está vazia! \n");
    printMatrix(&matrix, lines, columns, "Caça-Palavras:");
}

// Lê do usuário uma palavra a ser caçada e acha suas ocorrências no caça palavras.
void _searchWord(char **matrix, int lines, int columns, int analysisMode) {
    char word[WORD_MAX_LENGTH];
    cprintf(GREEN, "\n\nDigite uma palavra para ser buscada: \n");
    prePrompt();
    scanf("%s", word);

    search(&matrix, word, lines, columns, analysisMode);

    // Após a execução, espera o usuário interagir, para dar tempo dele ver os resultados
    cprintf(RED, "\nDigite enter para continuar...");
    return (getchar() && getchar());
}

// Limpa a tela e pede uma ação ao usuário: carregar um arquivo, buscar uma palavra ou voltar ao menu inicial
void _promptAction(char **matrix, int *lines, int *columns, int analysisMode) {
    int choice;

    system("clear");
    printLine();
    _printCurrentMatrix(matrix, *lines, *columns);

    printf("\n\n");
    cprintf(GREEN, "Escolha uma ação: \n\n");
    cprintf(GREEN, "1 - Carregar arquivo de caça-palavras\n");
    cprintf(GREEN, "2 - Buscar palavra\n");
    cprintf(GREEN, "3 - Sair\n");

    prePrompt();
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            loadMatrix(&matrix, lines, columns);
            break;
        case 2:
            _searchWord(matrix, *lines, *columns, analysisMode);
            break;
        case 3:
            return printHeader(analysisMode);
        default:
            cprintf(RED, "Opção inválida!\n");
            break;
    }

    return _promptAction(matrix, lines, columns, analysisMode);
}

// Inicializa o ponteiro da matriz a ser utilizada, e aloca na memória os inteiros que salva linhas e colunas
void _wordHuntMenu(int analysisMode) {
    char **matrix = NULL;
    int lines, columns;

    _promptAction(matrix, &lines, &columns, analysisMode);
}
