
#include "../util/fileReader.h"
#include "../util/logger.h"

#define TAM_SUDOKU 9
#define SUM_CHECK 45
#define CONVERSOR_ASCII 48
void loadSudoku(int ***matrix, char* filePath);

void allocMatrixSudoku(int ***matrix);

void createEmptyMatrix(int ***matrix);

void printSudokuLine(int index);

void printSudoku(int **matrix);

void printSolutionSudoku(int **matrix, int **solutionMatrix);

int solveSudoku(int **matrix, int *numTentativas, int ***solutionMatrix);

int isSudokuResolvido(int **matrix);

int backTracking(int **matrix, int index, int *numTentativas, int **solutionMatrix);

int canBeTry(int **matrix, int lineIndex, int columnIndex, int tenta);

void readSudoku(int ***matrix);
