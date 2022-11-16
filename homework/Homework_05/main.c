#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function returns inputarr as a list of chars
struct reg {
    char letter;
    int reg_num;
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
void use_LI(struct reg registers[10], int ourReg, char tmp[8]){
    tmp[strlen(tmp)-1] = '\0';
    int val;
    // all variables are single letters, we can make this assumption
    if (isalpha(tmp[0])){ // might not need this? not stated in assumption if a = b is possible
        // we assume that all variables on the rhs should be in registers already
        int varReg = inReg(registers, tmp[0]);
        printf("add $s%d,$s%d,$%d", ourReg, ourReg, varReg);
        // return val;
    } else {
        val = atoi(tmp);
        printf("li $s%d,%d\n", ourReg, val);
    }
}

void remove_semicolon(char var[8]){
    var[strlen(var)-1] = '\0';
}

void plus_minus(struct reg registers[10], int ourReg, char var1[8], char var2[8], int tmp_var, int usedtmp, char operation){
    // var1 is the first variable and var2 is the second variable
    // int t_count = 0;
    int first_var = inReg(registers, var1[0]);
    int second_var = inReg(registers, var2[0]);

    // if var2 is the last variable, we can just add tmp_var to 
    // our var along with the last variable
    if (var2[strlen(var2)-1] == ';'){
        // add/sub condition
        if (isalpha(var2[0])){
            // used a temporary variable
            if (operation == '+') printf("add ");
            else printf("sub ");

            if (usedtmp) {
                printf("$s%d,$t%d,$s%d\n", ourReg, tmp_var, second_var);
            // didn't use a temporary variable
            } else {
                printf("$s%d,$s%d,$s%d\n", ourReg, first_var, second_var);
            }
        }
        // addi condition
        else {
            // used a temporary variable
            char new_var2[8]; // seg fault, a new variable is needed
            sscanf(var2, "%s", new_var2);
            remove_semicolon(new_var2);
            if (usedtmp) {
                printf("addi $s%d,$t%d,", ourReg, tmp_var);
            }
            else {
                printf("addi $s%d,$s%d,", ourReg, first_var);
            }

            if (operation == '-') printf("-%s\n", new_var2);
            else printf("%s\n", new_var2);
            
        }
        return;
    }

    // var2 isn't the last variable
    // add condition
    if (isalpha(var2[0])){
        if (operation == '+') printf("add ");
        else printf("sub ");

        if (usedtmp) {
            printf("$t%d,$t%d,$s%d\n", tmp_var, tmp_var-1, second_var);
        } else {
            printf("$t%d,$s%d,$s%d\n", tmp_var, first_var, second_var);
        }
    }
    // addi condition
    else {
        if (usedtmp) {
            printf("addi $t%d,$t%d,", tmp_var, tmp_var-1);
        }
        else {
            printf("addi $t%d,$s%d,", tmp_var, first_var);
        }

        if (operation == '-') printf("-%s\n", var2);
        else printf("%s\n", var2);
    }
}

void mult_divide(struct reg registers[10], int ourReg, char var1[8], char var2[8], int *tmp_var, int usedtmp, char operation){
    int first_var = inReg(registers, var1[0]);
    int second_var = inReg(registers, var2[0]);

    // it's the last variable
    if (var2[strlen(var2)-1] == ';'){
        // both are chars
        if (isalpha(var2[0])){
            // multiplying two variables, one of them is the end
            if (operation == '*') printf("mult ");
            else printf("div ");

            // used temporary variable requires you to print the tempvar
            if (usedtmp){
                printf("$t%d,$s%d\n", *tmp_var, second_var);
                // access hi or lo depending on division or modulus
                if (operation == '%') printf("mfhi ");
                else printf("mflo ");
                printf("$s%d\n", ourReg);
            }
            // haven't used the temporary variable, just multiple both
            else {
                printf("$s%d,$s%d\n", first_var, second_var);
                // access hi or lo depending on division or modulus
                if (operation == '%') printf("mfhi ");
                else printf("mflo ");
                printf("$s%d\n", ourReg);
            }
        }
        else {
            // case check whether it's 0 or not
            if (var2[0] == '0'){
                printf("li $s%d,0\n", ourReg);
                return;
            }

            char new_var2[8]; // for some reason it's segfaulting when i call remove_semicolon
            sscanf(var2, "%s", new_var2);
            remove_semicolon(new_var2);
            printf("li $t%d,%s\n", *tmp_var, new_var2);

            if (operation == '*') printf("mult ");
            else printf("div ");

            printf("$s%d,$t%d\n", first_var, *tmp_var);
            *tmp_var += 1;
            // access hi or lo depending on division or modulus
            if (operation == '%') printf("mfhi ");
            else printf("mflo ");
            printf("$s%d\n", ourReg);
        }
        return;
    }

    if (isalpha(var2[0])){
        if (operation == '*') printf("mult ");
        else printf("div ");
        // if previously used a temp variable
        if (usedtmp) {
            printf("$t%d,$s%d\n", *tmp_var-1, second_var);
            // access hi or lo depending on division or modulus
            if (operation == '%') printf("mfhi ");
            else printf("mflo ");
            printf("$t%d\n", *tmp_var);
        } else {
            printf("$s%d,$s%d\n", first_var, second_var);
            // access hi or lo depending on division or modulus
            if (operation == '%') printf("mfhi ");
            else printf("mflo ");
            printf("$t%d\n", *tmp_var);
        }
    }
    else {
        // case check whether it's 0 or not
        if (var2[0] == '0'){
            printf("li $s%d,0\n", ourReg);
            return;
        }

        printf("li $t%d,%s\n", *tmp_var, var2);

        if (operation == '*') printf("mult ");
        else printf("div ");

        printf("$s%d,$t%d\n", first_var, *tmp_var);
        *tmp_var += 1;
        // access hi or lo depending on division or modulus
        if (operation == '%') printf("mfhi ");
        else printf("mflo ");
        printf("$t%d\n", *tmp_var);
    }
}

// return the value of the right hand side of the equation
void getRHS(struct reg registers[10], int ourReg, char line[128], int offset, int *tmpReg){
    
    // contains each variable on the right hand side
    char tmp[8];
    // offset counter
    int n = 0;
    // temp register counter
    int usedtmp = 0;
    // loading condition (only 1 variable is in RHS)
    sscanf(line + offset, "%s%n", tmp, &n);
    if (tmp[strlen(tmp)-1] == ';'){
        use_LI(registers, ourReg, tmp);
        return;
    }
    offset += n;
    
    // not loading contion:
    while (tmp[strlen(tmp)-1] != ';'){

        // not loading, use operations
        char operation[2];
        char var[8];
        sscanf(line + offset, "%s%s%n", operation, var, &n);

        // if it's the last variable we don't need another tmp holder
        if (usedtmp && var[strlen(var)-1] != ';'){
            *tmpReg += 1;
        }
        // add and subtraction
        if (operation[0] == '+' || operation[0] == '-'){
            plus_minus(registers, ourReg, tmp, var, *tmpReg, usedtmp, operation[0]);
        } 
        else if (operation[0] == '*' || operation[0] == '/' || operation[0] == '%'){
            mult_divide(registers, ourReg, tmp, var, *&tmpReg, usedtmp, operation[0]);
        }

        offset += n;
        // used a temp variable
        
        usedtmp = 1;
        // put var in tmp
        sscanf(var, "%s", tmp);
    }
}

// helper function to see all the variables
void printValues(struct reg registers[10]){
    for (int i = 0; i < 10; i++){
        printf("variable: %c, registers: $s%d\n", registers[i].letter, registers[i].reg_num);
    }
}

void read(char* fname){
    FILE *in_file = fopen(fname, "r");
    // allocate 128 spaces for the line to be read
    char line[128];

    // array of variables
    struct reg registers[10];

    int reg_count = 0;
    int tmp_reg = 0;
    // read in line by line
    while (fgets(line, sizeof(line), in_file)){
        printf("# %s", line);
        // formatting new line for the last line in the program
        if (line[strlen(line)-1] != '\n'){
            printf("\n");
        }
        // name of variable
        char var;
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
            registers[reg_count] = r;
            getRHS(registers, reg_count, line, offset, &tmp_reg);
            reg_count += 1;
        }
    }
    // printValues(registers);
}

int main(int argc, char* argv[]){
    // argv[1] will be the filename
    read(argv[1]);
}