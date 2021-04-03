/*
 * list.c
 *
 *  Created on: 3 de abr de 2021
 *  Author: José Gustavo
 */

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "list.h"

PtList createList(){
	PtList List = (PtList)malloc(sizeof(struct list));
	List->Start = NULL;
	List->Last = NULL;
	return List;
}

void storeList(PtList List, int* info){
	PtNode New_Node, Help_Node;
	int index = 0;
	int data = *(int*)(info);
	New_Node = createNode(data);
	if(!(List->Start)){			
		List->Start = New_Node;
		List->Last = New_Node;
	}else{
		Help_Node = List->Start;
		while(Help_Node->next){
			index = Help_Node->next->index;
			Help_Node = Help_Node->next;
		}
		index++;
		New_Node->back = Help_Node;
		New_Node->index = index;
		Help_Node->next = New_Node;
		List->Last = New_Node;
	}
}

void printList(PtList List){
	PtNode Help_Node = List->Start;
	if(!Help_Node){
		printf("\n\n\tList is empty");
		return;
	}
	while(Help_Node){
		printf("\t%d", (Help_Node->info));
		Help_Node = Help_Node->next;
	}
}

int lengthList(PtList List){
	if(List->Last != NULL){
		return (List->Last->index) + 1;
	}
	return 0;
}

int getInfo(PtList list, int i){
	PtNode help_node = list->Start;
	while(help_node){
		if((help_node->index) == i){
			return (help_node->info);
		}
		help_node = help_node->next;
	}
	return -1;
}

void writeInfo(PtList List, int i, int new_info){
	PtNode help_node = List->Start;
	while(help_node){
		if(help_node->index == i){
			help_node->info = new_info;
			return;
		}
		help_node = help_node->next;
	}
}

void changeStartLast(PtList List){
	PtNode delete_node = List->Start, help_node = List->Last;
	if(List->Start && List->Last){
		List->Last = help_node->back;
		List->Last->next = NULL;
		help_node->back = NULL;
		help_node->next = delete_node->next;
		help_node->index = 0;
		List->Start = help_node;
		free(delete_node);
	}
}

int removeInfo(PtList List){
	int info;
	info = List->Start->info;
	changeStartLast(List);
	return info;
}

void swap(PtList List, int* i, int* j)
{
	int bkp_info1, bkp_info2;
	bkp_info1 = getInfo(List, *(int*)(i));
	bkp_info2 = getInfo(List, *(int*)(j));
	writeInfo(List,*(int*)(i),bkp_info2);
	writeInfo(List,*(int*)(j),bkp_info1);
}

void clearList(PtList List){
	PtNode i;
	PtNode Help_Node = List->Start;
	while(Help_Node){
		i = Help_Node;
		Help_Node = Help_Node->next;
		free(i);
	}
	List->Start = NULL;
	List->Last = NULL;
}

void destroyList(PtList List){
	PtNode i;
	PtNode Help_Node = List->Start;
	while(Help_Node){
		i = Help_Node;
		Help_Node = Help_Node->next;
		free(i);
	}
	if(List){
		free(List);
	}
}