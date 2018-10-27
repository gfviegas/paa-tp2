/**
 * Gerencia e chama as funções relacionadas ao sudoku, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#include "interfaceS.h"

// Menu Principal para interface do Sudoku
void _sudokuMenu(int analysisMode) {
    system("clear"); // Limpa o terminal
    int **matrix = NULL;
    int arquivo;

    printLine();
    cprintf(GREEN, "Deseja escrever um sudoku ou resolver um que nós já possuímos em nossos arquivos ?\n");
    cprintf(GREEN, "1 - Escrever\n");
    cprintf(GREEN, "2 - Arquivos\n");
    cprintf(GREEN, "3 - Cancelar\n");

    prePrompt(); // Exibe uma seta amarela para representar a escolha do usuário
    scanf("%d", &arquivo);

    switch (arquivo) {
        case 1:
            readSudoku(&matrix); // Usuário escrve o sudoku no terminal
            break;
        case 2:
            _printAllSudoku(&matrix); // Exibe todos os sudokus
            break;
        case 3:
            return printHeader(analysisMode);
        default:
            cprintf(RED, "\n Digite 1 ou 2, não temos tantas opções\n\n");
            return _sudokuMenu(analysisMode);
    }

    _showResultSudoku(&matrix, analysisMode); // Após o usuario ter determinado o seu sudoku exibe o resultado
}

// Lê do usuário uma das opções de sudoku disponíveis pelo sistema
void _readSudokuChoice(int *sudokuChoice) {
    cprintf(GREEN, "Escolha um dos sudokus de 1 a 4 !\n");
    prePrompt();
    scanf("%d", sudokuChoice);
}

// Exibe todos os sudokus que temos de arquivo
void _printAllSudoku(int ***matrix) {
    char *sudokus [] = {"sudoku1.txt", "sudoku2.txt", "sudokuResolvido.txt", "sudokuBranco.txt"};
    int sudokuChoice = -1;

    printLine();
    cprintf(GREEN, "Escolha um dos nossos excelentes sudokus\n");

    for (int i = 0; i < 4; i++) {
        cprintf(GREEN, "Sudoku #%d: \n", i+1);
        loadSudoku(matrix, sudokus[i]);
        printSudoku(*matrix);
        printLine();
    }

    _readSudokuChoice(&sudokuChoice);
    while (sudokuChoice < 1 || sudokuChoice > 4) {
        cprintf(RED, "\nNão temos tantos sudokus, escolha um de 1 a 4\n");
        _readSudokuChoice(&sudokuChoice);
    }

    loadSudoku(matrix, sudokus[sudokuChoice - 1]);
}

// Resolve e exibe um sudokus
void _showResultSudoku (int ***matrix, int analysisMode) {
    int **solutionMatrix = NULL;
    int calls = 0;
    int choice;

    if (!solveSudoku(*matrix, &calls, &solutionMatrix)) {
        cprintf(RED, "Sudoku não possui solução!");
        return _sudokuMenu(analysisMode);
    }

    cprintf(MAGENTA, "\nExibindo o sudoku solucionado!\n");
    printLine();
    printSolutionSudoku(*matrix, solutionMatrix);
    printLine();

    if (analysisMode) {
        printLine();
        cprintf(RED, "\n[STATS] Foram feitas %d chamadas!\n", calls);
    }

    cprintf(GREEN, "\nDigite 1 para resolver outro sudoku ou 2 para voltar\n");
    prePrompt();
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            return _sudokuMenu(analysisMode);
        case 2:
            return printHeader(analysisMode);
        default:
            printLine();
            cprintf(RED, "Interrompendo execução do programa...\n");
    }

}
