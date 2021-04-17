/*
 * tabu_search.c
 *
 *  Created on: 5 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdio.h>
#include <stdlib.h>

#include "setup.h"
#include "list.h"

int* tabuSearch(GraphInfo *graph_info, int color_number, int max_iteration, unsigned long int *seed)
{
	
	/* Set Variables */
	PtList move_candidates = NULL;

	int *colors, *solution, *new_solution, **tabu, *move_candidates_bkp, *aspiration_level;
	int node, random_node, new_color, iteration = 0, reps = 100;
	int conflict_count, new_conflict_count, aspiration_value, length_move_candidates , i, j, k;

	/* Colors are represented by numbers, [0, 1, ..., k-1] */
	colors = setupColor(color_number);

	/* Initial Solution: Random Mode */
	solution = setupInitialSolution(seed, graph_info->vertice_number, color_number);

	/* Initial New Solution */
	new_solution = (int *)malloc(graph_info->vertice_number * sizeof(int));

	/* Initial Tabu Table
	* Row: Nodes
	* Column: Colors
	*/
	tabu = setupTabuTable(graph_info->vertice_number, color_number);

	/* Initial Move Candidates */
	move_candidates = createList();

	/* Initial Aspiration Level
	* A(z) is represented by Vector
	*/
	aspiration_level = (int *)malloc(graph_info->edge_number * sizeof(int));
	/* The reset value is -10 */
	resetAspirationLevel(aspiration_level, graph_info->edge_number);

	/* Initial Move Candidates Bkp */
	move_candidates_bkp = (int*)malloc(graph_info->vertice_number * sizeof(int));

	while(iteration < max_iteration){
		conflict_count = 0;
		resetVector(move_candidates_bkp, graph_info->vertice_number);
		clearList(move_candidates);

		for(i = 0; i < graph_info->vertice_number; i++){
			for(j = i+1; j < graph_info->vertice_number; j++){
				if(graph_info->graph[i][j] > 0 && solution[i] == solution[j]){
					/* Move Candidates */
					conflict_count++;				
					move_candidates_bkp[i] = 1;
					move_candidates_bkp[j] = 1;
				}
			}
		}

		/* Break iteration if found the best solution */
		if(conflict_count == 0){
			break;
		}

		setCandidates(move_candidates, move_candidates_bkp, graph_info->vertice_number);
		length_move_candidates = lengthList(move_candidates);

		for(k = 0; k < reps; k++){
			/* Choose a node to move */
			random_node = randomInt(seed, length_move_candidates);
			node = getInfo(move_candidates, random_node);
			/* Choose a new color */
			new_color = colors[randomInt(seed, color_number)];
			/* Set new solution with new color */
			copySolution(new_solution, solution, graph_info->vertice_number);
			new_solution[node] = new_color;
			/* Count adjacent pairs with the same color in the new solution */
			new_conflict_count = 0;
			for(i = 0; i < graph_info->vertice_number; i++){
				for(j = i+1; j < graph_info->vertice_number; j++){
					if(graph_info->graph[i][j] > 0 && new_solution[i] == new_solution[j]){
						/* Move Candidates */
						new_conflict_count++;
					}
				}
			}
			/* Verify if found an improved solution */
			if(new_conflict_count < conflict_count){
				/* Set aspiration value */
				if(aspiration_level[conflict_count] == -10){
					aspiration_value = conflict_count - 1;
				}else{
					aspiration_value = aspiration_level[conflict_count];
				}
				/* Verify the cost */
				if(new_conflict_count <= aspiration_value){
					/* Set A(f(s)) = f(s') - 1 */
					aspiration_level[conflict_count] = new_conflict_count - 1;
					/* Permit Tabu Move if it is better any prior */
					if(tabu[node][new_color] == 1){
						/* Remove Tabu Status (Good Move) */
						tabu[node][new_color] = 0;
						break;
					}
				}else{
					if(tabu[node][new_color] == 1){
						continue;
					}
				}
				break;
			}
		}

		/* At this point, either found a better solution,
		*  or ran out of reps, using the last solution generated 
		*/

		/* Add Tabu Status the current node color (Bad Move) */
		tabu[node][solution[node]] = 1;
		/* Set new solution */
		copySolution(solution, new_solution, graph_info->vertice_number);
		iteration++;
	}

	/* Destroy Variables */
	for(i = 0; i < graph_info->vertice_number; i++){
		free(tabu[i]);
	}
	free(tabu);
	destroyList(move_candidates);
	free(colors);
	free(new_solution);
	free(move_candidates_bkp);
	free(aspiration_level);

	if(conflict_count != 0){
		free(solution);
		return NULL;
	}else{
		return solution;	
	}
}