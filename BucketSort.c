#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PNUM 4
#define SIZE 100
//#define B_LENGTH SIZE / PNUM;
#define Divide  (int)ceil(RAND_MAX / PNUM)

typedef unsigned long ULONG;


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


int main() {
	//const ULONG m = (ULONG) pow(2, 32);
	int *arr = (int *) calloc(SIZE, sizeof(int));
	int *bucket[PNUM];
	int i, j, k;
	int count[PNUM] = {0}; // array count will now used for counting the numbers in each buckets
	int index[PNUM] = {0}; //add another counter to simplify the code

	srand(12345); //random number generator seed
	printf("original array is:\n");
	for(i=0; i<SIZE; i++) {
		arr[i] = rand();
		printf("%d ", arr[i]);
		j = arr[i] / Divide;
		count[j]++; 
	}
	printf("\n\n");
	printf("Divide is: %d\n", Divide);
	//allocate less memory than first version: 1/PNUM
	//in the first version, memory was allocated before knowing the actual number of each bucket
	//thus every bucket will allocate memory the same SIZE of original array in case of overflow
	for (int j=0; j<PNUM; j++) {
		bucket[j] = (int *) calloc(count[j], sizeof(int));
	}

	//divide and scatter array members into PNUM buckets
	//lowest members will be sent to bucket 0 and higher number to next buckets
	//numbers in buckets are unordered, but among buckets are ascend ordered

	for(i=0; i<SIZE; i++) {
		j = arr[i] / Divide;
		k = index[j];
		bucket[j][k] = arr[i];
		index[j]++;
	}

	//quickSort is used in each bucket
	for(i=0, j=0; j<PNUM; j++) {
		qsort(bucket[j], count[j], sizeof(int), cmpfunc);
		printf("total %d numbers in bucket %d:\n", count[j], j);
		for(k=0; k<count[j]; k++) {
			//printf("%d ", bucket[j][k]);
			arr[i] = bucket[j][k];
			i++;
		}
		printf("\n\n");
	}


	printf("after bucket sort, the array is:\n");
	for(i=0; i<SIZE; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n\n");

	free(arr);
	// free(bucket);
	for (int j=0; j<PNUM; j++) {
		free(bucket[j]);
	}

	return 0;

}
