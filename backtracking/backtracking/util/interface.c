/**
 * Gerencia e chama as funções relacionadas aos puzzles, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#include "interface.h"

void prePrompt(void) {
    cprintf(YELLOW, "->  ");
}

void printHeader(int analysisMode) {
    system("clear");
    if (analysisMode) cprintf(RED, " *** \n [STATS] MODO ANALISE ATIVADO! \n *** \n");

    printf("\n\n");
    printLine();
    cprintf(BLUE, "_____                      _   _ _           _       \n| ___ \\                    | | | (_)         | |\n| |_/ / ___ _ __ ___ ______| | | |_ _ __   __| | ___\n| ___ \\/ _ \\ '_ ` _ \\______| | | | | '_ \\ / _` |/ _ \\\n| |_/ /  __/ | | | | |     \\ \\_/ / | | | | (_| | (_) |\n\\____/ \\___|_| |_| |_|      \\___/|_|_| |_|\\__,_|\\___/\n");
    cprintf(BLUE, "\n \t Ao Resolvedor COQUETEL !");
    printLine();

    printMenu(analysisMode);
}

void printMenu(int analysisMode) {
    int choice;

    cprintf(GREEN, "\n \n Selecione qual quebra-cabeça COQUETEL você deseja resolver : \n\n");
    cprintf(GREEN, "1 - Caça-palavra\n");
    cprintf(GREEN, "2 - Sudoku\n");
    cprintf(GREEN, "3 - Sair\n");
    prePrompt();
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            _wordHuntMenu(analysisMode);
            break;
        case 2:
            _sudokuMenu(analysisMode);
            break;
        case 3:
            return;
        default:
            cprintf(RED, "\n\n * Digite apenas 1 ou 2, ainda não temos tantos quebra-cabeças :(\n");
            return printMenu(analysisMode);
    }
}
