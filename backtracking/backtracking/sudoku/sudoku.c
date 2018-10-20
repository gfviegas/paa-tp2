#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadSudoku(int ***matrix){
    *matrix = (int **) malloc(TAM_SUDOKU* TAM_SUDOKU * sizeof(int));
    int i = 0, j = 0, som = 0 ;
    char currentLine[FILE_BUFFER_SIZE];
    FILE *file = NULL;
    openFile(&file);
    for(i = 0;i < TAM_SUDOKU;i++){

        j = 0;
        readLine(file, currentLine);
        printf("A linha lida é %s", currentLine);
        (*matrix)[i] = (int *) malloc(TAM_SUDOKU * sizeof(int));

        for(j = 0;j < TAM_SUDOKU;j++){
            (*matrix)[i][j] = (currentLine[j] - CONVERSOR_ASCII);
            som++;
            printf("entrei aqui %d vezes\n", som);
        }
    }
    fclose(file);
}

void printSudoku(int **matrix){
    int i, j;
    for(i = 0; i < TAM_SUDOKU; i++){
        for(j = 0; j < TAM_SUDOKU; j++){
            if(matrix[i][j] == 0)
                printf(" ");
            else
                printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int checaVetor(int *vetor){
    int i, j, som = 0, condSoma = 1, condDuplicata = 1;
    for(i = 0; i < TAM_SUDOKU; i++){
        for(j = i + 1; j < TAM_SUDOKU; j++){
            if(vetor[i] == vetor[j]){
                condDuplicata = 0;
                break;
            }
        }
    }
    for(i = 0; i < TAM_SUDOKU; i++)
        som += vetor[i];
    if(som != SUM_CHECK)
        condSoma = 0;
    return (condDuplicata & condSoma);
}

int isSudokuResolvido(int **matrix){
    int i, j, k, line[TAM_SUDOKU], column[TAM_SUDOKU], cond = 1;
    for(i = 0; i < TAM_SUDOKU; i++){
        if(cond == 0)
            return cond;
        for(j = 0; j < TAM_SUDOKU; j++){
            line[j] = matrix[i][j];
            cond = (cond & checaVetor(line));
            for(k=0; k<TAM_SUDOKU; k++){
                column[k] = matrix [k][j];
                cond = (cond & checaVetor(column));
            }
        }

    }
}
void solveSudoku(int **matrix){
    if()
}
