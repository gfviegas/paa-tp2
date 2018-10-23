//
//  interfaceWH.h
//  backtracking
//
//  Created by Gustavo Viegas on 23/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef interfaceWH_h
#define interfaceWH_h

#include <stdio.h>
#include "wordHunt.h"

void _loadMatrix(char ***matrix, int *lines, int *columns);
void _printCurrentMatrix(char **matrix, int lines, int columns);
void _searchWord(char **matrix, int lines, int columns, int analysisMode);
void _promptAction(char **matrix, int *lines, int *columns, int analysisMode);
void _wordHuntMenu(int analysisMode);

#endif /* interfaceWH_h */
