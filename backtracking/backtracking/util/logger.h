//
//  logger.h
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef logger_h
#define logger_h

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>


// Código ANSI das cores para colorir o terminal
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#define LINE_SIZE 60
#define CPRINTF_BUFFER_LENGTH 4096

typedef enum AvailableColors {
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN
} AvailableColors;

void cprintf(AvailableColors color, const char* fmt, ...);

void logInfo(char* message);

void logWarning(char* message);

void logError(char* message);

void printLine(void);

#endif /* logger_h */
