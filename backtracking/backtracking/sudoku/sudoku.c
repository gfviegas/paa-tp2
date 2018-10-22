#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadSudoku(int ***matrix, char* filePath){
    *matrix = (int **) malloc(TAM_SUDOKU* TAM_SUDOKU * sizeof(int));
    int i = 0, j = 0;
    char currentLine[FILE_BUFFER_SIZE];
    FILE *file = NULL;
    openFile(&file, filePath);
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

void readSudoku(int ***matrix){
    *matrix = (int **) malloc(TAM_SUDOKU* TAM_SUDOKU * sizeof(int));
    int i, j;
    printf("Você irá escrever o seu sudoku, quando o quadrado for vazio coloque 0\n\n");
    for(i=0;i<TAM_SUDOKU;i++){
        printf("Digite a linha número %d do seu sudoku", i);
        for(j=0;j<TAM_SUDOKU;j++){
            scanf("%d", matrix[i][j]);
        }
    }
}

void printSudoku(int **matrix){
    int i, j;
    for(i = 0; i < TAM_SUDOKU; i++){
        for(j = 0; j < TAM_SUDOKU; j++){
            if(matrix[i][j] == 0)
                printf("0");
            else
                printf("%d", matrix[i][j]);
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
    for(i = 0; i < TAM_SUDOKU; i++)
        som += vetor[i];
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
    if(backTracking(matrix, 0))
        printf("SUDOKU RESOLVIDO!\n\n");
    else
        printf("SUDOKU N TEM SOLUÇÃO\n");
}

int backTracking(int **matrix, int index){
    int tenta;
    int i = index / TAM_SUDOKU;
    int j = index % TAM_SUDOKU;
    if(isSudokuResolvido(matrix))
        return 1;
    if(index > TAM_SUDOKU*TAM_SUDOKU)
        return 0;
    if(matrix[i][j] == 0){
        for(tenta = 1; tenta <= 9; tenta++){
            if(canBeTry(matrix, i, j, tenta)){
                    matrix[i][j] = tenta;
                    if(backTracking(matrix, index + 1))
                        return 1;
                    else
                        matrix[i][j] = 0;
            }
        }
    }
    else if(backTracking(matrix, index+1))
        return 1;
    else
        return 0;
    return 0;
}


int canBeTry(int **matrix, int lineIndex, int columnIndex, int tenta){
    int i,j;
    int boxIndexLine = lineIndex / 3;
    int boxIndexColumn = columnIndex / 3;
    if(matrix[lineIndex][columnIndex] != 0)
        return 1;
    for(i=0; i<TAM_SUDOKU; i++)
        if(matrix [lineIndex][i] == tenta || matrix[i][columnIndex] == tenta)
            return 0;
    for(i=0;i<TAM_SUDOKU/3;i++){
        for(j=0;j<TAM_SUDOKU/3;j++){
            if(matrix [i + (3*boxIndexLine)] [j + (3*boxIndexColumn)] == tenta)
                return 0;
        }
    }
    return 1;
}
