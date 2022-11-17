#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function returns inputarr as a list of chars
struct reg {
    char letter;
    int reg_num;
};

// 
// HELPER FUNCTIONS
// 

// checks if a letter is in the registers, returns 1 if yes
int inReg(struct reg registers[10], char letter){
    for (int i = 0; i < 10; i++){
        if (registers[i].letter == letter){
            return i;
        }
    }
    return -1;
}

// keeps track of temp variables
void add_tmp(int *tmp_var){
    if (*tmp_var > 9) {
        *tmp_var = 0;
    }
    else {
        *tmp_var += 1;
    }
}

// used when using li is needed
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

// takes var and a desired power and raises it to that
int pow_(int var, int power) {
    if (power == 0) return 1;

    int ret = var;
    for (int i = 1; i < power; i++){
        ret *= var;
    }
    return ret;
}

// breaks down a constant to powers of 2 and prints them out
void breakDown(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int num){

    int var1_reg = inReg(registers, var1[0]);
    // copy the original value of num first
    int neg = 0;

    // make num positive if its negative
    if (num < 0) {
        num *= -1;
        neg = 1;
    }

    // first time, move it
    int exp = 0;
    while (1) {
        if (pow_(2, exp + 1) > num) break;
        exp += 1;
    }

    // assigning t_before and t_after
    int t_before, t_after;
    if (*tmp_var + 1 > 9){
        t_before = 9;
        t_after = 0;
    } else {
        t_before = *tmp_var;
        t_after = *tmp_var + 1;
    }
    *tmp_var = t_after;

    printf("sll $t%d,$s%d,%d\n", t_before, t_before, exp);
    printf("move $t%d,$t%d\n", t_after, t_before);
    num -= pow_(2, exp);
    while (num > 0) {
        exp = 0;
        while (1) {
            if (pow_(2, exp + 1) > num) break;
            exp += 1;
        }
        // save value in t_after
        if (exp == 0) {
            printf("add $t%d,$t%d,$s%d\n", t_after, t_after, var1_reg);
        } 
        // keep adding
        else {
            printf("sll $t%d,$s%d,%d\n", t_before, var1_reg, exp);
            printf("add $t%d,$t%d,$t%d\n", t_after, t_after, t_before);
        }
        num -= pow_(2, exp);
    }

    // if its the last one, add a var2 statement
    if (var2[strlen(var2)-1] == ';'){
        if (neg) {
            printf("sub $s%d,$zero,$t%d\n", ourReg, t_after);
        }
        else {
            printf("move $s%d,$t%d\n", ourReg, t_after);
        }
    }
}

// break_down but we're given a -1 or 1
void breakdown_1(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int num, int usedtmp){
    int first_reg = inReg(registers, var1[0]);

    // last variable
    if (var2[strlen(var2)-1] == ';'){
        if (usedtmp) {
            printf("move $t%d,$t%d\n", *tmp_var, *tmp_var-1);
            if (num > 0) printf("move $s%d,$t%d\n", ourReg, *tmp_var);
            else printf("sub $s%d,$zero,$t%d\n", ourReg, *tmp_var);
        }
        else {
            printf("move $t%d,$s%d\n", *tmp_var, first_reg);
            if (num > 0) printf("move $s%d,$t%d\n", ourReg, *tmp_var);
            else printf("sub $s%d,$zero,$t%d\n", ourReg, *tmp_var);
        }
        add_tmp(*&tmp_var);
    }
    else {
        if (usedtmp) {
            printf("move $t%d,$t%d\n", *tmp_var, *tmp_var-1);
            add_tmp(*&tmp_var);
            if (num > 0) printf("move $t%d,$t%d\n", *tmp_var, *tmp_var-1);
            else printf("sub $t%d,$zero,$t%d\n", *tmp_var, *tmp_var-1);
        }
        else {
            printf("move $t%d,$t%d\n", *tmp_var, first_reg);
            add_tmp(*&tmp_var);
            if (num > 0) printf("move $t%d,$s%d\n", *tmp_var, first_reg);
            else printf("sub $t%d,$zero,$s%d\n", *tmp_var, first_reg);
        }
    }
}

