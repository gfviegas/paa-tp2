//
//  wordHunt.h
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef wordHunt_h
#define wordHunt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/fileReader.h"
#include "../util/logger.h"

typedef enum Movements {
    NONE,
    LEFT,
    RIGHT,
    BOTTOM
} Movements;

void loadMatrix(char ***matrix, int *matrixLines, int *matrixColumns);
void printMatrix(char ***matrix, int lines, int columns);
int backtracking(char ***matrix, int linesAmt, int columnsAmt, int lineIdx, int columnIdx, char* word, int wordIdx, int wordLen, char ***resultMatrix, Movements lastMovement, int *calls);
void search(char ***matrix, char *word, int lines, int columns);
#endif /* wordHunt_h */
