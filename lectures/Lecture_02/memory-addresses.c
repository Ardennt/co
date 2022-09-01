#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int pop_quiz_test()
{
  char array_stack[4][4];
  char **array_heap;
  int i;
  array_heap = (char **)malloc(4*sizeof(char*));
  for(i = 0; i < 4; ++i)
    array_heap[i] = (char *)malloc(4);

  printf("Array_stack[2][2]: %p\n", &array_stack[2][2]);
  printf("Array_stack[2][3]: %p\n", &array_stack[2][3]);
  printf("Array_stack[3][0]: %p\n", &array_stack[3][0]);
  printf("Array_heap[2][2]: %p\n", &array_heap[2][2]);
  printf("Array_heap[2][3]: %p\n", &array_heap[2][3]);
  printf("Array_heap[3][0]: %p\n", &array_heap[3][0]);

  // clean up that dynamically allocated memory!
  for(i = 0; i < 4; ++i)
    free(array_heap[i]);
  free(array_heap);

  return 0;
}

int main()
{
  // First let's look at the 'pop quiz' from slide 66
  pop_quiz_test();

  // Next, let's examine the differences in text, heap, and stack
  int stack_int = 5;
  char* in_text = "Woooo wooo!!";
  char in_stack[100];
  char* in_heap = (char*)malloc(100);
  strcpy(in_stack, in_text);
  strcpy(in_heap, in_text);


  printf("address of in_text is %p\n", in_text);
  printf("address of in_stack is %p\n", in_stack);
  printf("address of in_heap is %p\n", in_heap);

  printf("address of stack_int is %p\n", &stack_int);
  printf("address of main is %p\n", &main);

  printf("Text: %s\n", in_text);
  printf("Stack: %s\n", in_stack);
  printf("Heap: %s\n", in_heap);

  // Can we modify these?
  in_text[0] = 'B';
  in_stack[0] = 'B';
  in_heap[0] = 'B';

  printf("Text: %s\n", in_text);
  printf("Stack: %s\n", in_stack);
  printf("Heap: %s\n", in_heap);

  // Remember: the above three pointers are themselves local variables
  // Where are they stored?
  printf("Text location: %p\n", &in_text);
  printf("Stack location: %p\n", &in_stack);
  printf("Heap location: %p\n", &in_heap);

  // Clean up!
  free(in_heap);

  return 0;
}
