#ifndef interface_h
#define interface_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "../sudoku/sudoku.h"
#include "../sudoku/interfaceS.h"
#include "../wordHunt/interfaceWH.h"

void prePrompt(void);

void printLine(void);

void printHeader(int analysisMode);

void printMenuInicial(int analysisMode);



#endif
