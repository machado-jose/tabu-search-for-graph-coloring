/*
 * setup.c
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "setup.h"
#include "convert.h"

#include "random.h"
#include "list.h"

#define MAX_LEN 256

void setupGraph(GraphInfo *graph_info, const char *path){
	FILE *file;
	char line[MAX_LEN], *token;
	unsigned short int i, j;
	int **graph;

	if( (file = fopen(path, "r")) == NULL)
	{
		fprintf(stderr, "%s: Nao foi possivel abrir o arquivo\n", path);
	}

	/* Gets vertice and edge numbers*/
	fgets(line, MAX_LEN - 1, file);
	token = strtok(line, " ");
	graph_info->vertice_number = convert_atoi(token, strlen(token), 10);
	token = strtok(NULL, " ");
	graph_info->edge_number = convert_atoi(token, strlen(token), 10);

	/* Create matrix */
	graph = (int **)malloc(graph_info->vertice_number * sizeof(int*));
	for (i = 0; i < graph_info->vertice_number; i++)
	{
		graph[i] = (int *)malloc(graph_info->vertice_number * sizeof(int));
	}
	
	/* Fill matrix*/
	i = 0;
	j = 0;
	while(fgets(line, MAX_LEN - 1, file))
	{
		token = strtok(line, " ");
		while(token != NULL){
			graph[i][j] = convert_atoi(token, strlen(token), 10);
			j++;
			token = strtok(NULL, " ");
		}
		i++;
		j = 0;
	}

	/* Saving in graph_info */
	graph_info->graph = graph;

	/* Closing function */
	fclose(file);
}

int* setupColor(int color_number){
	int *colors, i;
	colors = (int *)malloc(color_number * sizeof(int));
	for (i = 0; i < color_number; ++i)
	{
		colors[i] = i;
	}
	return colors;
}

int* setupInitialSolution(unsigned long int *seed, int vertice_number, int color_number){
	int *solution, i;
	solution = (int *)malloc(vertice_number * sizeof(int));
	for(i = 0; i < vertice_number; i++){
		solution[i] = randomInt(seed, color_number);
	}
	return solution;
}

int** setupTabuTable(int vertice_number, int color_number){
	int i, j;
	int** tabu;
	tabu = (int **)malloc(vertice_number * sizeof(int*));

	for (i = 0; i < vertice_number; i++)
	{
		tabu[i] = (int *)malloc(color_number * sizeof(int));
	}

	for(i = 0; i < vertice_number; i++){
		for(j = 0; j < color_number; j++){
			tabu[i][j] = 0;
		}
	}

	return tabu;
}

void resetVector(int* vector, int n){
	int i;
	for(i = 0; i < n; i++){
		vector[i] = 0;
	}
}

void resetAspirationLevel(int* vector, int n){
	int i;
	for(i = 0; i < n; i++){
		vector[i] = -10;
	}
}

void setCandidates(PtList move_candidates, int* move_candidates_bkp, int n){
	int i;
	for(i = 0; i < n; i++){
		if(move_candidates_bkp[i] == 1){
			storeList(move_candidates, &i);
		}
	}
}

void copySolution(int* new_solution, int* solution, int n){
	int i;
	for(i = 0; i < n; i++){
		new_solution[i] = solution[i];
	}
}
