/**
 *  \file insertion-sort.cc
 *
 *  \brief Implement your insertion sort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sort.hh"

int
binaryResearch(keytype* A, int start, int end, keytype insertee);

void
mySort (int N, keytype* A)
{
	int i, j, k, insertOrder;
	keytype temp;
	for (i = 1; i < N; i++){		//the first element in array could be ignored
		if (i == 1){
			if (A[i] < A[i-1]){
				temp =  A[i];
				A[i] = A[i-1];
				A[i-1] = temp;
			}
		}
		else {
			insertOrder = binaryResearch(A, 0, i - 1, A[i]);
			temp = A[i];
			for (j = i; j >= insertOrder; j--){
				A[j] = A[j-1];
			}
			A[insertOrder] = temp;
		}
	}
}

int
binaryResearch(keytype* A, int start, int end, keytype insertee){
	int N = end - start + 1;
	if (N == 1){												//only one element to compare
		if (A[start] > insertee){
				return start;
		}
		else {
			return start + 1;
		}
	}
	else {
		if (N % 2 == 0){			//even
		int mid = round((start + end) / 2);
			if (insertee > A[mid] && insertee < A[mid+1]){	//not equal to one of the middle values
				return mid + 1;
			}
			else {												//equal to one of the middle values
				if (insertee < A[mid]) {
					return binaryResearch(A, start, mid, insertee);
				}
				else {
					return binaryResearch(A, mid + 1, end, insertee);
				}
			}
		}
		else {						//odd
			int mid = (start + end) / 2;
			if (insertee != A[mid]){	//not equal to the middle values
				if (insertee < A[mid]) {
					return binaryResearch(A, start, mid, insertee);
				}
				else {
					return binaryResearch(A, mid, end, insertee);
				}
			}
			else {												//equal to one of the middle values
				return mid;
			}
		}
	}
}

/* eof */
