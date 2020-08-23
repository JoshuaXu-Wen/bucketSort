#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PNUM 4
#define SIZE 100000000
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
	int i, j, k, count[PNUM];
	for (int j=0; j<PNUM; j++) {
		bucket[j] = (int *) calloc(SIZE, sizeof(int));
		count[j] = 0;
	}

	srand(12345);
	printf("original array is:\n");
	for(i=0; i<SIZE; i++) {
		arr[i] = rand();
		printf("%d ", arr[i]);
	}
	printf("\n\n");
	printf("Divide is: %d\n", Divide);

	//divide and scatter array members into PNUM buckets
	//lowest members will be sent to bucket 0 and higher number to next buckets
	//numbers in buckets are unordered, but between buckets are ascend ordered
	for(i=0; i<SIZE; i++) {
		j = arr[i] / Divide;
		k = count[j];
		bucket[j][k] = arr[i];
		count[j]++ ;
	}

	//quickSort is used in each bucket
	for(i=0, j=0; j<PNUM; j++) {
		qsort(bucket[j], count[j], sizeof(int), cmpfunc);
		printf("total %d numbers in bucket %d:\n", count[j], j);
		for(k=0; k<count[j]; k++) {
			printf("%d ", bucket[j][k]);
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

	return 0;

}
