#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* f = fopen("plain.txt", "r");
    // assume both inputs are doubles

    // check whether they're strictly integers
    char row[15];
    char col[15];

    fscanf(f, "%s%s", row, col);

    printf("%d", sizeof(row));
    // int i = 0;
    // while (row[i] != '\0' || i < 15){
    //     printf("%d\n", i);
    //     printf("%c %c\n", row[i], col[i]);
    //     i++;
    // }
}