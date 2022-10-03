#include <stdio.h>
#include <stdlib.h>

/* Given unsigned int variable n, write exactly one malloc() call to dynamically allocate the exact amount of 
memory needed to create an array containing exactly n double values. Call this array a and be sure to properly 
declare this variable. Set all values in a to 1.0 and then free up the allocated memory. */

int main() {
    unsigned n = 100;

    unsigned *arr = (unsigned*)malloc(n * sizeof(unsigned));
    for (unsigned i = 0; i < n; i++){
        arr[i] = 1;
    }

    free(arr);
}