#include <stdio.h>

int Fibonacci(int n) {
   /* Type your code here. */
   if (n < 0) return -1;
   if (n == 0) return 0;
   if (n == 1) return 1;

   int last2 = 0;
   int last1 = 1;
   int index = 2;
   while (index < n){
    int me = last2 + last1;
    last2 = last1;
    last1 = me;
    index += 1;
   }
   
   return last2 + last1;
}

int main(void) {
   int startNum;
   scanf("%d", &startNum);
   
   printf("Fibonacci(%d) is %d", startNum, Fibonacci(startNum));

   return 0;
}