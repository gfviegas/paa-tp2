//
//  solution.c
//  backtracking
//
//  Created by Gustavo Viegas on 22/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "solution.h"

int isEmpty(SolutionNodePointer stack) {
    return (stack == NULL);
}

SolutionNodePointer allocNode() {
    SolutionNodePointer node = (SolutionNodePointer) malloc(sizeof(SolutionNode));
    if (!node) return NULL;
    return node;
}

SolutionNodePointer getLast(SolutionNodePointer stack) {
  SolutionNodePointer aux = stack;
  while (aux->next != NULL) aux = aux->next;
  return aux;
}

void createNode(SolutionNodePointer node, int line, int column) {
    if (node == NULL) node = allocNode();
    node->line = line;
    node->column = column;
    node->next = NULL;
}

void insertSolution(SolutionNodePointer stack, int line, int column) {
    SolutionNodePointer node = allocNode();
    createNode(node, line, column);

    if (isEmpty(stack)) {
        stack = node;
        return;
    }

    SolutionNodePointer aux = getLast(stack);
    aux->next = node;
}

void clearSolution(SolutionNodePointer stack) {
    SolutionNodePointer aux1 = stack, aux2;
    if (isEmpty(stack)) return;

    while (aux1->next != NULL) {
      aux2 = aux1;
      aux1 = aux1->next;
      free(aux2);
    }
}

void printSolution(SolutionNodePointer stack) {
    SolutionNodePointer aux = stack;

    printf("*** Imprimindo solução.. *** \n");
    while (aux != NULL) {
        printf("\t [%d][%d]", aux->line, aux->column);
        aux = aux->next;
    }
    printf("\n *** FIM *** \n");
}

SolutionNodePointer copySolution(SolutionNodePointer stack) {
    SolutionNodePointer copy = allocNode();
    copy->line = stack->line;
    copy->column = stack->column;
    copy->next = stack->next;

    return copy;
}
