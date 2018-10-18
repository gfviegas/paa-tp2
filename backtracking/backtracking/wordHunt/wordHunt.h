//
//  wordHunt.h
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef wordHunt_h
#define wordHunt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/fileReader.h"
#include "../util/logger.h"

void loadMatrix(char ***matrix, int *matrixLines, int *matrixColumns);
void printMatrix(char **matrix, int lines, int columns);

#endif /* wordHunt_h */
