/*
 * node.c
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

PtNode createNode(int info){
	PtNode New_Node = (PtNode)malloc(sizeof(struct node));
	New_Node->info = info;
	New_Node->next = NULL;
	New_Node->back = NULL;
	New_Node->index = 0;
	return New_Node;
}