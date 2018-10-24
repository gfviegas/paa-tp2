//
//  wordHunt.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "wordHunt.h"
void createMatrix(char ***matrix, int matrixLines, int matrixColumns) {
    *matrix = (char **) malloc(matrixLines * sizeof(char *));

    for (int i = 0; i < matrixLines; i++)
        (*matrix)[i] = (char *) malloc(matrixColumns * sizeof(char));
}

void fillMatrix(char ***matrix, int matrixLines, int matrixColumns) {
    for (int i = 0; i < matrixLines; i++) {
        for (int j = 0; j < matrixColumns; j++) {
            (*matrix)[i][j] = '*';
        }
    }
}

void loadMatrix(char ***matrix, int *matrixLines, int *matrixColumns) {
    char currentLine[FILE_BUFFER_SIZE];
    char fileName[FILE_BUFFER_SIZE];
    FILE *file = NULL;

    if (*matrix != NULL) free(*matrix);

    promptFilePath(fileName);
    openFile(&file, fileName);

    fscanf(file, "%d %d\n", matrixLines, matrixColumns);

    createMatrix(matrix, *matrixLines, *matrixColumns);

    for (int i = 0; i < *matrixLines; i++) {
        readLine(file, currentLine);
        for (int j = 0; j < *matrixColumns; j++) {
            (*matrix)[i][j] = currentLine[j];
        }
    }

    fclose(file);
}

void printMatrixLine(int size, int brBefore, int brAfter) {
    if (brBefore) printf("\n");
    for (int i = 0; i <= size + 1; i++)
        cprintf(BLUE, "---");
    if (brAfter) printf("\n");
}

void printMatrix(char ***matrix, int lines, int columns, char* header) {
    int precision = ((columns * 3) / 2) + ((int) strlen(header) / 2);
    printMatrixLine(columns, 1, 1);
    cprintf(MAGENTA, "%*s", precision, header);
    printMatrixLine(columns, 1, 1);

    for (int i = 0; i < lines; i++) {
        cprintf(BLUE, " | ");
        for (int j = 0; j < columns; j++) {
            cprintf(CYAN, " %c ", (*matrix)[i][j]);
        }
        cprintf(BLUE, " |\n");
    }

    printMatrixLine(columns, 0 , 1);
}

int checkMatch(char ***matrix, char query, int line, int column) {
    if (matrix == NULL) return 0;

    char matrixValue = (*matrix)[line][column];
    return (line >= 0 && column >= 0 && (query == matrixValue));
}

int backtracking(char ***matrix, int linesAmt, int columnsAmt, int lineIdx, int columnIdx, char* word, int wordIdx, int wordLen, char ***resultMatrix, Movements lastMovement, int* calls, int* occurrences) {
    int successCalls = 0;
    (*calls)++;

    // Se os indices de procura nao estao na matriz, entao é sem-esperança.
    if (lineIdx < 0 || columnIdx < 0 || lineIdx >= linesAmt || columnIdx >= columnsAmt) return 0;

    char query = word[wordIdx];

    // Se estou em uma posição cuja letra procurada nao está presente, não adianta continuar.
    if (!checkMatch(matrix, query, lineIdx, columnIdx)) return 0;

    // Acabou se estou procurando a n-esima letra da palavra e ela está na posicao certa
    if (wordIdx == (wordLen - 1)) {
        (*resultMatrix)[lineIdx][columnIdx] = query;
        (*occurrences)++;
        return 1;
    }

    // Incrementa o indice pra procurar a próxima letra.
    wordIdx++;
    // Para cada direção, se procura a próxima letra.
    for (Movements i = LEFT; i <= BOTTOM; i++) {
        if (i == lastMovement) continue;
        if ((i == LEFT || i == RIGHT) & (lastMovement == LEFT || lastMovement == RIGHT)) continue;

        int nextLine = (i == BOTTOM) ? lineIdx + 1 : lineIdx;
        int nextColumn = (i == LEFT) ? columnIdx - 1 : (i == RIGHT) ? columnIdx + 1 : columnIdx;

        if (backtracking(matrix, linesAmt, columnsAmt, nextLine, nextColumn, word, wordIdx, wordLen, resultMatrix, i, calls, occurrences)) {
            (*resultMatrix)[lineIdx][columnIdx] = query;
            successCalls++;
        }
    }

    return successCalls;
}

void search(char ***matrix, char *word, int lines, int columns, int analysisMode) {
    int results = 0;
    int calls = 0;
    int wordLen = (int)(strlen(word));
    char **resultMatrix;
    createMatrix(&resultMatrix, lines, columns);
    fillMatrix(&resultMatrix, lines, columns);

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if ((*matrix)[i][j] == word[0])
                backtracking(matrix, lines, columns, i, j, word, 0, wordLen, &resultMatrix, NONE, &calls, &results);
        }
    }

    if (analysisMode) {
        cprintf(RED, "[STATS] Teve %d chamadas recursivas\n", calls);
    }

    printf("Foram encontradas %d ocorrências\n", results);
    if (results > 0)
        printMatrix(&resultMatrix, lines, columns, "Resultado");
    else
        logError("Não foi encontrada a palavra");

    free(resultMatrix);
}
