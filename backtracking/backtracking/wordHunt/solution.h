//
//  solution.h
//  backtracking
//
//  Created by Gustavo Viegas on 22/10/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef solution_h
#define solution_h

#include <stdlib.h>
#include <stdio.h>

typedef struct SolutionNode *SolutionNodePointer;
typedef struct SolutionNode {
    int line;
    int column;
    SolutionNodePointer next;
} SolutionNode;

int isEmpty(SolutionNodePointer stack);

void createNode(SolutionNodePointer node, int line, int column);

void insertSolution(SolutionNodePointer stack, int line, int column);

SolutionNodePointer getLast(SolutionNodePointer stack);

void clearSolution(SolutionNodePointer stack);

void printSolution(SolutionNodePointer stack);

SolutionNodePointer copySolution(SolutionNodePointer stack);

#endif /* solution_h */
