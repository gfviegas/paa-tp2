/**
 * Gerencia e chama as funções relacionadas ao caça palavras, manipulando os arquivos,
 * matrizes e strings de busca, utilizando do backtracking
 *
 * Gustavo Viegas (3026) e Heitor Passeado (3055)
 */

#include "wordHunt.h"

// Aloca a memória para uma matriz de tamanho lines x columns
void createMatrix(char ***matrix, int lines, int columns) {
    *matrix = (char **) malloc(lines * sizeof(char *));

    for (int i = 0; i < lines; i++)
        (*matrix)[i] = (char *) malloc(columns * sizeof(char));
}

// Percorre uma matriz, preenchendo toda posição dela com um asterisco
void fillMatrix(char ***matrix, int lines, int columns) {
    for (int i = 0; i < lines; i++)
        for (int j = 0; j < columns; j++)
            (*matrix)[i][j] = '*';
}

// A partir de uma arquivo de caça-palavras que o usuário fornece, cria e preenche a matriz com seus dados
void loadMatrix(char ***matrix, int *lines, int *columns) {
    char currentLine[FILE_BUFFER_SIZE];
    char fileName[FILE_BUFFER_SIZE];
    FILE *file = NULL;

    if (*matrix != NULL) free(*matrix);

    promptFilePath(fileName);
    openFile(&file, fileName);

    fscanf(file, "%d %d\n", lines, columns);

    createMatrix(matrix, *lines, *columns);

    for (int i = 0; i < *lines; i++) {
        readLine(file, currentLine);
        for (int j = 0; j < *columns; j++)
            (*matrix)[i][j] = currentLine[j];
    }

    fclose(file);
}

// Imprime uma linha azul com o tamanho da matriz, para fazer uma borda, quebrando ou não linhas antes e depois
void printMatrixLine(int size, int brBefore, int brAfter) {
    if (brBefore) printf("\n");
    for (int i = 0; i <= size + 1; i++)
        cprintf(BLUE, "---");
    if (brAfter) printf("\n");
}

// Imprime uma matriz de caça-palavras ou solução, entre uma bonita borda
void printMatrix(char ***matrix, int lines, int columns, char* header) {
    int precision = ((columns * 3) / 2) + ((int) strlen(header) / 2);

    printMatrixLine(columns, 1, 1);
    cprintf(MAGENTA, "%*s", precision, header);
    printMatrixLine(columns, 1, 1);

    for (int i = 0; i < lines; i++) {
        cprintf(BLUE, " | ");
        for (int j = 0; j < columns; j++)
            cprintf(CYAN, " %c ", (*matrix)[i][j]);
        cprintf(BLUE, " |\n");
    }

    printMatrixLine(columns, 0 , 1);
}

// Dado um caracter, verifica se ele está em uma dada posição de uma matriz
int checkMatch(char ***matrix, char query, int line, int column) {
    if (matrix == NULL) return 0;

    char matrixValue = (*matrix)[line][column];
    return (line >= 0 && column >= 0 && (query == matrixValue));
}

/* Função de backtracking, buscando uma palavra recursivamente apenas nas direções baixo, esquerda e direita,
  sem repetir direção ou ambiguidade de movimento. A função também conta a quantidade de ocorrências da palavra
  na matriz e quantas chamadas recursivas foram feitas.
  Se a palavra for encontrada no caça-palavras, ela é escrita na sua devida posição em uma matriz secundária (de resposta) */
int backtracking(char ***matrix, int lines, int columns, int lineIdx, int columnIdx, char* word, int wordIdx, int wordLen, char ***resultMatrix, Movements lastMovement, int* calls, int* occurrences) {
    int successCalls = 0;
    (*calls)++; // Incrementa a quantidade de chamadas recursivas

    // Se os indices de procura nao estao na matriz, entao é sem-esperança.
    if (lineIdx < 0 || columnIdx < 0 || lineIdx >= lines || columnIdx >= columns) return 0;

    // Letra a ser buscada na atual chamada recursiva
    char query = word[wordIdx];

    // Se estou em uma posição cuja letra procurada nao está presente, não adianta continuar.
    if (!checkMatch(matrix, query, lineIdx, columnIdx)) return 0;

    // Acabou se estou procurando a n-esima letra da palavra e ela está na posicao certa
    if (wordIdx == (wordLen - 1)) {
        (*resultMatrix)[lineIdx][columnIdx] = query;
        (*occurrences)++;
        return 1;
    }

    // Incrementa o indice pra procurar a próxima letra.
    wordIdx++;

    // Para cada direção, se procura a próxima letra.
    for (Movements i = LEFT; i <= BOTTOM; i++) {
        if (i == lastMovement) continue;
        if ((i == LEFT || i == RIGHT) & (lastMovement == LEFT || lastMovement == RIGHT)) continue;

        int nextLine = (i == BOTTOM) ? lineIdx + 1 : lineIdx;
        int nextColumn = (i == LEFT) ? columnIdx - 1 : (i == RIGHT) ? columnIdx + 1 : columnIdx;

        // Se ao fim da call stack houve um retorno verdadeiro, escreve na matriz de resultados na atual posição
        if (backtracking(matrix, lines, columns, nextLine, nextColumn, word, wordIdx, wordLen, resultMatrix, i, calls, occurrences)) {
            (*resultMatrix)[lineIdx][columnIdx] = query;
            successCalls++;
        }
    }

    return successCalls;
}

/* Percorre a matriz procurando a primeira letra de uma palavra a ser encontrada e inicia o processo de backtracking para cada uma
  Contabiliza quantas chamadas e ocorrências foram feitas, e imprime os resultados */
void search(char ***matrix, char *word, int lines, int columns, int analysisMode) {
    int results = 0;
    int calls = 0;
    int wordLen = (int)(strlen(word));
    char **resultMatrix;

    createMatrix(&resultMatrix, lines, columns);
    fillMatrix(&resultMatrix, lines, columns);

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if ((*matrix)[i][j] == word[0])
                backtracking(matrix, lines, columns, i, j, word, 0, wordLen, &resultMatrix, NONE, &calls, &results);
        }
    }

    if (analysisMode) cprintf(RED, "[STATS] Teve %d chamadas recursivas\n", calls);

    cprintf(RED, "Foram encontradas %d ocorrências\n", results);

    if (results > 0)
        printMatrix(&resultMatrix, lines, columns, "Resultado");
    else
        cprintf(RED, "\n ** Não foi encontrada a palavra %s! ** \n", word);

    free(resultMatrix);
}
