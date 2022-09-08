#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MAX_NAME_SIZE = 50; 

// TODO: Write function to create and output all permutations of the list of names.
void printArr(char** arr, int size){
    for (int i = 0; i < size; i++){
        printf("%s, ", arr[i]);
    }
    printf("\n");
}

void swap(char* one, char* two){
    char* tmp = one;
    *one = *two;
    *two = *tmp;
}

void PrintAllPermutations(char **permList, int permSize, int nameSize) {
    if (permSize == nameSize){
        printArr(permList, nameSize);
    }

    for (int i = permSize; i < nameSize; i++){
        swap(permList[permSize], permList[i]);

        PrintAllPermutations(permList, permSize + 1, nameSize);

        swap(permList[permSize], permList[i]);
    }
}

int main(void) {
   int size;
   int i = 0;
   char name[MAX_NAME_SIZE];
   scanf("%d", &size);
   char *nameList[size];
   char *permList[size];

   for (i = 0; i < size; ++i) {
      nameList[i] = (char *)malloc(MAX_NAME_SIZE);
      scanf("%s", name);
      strcpy(nameList[i], name);
   }

   PrintAllPermutations(nameList, 0, size);
   
   // Free dynamically allocated memory
   for (i = 0; i < size; ++i) {
      free(nameList[i]);
   }
   
   return 0;
}