/////////////////////////////////////////////////////////////////////////////////
//Chain HashTable
//Qihao Yu
//EECS 114
//Generate key bewteen two numbers and ramdonly to insert the hash table, return just for value. And the key and value should be pair. 
/////////////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include<time.h> 

#define TRUE 1

struct SLOT{

	int data;
	int key;
	SLOT *next;
	SLOT *prev;

};

struct HashTable{
	
	int length;
	int load;
	SLOT **slot;
	
};

int hashFunction(int m, int key);
int insert(HashTable *hashTable, SLOT *slot);
SLOT *createSlot(int data);
HashTable *createHashTable(int size);
int search(HashTable *hashTable, int key);

int main(int argc, char** argv){
	
	int N, i;
	float alpha = 0.0;
	
	if (argc == 2) {
		N = atoi (argv[1]);
		assert (N > 0);
		printf("N = %d\n", N);
	} else {
		fprintf (stderr, "usage: %s <n>\n", argv[0]);
		fprintf (stderr, "where <n> is the size of the hash table.\n");
		return -1;
	}
	
	//printf("Create HashTable\n");
	
	HashTable *hashTable = createHashTable(N);
	if (hashTable == NULL) {
		return -1;
	}
	
	int reprobe = 0;
	int reprobeSearch = 0;
	
	//printf("Start Insert\n");
	
	while( alpha <= 0.5 ){
		
		
		SLOT *slot = createSlot((int)rand() % 100000);
		if (slot == NULL) {
			return -1;
		}
		
		//printf("Slot: %d\n", slot->data);
		
		int temp = insert(hashTable, slot);
		
		//printf("Reprobe: %d\n", temp);
		
		if (temp != hashTable->length){
			reprobe += temp;
		}
		alpha = (float)hashTable->load / (float)hashTable->length;
		//printf("-Load: %d, Load Factor = %f-\n", hashTable->load, alpha);
		
	}
	
	float avg_reprobe = (float)reprobe / (float)hashTable->load;
	printf("50%% load factor, average reprobe: %f\n", avg_reprobe);
	
	//printf("\n");
	//printf("Start Search\n");
	
	for (i = 0; i < 100000; i++){
		
		//printf("");
		reprobeSearch += search(hashTable, (int)rand() % 100000);
		
	}
	
	printf("\n");
	printf("50%% load factor, average search reprobe: %f\n", reprobeSearch / 100000);
	
	while( alpha <= 0.9 ){
		
		SLOT *slot = createSlot((int)rand() % 100000);
		if (slot == NULL) {
			return -1;
		}
		
		//printf("Slot: %d\n", slot->data);
		
		int temp = insert(hashTable, slot);
		//printf("Reprobe: %d\n", temp);
		
		if (temp != hashTable->length){
			reprobe += temp;
		}
		alpha = (float)hashTable->load / (float)hashTable->length;
		//printf("+Load: %d, Load Factor = %f+\n", hashTable->load, alpha);
	}
	
	printf("\n");
	avg_reprobe = (float)reprobe / (float)hashTable->load;
	printf("90%% load factor, average reprobe: %f\n", avg_reprobe);
	
	reprobeSearch = 0;
	
	for (i = 1; i < 100000; i++){
		
		//printf(":");
		reprobeSearch += search(hashTable, (int)rand() % 100000);
		
	}
	
	printf("\n");
	printf("90%% load factor, average search reprobe: %f\n", reprobeSearch / 100000);
	
	return 0;
	
}

int hashFunction(int m, int key){
	
	float A = (sqrt(5) - 1) / 2;
	int hash = (int)floor(m * ((key * A) - floor(key * A)));
	return hash;
	
}

int insert(HashTable *hashTable, SLOT *slot){
	
	int length = hashTable->length;
	int hash = hashFunction(hashTable->length, slot->key);
	
	int reprobeCounter = 0;
	
	SLOT *probe = hashTable->slot[hash];
	
	while ( probe != NULL ){
		
		probe = probe->next;
		reprobeCounter++;
		
	}
	
	probe = slot;
	hashTable->load++;
	
	return reprobeCounter;
}

SLOT *createSlot(int data){
	
	SLOT *slot = (SLOT *)malloc(sizeof(SLOT));
	
	if (slot == NULL) {
		
		printf("Unable to Memory Allocate for SLOT.\n");
		return NULL;
		
	}
	
	slot->data = data;
	slot->key = data;
	slot->next = NULL;
	slot->prev = NULL;
	
	return slot;
	
}

HashTable *createHashTable(int size){
	
	//printf("Allocate HashTable\n");
	HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
	if (hashTable == NULL) {
		
		printf("Unable to Memory Allocate for HashTable.\n");
		return NULL;
		
	}
	
	//printf("Allocate SLOT ARRAY\n");
	hashTable->slot = (SLOT **)malloc(sizeof(SLOT *) * size);
	if (hashTable == NULL) {
		
		printf("Unable to Memory Allocate for SLOT Array.\n");
		return NULL;
		
	}
	
	hashTable->length = size;
	
	hashTable->load = 0;
	
	return hashTable;
	
}

int search(HashTable *hashTable, int key){
	
	//printf("search function\n");
	
	int length = hashTable->length;
	int hash = hashFunction(hashTable->length, key);
	
	int reprobeCounter = 0;
	SLOT *probe = hashTable->slot[hash];
	
	if(probe == NULL){
		
		return 1;
		
	}
	
	//printf("probe->next\n");
	
	while (probe->next != NULL){
		
		//printf("probe->key\n");
		if (probe->key == key){
			return reprobeCounter;
		}
		else {
			
			probe =  probe->next;
			reprobeCounter++;
			
		}
		
	}
	
	return reprobeCounter;
}