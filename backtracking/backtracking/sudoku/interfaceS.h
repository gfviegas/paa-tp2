/**
 * Gerencia e chama as funções relacionadas ao sudoku, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */

#ifndef interfaceS_h
#define interfaceS_h

#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"
#include "../util/interface.h"
#include "../util/logger.h"

/**
 * Menu Principal para interface do Sudoku
 * @param analysisMode é 1 caso esteja no modo análise e 0 caso contrário
 */
void _sudokuMenu(int analysisMode);

/**
 * Lê do usuário uma das opções de sudoku disponíveis pelo sistema
 * @param sudokuChoice Ponteiro para o inteiro representando qual sudoku o usuário quer ver resolvido
 */
void _readSudokuChoice(int *sudokuChoice);

/**
 * Exibe todos os sudokus que temos de arquivo
 * @param matrix Ponteiro para a matriz com o sudoku
 */
void _printAllSudoku(int ***matrix);

/**
 * Resolve e exibe um sudokus
 * @param matrix       Matriz que contém o sudoku
 * @param analysisMode 1 caso esteja em modo análise e 0 caso contrário
 */
void _showResultSudoku(int ***matrix, int analysisMode);

#endif /* interfaceS_h */
