#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadSudoku(int ***matrix){
    *matrix = (int **) malloc(TAM_SUDOKU* TAM_SUDOKU * sizeof(int));
    int i = 0, j = 0;
    char currentLine[FILE_BUFFER_SIZE];
    FILE *file = NULL;
    openFile(&file);
    for(i = 0;i < TAM_SUDOKU;i++){

        j = 0;
        readLine(file, currentLine);
        (*matrix)[i] = (int *) malloc(TAM_SUDOKU * sizeof(int));

        for(j = 0;j < TAM_SUDOKU;j++){
            (*matrix)[i][j] = (currentLine[j] - CONVERSOR_ASCII);
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
    for(i = 0; i < TAM_SUDOKU - 1; i++){
        for(j = i + 1; j < TAM_SUDOKU; j++){
            if(vetor[i] == vetor[j]){
                condDuplicata = 0;
                break;
            }
        }
    }
    for(i = 0; i < TAM_SUDOKU; i++){x''
        som += vetor[i];
    }
    if(som != SUM_CHECK)
        condSoma = 0;
    return (condDuplicata & condSoma);
}

int isSudokuResolvido(int **matrix){
    int i, j, k, l, line[TAM_SUDOKU], column[TAM_SUDOKU], box[TAM_SUDOKU], cond = 1, indice = 0;
    for(i = 0; i < TAM_SUDOKU; i++){
        if(cond == 0)
            return cond;
        for(j = 0; j < TAM_SUDOKU; j++){
            line[j] = matrix[i][j];
            for(k=0; k<TAM_SUDOKU; k++){
                column[k] = matrix [k][j];
            }
            cond = (cond & checaVetor(column));
            if(!cond)
                return cond;
        }
        cond = (cond & checaVetor(line));
    }
    for(i=0;i<TAM_SUDOKU/3;i++){
        for(j=0;j<TAM_SUDOKU/3;j++){
            for(k=0;k<TAM_SUDOKU/3;k++){
                for(l=0;l<TAM_SUDOKU/3;l++){
                    box[indice] = matrix[k + (3 * i)] [l + (3 * j)];
                    indice++;
                }
            }
            indice = 0;
            cond = (cond & checaVetor(box));
            if(!cond)
                return cond;
        }
    }
    return cond;
}

void solveSudoku(int **matrix){

}

int backTracking(int **matrix, int lineIndex, int columnIndex, int try){
    if(isSudokuResolvido)
        return 1;
    for(i=lineIndex; i<TAM_SUDOKU; i++){
        for(j=0; j<TAM_SUDOKU; j++){
            while(1){
                if(canBeTry){
                    if(backTracking(matrix, lineIndex, columnIndex, try)){
                        return 1;
                    }
                    else{
                        try = 0;
                    }
                }
                try++;
                if(try == TAM_SUDOKU + 1)
                    return 0;
            }
        }
    }
    return 0;
}
