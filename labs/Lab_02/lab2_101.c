#include <stdbool.h>                        // needed for bool type
#include <stdio.h>

int main() {
   int nums[50];
   int count;

   // Step 0: Input values
   scanf("%d", &count);
   for (int i = 0; i < count; ++i) {
      scanf("%d", &nums[i]);
   }

   // Step 1: Find minimum and maximum values
   /* Type your code here. */
   int min = nums[0];
   int max = nums[0];
   for (int i = 0; i < count; i++){
      if (nums[i] < min) min = nums[i];
      if (nums[i] > max) max = nums[i];
   }
   printf("Minimum: %d\n", min);
   printf("Maximum: %d\n", max);

   // Step 2: Calculate mean
   /* Type your code here. */
   double mean = 0.0;
   for (int i = 0; i < count; i++){
      mean += (double)nums[i];
   }
   mean /= (double)count;

   printf("Mean: %.1f\n", mean);

   // Step 3: Check if palindrome
   /* Type your code here. */
   int isPalin = 1;
   for (int i = 0; i < count / 2; i++){
      int i_back = count - 1;
      if (nums[i] != nums[i_back - i]){
         isPalin = 0;
         break;
      }
   }
   if (isPalin) printf("Palindrome: true\n");
   else printf("Palindrome: false\n");

   // Step 4: Read the same array elements in an ascending order. Find and output median
   /* Type your code here. */

   // take array in
   int arr2[50];
   for (int i = 0; i < count; i++){
      scanf("%d", &arr2[i]);
   }
   double median;
   // even
   if (count % 2 == 0) {
      median = ((double)arr2[count / 2 - 1] + (double)arr2[count / 2]) / 2.0;
   }
   // odd
   else {
      median = arr2[count / 2]; 
   }
   printf("Median: %.1f\n", median);


   // Step 5: Find and output mode of the sorted array
   /* Type your code here. */
   int mostcount = 0;
   int mostint = 0;
   int checkingint = arr2[0];
   int checkingcount = 0;
   for (int i = 0; i < count; i++){
      if (arr2[i] == checkingint) {
         checkingcount += 1;
      }
      else {
         checkingint = arr2[i];
         checkingcount = 1;
      }

      if (checkingcount > mostcount){
         mostcount = checkingcount;
         mostint = checkingint;
      }
   }
   printf("Mode: %d\n", mostint);
}
