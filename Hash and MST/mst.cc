/////////////////////////////////////////////////////////////////////////////////
//MST
//Qihao Yu
//EECS 114
//
/////////////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <time.h> 
#include <string.h>

#include "timer.c"

struct VERTICE{
	VERTICE* prev;
	VERTICE* next;
	int A;
	int B;
	float weight;
};

struct LIST{
	VERTICE* first;
	VERTICE* last;
	int length;
};

void addFront(LIST *list, VERTICE* vertice);
void addBack(LIST *list, VERTICE* vertice);
LIST *createList();
VERTICE *createVertice();
VERTICE *searchMinimum(LIST* list, int verticeA, int verticeB, int verticeC, int verticeD, int *verticeList);
VERTICE *removeVertice(LIST *list, VERTICE *vertice);

int main(int argc, char** argv){
	
	int i;
	char *filename;
	char line[60];
	FILE *fp;
	float minWeight = 1.0;
	VERTICE *minVertice;
	
	if (argc == 2) {
		filename = argv[1];
		printf("File Name = %s\n", filename);
	} else {
		fprintf (stderr, "usage: %s <n>\n", argv[0]);
		fprintf (stderr, "where <n> is the name of input file.\n");
		return -1;
	}

	if (!( fp = fopen( filename, "rb" ) ))
	{
		fprintf( stderr, "error: couldn't open %s\n", argv[1] );
		exit(1);
	}
	
	LIST *list = createList();
	LIST *outputList = createList();
	
	fscanf(fp, "%60[^\n]\n", line);
	int N = atoi(line);
	printf("N: %d\n", N);
	//int flag = 1;
	
	int *verticeList = (int *)malloc(sizeof(int) * N);
	
	while (EOF != fscanf(fp, "%60[^\n]\n", line))
    {
		
		//split
		char *token = strtok(line, " ");
		
		int counter = 0; 
		
		while(token != NULL){
			
			int A, B;
			VERTICE *vertice = createVertice();
			
			if (counter == 0){
				A = atoi(token);
				verticeList[A] = 1;
				//printf("A: %d\n", vertice->A);
			}
			else if (counter == 1){
				B = atoi(token);
				verticeList[B] = 1;
				//printf("B: %d\n", vertice->B);
			}
			else if (counter == 2){
				vertice->weight = atof(token);
				vertice->A = A;
				vertice->B = B;
				//printf("weight: %f\n", vertice->weight);
				addBack(list, vertice);
				counter = 0;
				if (vertice->weight < minWeight){
					minWeight = vertice->weight;
					minVertice = vertice;
				}
			}
			//printf("token: %s\n", token);
			
			token = strtok(NULL, " "); 
			counter++;
		}
    }
	
	fclose( fp );
	
	//printf("minimum weight: %f\n", minWeight);
	//printf("%d -- %d : %f\n", minVertice->A, minVertice->B, minVertice->weight);
	
	stopwatch_init();
	struct stopwatch_t* timer = stopwatch_create();
	assert(timer);
	
	printf("Origin length: %d\n", list->length);
	
	stopwatch_start(timer);
	
	LIST *mst = createList();
	
	removeVertice(list, minVertice);
	addBack(mst, minVertice);
	verticeList[minVertice->A] = 2;
	verticeList[minVertice->B] = 2;
	
	int mstsize = 1;
	
	//printf("Start Prim\n");
	while(mst->length < (N - 1)){
		
		minWeight = 1.0;
		minVertice = NULL;
		
		VERTICE *tempHead = list->first;
		VERTICE *tempEnd = list->last;
		
		while(tempHead && tempEnd){		//scan mst
			
			if ((verticeList[tempHead->A] == 1 && verticeList[tempHead->B] == 2) || (verticeList[tempHead->A] == 2 && verticeList[tempHead->B] == 1)){
				if (tempHead->weight < minWeight){
					minWeight = tempHead->weight;
					minVertice = tempHead;
				}
			}
			if ((verticeList[tempEnd->A] == 1 && verticeList[tempEnd->B] == 2) || (verticeList[tempEnd->A] == 2 && verticeList[tempEnd->B] == 1)){
				if (tempEnd->weight < minWeight){
					minWeight = tempEnd->weight;
					minVertice = tempEnd;
				}
			}
			
			if (tempHead->next){
				if (tempHead->next == tempEnd){
					break;
				}
			}
			else{
				break;
			}
			if (tempHead == tempEnd){
				break;
			}
			
			tempHead = tempHead->next;
			tempEnd = tempEnd->prev;
			
		}
		
		if (minVertice == NULL) {
			
			VERTICE *reVerticeHead = list->first;
			VERTICE *reVerticeEnd = list->last;
			VERTICE *reMinVertice = NULL;
			float reMin = 1.0;
			
			while (1){
				
				if (verticeList[reVerticeHead->A] == 1 && verticeList[reVerticeHead->B] == 1){
					if (reVerticeHead->weight < reMin){
						reMin = reVerticeHead->weight;
						reMinVertice = reVerticeHead;
					}
				}
	
				if (verticeList[reVerticeEnd->A] == 1 && verticeList[reVerticeEnd->B == 1]){
					if (reVerticeEnd->weight < reMin){
						reMin = reVerticeEnd->weight;
						reMinVertice = reVerticeEnd;
					}
				}
				
				if (reVerticeHead->next){
					if (reVerticeHead->next == reVerticeEnd){
						break;
					}
				}
				else{
					break;
				}
				if (reVerticeHead == reVerticeEnd){
					break;
				}
				
				reVerticeHead = reVerticeHead->next;
				reVerticeEnd = reVerticeEnd->prev;
			}
			
			if (reMinVertice == NULL){
				break;
			}
			
			removeVertice(list, reMinVertice);
			addFront(mst, reMinVertice);
			verticeList[reMinVertice->A] = 2;
			verticeList[reMinVertice->B] = 2;
			continue;
			
		}
		
		//printf("addBack\n");
		removeVertice(list, minVertice);
		addBack(mst, minVertice);
		verticeList[minVertice->A] = 2;
		verticeList[minVertice->B] = 2;
		//printf("No. %d: %d -- %d : %f\n", mst->length, minVertice->A, minVertice->B, minVertice->weight);
	}
	
	//printf("Origin, length: %d\n", list->length);
	
	long double time = stopwatch_stop (timer);
	printf("Time: %Lg.\n", time);
	stopwatch_destroy (timer);
		
	strcpy ( filename, "MST-Output.txt" );
	if (!( fp = fopen( filename, "wt" ) ))
	{
		fprintf( stderr, "error: couldn't open %s\n", filename );
		exit(1);
	}
	/*
	for (i = 0; i <= N; i++){
		
		if (verticeList[i] == 1){
			printf("Vertice %d   ", i);
		}
		
	}
	*/
	VERTICE *outputVertice = mst->first;
		
	while (outputVertice){
		fprintf( fp, "%d %d %f\n\n", outputVertice->A, outputVertice->B, outputVertice->weight);	
		//printf("%d -- %d : %f\n", outputVertice->A, outputVertice->B, outputVertice->weight);
		outputVertice = outputVertice->next;
		
	}
	printf("MST length: %d\n", mst->length);
	fclose( fp );
	return 0;
	
}

