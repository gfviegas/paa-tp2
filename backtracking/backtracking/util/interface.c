#include "interface.h"
#include "logger.h"
#include "../sudoku/sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLinha(){
    int i;
    printf("\n");
    for(i=0;i<LINE_SIZE;i++){
        printf("=");
    }
    printf("\n");
}
void printHeader(){
    char BemVindo[1000];
    sprintf(BemVindo, "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n");
    printf("\n\n");
    printLinha();
    logInfo(BemVindo);
    printf("\n Ao Resolvedor COQUETEL !");
    printLinha();
    printMenuInicial();
}

void printMenuInicial(){
    printf("\n\n");
    printf("Selecione qual quebra-cabeça COQUETEL você deseja resolver : \n\n");
    printf("1- Caça-palavra\n");
    printf("2- Sudoku\n");
    int escolha;
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            //MenuCacaPalavra();
            break;
        case 2:
            MenuSudoku();
            break;
        default:
            printf("\n\n * Digite apenas 1 ou 2, ainda não temos tantos quebra-cabeças :(\n");
            return printMenuInicial();
    }
}

void MenuSudoku(){
    int modo, arquivo;
    char analysis;
    int **matrix = NULL;
    int escolhaSudoku;
    char sudoku1[20], sudoku2[20], sudokuResolvido[30], sudokuBranco[30];
    strcpy(sudoku1, "sudoku1.txt");
    strcpy(sudoku2, "sudoku2.txt");
    strcpy(sudokuResolvido, "sudokuResolvido.txt");
    strcpy(sudokuBranco, "sudokuBranco.txt");
    printLinha();
    // printf("Você deseja executar em modo análise ? (s ou n)\n");
    // scanf("%c\n", &analysis);
    // modo = (analysis == 's');
    printf("Deseja escrever um sudoku ou resolver um que nós já possuímos em nossos arquivos ?\n");
    printf("1- escrever\n");
    printf("2- arquivos\n");
    scanf("%d", &arquivo);
    switch (arquivo) {
        case 1:
            readSudoku(matrix);
            break;
        case 2:
            printf("Escolha um dos nossos excelentes sudokus\n");
            printf("1-Sudoku 1:\n");
            loadSudoku(&matrix, sudoku1);
            printSudoku(matrix);
            printLinha();
            printf("2-Sudoku 2:\n");
            loadSudoku(&matrix, sudoku2);
            printSudoku(matrix);
            printLinha();
            printf("3-Sudoku que já está resolvido:\n");
            loadSudoku(&matrix, sudokuResolvido);
            printSudoku(matrix);
            printLinha();
            printf("4-Sudoku em branco (resultado desse é legal)\n");
            loadSudoku(&matrix, sudokuBranco);
            printSudoku(matrix);
            printLinha();
            scanf("%d", &escolhaSudoku);
            switch (escolhaSudoku) {
                case 1:
                    loadSudoku(&matrix, sudoku1);
                    break;
                case 2:
                    loadSudoku(&matrix, sudoku2);
                    break;
                case 3:
                    loadSudoku(&matrix, sudokuResolvido);
                    break;
                case 4:
                    loadSudoku(&matrix,sudokuBranco);
                    break;
                default:
                    printf("\nNão temos tantos sudokus, escolha um de 1 a 4\n");
                    return MenuSudoku();
            }
            break;
        default:
            printf("\n Digite 1 ou 2, não temos tantas opções\n\n");
            return MenuSudoku();
    }
    printf("Printando a sua solução\n\n");
    printLinha();
    solveSudoku(matrix);
    printSudoku(matrix);
}
