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

int backtracking(char ***matrix, int linesAmt, int columnsAmt, int lineIdx, int columnIdx, char* word, int wordIdx, int wordLen, char ***resultMatrix, Movements lastMovement, int* calls) {
    Movements i;
    (*calls)++;

    // Acabou se estou procurando a n-esima + 1 letra da palavra
    if (wordIdx == wordLen) return 1;

    char query = word[wordIdx];

    // Se os indices de procura nao estao na matriz, entao é sem-esperança.
    if (lineIdx < 0 || columnIdx < 0 || lineIdx >= linesAmt || columnIdx >= columnsAmt) return 0;
    // Se estou em uma posição cuja letra procurada nao está presente, não adianta continuar.
    if (!checkMatch(matrix, query, lineIdx, columnIdx)) return 0;

    // Incrementa o indice pra procurar a próxima letra.
    wordIdx++;
    // Para cada direção, se procura a próxima letra.
    for (i = LEFT; i <= BOTTOM; i++) {
        if (i == lastMovement) continue;
        if ((i == LEFT || i == RIGHT) & (lastMovement == LEFT || lastMovement == RIGHT)) continue;

        int nextLine = (i == BOTTOM) ? lineIdx + 1 : lineIdx;
        int nextColumn = (i == LEFT) ? columnIdx - 1 : (i == RIGHT) ? columnIdx + 1 : columnIdx;

        if (backtracking(matrix, linesAmt, columnsAmt, nextLine, nextColumn, word, wordIdx, wordLen, resultMatrix, i, calls)) {
            (*resultMatrix)[lineIdx][columnIdx] = query;
            return 1;
        }

        (*resultMatrix)[lineIdx][columnIdx] = '*';
    }

    return 0;
}

void search(char ***matrix, char *word, int lines, int columns) {
    int results = 0;
    int calls = 0;
    int wordLen = (int)(strlen(word));
    char **resultMatrix;
    createMatrix(&resultMatrix, lines, columns);
    fillMatrix(&resultMatrix, lines, columns);

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if ((*matrix)[i][j] == word[0] && backtracking(matrix, lines, columns, i, j, word, 0, wordLen, &resultMatrix, NONE, &calls)) results++;
        }
    }

//    char msg[100];
//    sprintf(msg, "Foram encontradas %d ocorrências", results);
//    logInfo(msg);
//    free(msg);

    printf("Teve %d chamadas\n", calls);
    printf("Foram encontradas %d ocorrências\n", results);
    if (results > 0)
        printMatrix(&resultMatrix, lines, columns);
    else
        logError("Não foi encontrada a palavra");
}
