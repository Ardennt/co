#include <stdio.h>
#include <stdlib.h>

// function returns inputarr as a list of chars
int parse_input(char* line, char* inputarr[]){
    int count = 0;
    
    char var[8];
    while (sscanf(line, "%c", &var)){
        inputarr[count++] = var;
    }
}

void translate(char** line_c, FILE* outfile){

}

void read(char* fname){
    FILE *in_file = fopen(fname, "r");
    
    // allocate 128 spaces for the line to be read
    char line[128];

    // read in line by line
    while (fgets(line, sizeof(line), in_file)){
        // store the line parsed here
        char parsed[32][8];
        int total_count = parse_input(line, parsed);
    }
}

int main(int argc, char* argv[]){
    // argv[1] will be the filename
    char in_fname[128] = argv[1];
    read(in_fname);
}