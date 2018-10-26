/**
 * Gerencia e chama as funções relacionadas ao sudoku, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 */

#include "interfaceS.h"

// Menu Principal para interface do Sudoku
void _sudokuMenu (int analysisMode) {
    system("clear");//limpa o terminal
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

// Exibe todos os sudokus que temos de arquivo
void _printAllSudoku (int ***matrix) {
    char *sudokus [] = {"sudoku1.txt", "sudoku2.txt", "sudokuResolvido.txt", "sudokuBranco.txt"};
    int escolhaSudoku;
    int i;

    printLine();
    cprintf(GREEN, "Escolha um dos nossos excelentes sudokus\n");

    for(i = 0; i < 4; i++) {
        cprintf(RED, "Pressione ENTER para ver o próximo sudoku!\n");
        getchar();
        system("clear");
        cprintf(GREEN, "%d -\n", i+1);
        loadSudoku(matrix, sudokus[i]);
        printSudoku(*matrix);
        printLine();

    }
    cprintf(GREEN, "Escolha um dos sudokus de 1 a 4 !\n");
    prePrompt();
    scanf("%d", &escolhaSudoku);
    switch (escolhaSudoku) {
        case 1:
            loadSudoku(matrix,sudokus[0]);
            break;
        case 2:
            loadSudoku(matrix, sudokus[1]);
            break;
        case 3:
            loadSudoku(matrix, sudokus[2]);
            break;
        case 4:
            loadSudoku(matrix, sudokus[3]);
            break;
        default:
            cprintf(RED, "\nNão temos tantos sudokus, escolha um de 1 a 4\n");
            return _printAllSudoku(matrix);
    }
}

// Resolve e exibe um sudokus
void _showResultSudoku (int ***matrix, int analysisMode) {
    int **solutionMatrix = NULL;
    int numTentativas = 0;
    int escolha;
    cprintf(MAGENTA, "\nExibindo o sudoku solucionado!\n");
    printLine();
    solveSudoku(*matrix, &numTentativas, &solutionMatrix);
    printSolutionSudoku(*matrix, solutionMatrix);
    printLine();
    if(analysisMode) {
        printLine();
        cprintf(RED, "\nForam feitas %d comparações!\n", numTentativas);
    }
    cprintf(GREEN, "\nDigite 1 para resolver outro sudoku ou 2 para voltar\n");
    prePrompt();
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            return _sudokuMenu(analysisMode);
        case 2:
            return printHeader(analysisMode);
        default:
            printLine();
            cprintf(RED, "Interrompendo execução do programa...\n");
    }

}
