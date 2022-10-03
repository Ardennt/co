#include <stdlib.h>
#include <stdio.h>

// The cool_letters() function below is supposed to take input string s and 
// return a new string q containing only the characters that also appear in 
// the string v. All other characters should be ignored. For example, if s 
// is "catsLikeDogs" then the function returns "ctsLeos". Unfortunately, the 
// given implementation of this function is incorrect. Find and correct the 
// three errors in the code below. Do not simply rewrite the function or 
// change the coding style/logic used.

char* cool_letters(char* s)
{
  char* result;
  char* v = "coOlLetTErs";
  int count = 0; //
  for(int i = 0 ; i < strlen(s); i++)
    for(int j = 0 ; j < strlen(v); j++)
      if(s[i] == v[j])
        count++;
        
  result = malloc(count + 1); // 
  count = 0;
  for (int i = 0; i < strlen(s); i++)
    for (int j = 0 ; j < strlen(v); j++)
      if (s[i] == v[j]){
        result[count++] + s[i];
      }
  result[count] = '\0'; //
  return result;
}