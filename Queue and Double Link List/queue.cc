#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h> 

#include "timer.c"

struct ELEMENT{
	ELEMENT* prev;
	ELEMENT* next;
	float data;
};
struct QUEUE{
	ELEMENT* first;
	ELEMENT* last;
	int length;
};

void enqueue(QUEUE *queue, ELEMENT* element);
ELEMENT* dequeue(QUEUE *queue);
QUEUE *createQueue();
ELEMENT *createElement(float input);

int main(int argc, char* argv[]){
	
	int i, n = -1, t = -1;

	if (argc == 3) {
		n = atoi (argv[1]);
		t = atoi (argv[2]);
		assert (n > 0);
		assert (t > 0);
	} else {
		fprintf (stderr, "usage: %s <n> <t>\n", argv[0]);
		fprintf (stderr, "where <n> is the length of the queue, <t> is times to test performace.\n");
		return -1;
	}
	
	srand(time(0)); 
	long double avg_time = 0.0;
	ELEMENT* element;
	
	stopwatch_init ();
	struct stopwatch_t* timer = stopwatch_create (); assert (timer);

	QUEUE* queue = createQueue();
	for (i = 0; i < n; i++){
		//create element and enqueue
		element = createElement((float) rand());
		enqueue(queue, element);
	}
	
	for (i = 0; i < t; i++){
		//test enqueue and dequeue
		
		//start timer
		stopwatch_start (timer);
		element = dequeue(queue);
		enqueue(queue, element);
		
		//stop timer
		avg_time += stopwatch_stop (timer);
	}
	
	avg_time /= t;
	printf("Average Time: %Lg \n", avg_time);
	stopwatch_destroy (timer);
}

void enqueue(QUEUE *queue, ELEMENT* element){
	if (queue->length == 0){
		queue->first = element;
		queue->last = element;
	}
	queue->last->next = element;
	element->prev = queue->last;
	queue->last = element;
	queue->length++;
}

ELEMENT* dequeue(QUEUE *queue){
	
	if(queue->length == 0){
		return NULL;
	}
	else if (queue->length == 1){
		ELEMENT* A = queue->first;
		queue->first = NULL;
		queue->last = NULL;
		queue->length--;
		return A;
	}
	else {
		ELEMENT* A = queue->first;
		queue->first = A->next;
		queue->first->prev = NULL;
		A->next = NULL;
		queue->length--;
		return A;
	}
}

QUEUE *createQueue(){
	QUEUE* A = (QUEUE* )malloc(sizeof(QUEUE));
	assert(A);
	A->first = NULL;
	A->last = NULL;
	A->length = 0;
	return A;
}

ELEMENT *createElement(float input){
	ELEMENT* A = (ELEMENT* )malloc(sizeof(ELEMENT));
	assert(A);
	A->data = input;
	A->prev = NULL;
	A->next = NULL;
	return A;
}