// for some reason dividing by a 1/-1 and multiplying by a/-1 requires different printing...
void breakdown_1_div(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int num, int usedtmp){

    int first_reg = inReg(registers, var1[0]);

    if (var2[strlen(var2)-1] == ';'){
        if (usedtmp){
            if (num > 0) printf("move $s%d,$t%d\n", ourReg, *tmp_var-1);
            else printf("sub $s%d,$zero,$t%d\n", ourReg, *tmp_var-1);
        }
        else {
            if (num > 0) printf("move $s%d,$s%d\n", ourReg, first_reg);
            else printf("sub $s%d,$zero,$s%d\n", ourReg, first_reg);
        }
    }
    else {
        if (usedtmp){
            if (num > 0) printf("move $t%d,$t%d\n", *tmp_var, *tmp_var-1);
            else printf("sub $t%d,$zero,$t%d\n", *tmp_var, *tmp_var-1);
        }
        else {
            if (num > 0) printf("move $t%d,$s%d\n", *tmp_var, first_reg);
            else printf("sub $t%d,$zero,$s%d\n", *tmp_var, first_reg);
        }
        add_tmp(*&tmp_var);
    }
}

// checks if a num can be a power of 2
int pow_of_two (int num) {
    if (num < 0) {
        num *= -1;
    }

    int i = 1;
    int ret = pow_(2, i);
    while ( ret < num ) {
        ret = pow_(2, i);
        if (ret == num) {
            return i;
        }
        i++;
    }
    return 0;
}

// 
// ARITHMETIC FUNCTIONS
// 

// responsible for printing and organizing temp variables/etc for adding/subtracting
void plus_minus(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int usedtmp, char operation){
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
                printf("$s%d,$t%d,$s%d\n", ourReg, *tmp_var-1, second_var);
            // didn't use a temporary variable
            } else {
                printf("$s%d,$s%d,$s%d\n", ourReg, first_var, second_var);
            }
        }
        // addi condition
        else {
            int v2 = atoi(var2);
            if (usedtmp) {
                printf("addi $s%d,$t%d,", ourReg, *tmp_var-1);
            }
            else {
                printf("addi $s%d,$s%d,", ourReg, first_var);
            }

            if (operation == '-') printf("-%d\n", v2);
            else printf("%d\n", v2);
            
        }
        return;
    }

    // var2 isn't the last variable
    // add condition
    if (isalpha(var2[0])){
        if (operation == '+') printf("add ");
        else printf("sub ");

        if (usedtmp) {
            printf("$t%d,$t%d,$s%d\n", *tmp_var, *tmp_var-1, second_var);
        } else {
            printf("$t%d,$s%d,$s%d\n", *tmp_var, first_var, second_var);
        }
        add_tmp(*&tmp_var);
    }
    // addi condition
    else {
        int v2 = atoi(var2);
        if (usedtmp) {
            printf("addi $t%d,$t%d,", *tmp_var, *tmp_var-1);
        }
        else {
            printf("addi $t%d,$s%d,", *tmp_var, first_var);
        }
        add_tmp(*&tmp_var);
        if (operation == '-') printf("-%d\n", v2);
        else printf("%d\n", v2);
    }
}

