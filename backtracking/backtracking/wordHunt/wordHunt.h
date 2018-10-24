/**
 * Gerencia e chama as funções relacionadas ao caça palavras, manipulando os arquivos,
 * matrizes e strings de busca, utilizando do backtracking
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 */

#ifndef wordHunt_h
#define wordHunt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/fileReader.h"
#include "../util/logger.h"

/**
 * Movimentos disponíveis para percorrer a matriz.
 */
typedef enum Movements {
    NONE, // Quando veio de "nenhum lugar", ou seja, da letra inicial.
    LEFT, // Movimento para esquerda
    RIGHT, // Movimento para direita
    BOTTOM // Movimento para baixo
} Movements;

/**
 * Aloca a memória para uma matriz de tamanho lines x columns
 * @param matrix  Ponteiro para a matriz de caracteres a ser criada
 * @param lines   Quantidade de linhas da matriz
 * @param columns Quantidade de colunas da matriz
 */
void createMatrix(char ***matrix, int lines, int columns);

/**
 * Percorre uma matriz, preenchendo toda posição dela com um asterisco
 * @param matrix  Ponteiro para a matriz de caracteres a ser criada
 * @param lines   Quantidade de linhas da matriz
 * @param columns Quantidade de colunas da matriz
 */
void fillMatrix(char ***matrix, int lines, int columns);

/**
 * A partir de uma arquivo de caça-palavras que o usuário fornece, cria e preenche a matriz com seus dados
 * @param matrix  Ponteiro para a matriz de caracteres a ser criada
 * @param lines   Ponteiro da quantidade de linhas da matriz
 * @param columns Ponteiro da quantidade de colunas da matriz
 */
void loadMatrix(char ***matrix, int *lines, int *columns);

/**
 * Imprime uma linha azul com o tamanho da matriz, para fazer uma borda, quebrando ou não linhas antes e depois
 * @param size     Tamanho da coluna da matriz
 * @param brBefore Quebrar (1) ou não (0) a linha antes da borda
 * @param brAfter  Quebrar (1) ou não (0) a linha depois da borda
 */
void printMatrixLine(int size, int brBefore, int brAfter);

/**
 * Imprime uma matriz de caça-palavras ou solução, entre uma bonita borda
 * @param matrix  Ponteiro para a matriz de caracteres a ser manipulada
 * @param lines   Quantidade de linhas da matriz
 * @param columns Quantidade de colunas da matriz
 * @param header  Mensagem a ser impressa no cabeçalho da borda
 */
void printMatrix(char ***matrix, int lines, int columns, char* header);

/**
 * Dado um caracter, verifica se ele está em uma dada posição de uma matriz
 * @param  matrix Ponteiro para a matriz de caracteres a ser manipulada
 * @param  query  Caracter a ser buscado
 * @param  line   Posição da linha da matriz a ser buscada
 * @param  column Posição da coluna da matriz a ser buscada
 * @return        Inteiro representando se o caracter está (1) na posição dada ou não (0)
 */
int checkMatch(char ***matrix, char query, int line, int column);

/**
 * Função de backtracking, buscando uma palavra recursivamente apenas nas direções baixo, esquerda e direita,
 * sem repetir direção ou ambiguidade de movimento. A função também conta a quantidade de ocorrências da palavra
 * na matriz e quantas chamadas recursivas foram feitas.
 * Se a palavra for encontrada no caça-palavras, ela é escrita na sua devida posição em uma matriz secundária (de resposta)
 * @param  matrix       Ponteiro para a matriz de caracteres a ser buscada (caça-palavras)
 * @param  lines        Quantidade de linhas da matriz
 * @param  columns      Quantidade de colunas da matriz
 * @param  lineIdx      Índice da linha da matriz da atual chamada recursiva
 * @param  columnIdx    Índice da coluna da matriz da atual chamada recursiva
 * @param  word         Palavra a ser buscada
 * @param  wordIdx      Índice do caracter da palavra da atual chamada recursiva
 * @param  wordLen      Tamanho da palavra a ser buscada
 * @param  resultMatrix Ponteiro para a matriz de resultado a ser escrita
 * @param  lastMovement Direção do último movimento
 * @param  calls        Ponteiro do inteiro representando quantas chamadas recursivas foram executadas
 * @param  occurrences  Ponteiro do inteiro representando quantas ocorrências da palavra foram encontradas
 * @return              Valor inteiro representando se a atual chamada tem uma ocorrência (>= 1) ou é sem-esperanças/não encontrada (0)
 */
int backtracking(char ***matrix, int lines, int columns, int lineIdx, int columnIdx, char* word, int wordIdx, int wordLen, char ***resultMatrix, Movements lastMovement, int* calls, int* occurrences);

/**
 * Percorre a matriz procurando a primeira letra de uma palavra a ser encontrada e inicia o processo de backtracking para cada uma
 * Contabiliza quantas chamadas e ocorrências foram feitas, e imprime os resultados
 * @param matrix       Ponteiro para a matriz de caracteres a ser buscada (caça-palavras)
 * @param word         Palavra a ser buscada
 * @param lines        Quantidade de linhas da matriz
 * @param columns      Quantidade de colunas da matriz
 * @param analysisMode Flag se está no modo de análise (1) ou não (0)
 */
void search(char ***matrix, char *word, int lines, int columns, int analysisMode);
#endif /* wordHunt_h */
