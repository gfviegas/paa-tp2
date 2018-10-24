//
//  interfaceS.c
//  backtracking
//
//  Created by Gustavo Viegas on 24/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "interfaceS.h"

void _sudokuMenu (int analysisMode) {
    system("clear");
    int **matrix = NULL;
    int arquivo;
    
    printLine();
    cprintf(GREEN, "Deseja escrever um sudoku ou resolver um que nós já possuímos em nossos arquivos ?\n");
    cprintf(GREEN, "1 - Escrever\n");
    cprintf(GREEN, "2 - Arquivos\n");
    cprintf(GREEN, "3 - Cancelar\n");
    
    prePrompt();
    scanf("%d", &arquivo);
    
    switch (arquivo) {
        case 1:
            readSudoku(&matrix);
            break;
        case 2:
            _printAllSudoku(&matrix);
            break;
        case 3:
            return printHeader(analysisMode);
        default:
            cprintf(RED, "\n Digite 1 ou 2, não temos tantas opções\n\n");
            return _sudokuMenu(analysisMode);
    }

    _showResultSudoku(&matrix, analysisMode);
}

void _printAllSudoku (int ***matrix) {
    char sudoku1[20], sudoku2[20], sudokuResolvido[30], sudokuBranco[30];
    int escolhaSudoku;
    strcpy(sudoku1, "sudoku1.txt");
    strcpy(sudoku2, "sudoku2.txt");
    strcpy(sudokuResolvido, "sudokuResolvido.txt");
    strcpy(sudokuBranco, "sudokuBranco.txt");
    printLine();
    cprintf(GREEN, "Escolha um dos nossos excelentes sudokus\n");
    cprintf(GREEN, "1 - Sudoku 1:\n");
    loadSudoku(matrix, sudoku1);
    printSudoku(*matrix);
    printLine();
    cprintf(RED, "Pressione enter para ver o próximo sudoku!\n");
    getchar();
    getchar();
    system("clear");
    cprintf(GREEN, "2 - Sudoku 2:\n");
    loadSudoku(matrix, sudoku2);
    printSudoku(*matrix);
    printLine();
    cprintf(RED, "Pressione enter para ver o próximo sudoku!\n");
    getchar();
    system("clear");
    cprintf(GREEN, "3 - Sudoku que já está resolvido:\n");
    loadSudoku(matrix, sudokuResolvido);
    printSudoku(*matrix);
    printLine();
    cprintf(RED, "Pressione enter para ver o próximo sudoku!\n");
    getchar();
    system("clear");
    cprintf(GREEN, "4 - Sudoku em Branco (o resultado desse é legal!)\n");
    loadSudoku(matrix, sudokuBranco);
    printSudoku(*matrix);
    printLine();
    cprintf(GREEN, "Escolha um dos sudokus de 1 a 4 !\n");
    prePrompt();
    scanf("%d", &escolhaSudoku);
    switch (escolhaSudoku) {
        case 1:
            loadSudoku(matrix, sudoku1);
            break;
        case 2:
            loadSudoku(matrix, sudoku2);
            break;
        case 3:
            loadSudoku(matrix, sudokuResolvido);
            break;
        case 4:
            loadSudoku(matrix,sudokuBranco);
            break;
        default:
            cprintf(RED, "\nNão temos tantos sudokus, escolha um de 1 a 4\n");
            return _printAllSudoku(matrix);
    }
}

void _showResultSudoku (int ***matrix, int analysisMode) {
    printLine();
    int numTentativas = 0;
    int escolha;
    cprintf(MAGENTA, "\nExibindo o sudoku solucionado!\n");
    printLine();
    solveSudoku(*matrix, &numTentativas);
    printSudoku(*matrix);
    if(analysisMode)
        printLine();
    cprintf(RED, "\nForam feitas %d comparações!\n", numTentativas);
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
