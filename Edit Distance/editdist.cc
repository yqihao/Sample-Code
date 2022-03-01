/////////////////////////////////////////////////////////////////////////////////
//Edit Distance
//Qihao Yu
/////////////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <time.h> 
#include <string.h>

#define DELETE 2
#define REPLACE 4
#define INSERT 3
#define RIGHT 0
#define TRUE 1

struct VERTICE{
	VERTICE* prev;
	VERTICE* next;
	int X;
	int Y;
	int distance;
};

struct LIST{
	VERTICE* first;
	VERTICE* last;
	int length;
};

struct String{
	
	char *string;
	int length;
	
};

void addFront(LIST *list, VERTICE* vertice);
void addBack(LIST *list, VERTICE* vertice);
LIST *createList();
VERTICE *createVertice();

String *createString(int length);
char *inserttoString(char *input, int length ,char insertee, int index);
void deleteinString(char *input, int index);
void editDistance(String *stringA, String *stringB);
int minimum3(int var1, int var2, int var3);

int main(int argc, char** argv){
	
	char *filename;
	char *stringX, *stringY;
	FILE *fp;
	int lengthX, lengthY;
	
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
	
	fscanf(fp, "%d\n", &lengthX);
	stringX = (char* )malloc(sizeof(char) * lengthX);
	fscanf(fp, "%[^\n]\n", stringX);
	fscanf(fp, "%d\n", &lengthY);
	stringY = (char* )malloc(sizeof(char) * lengthY);	
	fscanf(fp, "%[^\n]\n", stringY);
	
	fclose(fp);
	
	String *strX = createString(lengthX);
	String *strY = createString(lengthY);
	strX->string = stringX;
	strY->string = stringY;
	
	printf("Start\n");
	editDistance(strX, strY);
	return 0;
	
}

String *createString(int length){
	
	String* A = (String* )malloc(sizeof(String));
	assert(A);
	A->string = (char* )malloc(sizeof(char) * length);
	assert(A->string);
	A->length = length;
	return A;
	
}

char *inserttoString(char *input, int length ,char insertee, int index){
	
	//printf("inserttoString\n");
	
	char *signle = (char* )malloc(sizeof(char) * 2);
	signle[0] = insertee;
	signle[1] = '\0';
	
	char *output = (char* )malloc(sizeof(char) * (length + 1));
	strncpy(output, input, index);
	//printf("%s\n", output);
	output[index] = '\0';
	strcat(output, signle);
	//printf("%s\n", output);
	strcat(output, input + index);
	output[length] = '\0';
	//printf("%s\n", output);
	
	return output;
	
}

void deleteinString(char *input, int index){
	
	memmove(&input[index], &input[index + 1], strlen(input) - index);
	
}

