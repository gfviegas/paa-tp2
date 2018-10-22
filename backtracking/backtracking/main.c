//
//  main.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include <stdio.h>
#include "wordHunt/wordHunt.h"

int main(int argc, const char * argv[]) {
    char **matrix = NULL;
    int lines, columns;
    
    loadMatrix(&matrix, &lines, &columns);
    printMatrix(&matrix, lines, columns);
    search(&matrix, "casa", lines, columns);

    return 0;
}
