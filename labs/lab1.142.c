#include <stdlib.h>
#include <stdio.h>

const char* intToStr(int n){
   if (n == 0) return "rock";
   if (n == 1) return "paper";
   if (n == 2) return "scissors";
   return "error";
}

const char* printWinner(int input1, int input2, const char* name1, const char* name2){
// rock vs paper
   if (input1 == 0 && input2 == 1){
      printf("%s wins with %s\n", name2, intToStr(1));
      return name2;
   }

   else if (input1 == 1 && input2 == 0){
    printf("%s wins with %s\n", name1, intToStr(1));
    return name1;
   }

    // rock vs scissor
   else if (input1 == 0 && input2 == 2){
    printf("%s wins with %s\n", name1, intToStr(0));
    return name1;
   }
   else if (input1 == 2 && input2 == 0){
    printf("%s wins with %s\n", name2, intToStr(0));
    return name2;
   }

   // paper vs scissor
   else if (input1 == 1 && input2 == 2){
    printf("%s wins with %s\n", name2, intToStr(2));
    return name2;
   }
   else if (input1 == 2 && input2 == 1){
    printf("%s wins with %s\n", name1, intToStr(2));
    return name1;
   }
}

int main() {
   const int ROCK = 0;
   const int PAPER = 1;
   const int SCISSORS = 2;

   int seed;
   scanf("%d", &seed);
   srand(seed);

   /* Type your code here. */
   
   // part 1
   char name1[100];
   char name2[100];
   int roundN;
   scanf("%s", name1);
   scanf("%s", name2);
   scanf("%d", &roundN);
   while(roundN <= 0){
      printf("Rounds must be > 0\n");
      scanf("%d", &roundN);
   }
   printf("%s vs %s for %d rounds\n", name1, name2, roundN);
   
   // part 2 below
   
   // final part
   int n1Score = 0;
   int n2Score = 0;

   for (int i = 0; i < roundN; i++){
    int input1 = rand() % 3;
    int input2 = rand() % 3;

    while (input1 == input2){
        printf("Tie\n");
        input1 = rand() % 3;
        input2 = rand() % 3;
    }

    if (printWinner(input1, input2, name1, name2) == name1) n1Score += 1;
    else n2Score += 1;
   }

    printf("%s wins %d and %s wins %d\n", name1, n1Score, name2, n2Score);

    
   
   return 0;

}
