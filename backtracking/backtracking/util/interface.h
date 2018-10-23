#ifndef interface_h
#define interface_h
#define LINE_SIZE 60

void printLinha();

void printHeader(int modo);

void printMenuInicial(int modo);

void MenuSudoku();

void printAllSudoku(int ***matrix);

void showResult(int ***matrix, int modo);
#endif
