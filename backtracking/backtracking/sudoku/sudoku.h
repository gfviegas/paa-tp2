
#include "../util/fileReader.h"
#include "../util/logger.h"

#define TAM_SUDOKU 9
#define SUM_CHECK 45
#define CONVERSOR_ASCII 48
void loadSudoku(int ***matrix, char* filePath);

void printSudoku(int **matrix);

int solveSudoku(int **matrix, int *numTentativas);

int isSudokuResolvido(int **matrix);

int backTracking(int **matrix, int index, int *numTentativas);

int canBeTry(int **matrix, int lineIndex, int columnIndex, int tenta);

void readSudoku(int ***matrix);
