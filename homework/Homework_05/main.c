#include <stdio.h>
#include <stdlib.h>

int parse_input(char* line, char* inputarr[]){
    int count = 0;
    
    char var[8];
    while (sscanf(line, "%c", &var)){
        
    }
}

int main(int argc, char* argv[]){
    // argv[1] will be the filename
    FILE *in_file = fopen(argv[1], "r");
    if (!in_file) {
        printf("file not opened successfully");
        return 1;
    }
    
    // allocate 128 spaces for the line to be read
    char line[128];

    // read in line by line
    while (fgets(line, sizeof(line), in_file)){
        
    }
}