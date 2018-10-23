//
//  logger.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "logger.h"

void logInfo(char* message) {
    printf("%s %s %s \n", ANSI_COLOR_BLUE, message, ANSI_COLOR_RESET);
}

void logWarning(char* message) {
    printf("%s %s %s \n", ANSI_COLOR_YELLOW, message, ANSI_COLOR_RESET);
}

void logError(char* message) {
    printf("%s %s %s \n", ANSI_COLOR_RED, message, ANSI_COLOR_RESET);
}

void printLine (void) {
    int i;
    printf("\n");

    for (i = 0; i < LINE_SIZE; i++) {
        printf("=");
    }
    
    printf("\n");
}
