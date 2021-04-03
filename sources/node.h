/*
 * node.h
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#ifndef _NODE_H
#define _NODE_H

struct node{
	int info;
	struct node *next, *back;
	int index;
};

typedef struct node* PtNode;

PtNode createNode(int info);

#endif