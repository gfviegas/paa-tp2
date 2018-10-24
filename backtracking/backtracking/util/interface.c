#include "interface.h"

void printHeader(int modo){
    system("clear");
    
    printf("\n\n");
    printLine();
    cprintf(BLUE, "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n");
    cprintf(BLUE, "\n \t Ao Resolvedor COQUETEL !");
    printLine();
    printMenuInicial(modo);
}

void printMenuInicial(int modo) {
    int escolha;
    
    cprintf(GREEN, "\n \n Selecione qual quebra-cabeça COQUETEL você deseja resolver : \n\n");
    cprintf(GREEN, "1 - Caça-palavra\n");
    cprintf(GREEN, "2 - Sudoku\n");
    cprintf(YELLOW, "->  ");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            _wordHuntMenu(modo);
            break;
        case 2:
            MenuSudoku(modo);
            break;
        default:
            cprintf(RED, "\n\n * Digite apenas 1 ou 2, ainda não temos tantos quebra-cabeças :(\n");
            return printMenuInicial(modo);
    }
}

void MenuSudoku(int modo){
    system("clear");
    int **matrix = NULL;
    int arquivo;

    printLine();
    cprintf(GREEN, "Deseja escrever um sudoku ou resolver um que nós já possuímos em nossos arquivos ?\n");
    cprintf(GREEN, "1 - Escrever\n");
    cprintf(GREEN, "2 - Arquivos\n");
    scanf("%d", &arquivo);
    switch (arquivo) {
        case 1:
            readSudoku(&matrix);
            break;
        case 2:
            printAllSudoku(&matrix);
            break;
        default:
            cprintf(RED, "\n Digite 1 ou 2, não temos tantas opções\n\n");
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
    cprintf(GREEN, "Escolha um dos nossos excelentes sudokus\n");
    cprintf(GREEN, "1 - Sudoku 1:\n");
    loadSudoku(matrix, sudoku1);
    printSudoku(*matrix);
    printLine();
    cprintf(RED, "Pressione enter para ver o próximo sudoku!\n");
    getchar();
    getchar();
    system("clear");
    cprintf(GREEN, "2 - Sudoku 2:\n");
    loadSudoku(matrix, sudoku2);
    printSudoku(*matrix);
    printLine();
    cprintf(RED, "Pressione enter para ver o próximo sudoku!\n");
    getchar();
    system("clear");
    cprintf(GREEN, "3 - Sudoku que já está resolvido:\n");
    loadSudoku(matrix, sudokuResolvido);
    printSudoku(*matrix);
    printLine();
    cprintf(RED, "Pressione enter para ver o próximo sudoku!\n");
    getchar();
    system("clear");
    cprintf(GREEN, "4 - Sudoku em Branco (o resultado desse é legal!)\n");
    loadSudoku(matrix, sudokuBranco);
    printSudoku(*matrix);
    printLine();
    cprintf(GREEN, "Escolha um dos sudokus de 1 a 4 !\n");
    cprintf(YELLOW, "->  ");
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
            cprintf(RED, "\nNão temos tantos sudokus, escolha um de 1 a 4\n");
            return printAllSudoku(matrix);
    }
}

void showResult(int ***matrix, int modo){
    printLine();
    int numTentativas = 0;
    int escolha;
    cprintf(MAGENTA, "\nExibindo o sudoku solucionado!\n");
    printLine();
    solveSudoku(*matrix, &numTentativas);
    printSudoku(*matrix);
    if(modo)
        printLine();
        cprintf(RED, "\nForam feitas %d comparações!\n", numTentativas);
    cprintf(GREEN, "\nDigite 1 para resolver outro sudoku e 2 para voltar\n");
    cprintf(YELLOW, "->  ");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            return MenuSudoku(modo);
        case 2:
            printHeader(modo);
        default:
            printLine();
            cprintf(RED, "Interrompendo execução do programa...\n");
    }

}
