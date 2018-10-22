//
//  wordHunt.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "wordHunt.h"
void createMatrix(char ***matrix, int matrixLines, int matrixColumns) {
    int i;

    *matrix = (char **) malloc(matrixLines * sizeof(char *));

    for (i = 0; i < matrixLines; i++)
        (*matrix)[i] = (char *) malloc(matrixColumns * sizeof(char));
}

void fillMatrix(char ***matrix, int matrixLines, int matrixColumns) {
    int i, j;
    for (i = 0; i < matrixLines; i++) {
        for (j = 0; j < matrixColumns; j++) {
            (*matrix)[i][j] = '*';
        }
    }
}

void loadMatrix(char ***matrix, int *matrixLines, int *matrixColumns) {
    int i, j;

    char currentLine[FILE_BUFFER_SIZE];
    FILE *file = NULL;
    openFile(&file);

    fscanf(file, "%d %d\n", matrixLines, matrixColumns);

    createMatrix(matrix, *matrixLines, *matrixColumns);

    for (i = 0; i < *matrixLines; i++) {
        readLine(file, currentLine);
        for (j = 0; j < *matrixColumns; j++) {
            (*matrix)[i][j] = currentLine[j];
        }
    }

    fclose(file);
}

void printMatrix(char ***matrix, int lines, int columns) {
    int i, j;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            printf("%c ", (*matrix)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void insertInResult(char ***matrix, char ***resultMatrix, SolutionNodePointer solution) {
    SolutionNodePointer aux = solution;

    while (aux != NULL) {
        char foundLetter = (*matrix)[aux->line][aux->column];
        (*resultMatrix)[aux->line][aux->column] = foundLetter;

        aux = aux->next;
    }
}

int checkMatch(char ***matrix, char query, int line, int column) {
    if (matrix == NULL) return 0;

    char matrixValue = (*matrix)[line][column];
    return (line >= 0 && column >= 0 && (query == matrixValue));
}

int backtracking(char ***matrix, int linesAmt, int columnsAmt, int lineIdx, int columnIdx, char* word, int wordIdx, int wordLen, char ***resultMatrix, Movements lastMovement) {
    
    if (wordIdx == wordLen) return 1;
    if (lineIdx < 0 || columnIdx < 0 || lineIdx >= linesAmt || columnIdx >= columnsAmt) return 0;
    
    char query = word[wordIdx];
    if (checkMatch(matrix, query, lineIdx, columnIdx)) {
        wordIdx++;
        (*resultMatrix)[lineIdx][columnIdx] = query;
    }
    
    
    int downCall = (lastMovement != BOTTOM) ? backtracking(matrix, linesAmt, columnsAmt, lineIdx + 1, columnIdx, word, wordIdx, wordLen, resultMatrix, BOTTOM) : 0;
    int leftCall = (lastMovement == BOTTOM || lastMovement == NONE) ? backtracking(matrix, linesAmt, columnsAmt, lineIdx, columnIdx - 1, word, wordIdx, wordLen, resultMatrix, LEFT) : 0;
    int rightCall = (lastMovement == BOTTOM || lastMovement == NONE) ? backtracking(matrix, linesAmt, columnsAmt, lineIdx, columnIdx + 1, word, wordIdx, wordLen, resultMatrix, RIGHT) : 0;
    
    int result = (rightCall || downCall || leftCall);
    if (!result) (*resultMatrix)[lineIdx][columnIdx] = '*';
    
    return result;
}

void search(char ***matrix, char *word, int lines, int columns) {
    int wordLen = (int)(strlen(word));
//    int i, j;
    
    char **resultMatrix;
    createMatrix(&resultMatrix, lines, columns);
    fillMatrix(&resultMatrix, lines, columns);
    int result = 0;
//
//    for (i = 0; i < lines; i++) {
//        for (j = 0; j < columns; j++) {
//            if ((*matrix)[i][j] == word[0]) {
//                resultMatrix[i][j] = word[0];
//                result += backtracking(matrix, lines, columns, i, j, word, 1, wordLen, &resultMatrix, NONE);
//            }
//        }
//    }
    
    if (backtracking(matrix, lines, columns, 0, 0, word, 0, wordLen, &resultMatrix, NONE))
        printMatrix(&resultMatrix, lines, columns);
    else
        logError("Não foi encontrada a palavra");
}
