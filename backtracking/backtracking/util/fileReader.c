/**
 * Gerencia e chama as funções relacionadas ao sudoku, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#include "fileReader.h"

void promptFilePath(char* filePath) {
    cprintf(GREEN, "\nInsira o caminho do arquivo de leitura: \n");
    prePrompt();
    scanf("%s", filePath);
}

void openFile(FILE** file, char *filePath) {
    *file = fopen(filePath, "r");

    if (*file == NULL) {
        cprintf(RED, "O arquivo %s não existe ou não pode ser lido corretamente.\n Confira o caminho inserido e digite outro.\n\n", filePath);
        promptFilePath(filePath);
        return openFile(file, filePath);
    }
}

void readLine(FILE* file, char* buffer) {
    fgets(buffer, FILE_BUFFER_SIZE, (FILE*) file);
}
