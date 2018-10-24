//
//  interfaceS.h
//  backtracking
//
//  Created by Gustavo Viegas on 24/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef interfaceS_h
#define interfaceS_h

#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"
#include "../util/interface.h"
#include "../util/logger.h"

void _sudokuMenu(int analysisMode);

void _printAllSudoku(int ***matrix);

void _showResultSudoku(int ***matrix, int analysisMode);

#endif /* interfaceS_h */