// dividing by a constant
void divide_constant(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int usedtmp, int *L_count){
    int first_reg = inReg(registers, var1[0]);
    int v2 = atoi(var2);
    if (var2[strlen(var2)-1] == ';'){
        
        if (usedtmp) {
            printf("bltz $t%d,L%d\n", *tmp_var-1, *L_count);
            printf("srl $s%d,$t%d,%d\n", ourReg, *tmp_var-1, pow_of_two(v2));
            // negative condition
            if (v2 < 0) {
                printf("sub $s%d,$zero,$s%d\n", ourReg, ourReg);
            }
            printf("j L%d\n", *L_count + 1);
            // first L
            printf("L%d:\n", *L_count);
            printf("li $t%d,%d\n", *tmp_var, v2);
            printf("div $t%d,$t%d\n", *tmp_var - 1, *tmp_var);
        }
        else {
            printf("bltz $s%d,L%d\n", first_reg, *L_count);
            printf("srl $s%d,$s%d,%d\n", ourReg, first_reg, pow_of_two(v2));
            if (v2 < 0) {
                printf("sub $s%d,$zero,$s%d\n", ourReg, ourReg);
            }
            printf("j L%d\n", *L_count + 1);
            // first L
            printf("L%d:\n", *L_count);
            printf("li $t%d,%d\n", *tmp_var, v2);
            printf("div $s%d,$t%d\n", first_reg, *tmp_var);
        }
        printf("mflo $s%d\n", ourReg);
        add_tmp(*&tmp_var);
    }
    else {
        if (usedtmp) {
            printf("bltz $t%d,L%d\n", *tmp_var-1, *L_count);
            printf("srl $t%d,$t%d,%d\n", *tmp_var, *tmp_var-1, pow_of_two(v2));
            add_tmp(*&tmp_var);
            // negative condition
            if (v2 < 0) {
                printf("sub $t%d,$zero,$t%d\n", *tmp_var, ourReg);
            }
            printf("j L%d\n", *L_count + 1);
            // first L
            printf("L%d:\n", *L_count);
            printf("li $t%d,%d\n", *tmp_var, v2);
            printf("div $t%d,$t%d\n", *tmp_var, *tmp_var-1);
        }
        else {
            printf("bltz $s%d,L%d\n", first_reg, *L_count);
            printf("srl $t%d,$s%d,%d\n", *tmp_var, first_reg, pow_of_two(v2));
            add_tmp(*&tmp_var);
            if (v2 < 0) {
                printf("sub $t%d,$zero,$t%d\n", *tmp_var, *tmp_var);
            }
            printf("j L%d\n", *L_count + 1);
            // first L
            printf("L%d:\n", *L_count);
            printf("li $t%d,%d\n", *tmp_var, v2);
            printf("div $t%d,$t%d\n", *tmp_var, *tmp_var-1);
        }
        // jumping condition
        printf("mflo $t%d\n", *tmp_var);
        add_tmp(*&tmp_var);
    }

    // second L
    printf("L%d:\n", *L_count + 1);
    *L_count += 2;

}

// multiplying
void mult(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int usedtmp){
    int first_var = inReg(registers, var1[0]);
    int second_var = inReg(registers, var2[0]);

    // it's the last variable
    if (var2[strlen(var2)-1] == ';'){
        // both are chars
        if (isalpha(var2[0])){
            // multiplying two variables, one of them is the end

            // used temporary variable requires you to print the tempvar
            if (usedtmp){
                printf("mult $t%d,$s%d\n", *tmp_var-1, second_var);
                printf("mflo $s%d\n", ourReg);
            }
            // haven't used the temporary variable, just multiple both
            else {
                printf("mult $s%d,$s%d\n", first_var, second_var);
                printf("mflo $s%d\n", ourReg);
            }
        }
        // constant condition
        else {
            // case check whether it's 0 or not
            if (var2[0] == '0'){
                printf("li $s%d,0\n", ourReg);
                return;
            }

            int v2 = atoi(var2);
            if (v2 == 1 || v2 == -1) breakdown_1(registers, ourReg, var1, var2, *&tmp_var, v2, usedtmp);
            else breakDown(registers, ourReg, var1, var2, *&tmp_var, v2);
            
        }
        return;
    }

    if (isalpha(var2[0])){
        // if previously used a temp variable
        if (usedtmp) {
            printf("mult $t%d,$s%d\n", *tmp_var-1, second_var);
            // access hi or lo depending on division or modulus
            printf("mflo $t%d\n", *tmp_var);
        } else {
            printf("mult $s%d,$s%d\n", first_var, second_var);
            // access hi or lo depending on division or modulus
            printf("mflo $t%d\n", *tmp_var);
        }
        add_tmp(*&tmp_var);
    }
    // constant conditions
    else {
        // case check whether it's 0 or not
        if (var2[0] == '0'){
            printf("li $s%d,0\n", ourReg);
            return;
        }

        printf("li $t%d,%s\n", *tmp_var, var2);

        int v2 = atoi(var2);
        if (v2 == 1 || v2 == -1) breakdown_1(registers, ourReg, var1, var2, *&tmp_var, v2, usedtmp);
        else breakDown(registers, ourReg, var1, var2, *&tmp_var, v2);
    }
}