void addFront(LIST *list, VERTICE* vertice){
	if (list->length == 0){
		list->first = vertice;
		list->last = vertice;
	} else{
		vertice->next = list->first;
		list->first->prev = vertice;
		list->first = vertice;
	}
	list->length++;
}

void addBack(LIST *list, VERTICE* vertice){
	
	if (list->length == 0){
		list->first = vertice;
		list->last = vertice;
	} else{
		vertice->prev = list->last;
		list->last->next = vertice;
		list->last = vertice;
	}
	list->length++;
}

VERTICE *getFirst(LIST *list){
	return list->first;
}

VERTICE *getLast(LIST *list){
	return list->last;
}

VERTICE* getPrev(VERTICE* vertice){
	return vertice->prev;
}

VERTICE *getNext(VERTICE* vertice){
	return vertice->next;
}

LIST *createList(){
	LIST* A = (LIST* )malloc(sizeof(LIST));
	assert(A);
	A->first = NULL;
	A->last = NULL;
	A->length = 0;
	return A;
}

VERTICE *createVertice(){
	VERTICE* A = (VERTICE* )malloc(sizeof(VERTICE));
	assert(A);
	A->A = 0;
	A->B = 0;
	A->weight = 0.0;
	A->prev = NULL;
	A->next = NULL;
	return A;
}

VERTICE *removeVertice(LIST *list, VERTICE *vertice){
	//printf("removeVertice\n");
	if (list->length == 1){
		list->first = NULL;
		list->last = NULL;
		vertice->prev = NULL;
		vertice->next = NULL;
		list->length--;
	}else if (vertice == list->first){
		list->first = vertice->next;
		vertice->next->prev = NULL;
		vertice->next = NULL;
		list->length--;
	} else if (vertice == list->last){
		list->last = vertice->prev;
		vertice->prev->next = NULL;
		vertice->prev = NULL;
		list->length--;
	}else{
		vertice->prev->next = vertice->next;
		vertice->next->prev = vertice->prev;
		vertice->prev = NULL;
		vertice->next = NULL;
		list->length--;
		if (list->length == 0){
			list->first = NULL;
			list->last = NULL;
		}
	}
	return vertice;
}