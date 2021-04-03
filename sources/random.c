/*
 * random.c
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdlib.h>
#include <time.h>

int randomInt(unsigned long int *seed, int n)
{
	int value;

	srand( time(NULL) + *seed );
	value = rand() % n;
	*seed += 1;

	return value;
}