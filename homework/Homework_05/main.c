#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function returns inputarr as a list of chars
struct reg {
    char letter;
    int reg_num;
    int val;
};

int inReg(struct reg registers[10], char letter){
    for (int i = 0; i < 10; i++){
        if (registers[i].letter == letter){
            return i;
        }
    }
    return -1;
}

// returns the value being loaded into
int use_LI(struct reg registers[10], int ourReg, char tmp[8]){
    tmp[strlen(tmp)-1] = '\0';
    int val;
    // all variables are single letters, we can make this assumption
    // DON'T KNOW IF WE NEED THIS??????
    if (isalpha(tmp[0])){
        // we assume that all variables on the rhs should be in registers already
        int varReg = inReg(registers, tmp[0]);
        val = registers[varReg].val;
        printf("add $s%d, $s%d, $%d", ourReg, ourReg, varReg);
        return val;
    } else {
        val = atoi(tmp);
        printf("li $s%d, %d\n", ourReg, val);
        return val;
    }
}

// return the value of the right hand side of the equation
int getRHS(struct reg registers[10], int ourReg, char line[128], int offset){
    
    // contains each variable on the right hand side
    char tmp[8];
    // offset counter
    int n = 0;
    // temp register counter
    int tmpReg = 0;
    // loading condition (only 1 variable is in RHS)
    int LI = 0;
    while (tmp[strlen(tmp)-1] != ';'){
        sscanf(line + offset, "%s%n", tmp, &n);
        // loading condition
        if (LI == 0 && tmp[strlen(tmp)-1] == ';'){
            return use_LI(registers, ourReg, tmp);
        }

        // not loading, use operations

        LI = 1;
        offset += n;
    }
    return 1;
}

// helper function to see all the variables
void printValues(struct reg registers[10]){
    for (int i = 0; i < 10; i++){
        printf("variable: %c, registers: $s%d, value: %d\n", registers[i].letter, registers[i].reg_num, registers[i].val);
    }
}

void read(char* fname){
    FILE *in_file = fopen(fname, "r");
    // allocate 128 spaces for the line to be read
    char line[128];

    // array of variables
    struct reg registers[10];

    int reg_count = 0;
    // read in line by line
    while (fgets(line, sizeof(line), in_file)){
        printf("# %s", line);
        // formatting new line for the last line in the program
        if (line[strlen(line)-1] != '\n'){
            printf("\n");
        }
        // name of variable
        char var;
        char equal; // useless variable
        int offset = 0;
        
        char tmp[8];
        sscanf(line, "%c %n", &var, &offset);
        // skip to after equals sign
        offset += 1;
        sscanf(line + offset, "%s", tmp);
        

        int regnum = inReg(registers, var);
        // if the variable on the left side doesn't exist
        if (regnum == -1){
            struct reg r;
            // assign reg_count and var
            r.letter = var;
            r.reg_num = reg_count;
            // get value
            r.val = getRHS(registers, reg_count, line, offset);
            // add to registers
            registers[reg_count++] = r;
        }
        // if the variable on the left side already exists
        else {
            registers[regnum].val = getRHS(registers, regnum, line, offset);
        }
    }
    printValues(registers);
}

int main(int argc, char* argv[]){
    // argv[1] will be the filename
    read(argv[1]);
}