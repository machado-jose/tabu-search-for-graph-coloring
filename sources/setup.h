/*
 * setup.h
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#ifndef SETUP_H_
#define SETUP_H_

#include "list.h"

typedef struct
{
	int vertice_number;
	int edge_number;
	int** graph;
} GraphInfo;

void setupGraph(GraphInfo *graph_info, const char *path);
int* setupColor(int color_number);
int* setupInitialSolution(unsigned long int *seed, int vertice_number, int color_number);
int** setupTabuTable(int vertice_number, int color_number);
void resetVector(int* vector, int n);
void setCandidates(PtList move_candidates, int* move_candidates_bkp, int n);
void copySolution(int* new_solution, int* solution, int n);
void resetAspirationLevel(int* vector, int n);

#endif
