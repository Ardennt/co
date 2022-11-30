#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct var{
    char regType; // tracks reg type (whether it is $s, $t, $a, $v, etc.)
    int regNum; // tracks reg num
    int line; // tracks what line it was last updated
};

int getIndex(char *v, struct var v_arr[16]) {
    for (int i = 0; i < 16; i++){
        if (v_arr[i].regType == v[1] && v_arr[i].regNum == v[2])
            return i;
    }
    return -1;
}

void parse(char line[64], char reg[8], char v1[8], char v2[8]){
    char instruction[8];
    char variables[16];
    sscanf(line, "%s%s", instruction, variables);

    // parse variables
    char *ptr = strtok(variables, ",");
    for (int i = 0; i < strlen(ptr); i++){
        reg[i] = ptr[i];
    }
    reg[strlen(ptr)] = '\0';

    // if instructions are sw or lw:
    if (instruction[1] == 'w') {
        ptr = strtok(NULL, "(");
        for (int i = 0; i < strlen(ptr); i++){
            v2[i] = ptr[i];
        }
        v2[strlen(ptr)] = '\0';

        ptr = strtok(NULL, ")");
        for (int i = 0; i < strlen(ptr); i++){
            v1[i] = ptr[i];
        }
        v1[strlen(ptr)] = '\0';

    } else {
        ptr = strtok(NULL, ",");
        for (int i = 0; i < strlen(ptr); i++){
            v1[i] = ptr[i];
        }
        v1[strlen(ptr)] = '\0';

        ptr = strtok(NULL, ",");
        for (int i = 0; i < strlen(ptr); i++){
            v2[i] = ptr[i];
        }
        v2[strlen(ptr)] = '\0';
    }
}

// this function updates a variable with the line they last appeared in
void update(char line[64], struct var v_arr[16], int* vcount, int lineN) {
    char reg[8];
    char v1[8];
    char v2[8];
    parse(line, reg, v1, v2);

    int ind = getIndex(reg, v_arr);
    if (ind == -1) {
        // add it into v_arr
        struct var tmp;
        tmp.line = lineN;
        tmp.regType = reg[1];
        tmp.regNum = reg[2];
        v_arr[*vcount] = tmp;
        *vcount += 1;
    } else {
        v_arr[ind].line = lineN;
    }
}

// this function checks if the variables are dependencies or not
// returns the numbers of nops required
int depen(char line[64], int lineN, struct var v_arr[16]) {
    char reg[8];
    char v1[8];
    char v2[8];
    parse(line, reg, v1, v2);
     
    // check if v1 and v2 are dependencies
    int v1_ind = getIndex(v1, v_arr);
    // calculates the difference of lines in between me and the index
    int v1dif = -1;
    
    if (v1_ind != -1) {
        // printf("lineN: %d, %c%c line: %d\n", lineN, v_arr[v1_ind].regType, v_arr[v1_ind].regNum, v_arr[v1_ind].line);
        if (v1_ind != -1) v1dif = lineN - v_arr[v1_ind].line - 1;
    }
    
    // check if v2 is a constant, if it is, you can ignore checking it for dependency
    int v2dif = -1;
    
    if (v2[0] == '$'){
        int v2_ind = getIndex(v2, v_arr);
        if (v2_ind != -1) v2dif = lineN - v_arr[v2_ind].line - 1;
    }

    // printf("v1dif: %d v2dif: %d\n", v1dif, v2dif);
    if (v1dif == 0 || v2dif == 0) return 2;
    if (v1dif == 1 || v2dif == 1) return 1;
    return 0;
}

int read(char fname[128], struct var v_arr[16], int cycle, char stages[][4]){
    // declare the file
    FILE* file = fopen(fname, "r");
    // line buffer
    char line[64];
    // variable counter;
    int v_count = 0;
    // read line by line
    int lineN = 1;
    for (; fgets(line, sizeof(line), file); lineN++){
        /*
        step for each line:
        1. check if the registers being read are dependencies
        2. store myself into the array of variables
        3. increment everyone's steps
        */
        // check if the registers being read are dependencies
        int dep = depen(line, lineN, v_arr);
        for (int i = 0; i < dep; i++){
            printf("nop\t");
            for (int i = 1; i <= 9; i++){
                if (i < lineN || i > cycle || lineN + 4 < i){
                    printf("\t.");
                    continue;
                }
                else if (i > lineN + 1) {
                    printf("\t*");
                    continue;
                }
                printf("\t%s", stages[i - lineN]);
            }
            printf("\n");
        }
        lineN += dep;

        strtok(line, "\n");
        printf("%s", line);

        for (int i = 1; i <= 9; i++){
            if (i < lineN || i > cycle || lineN + 4 < i){
                printf("\t.");
                continue;
            }
            printf("\t%s", stages[i - lineN]);
        }
        printf("\n");

        // printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
        // store myself into the array of variables
        update(line, v_arr, &v_count, lineN);
    }
    lineN -= 1;
    if (lineN + 4 == cycle) return 1;
    return 0;
}

void print(char fname[128], struct var v_arr[16], char stages[][4]) {
    printf("START OF SIMULATION\n\n");
    
    for (int i = 1; i <= 9; i++) {
        printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
        if (read(fname, v_arr, i, stages) == 1) break;
        printf("\n");
    }

    printf("\nEND OF SIMULATION\n");
}

int main(int argc, char* argv[]) {
    char stages[][4] = {"IF", "ID", "EX", "MEM", "WB"};
    struct var v_arr[16];
    print(argv[1], v_arr, stages);
}