// divide/modulus
void divide_mod(struct reg registers[10], int ourReg, char var1[64], char var2[64], int *tmp_var, int usedtmp, char operation){
    int first_var = inReg(registers, var1[0]);
    int second_var = inReg(registers, var2[0]);

    // it's the last variable
    if (var2[strlen(var2)-1] == ';'){
        // both are chars
        if (isalpha(var2[0])){

            // used temporary variable requires you to print the tempvar
            if (usedtmp){
                printf("div $t%d,$s%d\n", *tmp_var-1, second_var);
                // access hi or lo depending on division or modulus
                if (operation == '%') printf("mfhi ");
                else printf("mflo ");
                printf("$s%d\n", ourReg);
            }
            // haven't used the temporary variable, just multiple both
            else {
                printf("div $s%d,$s%d\n", first_var, second_var);
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
            int v2 = atoi(var2);
            if (v2 == 1 || v2 == -1){
                breakdown_1_div(registers, ourReg, var1, var2, *&tmp_var, v2, usedtmp);
                return;
            }

            if (usedtmp){
                printf("li $t%d,%d\n", *tmp_var, v2);
                printf("div $t%d,$t%d\n", *tmp_var-1, *tmp_var);
                add_tmp(*&tmp_var);
            }
            else {
                printf("li $t%d,%d\n", *tmp_var, v2);
                printf("div $s%d,$t%d\n", first_var, *tmp_var);
                add_tmp(*&tmp_var);
            }
            
            
            // access hi or lo depending on division or modulus
            if (operation == '%') printf("mfhi ");
            else printf("mflo ");
            printf("$s%d\n", ourReg);
        }
        return;
    }

    if (isalpha(var2[0])){
        // if previously used a temp variable
        if (usedtmp) {
            printf("div $t%d,$s%d\n", *tmp_var-1, second_var);
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
        add_tmp(*&tmp_var);
    }
    else {
        // case check whether it's 0 or not
        if (var2[0] == '0'){
            printf("li $s%d,0\n", ourReg);
            return;
        }

        int v2 = atoi(var2);
        if (v2 == 1 || v2 == -1){
            breakdown_1_div(registers, ourReg, var1, var2, *&tmp_var, v2, usedtmp);
            return;
        }

        printf("li $t%d,%s\n", *tmp_var, var2);
        if (usedtmp){
            printf("div $t%d,$%d\n", *tmp_var - 1, *tmp_var);
        }
        else {
            printf("div $s%d,$t%d\n", first_var, *tmp_var);
        }

        add_tmp(*&tmp_var);
        // access hi or lo depending on division or modulus
        if (operation == '%') printf("mfhi ");
        else printf("mflo ");
        printf("$t%d\n", *tmp_var);
        add_tmp(*&tmp_var);
    }
}

// calculates the right hand side of an equation
void getRHS(struct reg registers[10], int ourReg, char line[128], int offset, int *tmpReg, int *L_count){
    
    // contains each variable on the right hand side
    char var1[64];
    // offset counter
    int n = 0;
    // temp register counter
    int usedtmp = 0;
    // loading condition (only 1 variable is in RHS)
    sscanf(line + offset, "%s%n", var1, &n);
    if (var1[strlen(var1)-1] == ';'){
        use_LI(registers, ourReg, var1);
        return;
    }
    offset += n;
    
    // not loading contion:
    while (var1[strlen(var1)-1] != ';'){

        // not loading, use operations
        char operation[2];
        char var2[64];
        sscanf(line + offset, "%s%s%n", operation, var2, &n);
        // add and subtraction
        if (operation[0] == '+' || operation[0] == '-'){
            plus_minus(registers, ourReg, var1, var2, *&tmpReg, usedtmp, operation[0]);
        }
        else if (operation[0] == '*') {
            mult(registers, ourReg, var1, var2, *&tmpReg, usedtmp);
        }
        else if (operation[0] == '/' || operation[0] == '%'){
            if (operation[0] == '/' && pow_of_two(atoi(var2)) != 0)
                divide_constant(registers, ourReg, var1, var2, *&tmpReg, usedtmp, *&L_count);
            else
                divide_mod(registers, ourReg, var1, var2, *&tmpReg, usedtmp, operation[0]);
        }
        else printf("Operation unknown\n");

        offset += n;
        
        usedtmp = 1;
        // put var in tmp
        sscanf(var2, "%s", var1);
    }
}

// function to read line by line
void read(char* fname){
    FILE *in_file = fopen(fname, "r");
    // allocate 128 spaces for the line to be read
    char line[128];

    // array of variables
    struct reg registers[10];

    int reg_count = 0;
    int tmp_reg = 0;
    int L_count = 0;
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
            getRHS(registers, reg_count, line, offset, &tmp_reg, &L_count);
            reg_count += 1;
        }
    }
    // printValues(registers);
}

int main(int argc, char* argv[]){
    // argv[1] will be the filename
    read(argv[1]);
}