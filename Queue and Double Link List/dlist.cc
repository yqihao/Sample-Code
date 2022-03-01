#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include<time.h> 

#include "timer.c"

struct NODE{
	NODE* prev;
	NODE* next;
	int data;
};

struct LIST{
	NODE* first;
	NODE* last;
	int length;
};

void addNodeFront(LIST *list, NODE* node);
void addNodeBack(LIST *list, NODE* node);
NODE *removeNode(LIST *list, int n);
NODE *getFirstNode(LIST *list);
NODE *getLastNode(LIST *list);
NODE *getPrevNode(NODE* node);
NODE *getNextNode(NODE* node);
NODE *srearchNode(LIST* list, int key);
LIST *createList();
NODE *createNode(int i);

int
main (int argc, char* argv[])
{
	int N = -1;
	
	if (argc == 2) {
		N = atoi (argv[1]);
		assert (N > 0);
		printf("N = %d\n", N);
	} else {
		fprintf (stderr, "usage: %s <n>\n", argv[0]);
		fprintf (stderr, "where <n> is the length of the list to sort.\n");
		return -1;
	}
	
	srand(time(0)); 
	
	stopwatch_init();
	struct stopwatch_t* timer = stopwatch_create();
	assert(timer);

	int i, randValue, counter = 0, testTimes = 10;
	long double avg_time = 0.0;

	LIST* list = createList();
	
	for (i = 1; i < N + 1; i++){
		//printf("i = %d\n", i);
		//printf("node = createNode(i);");
		NODE *node = createNode(i);
		//printf("addNodeBack(list, node);");
		addNodeBack(list, node);
	}
	
	for (i = 0; i < testTimes; i++){
		
		randValue = rand() % N + 1;
		//printf("Random Value: %d\n", randValue);
		//start timer
		stopwatch_start(timer);
		
		NODE *node = removeNode(list, randValue);
		addNodeFront(list, node);
		
		//stop timer
		long double time = stopwatch_stop (timer);
		avg_time = avg_time + time;
		/*
		node = list->first;
		while (node){
			printf("%d ", node->data);
			node = node->next;
		}
		printf("\n");
		*/
	}
	
	avg_time = avg_time / (long double)testTimes;
	printf("Average Time: %Lg.\n", avg_time);
	stopwatch_destroy (timer);
}

void addNodeFront(LIST *list, NODE* node){
	if (list->length == 0){
		list->first = node;
		list->last = node;
	} else{
		//printf("node->prev = list->last;");
		node->next = list->first;
		//printf("list->last->next = node;");
		list->first->prev = node;
		//printf("node->prev = list->last;");
		list->first = node;
	}
	list->length++;
}

void addNodeBack(LIST *list, NODE* node){
	
	if (list->length == 0){
		list->first = node;
		list->last = node;
	} else{
		//printf("node->prev = list->last;");
		node->prev = list->last;
		//printf("list->last->next = node;");
		list->last->next = node;
		//printf("node->prev = list->last;");
		list->last = node;
	}
	list->length++;
}

NODE *removeNode(LIST *list, int n){
	NODE* A = list->first;
	while(list->length != 0){
		if (A->data == n){
			if (list->length == 1){
				list->first = NULL;
				list->last = NULL;
				A->prev = NULL;
				A->next = NULL;
				list->length--;
				break;
			}
			if (A == list->first){
				list->first = A->next;
				A->next->prev = NULL;
				A->next = NULL;
				list->length--;
				break;
			}
			if (A == list->last){
				list->last = A->prev;
				A->prev->next = NULL;
				A->prev = NULL;
				list->length--;
				break;
			}
			A->prev->next = A->next;
			A->next->prev = A->prev;
			A->prev = NULL;
			A->next = NULL;
			list->length--;
			if (list->length == 0){
				list->first = NULL;
				list->last = 0;
			}
			break;
		}
		A = A->next;
	}
	return A;
}

NODE *getFirstNode(LIST *list){
	return list->first;
}

NODE *getLastNode(LIST *list){
	return list->last;
}

NODE* getPrevNode(NODE* node){
	return node->prev;
}

NODE *getNextNode(NODE* node){
	return node->next;
}

NODE *srearchNode(LIST* list, int key){
	NODE* temp;
	temp = list->first;
	while (temp != NULL){
		if (temp->data == key)
			return temp;
	}
	return NULL;
}

LIST *createList(){
	LIST* A = (LIST* )malloc(sizeof(LIST));
	assert(A);
	A->first = NULL;
	A->last = NULL;
	A->length = 0;
	return A;
}

NODE *createNode(int i){
	//printf("NODE* A = (NODE* )malloc(sizeof(NODE));");
	NODE* A = (NODE* )malloc(sizeof(NODE));
	assert(A);
	//printf("A->data = i;");
	A->data = i;
	//printf("A->prev = NULL;");
	A->prev = NULL;
	//printf("A->next = NULL;");
	A->next = NULL;
	return A;
}