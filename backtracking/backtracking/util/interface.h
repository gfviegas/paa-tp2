#ifndef interface_h
#define interface_h
#define LINE_SIZE 60

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "../sudoku/sudoku.h"
#include "../wordHunt/interface.h"

void printLinha(void);

void printHeader(int modo);

void printMenuInicial(int modo);

void MenuSudoku(int modo);

void printAllSudoku(int ***matrix);

void showResult(int ***matrix, int modo);
#endif
