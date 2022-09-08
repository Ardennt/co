#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE* f = fopen("plain.txt", "r");
    
    printf("%d", isdigit('1'));
    return 0;
}