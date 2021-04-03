/*
 * convert.c
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdlib.h>
#include <string.h>

#include "convert.h"

#define CONVSTR_BUF 5

int convert_atoi(char *str, int str_sz, int radix)
{
	int res;
	char buff[CONVSTR_BUF], *tmp_ptr;

	memcpy(&buff[0], str, str_sz);
	buff[str_sz] = '\0';
	res = strtol(&buff[0], &tmp_ptr, radix);

	return res;
}