//
//  interface.h
//  backtracking
//
//  Created by Gustavo Viegas on 23/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef interface_h
#define interface_h

#include <stdio.h>

#include "wordHunt.h"
#include "../util/interface.h"
#include "../util/logger.h"

void _loadMatrix(char ***matrix, int *lines, int *columns);
void _printCurrentMatrix(char **matrix, int lines, int columns);
void _searchWord(char **matrix, int lines, int columns);
void _promptAction(char **matrix, int *lines, int *columns);
void _wordHuntMenu(int mode);

#endif /* interface_h */
