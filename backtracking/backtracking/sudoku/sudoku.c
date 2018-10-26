#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Com um caminho para o arquivo, carrega uma matriz com o sudoku( 0 é igual a espaço vazio)
 * @param matrix   Matriz que terá o sudoku para ser manipulada
 * @param filePath Caminho do arquivo com extensão
 */
void loadSudoku(int ***matrix, char* filePath){
    allocMatrixSudoku(matrix);

    char currentLine[FILE_BUFFER_SIZE];
    FILE *file = NULL;
    openFile(&file, filePath);

    for (int i = 0; i < TAM_SUDOKU; i++) {
        readLine(file, currentLine);

        for (int j = 0; j < TAM_SUDOKU; j++)
            (*matrix)[i][j] = (currentLine[j] - CONVERSOR_ASCII);
    }

    fclose(file);
}

void allocMatrixSudoku(int ***matrix) {
    *matrix = (int **) malloc(TAM_SUDOKU* TAM_SUDOKU * sizeof(int));

    for (int i = 0; i < TAM_SUDOKU; i++)
        (*matrix)[i] = (int *) malloc(TAM_SUDOKU * sizeof(int));
}

void createEmptyMatrix(int ***matrix) {
    if (*matrix != NULL) free(matrix);
    allocMatrixSudoku(matrix);

    for (int i = 0; i < TAM_SUDOKU; i++)
        for (int j = 0; j < TAM_SUDOKU; j++)
            (*matrix)[i][j] = 0;
}

/*
 * Função chamada caso o usuário queira escrever o sudoku na mão
 * @param matrix [Matriz que terá o sudoku armazenado]
 */
void readSudoku(int ***matrix){
    if (*matrix != NULL) free(matrix);
    allocMatrixSudoku(matrix);
    int num;

    printf("Você irá escrever o seu sudoku, quando o quadrado for vazio coloque 0--\n\n");
    for (int i = 0; i < TAM_SUDOKU; i++) {
        printf("Digite a linha número %d do seu sudoku:\n", i + 1);
        for(int j = 0; j < TAM_SUDOKU; j++) {
            scanf("%d", &num);
            (*matrix)[i][j] = num;
        }
    }
}

void printSudokuLine(int index) {
    int isRow = (index == 0 || index == 8);
    char* border = isRow ? "-" : "|";

    cprintf(CYAN, "%s", border);

    for (int i = 0; i < (TAM_SUDOKU * 2) + 5; i++) {
        char* toPrint = ((!isRow) && (i == 7 || i == 15)) ? "+" : "-";
        cprintf(CYAN, "%s", toPrint);
    }

    cprintf(CYAN, "%s\n", border);
}

/**
 * Exibe o sudoku no terminal com os caracteres '|' e '--' para separar os nove blocos do sudoku1
 * @param matrix Matriz que contém o sudoku a ser exibido
 */
void printSudoku(int **matrix){
    for (int i = 0; i < TAM_SUDOKU; i++) {
        if (i % 3 == 0) printSudokuLine(i);

        for (int j = 0; j < TAM_SUDOKU; j++) {
            if (j % 3 == 0) cprintf(CYAN, "| ");

            if (matrix[i][j] == 0)
                cprintf(YELLOW, "  ");
            else
                cprintf(YELLOW, "%d ", matrix[i][j]);
        }
        cprintf(CYAN, "|\n");
        if (i == 8) printSudokuLine(i);
    }
    printf("\n");
}

void printSolutionSudoku(int **matrix, int **solutionMatrix) {
    AvailableColors color;
    int currentValue;

    for (int i = 0; i < TAM_SUDOKU; i++) {
        if (i % 3 == 0) printSudokuLine(i);

        for (int j = 0; j < TAM_SUDOKU; j++) {
            color = RED;
            currentValue = solutionMatrix[i][j];

            if (j % 3 == 0) cprintf(CYAN, "| ");

            if (currentValue == 0) {
                currentValue = matrix[i][j];
                color = YELLOW;
            }

            if (currentValue == 0)
                cprintf(color, "  ");
            else
                cprintf(color, "%d ", currentValue);
        }

        cprintf(CYAN, "|\n");
        if (i == 8) printSudokuLine(i);
    }
    printf("\n");
}
/**
 * Verifica se a matriz possui algum 0, pois siginifica que todos os espaços já foram preenchidos e consequentemente
 * o sudoku está resolvido visto que é garantidamente uma posição válida
 * @param  matrix sudoku a ser analisado
 * @return        0 caso ainda haja espaços a serem preenchidos e 1 caso sudoku esteja resolvido
 */
