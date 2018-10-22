//
//  fileReader.c
//  paa-tp2
//
//  Created by Gustavo Viegas on 16/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "fileReader.h"


void promptFilePath(char* filePath) {
    printf("Insira o caminho do arquivo de leitura: ");
    scanf("%s", filePath);
}

void openFile(FILE** file, char *filePath) {;

    *file = fopen(filePath, "r");

    if (*file == NULL) {
        char message[300];
        sprintf(message, "O arquivo %s não existe ou não pode ser lido corretamente.\n Confira o caminho inserido e digite outro.", filePath);
        logError(message);
        return openFile(file, filePath);
    }

    //logInfo("Arquivo carregado com sucesso.");
}

void readLine(FILE* file, char* buffer) {
    fgets(buffer, FILE_BUFFER_SIZE, (FILE*) file);
}
