/**
 * Arquivo principal, que inicia a interface/programa em modo análise ou normal
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#define NORMAL_MODE 0
#define ANALYSIS_MODE 1

#include <stdio.h>
#include <string.h>

#include "util/interface.h"

int main(int argc, const char * argv[]) {
    // Modo default é o modo normal
    int programMode = NORMAL_MODE;

    for (int i = 0; i < argc; i++)
        if (strcmp(argv[i], "-a") == 0) programMode = ANALYSIS_MODE;


    printHeader(programMode);
    return 0;
}
