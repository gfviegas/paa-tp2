/**
 * Gerencia e chama as funções relacionadas ao sudoku, manipulando os arquivos,
 * e matrizes, utilizando do backtracking
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 * @author Heitor Passeado
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/fileReader.h"
#include "../util/logger.h"

// Número de linhas/colunas do sudoku
#define TAM_SUDOKU 9
//  para traduzir um char para inteiro, utilizado na leitura de caracteres para construir um sudoku dinamicamente
#define CONVERSOR_ASCII 48

/**
 * Função auxiliar para imprimir uma linha para dividir o sudoku
 * @param index Indice da linha da matriz sendo impressa, para verificar os caracteres de borda
 */
void printSudokuLine(int index);

/**
 * Exibe o sudoku no terminal com os caracteres '|' e '--' para separar os nove blocos do sudoku1
 * @param matrix Matriz que contém o sudoku a ser exibido
 */
void printSudoku(int **matrix);

/*
 * Com um caminho para o arquivo, carrega uma matriz com o sudoku (0 é igual a espaço vazio)
 * @param matrix   Matriz que terá o sudoku para ser manipulada
 * @param filePath Caminho do arquivo com extensão
 */
void loadSudoku(int ***matrix, char* filePath);

/**
 * Aloca a memória necessária para uma matriz que represente um sudoku
 * @param matrix Ponteiro para a matriz a ser manipulada
 */
void allocMatrixSudoku(int ***matrix);

/**
 * Cria uma matriz do tamanho do sudoku com todos os registros zerado
 * @param matrix Ponteiro para a matriz a ser manipulada
 */
void createEmptyMatrix(int ***matrix);

/*
 * Função chamada caso o usuário queira escrever o sudoku na mão
 * @param matrix [Matriz que terá o sudoku armazenado]
 */
void readSudoku(int ***matrix);

/**
 * Imprime um sudoku resolvido, colorindo os caracteres escritos para destacá-los
 * @param matrix         Matriz do sudoku original
 * @param solutionMatrix Matriz do sudoku resolvido
 */
void printSolutionSudoku(int **matrix, int **solutionMatrix);

/**
 * Conta a quantidade de 0s, ou elementos a serem escritos, na matriz
 * @param  matrix Matriz do sudoku a ser contado
 * @return        Valor inteiro representando a quantidade de valores 0 nela presentes
 */
int countEmptySpots(int **matrix);

/**
* Função usada para encapsular os parâmetros passados no backTracking, resolve o sudoku
* @param  matrix        Matriz que contém o sudoku a ser resolvido
* @param  calls         Número de tentativas, passada como ponteiro para contabilizar quantas chamadas foram efetuadas
* @return               1 se o sudoku foi resolvido, 0 se ele não possui solução
*/
int solveSudoku(int **matrix, int *calls, int ***solutionMatrix);

/**
 * Função recursiva que resolve o sudoku por backTracking
 * @param  matrix           Matriz que contém o sudoku
 * @param  index            Índice unidemensional da matriz
 * @param  calls            Número de tentativas
 * @param  solutionMatrix   Matriz que contém somente os caracteres escritos pelo backtracking
 * @return                  1 (sucesso) caso aquela tentativa seja bem sucedida e 0 caso aquela tentativa falhe
 */
int sudokuBacktracking(int **matrix, int index, int *emptySpots, int *calls, int **solutionMatrix);

/**
 * Função que verifica se um certo índice e tentativa satisfazem as regras do sudokus
 * @param  matrix      Matriz que contém o sudokus
 * @param  lineIndex   Índice da linhas
 * @param  columnIndex Índice da colunas
 * @param  tenta       Número que verificaremos a validade
 * @return             1 caso possa ser colocado e 0 caso contŕario
 */
int checkSudokuCall(int **matrix, int lineIndex, int columnIndex, int try);
