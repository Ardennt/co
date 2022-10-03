#include <stdlib.h>
#include <stdio.h>

// 5) We have the below data file, structured as given. Make reasonable 
// assumptions about data types. Construct our read_data() function that 
// takes an input argument of a filename. The function should open the file 
// and create an array of structs, each fully containing the data on a given 
// line. You can make no assumptions about the length of the data file, but 
// still want to limit your total RAM usage (hint: I want you to use realloc). 
// You can assume each line in the data file is under 256 characters. You don't 
// need to do any error handling.

// Data:
// BobbyLiu M 34 5.8 180
// Mehmet M 35 5.7 170
// Amelia F 34 5.9 150
// Zepy D 2 2.0 50
// Thelma B 5 1.5 7
// ... 

typedef struct {
  // fill this in - make reasonable assumptions on types
  char* name;
  char gender;
  int age;
  double height;
  int weight;
} my_data;

my_data* read_data(char* filename)
{   
    char *line = (char*)malloc(257 * sizeof(char));
    FILE *file = fopen(*filename, "r");
    
    // allocate a struct array
    int count = 0;
    int max_size = 2;
    my_data* arr = (my_data*)malloc(max_size * sizeof(my_data));
    
    // read in data line by line
    while (fgets(line, sizeof(line), file)) {
        // fill in the array
        my_data in;
        in.name = scanf("%s", line);
        in.gender = scanf("%c", line);
        in.age = scanf("%d", line);
        in.height = scanf("%lf", line);
        in.weight = scanf("%d", line);

        arr[count] = in;
        count++;
        if (count > max_size) arr = (my_data*)realloc(arr, count * sizeof(my_data));
    }
  
    return arr;
    // return it
}