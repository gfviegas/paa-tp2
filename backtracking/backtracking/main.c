//
//  main.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include <stdio.h>
#include "wordHunt/wordHunt.h"
#include "sudoku/sudoku.h"

int main(int argc, const char * argv[]) {
    char **matrix = NULL;
    int **sudoku = NULL;
    int lines, columns;

    //loadMatrix(&matrix, &lines, &columns);
    //printMatrix(matrix, lines, columns);
    loadSudoku(&sudoku);
    printSudoku(sudoku);
    if(isSudokuResolvido(sudoku))
        printf("Sudoku solucionado !");
    else
        printf("FRACASSADO!!!!");
    return 0;
}
