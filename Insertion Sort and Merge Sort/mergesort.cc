/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sort.hh"

void iSort(keytype* A, int start, int end);
int binaryResearch(keytype* A, int start, int end, keytype insertee);

void mySort (int N, keytype* A)
{
	keytype* B = newCopy (N, A);
	mergeSort(N, A, B, 0, N - 1);
}

void mergeSort(int N, keytype* A, keytype* B, int start, int end){
	
	int N_R, N_L, i, j, k, mid, length = end - start + 1;
	
	//printf("length = %d, start = %d, end = %d \n", length, start, end);
	
	//printf("Before: ");
	//for (i = start; i <= end; i++){
//		printf("A[%d] = %d ", i, A[i]);
//	}
//	printf("\n");
	
	if (length == 1){
		B[start] = A[start];
		return;
	}
	else if (length == 2){
		if (A[start] > A[end]){
			B[start] = A[end];
			B[end] = A[start];
			A[start] = B[start];
			A[end] = B[end];
		}
		else{
			B[start] = A[start];
			B[end] = A[end];
		}
		//printf("After: ");
		//for (i = start; i <= end; i++){
		//	printf("A[%d] = %d ", i, A[i]);
		//}
	//	printf("\n");
		return;
	}
	else{
		mid = round((start + end) / 2);
		
		N_L = mid - start + 1;
		N_R = length - N_L;
		//printf("mid = %d, N_L = %d, N_R = %d \n", mid, N_L, N_R);
		mergeSort(N, A, B, start, mid);
		mergeSort(N, A, B, mid + 1, end);
		
		i = 0;
		j = 0;
		//printf("Merge\n");
		//printf("length = %d, start = %d, end = %d \n", length, start, end);
//printf("mid = %d, N_L = %d, N_R = %d \n", mid, N_L, N_R);
		
		for (k = start; k <= end; k++){
			//printf("i = %d, j = %d, k = %d \n", i, j, k);
			if (i >= N_L){
				A[k] = B[mid+j+1];
				j++;
				continue;
			}
			if (j >= N_R){
				A[k] = B[start+i];
				i++;
				continue;
			}
			
			if (B[start+i] <= B[mid+j+1]){
				A[k] = B[start+i];
				//printf("A[%d] = B[start(%d)+i(%d)]; \n", k, start, i);
				i++;
			}
			else {
				A[k] = B[mid+j+1];
				//printf("A[%d] = B[start(%d)+i(%d)]; \n", k, start, j);
				j++;
			}
		}
			
		for (i = 0; i < length; i++){
			B[start+i] = A[start+i];
		}
		
		//printf("After: ");
		//for (i = start; i <= end; i++){
			//printf("A[%d] = %d ", i, A[i]);
	//	}
		//printf("\n");
		return;
	}	
	return;
}
/* eof */
