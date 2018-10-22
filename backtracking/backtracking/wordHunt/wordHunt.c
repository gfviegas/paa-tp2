//
//  wordHunt.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "wordHunt.h"

void loadMatrix(char ***matrix, int *matrixLines, int *matrixColumns) {
    int i, j;

    char currentLine[FILE_BUFFER_SIZE];
    FILE *file = NULL;
    openFile(&file, "xesque");

    fscanf(file, "%d %d\n", matrixLines, matrixColumns);
    *matrix = (char **) malloc(*matrixLines * sizeof(char *));

    for (i = 0; i < *matrixLines; i++) {
        j = 0;
        (*matrix)[i] = (char *) malloc(*matrixColumns * sizeof(char));

        readLine(file, currentLine);

        for (j = 0; j < *matrixColumns; j++) {
            (*matrix)[i][j] = currentLine[j];
        }
    }

    fclose(file);
}

void printMatrix(char **matrix, int lines, int columns) {
    int i, j;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}
