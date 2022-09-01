#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void print_output(int n) 
{ 
  printf("Hello World: %d\n", n); 
}

// Copied from https://stackoverflow.com/questions/9960721/how-to-get-c-code-to-execute-hex-bytecode
// Credit: Antoine Mathys
void run_stack_code()
{
  // x86-64 assembly -- add first two arguments, return result
  // lea [a], [b] -- load [b] into [a]
  // rdi - register of first argument
  // rsi - register of second argument
  // rax - register of return value
  // ret - return call
  // i.e., somewhat 'literal' translation:
  /*
  int code(int rdi, int rsi) {
    int rax = rdi + rsi;
    return rax;
  }
  */
  // See http://www.egr.unlv.edu/~ed/assembly64.pdf
  char code[] = {
    0x48, 0x8D, 0x04, 0x37,     //  lea rax, [rdi+rsi] 
    0xC3                        //  ret
  };

  // our function pointer
  int (*sum) (int, int) = NULL;

  // Copy the code to an executable buffer 
  // Map a chunk of memory of sizeof(code) with read+write+exec permissions
  // - See 'man mmap'
  // Call memcpy to copy the actual contents of code[]
  sum = mmap(0, sizeof(code), 
    PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
  memcpy(sum, code, sizeof(code));

  // call our function pointer with some arguments
  int a = 2;
  int b = 3;
  
  int c = sum(a, b);

  // verify our result
  printf ("%d + %d = %d\n", a, b, c);

  // Where is the code we just executed???
  printf("Location of code: %p\n", &code);
  printf("Location of sum: %p\n", sum);
  printf("Location of function: %p\n", &run_stack_code);

  // clean it up
  munmap(sum, sizeof(code));
}

int main()
{
  setbuf(stdout, 0);
  void (*function_ptr)(int) = &print_output;
  printf("%p %p\n", function_ptr, &print_output);

  (function_ptr)(5);
  printf("%p\n", ++function_ptr);
  (function_ptr)(5);
  run_stack_code();

  return 0;
}
