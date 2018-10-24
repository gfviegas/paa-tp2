//
//  interfaceWH.c
//  backtracking
//
//  Created by Gustavo Viegas on 23/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "interfaceWH.h"

void _loadMatrix(char ***matrix, int *lines, int *columns) {
    if (*matrix != NULL) free(*matrix);
    loadMatrix(matrix, lines, columns);
}

void _printCurrentMatrix(char **matrix, int lines, int columns) {
    if (matrix == NULL) {
        cprintf(YELLOW, "A matriz atual está vazia! \n");
        return;
    }
    
    printMatrix(&matrix, lines, columns, "Caça-Palavras:");
}

void _searchWord(char **matrix, int lines, int columns, int analysisMode) {
    char word[FILE_BUFFER_SIZE];
    printf("\n\n");
    cprintf(GREEN, "Digite uma palavra para ser buscada: \n");
    cprintf(YELLOW, " ->  ");
    scanf("%s", word);
    search(&matrix, word, lines, columns, analysisMode);
    cprintf(RED, "\nDigite enter para continuar...");
    
    getchar();
    getchar();
}

void _promptAction(char **matrix, int *lines, int *columns, int analysisMode) {
    system("clear");
    printLine();
    _printCurrentMatrix(matrix, *lines, *columns);
    
    printf("\n\n");
    cprintf(GREEN, "Escolha uma ação: \n\n");
    cprintf(GREEN, "1 - Carregar arquivo de caça-palavras\n");
    cprintf(GREEN, "2 - Buscar palavra\n");
    cprintf(GREEN, "3 - Sair\n");
    
    int choice;
    cprintf(YELLOW, "->  ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            _loadMatrix(&matrix, lines, columns);
            break;
        case 2:
            _searchWord(matrix, *lines, *columns, analysisMode);
            break;
        case 3:
            return printMenuInicial(analysisMode);
        default:
            cprintf(RED, "Opção inválida!\n");
            break;
    }
    
    return _promptAction(matrix, lines, columns, analysisMode);
}

void _wordHuntMenu(int analysisMode) {
    char **matrix = NULL;
    int lines, columns;
    
    _promptAction(matrix, &lines, &columns, analysisMode);
}