void editDistance(String *stringA, String *stringB){
		
	int i, j;
	
	VERTICE ***verticeMartix = (VERTICE*** )malloc(sizeof(VERTICE**) * (stringA->length+1));
	
	//printf("Initial Martix Vertice\n");
	
	for (i = 0; i < (stringA->length+1); i++){
		verticeMartix[i] = (VERTICE** )malloc(sizeof(VERTICE*) * (stringB->length+1));
	}
	
	//printf("Initial Martix\n");
	
	int **editDistMartix = (int** )malloc(sizeof(int*) * (stringA->length+1));
	for (i = 0; i < (stringA->length+1); i++){
		editDistMartix[i] = (int* )malloc(sizeof(int) * (stringB->length+1));
	}
	
	LIST *list = createList();
	
	String *strZ;
	if (stringA->length >= stringB->length){
		strZ = createString(stringA->length);
	}else{
		strZ = createString(stringB->length);
	}
	
	strZ->length = stringA->length;
	strcpy(strZ->string, stringA->string);
	
	printf("Calculating Egde\n");
	
	for (i = 0; i <= stringA->length; i++){
		editDistMartix[i][0] = i * DELETE;
		verticeMartix[i][0] = createVertice();
		verticeMartix[i][0]->X = i;
		verticeMartix[i][0]->Y = 0;
		verticeMartix[i][0]->distance = editDistMartix[i][0];
		if (i != 0){
			verticeMartix[i][0]->prev = verticeMartix[i-1][0];
		}
	}	
	for (j = 0; j <= stringB->length; j++){
		editDistMartix[0][j] = j * INSERT;
		verticeMartix[0][j] = createVertice();
		verticeMartix[0][j]->X = 0;
		verticeMartix[0][j]->Y = j;
		verticeMartix[0][j]->distance = editDistMartix[0][j];
		if (j != 0){
			verticeMartix[0][j]->prev = verticeMartix[0][j-1];
		}
	}
	
	printf("Calculating Martix\n");
	
	for (j = 1; j <= stringB->length; j++){
		for (i = 1; i <= stringA->length; i++ ){
			if (stringA->string[i-1] == stringB->string[j-1]){
				//printf("%d %c, %d %c\n", i, stringA->string[i], j, stringB->string[j]);
				editDistMartix[i][j] = editDistMartix[i-1][j-1];
				verticeMartix[i][j] = createVertice();
				verticeMartix[i][j]->X = i;
				verticeMartix[i][j]->Y = j;
				verticeMartix[i][j]->distance = editDistMartix[i][j];
				verticeMartix[i][j]->prev = verticeMartix[i-1][j-1];
			}
			else {
				editDistMartix[i][j] = minimum3(editDistMartix[i-1][j]+DELETE, editDistMartix[i-1][j-1]+REPLACE, editDistMartix[i][j-1]+INSERT);
				verticeMartix[i][j] = createVertice();
				verticeMartix[i][j]->X = i;
				verticeMartix[i][j]->Y = j;
				verticeMartix[i][j]->distance = editDistMartix[i][j];
				if (editDistMartix[i][j] == editDistMartix[i-1][j]+DELETE){
					verticeMartix[i][j]->prev = verticeMartix[i-1][j];
				} else if(editDistMartix[i][j] == editDistMartix[i-1][j-1]+REPLACE){
					verticeMartix[i][j]->prev = verticeMartix[i-1][j-1];
				}else {
					verticeMartix[i][j]->prev = verticeMartix[i][j-1];
				}
			}
		}
	}
	/*
	for (j = 0; j <= stringB->length; j++){
		for (i = 0; i <= stringA->length; i++ ){
			printf("%5d", editDistMartix[i][j]);
		}
		printf("\n\n");
	}
	*/
	printf("Find Route\n");
	
	VERTICE *vertice = verticeMartix[stringA->length][stringB->length];
	VERTICE *prev;
	
	while (vertice){
		
		prev = vertice->prev;
		addFront(list, vertice);
		vertice = prev;
		
	}
	
	vertice = list->first;
	
	printf("Operation: Initial\nString: %s\nCost: %d, Total: %d\n", strZ->string, 0, 0);
	
	while(vertice->next){
		
		int operation = vertice->next->distance - vertice->distance;
		
		//printf("Operation Code: %d\n", operation);
				
		if (operation == REPLACE){
			//printf("cursorX: %d, cursorY: %d cursorX: %c, cursorY: %c\n", vertice->X, vertice->Y, stringA->string[vertice->X], stringB->string[vertice->Y]);
			strZ->string[vertice->Y] = stringB->string[vertice->Y];
			printf("Operation: Replace\n");
			printf("String: %s\nCost: %d, Total: %d\n", strZ->string, REPLACE, vertice->next->distance);
		}else if (operation == INSERT){
			//printf("cursorX: %d, cursorY: %d cursorX: %c, cursorY: %c\n", vertice->X, vertice->Y, stringA->string[vertice->X], stringB->string[vertice->Y]);
			strZ->string = inserttoString(strZ->string, strZ->length, stringB->string[vertice->Y], vertice->Y);
			strZ->length++;	
			printf("Operation: Insert\nString: %s\nCost: %d, Total: %d\n", strZ->string, INSERT, vertice->next->distance);
		}else if (operation == DELETE){
			//printf("cursorX: %d, cursorY: %d cursorX: %c, cursorY: %c\n", vertice->X, vertice->Y, stringA->string[vertice->X], stringB->string[vertice->Y]);
			deleteinString(strZ->string, vertice->Y);
			strZ->length--;
			printf("Operation: Delete\nString: %s\nCost: %d, Total: %d\n", strZ->string, DELETE, vertice->next->distance);
		}else {
			//printf("cursorX: %d, cursorY: %d cursorX: %c, cursorY: %c\n", vertice->X, vertice->Y, stringA->string[vertice->X], stringB->string[vertice->Y]);
			printf("Operation: Right\nString: %s\nCost: %d, Total: %d\n", strZ->string, RIGHT, vertice->next->distance);
		}
		
		vertice = vertice->next;
		
	}

	printf("Edit Distance: %d, All Operation Finished.\n", verticeMartix[stringA->length][stringB->length]->distance);
}

int minimum3(int var1, int var2, int var3){
	
	int minimum = 0;
	if (var1 < var2){
		minimum = var1;
	}else {
		minimum = var2;
	}
	if (var3 < minimum){
		minimum = var3;
	}
	
	return minimum;
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
	A->X = 0;
	A->Y = 0;
	A->distance = 0;
	A->prev = NULL;
	A->next = NULL;
	return A;
}