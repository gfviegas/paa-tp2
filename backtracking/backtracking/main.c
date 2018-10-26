//
//  main.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//
#define MODO_ANALISE 1
#define MODO_NORMAL 0

#include <stdio.h>
#include <string.h>
#include "util/interface.h"

int main(int argc, const char * argv[]) {
    // if(strcpy("analise", argv[1]) == 0)
    //     printHeader(MODO_ANALISE);
    // else
    //     printHeader(MODO_NORMAL);
    printHeader(MODO_ANALISE);
    return 0;
}
