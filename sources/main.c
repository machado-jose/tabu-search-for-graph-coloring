/*
 * main.c
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdio.h>
#include <stdlib.h>

#include "setup.h"
#include "tabu_search.h"

int main(int argc, char const *argv[])
{
	
	/* Set Variables */
	GraphInfo graph_info;
	int color_number, max_iteration, max_color_number, *solution, i;
	unsigned long int seed = 0;

	/* Load Graph*/
	if(argc != 2)
	{
		fprintf(stderr, "%s: Execução incorreta do comando.\n", argv[0]);
		return 0;
	}
	setupGraph(&graph_info, argv[1]);

	/* Set Configuration to Tabu Search */
	printf("\n----- Tabu Search -----\r\n\n[-] Configuracoes: \r\n\n");
	printf("Digite o numero maximo de iterações: ");
	scanf("%d", &max_iteration);
	printf("Digite o numero maximo de cores: ");
	scanf("%d", &max_color_number);

	printf("\r\n[-] Analisando...\r\n\n");

	for(color_number = 1; color_number <= max_color_number; color_number++){
		solution = tabuSearch(&graph_info, color_number, max_iteration, &seed);
		if(solution != NULL){
			printf("[+] Numero Minimo de Cores igual a %d\n", color_number);
			break;
		}
		printf("[X] Numero Minimo de Cores igual a %d\n", color_number);
	}

	printf("\r\n[-] Resultado: \r\n\n");

	if(solution != NULL){
		printf("[+] A Solucao e: \n\n");
		for (i = 0; i < graph_info.vertice_number; i++)
		{
			printf("\t\tVertice %d: Cor %d\n", i+1, solution[i]);
		}
	}else{
		printf("[X] Nao foi possivel encontrar uma solucao!\n");
	}

	printf("\r\n---- Fim ----\r\n\n");

	/* Destroy Variables */
	free(solution);

	return 0;
}