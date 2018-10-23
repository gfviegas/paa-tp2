#include "interface.h"

void printHeader(int modo){
    system("clear");
    char BemVindo[1000];
    sprintf(BemVindo, "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n");
    printf("\n\n");
    printLine();
    logInfo(BemVindo);
    printf("\n Ao Resolvedor COQUETEL !");
    printLine();
    printMenuInicial(modo);
}

void printMenuInicial(int modo){
    printf("\n\n");
    printf("Selecione qual quebra-cabeça COQUETEL você deseja resolver : \n\n");
    printf("1- Caça-palavra\n");
    printf("2- Sudoku\n");
    int escolha;
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            _wordHuntMenu(modo);
            break;
        case 2:
            MenuSudoku(modo);
            break;
        default:
            printf("\n\n * Digite apenas 1 ou 2, ainda não temos tantos quebra-cabeças :(\n");
            return printMenuInicial(modo);
    }
}

void MenuSudoku(int modo){
    system("clear");
    int **matrix = NULL;
    int arquivo;

    printLine();
    printf("Deseja escrever um sudoku ou resolver um que nós já possuímos em nossos arquivos ?\n");
    printf("1- escrever\n");
    printf("2- arquivos\n");
    scanf("%d", &arquivo);
    switch (arquivo) {
        case 1:
            readSudoku(&matrix);
            break;
        case 2:
            printAllSudoku(&matrix);
            break;
        default:
            printf("\n Digite 1 ou 2, não temos tantas opções\n\n");
            return MenuSudoku(modo);
    }
    showResult(&matrix, modo);
}

void printAllSudoku(int ***matrix){
    char sudoku1[20], sudoku2[20], sudokuResolvido[30], sudokuBranco[30];
    int escolhaSudoku;
    strcpy(sudoku1, "sudoku1.txt");
    strcpy(sudoku2, "sudoku2.txt");
    strcpy(sudokuResolvido, "sudokuResolvido.txt");
    strcpy(sudokuBranco, "sudokuBranco.txt");
    printLine();
    printf("Escolha um dos nossos excelentes sudokus\n");
    printf("1-Sudoku 1:\n");
    loadSudoku(matrix, sudoku1);
    printSudoku(*matrix);
    printLine();
    printf("Pressione enter para ver o próximo sudoku!\n");
    getchar();
    getchar();
    system("clear");
    printf("2-Sudoku 2:\n");
    loadSudoku(matrix, sudoku2);
    printSudoku(*matrix);
    printLine();
    printf("Pressione enter para ver o próximo sudoku!\n");
    getchar();
    system("clear");
    printf("3-Sudoku que já está resolvido:\n");
    loadSudoku(matrix, sudokuResolvido);
    printSudoku(*matrix);
    printLine();
    printf("Pressione enter para ver o próximo sudoku!\n");
    getchar();
    system("clear");
    printf("4-Sudoku em branco (resultado desse é legal)\n");
    loadSudoku(matrix, sudokuBranco);
    printSudoku(*matrix);
    printLine();
    printf("Escolha um dos sudokus de 1 a 4 !\n");
    printf("->");
    scanf("%d", &escolhaSudoku);
    switch (escolhaSudoku) {
        case 1:
            loadSudoku(matrix, sudoku1);
            break;
        case 2:
            loadSudoku(matrix, sudoku2);
            break;
        case 3:
            loadSudoku(matrix, sudokuResolvido);
            break;
        case 4:
            loadSudoku(matrix,sudokuBranco);
            break;
        default:
            printf("\nNão temos tantos sudokus, escolha um de 1 a 4\n");
            return printAllSudoku(matrix);
    }
}

void showResult(int ***matrix, int modo){
    printLine();
    int numTentativas = 0;
    int escolha;
    printf("Exibindo o sudoku solucionado!\n");
    printLine();
    solveSudoku(*matrix, &numTentativas);
    printSudoku(*matrix);
    if(modo)
        printLine();
        printf("Foram feitas %d comparações!\n", numTentativas);
    printf("Digite 1 para resolver outro sudoku e 2 para resolver outro quebra-cabeça ?\n");
    printf("->");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            return MenuSudoku(modo);
        case 2:
            printHeader(modo);
        default:
            printLine();
            printf("Interrompendo execução do programa...\n");
    }

}
