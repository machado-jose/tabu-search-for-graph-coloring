/*
 * list.h
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#ifndef _LIST_H
#define _LIST_H

#include "node.h"

struct list
{
	PtNode Start, Last;
};

typedef struct list *PtList;

PtList createList();
void storeList(PtList List, int* info);
void printList(PtList List);
int lengthList(PtList List);
int getInfo(PtList list, int i);
void writeInfo(PtList List, int i, int new_info);
void changeStartLast(PtList List);
void swap(PtList List, int* i, int* j);
int removeInfo(PtList List);
void clearList(PtList List);
void destroyList(PtList List);

#endif