#include <stdlib.h>
#include <stdio.h>

// 7) Assume we have a function filesize(FILE* fp) that tells us the size of a file 
// in bytes. What might the expected values of x and y from the code snippet below 
// be if we assume one byte per character in an ASCII text files?

int main() {
    char* a = "Woo!";
    FILE* fp1 = fopen("file1", "w");
    FILE* fp2 = fopen("file2", "w");
    fprintf(fp1, "%s", a);
    fwrite(a, 1, 4, fp2);
    int x = filesize(fp1); // 4 bytes
    int y = filesize(fp2); // 4 bytes
}
