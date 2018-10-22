
#include "../util/fileReader.h"
#include "../util/logger.h"

#define TAM_SUDOKU 9
#define SUM_CHECK 45
#define CONVERSOR_ASCII 48
void loadSudoku(int ***matrix);

void printSudoku(int **matrix);

void solveSudoku(int **matrix);

int checaVetor(int *vetor);

int isSudokuResolvido(int **matrix);

int backTracking(int **matrix, int index);

int canBeTry(int **matrix, int lineIndex, int columnIndex, int tenta);
