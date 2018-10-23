#ifndef interface_h
#define interface_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "../sudoku/sudoku.h"
#include "../wordHunt/interfaceWH.h"

void printLine(void);

void printHeader(int modo);

void printMenuInicial(int modo);

void MenuSudoku(int modo);

void printAllSudoku(int ***matrix);

void showResult(int ***matrix, int modo);

#endif
