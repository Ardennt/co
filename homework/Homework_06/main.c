#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct var{
    char regType; // tracks reg type (whether it is $s, $t, $a, $v, etc.)
    int regNum; // tracks reg num
    int line; // tracks what line it was last updated
};

// this function updates a variable with the line they last appeared in
void update(struct var v, struct var v_arr[16], int* vcount) {

}

int getIndex(char *v, struct var v_arr[16]) {
    for (int i = 0; i < 16; i++){
        if (v_arr[i].regType == v[1] && v_arr[i].regNum == v[2])
            return i;
    }
    return -1;
}

// this function checks if the variables are dependencies or not
void depen(char line[64], int lineN, struct var v_arr[16]) {
    char instruction[8];
    char variables[16];
    sscanf(line, "%s%s", instruction, variables);
    // lw and sw conditions are different...
    if (instruction[1] == 'w') return;
     
    // parse variables, split by comma
    char *ptr; // temporary pointer
    char *reg; // our register
    char *v1;  // first register
    char *v2;  // second register 

    ptr = strtok(variables, ",");
    reg = ptr;
    ptr = strtok(NULL, ",");
    v1 = ptr;
    ptr = strtok(NULL, ",");
    v2 = ptr;

    // check if v1 and v2 are dependencies
    int v1_ind = getIndex(v1, v_arr);
    int v2_ind = getIndex(v2, v_arr);

    // continue here: check if v2 is a constant, if it is, you can ignore checking it for dependency
}

void read(char fname[128], struct var v_arr[16]){
    // declare the file
    FILE* file = fopen(fname, "r");
    // line buffer
    char line[64];
    // read line by line
    for (int lineN = 1; fgets(line, sizeof(line), file); lineN++){
        /*
        step for each line:
        1. check if the registers being read are dependencies
        2. store myself into the array of variables
        3. increment everyone's steps
        */

       // check if the registers being read are dependencies
       depen(line, lineN, v_arr);
    }
}

void print() {

}

int main(int argc, char* argv[]) {
    // char stages[][4] = {"IF", "ID", "EX", "MEM", "WB"};
    struct var v_arr[16];
    read(argv[1], v_arr);
}