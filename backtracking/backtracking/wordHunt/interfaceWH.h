/**
 * Gerencia e chama as funções relacionadas ao caça palavras, imprimindo e lendo
 * os dados necessários
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Gustavo Viegas
 */

#ifndef interfaceWH_h
#define interfaceWH_h

#define WORD_MAX_LENGTH 250

#include <stdio.h>

#include "wordHunt.h"
#include "../util/interface.h"
#include "../util/logger.h"

/**
 * Imprime a matriz carregada, em uma tabela estilizada
 * @param matrix  Matriz a ser impressa
 * @param lines   Quantidade de linhas da matriz
 * @param columns Quantidade de colunas da matriz
 */
void _printCurrentMatrix(char **matrix, int lines, int columns);

/**
 * Lê do usuário uma palavra a ser caçada e acha suas ocorrências no caça palavras.
 * @param matrix       Matriz com o caça palavras a ser buscado
 * @param lines        Quantidade de linhas da matriz
 * @param columns      Quantidade de colunas da matriz
 * @param analysisMode Flag se está no modo de análise (1) ou não (0)
 */
void _searchWord(char **matrix, int lines, int columns, int analysisMode);

/**
 * Limpa a tela e pede uma ação ao usuário: carregar um arquivo, buscar uma palavra ou voltar ao menu inicial
 * @param matrix       Matriz com o caça palavras a ser manipulado
 * @param lines        Quantidade de linhas da matriz
 * @param columns      Quantidade de colunas da matriz
 * @param analysisMode Flag se está no modo análise (1) ou não (0)
 */
void _promptAction(char **matrix, int *lines, int *columns, int analysisMode);

/**
 * Inicializa o ponteiro da matriz a ser utilizada, e aloca na memória os inteiros que salva linhas e colunas
 * @param analysisMode Flag se está no modo análise (1) ou não (0)
 */
void _wordHuntMenu(int analysisMode);

#endif /* interfaceWH_h */
