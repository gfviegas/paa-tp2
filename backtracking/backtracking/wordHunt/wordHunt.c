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
    return (line > 0 && column > 0 && (query == matrixValue));
}

int backtracking(char ***matrix, int linesAmt, int columnsAmt, int lineIdx, int columnIdx, char* word, int wordIdx, SolutionNode solution, int wordLen, char ***resultMatrix, Movements lastMovement) {

    if (wordIdx == wordLen) {
//        printSolution(&solution);
        insertInResult(matrix, resultMatrix, &solution);
        return 1;
    }

    char query = word[wordIdx];

    if (lineIdx < 0 || columnIdx < 0) return 0;
    if (lineIdx >= linesAmt || columnIdx >= columnsAmt) return 0;

    SolutionNodePointer lastNode = getLast(&solution);
    if (lineIdx > (lastNode->line + 1) || columnIdx > (lastNode->column + 1)) return 0;

    if (checkMatch(matrix, query, lineIdx, columnIdx)) {
        wordIdx++;
        insertSolution(&solution, lineIdx, columnIdx);
    }

    int downCall, rightCall, leftCall;
    
    downCall = (lastMovement != BOTTOM) ? backtracking(matrix, linesAmt, columnsAmt, lineIdx + 1, columnIdx, word, wordIdx, solution, wordLen, resultMatrix, BOTTOM) : 1;
    leftCall = (lastMovement != LEFT && lastMovement != RIGHT) ? backtracking(matrix, linesAmt, columnsAmt, lineIdx, columnIdx - 1, word, wordIdx, solution, wordLen, resultMatrix, LEFT) : 1;
    rightCall = (lastMovement != LEFT && lastMovement != RIGHT) ? backtracking(matrix, linesAmt, columnsAmt, lineIdx, columnIdx + 1, word, wordIdx, solution, wordLen, resultMatrix, RIGHT) : 1;
    
    return (rightCall || downCall || leftCall);
}

void search(char ***matrix, char *word, int lines, int columns) {
    int i, j;
    char firstLetter = word[0];
    int wordLen = (int)(strlen(word));

    char **resultMatrix;
    createMatrix(&resultMatrix, lines, columns);
    fillMatrix(&resultMatrix, lines, columns);

    // Percorre a matriz procurando a primeira letra da palavra buscada
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            if ((*matrix)[i][j] == firstLetter) {
                SolutionNode solution;
                createNode(&solution, i, j);

                backtracking(matrix, lines, columns, i, j, word, 1, solution, wordLen, &resultMatrix, NONE);
            }
        }
    }

    printMatrix(&resultMatrix, lines, columns);
}
