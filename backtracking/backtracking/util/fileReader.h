//
//  fileReader.h
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef fileReader_h
#define fileReader_h

#include <stdio.h>
#include "logger.h"

#define FILE_PATH_BUFFER_SIZE 150
#define FILE_BUFFER_SIZE 255

void promptFilePath(char* filePath);

void openFile(FILE** file);

void readLine(FILE* file, char* buffer);

#endif /* fileReader_h */
