//
//  logger.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "logger.h"

void cprintf(AvailableColors color, const char* fmt, ...) {
    static const char* colors[] = {
        ANSI_COLOR_RED,
        ANSI_COLOR_GREEN,
        ANSI_COLOR_YELLOW,
        ANSI_COLOR_BLUE,
        ANSI_COLOR_MAGENTA,
        ANSI_COLOR_CYAN
    };
    
    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    printf("%s%s%s", colors[color], buffer, ANSI_COLOR_RESET);
}

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
        printf("%s=", ANSI_COLOR_CYAN);
    }
    
    printf("\n%s", ANSI_COLOR_RESET);
}
