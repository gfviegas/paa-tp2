/**
 * Gerencia e chama as funções relacionadas ao sudoku, manipulando os arquivos,
 * e matrizes, utilizando do backtracking
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#include "sudoku.h"

// Função auxiliar para imprimir uma linha para dividir o sudoku
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

// Exibe o sudoku no terminal com os caracteres '|' e '--' para separar os nove blocos do sudoku1
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

// Imprime um sudoku resolvido, colorindo os caracteres escritos para destacá-los
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

// Com um caminho para o arquivo, carrega uma matriz com o sudoku( 0 é igual a espaço vazio)
void loadSudoku(int ***matrix, char* filePath) {
    if (*matrix != NULL) free(*matrix);
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

// Aloca a memória necessária para uma matriz que represente um sudoku
void allocMatrixSudoku(int ***matrix) {
    *matrix = (int **) malloc(TAM_SUDOKU* TAM_SUDOKU * sizeof(int));

    for (int i = 0; i < TAM_SUDOKU; i++)
        (*matrix)[i] = (int *) malloc(TAM_SUDOKU * sizeof(int));
}

// Cria uma matriz do tamanho do sudoku com todos os registros zerado
void createEmptyMatrix(int ***matrix) {
    if (*matrix != NULL) free(matrix);
    allocMatrixSudoku(matrix);

    for (int i = 0; i < TAM_SUDOKU; i++)
        for (int j = 0; j < TAM_SUDOKU; j++)
            (*matrix)[i][j] = 0;
}

// Função chamada caso o usuário queira escrever o sudoku na mão
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

// Verifica se a matriz possui algum 0, pois siginifica que todos os espaços já foram preenchidos e consequentemente
// o sudoku está resolvido visto que é garantidamente uma posição válida
int isSudokuResolvido(int **matrix){
    for (int i = 0; i < TAM_SUDOKU; i++)
        for (int j = 0; j < TAM_SUDOKU; j++)
            if (matrix[i][j] == 0) return 0;
    return 1;
}

// Conta a quantidade de 0s, ou elementos a serem escritos, na matriz
int countEmptySpots(int **matrix) {
    int amount = 0;
    for (int i = 0; i < TAM_SUDOKU; i++)
        for (int j = 0; j < TAM_SUDOKU; j++)
            if (matrix[i][j] == 0) amount++;

    return amount;
}

// Função usada para encapsular os parâmetros passados no sudokuBacktracking, resolve o sudoku
int solveSudoku(int **matrix, int *calls, int ***solutionMatrix) {
    // Conta a quantidade de espaços vazios, ou de numeros que devemos escrever no sudoku
    int emptySpots = countEmptySpots(matrix);
    createEmptyMatrix(solutionMatrix);

    return(sudokuBacktracking(matrix, 0, &emptySpots, calls, *solutionMatrix));
}

// Função recursiva que resolve o sudoku por sudokuBacktracking
int sudokuBacktracking(int **matrix, int index, int *emptySpots, int *calls, int **solutionMatrix) {
    (*calls)++;

    // i e j recebem seus respectivos índices, sendo i a linha atual e j a coluna atual
    int i = index / TAM_SUDOKU;
    int j = index % TAM_SUDOKU;

    // Se não há mais 0s na matriz, o sudoku está resolvido.
    if ((*emptySpots) == 0) return 1;

    // Se estamos tentando para fora do tabuleiro (índice 82) certamente não estamos na solução
    if (index >= TAM_SUDOKU * TAM_SUDOKU) return 0;

    // Devemos tentar apenas para espaços vazios
    if (matrix[i][j] == 0) {
        for (int try = 1; try <= 9; try++) {
            // Se parece uma tentativa válida
            if (checkSudokuCall(matrix, i, j, try)) {
                // Grava a tentativa. A matriz de solução é escrita pra diferenciar os caracteres escritos dos originais
                matrix[i][j] = try;
                solutionMatrix[i][j] = try;
                (*emptySpots)--;

                if (sudokuBacktracking(matrix, index + 1, emptySpots, calls, solutionMatrix)) return 1;

                // Se não deu certo, apaga os traços
                matrix[i][j] = 0;
                solutionMatrix[i][j] = 0;
                (*emptySpots)++;
            }
        }
    } else if (sudokuBacktracking(matrix, index + 1, emptySpots, calls, solutionMatrix)) {
        // Quando estamos em um número fixo devemos "ignorá-lo", chamar para o próximo índice e caso de certo retorne sucesso
        return 1;
    }

    return 0;
}

// Função que verifica se um certo índice e tentativa satisfazem as regras do sudokus
int checkSudokuCall(int **matrix, int lineIndex, int columnIndex, int try) {
    // Considerando um sudoku uma matriz [3][3] de matrizes [3][3], boxIndexLine e boxIndexColumn recebem os índices das matrizes externas
    int boxIndexLine = lineIndex / 3;
    int boxIndexColumn = columnIndex / 3;

    for (int i = 0; i < TAM_SUDOKU; i++) {
        // Se ja possui o número na linha ou na coluna retorna falso
        if (matrix [lineIndex][i] == try || matrix[i][columnIndex] == try) return 0;
    }

    //Percorre a matriz[3][3] interna
    for (int i = 0; i < TAM_SUDOKU / 3; i++) {
        for (int j = 0; j < TAM_SUDOKU / 3; j++) {
            // Se ja possui o número no bloco retorna falso
            if (matrix [i + (3 * boxIndexLine)] [j + (3 * boxIndexColumn)] == try) return 0;
        }
    }

    return 1;
}