int isSudokuResolvido(int **matrix){
    for (int i = 0; i < TAM_SUDOKU; i++)
        for (int j = 0; j < TAM_SUDOKU; j++)
            if (matrix[i][j] == 0) return 0;
    return 1;
}
/**
 * Função usada para encapsular os parâmetros passados no backTracking, resolve o sudoku
 * @param  matrix        Matriz que contém o sudoku a ser resolvido
 * @param  numTentativas Número de tentativas, passada como ponteiro para contabilizar quantas chamadas foram efetuadas
 * @return               1 se o sudoku foi resolvido, 0 se ele não possui solução
 */
int solveSudoku(int **matrix, int *numTentativas, int ***solutionMatrix) {
    createEmptyMatrix(solutionMatrix);

    return(backTracking(matrix, 0, numTentativas, *solutionMatrix));
}

/**
 * Função recursiva que resolve o sudoku por backTracking
 * @param  matrix        Matriz que contém o sudoku
 * @param  index         qual índice está
 * @param  numTentativas Número de tentativas
 * @return               1(sucesso) caso aquela tentativa seja bem sucedida e 0 caso aquela tentativa falhe
 */
int backTracking(int **matrix, int index, int *numTentativas, int **solutionMatrix) {
    (*numTentativas)++;
    //i e j recebem seus respectivos índices, sendo i a linha atual e j a coluna atual
    int i = index / TAM_SUDOKU;
    int j = index % TAM_SUDOKU;

    if(isSudokuResolvido(matrix)) //Se encontramos um sudoku válido retorne sucesso
        return 1;
    if(index > TAM_SUDOKU*TAM_SUDOKU)//Se estamos tentando para fora do tabuleiro(índice 82) certamente não estamos na solução
        return 0;
    //Devemos tentar apenas para espaços vazios
    if(matrix[i][j] == 0) {
        for(int tenta = 1; tenta <= 9; tenta++){
            if(canBeTry(matrix, i, j, tenta)){//Se parece uma tentativa válida
                    matrix[i][j] = tenta;//Grava a tentativa
                    solutionMatrix[i][j] = tenta;

                    if (backTracking(matrix, index + 1, numTentativas, solutionMatrix)) return 1;
                    // Se não deu certo, apaga os traços
                    matrix[i][j] = 0;
                    solutionMatrix[i][j] = 0;
            }
        }
    }
    // Quando estamos em um número fixo devemos "ignorá-lo", chamar para o próximo índice e caso de certo retorne sucesso
    else if (backTracking(matrix, index+1, numTentativas, solutionMatrix))
        return 1;

    return 0;
}

/**
 * Função que verifica se um certo índice e tentativa satisfazem as regras do sudokus
 * @param  matrix      Matriz que contém o sudokus
 * @param  lineIndex   Índice da linhas
 * @param  columnIndex índice da colunas
 * @param  tenta       Número que verificaremos a validade
 * @return             1 caso possa ser colocado e 0 caso contŕario
 */
int canBeTry(int **matrix, int lineIndex, int columnIndex, int tenta){
    int i,j;
    //Considerando um sudoku uma matriz [3][3] de matrizes [3][3], boxIndexLine e boxIndexColumn recebem os índices das
    //matrizes externas
    int boxIndexLine = lineIndex / 3;
    int boxIndexColumn = columnIndex / 3;
    for(i=0; i<TAM_SUDOKU; i++) //Percorre uma sequencia do tamanho do sudoku
        if(matrix [lineIndex][i] == tenta || matrix[i][columnIndex] == tenta)
        //Se ja possui o número na linha ou na coluna retorna falso
            return 0;
    //Percorre a matriz[3][3] interna
    for(i=0;i<TAM_SUDOKU/3;i++){
        for(j=0;j<TAM_SUDOKU/3;j++){
            if(matrix [i + (3*boxIndexLine)] [j + (3*boxIndexColumn)] == tenta)
            //se ja possui o número no bloco retorna falso
                return 0;
        }
    }
    return 1;//Tudo ok, retorna 1
}
