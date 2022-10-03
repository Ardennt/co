#include <stdio.h>
#include <stdlib.h>


// 8) Your friend Sally wrote a cool C program that encodes a secret string 
// as a series of integers and then writes out those integers to a binary file. 
// For example, she would encode string "hey!" within a single int as:
// int a = (unsigned)'h' * 256*256*256 + (unsigned)'e' * 256*256 + (unsigned)'y' * 256 + (unsigned)'!';

int main() {
    
    // After outputting a secret string to a file, Sally sends you that file and you read 
    // it in as follows (assume we have the filesize() function as above):

    FILE* fp = fopen("secret", "r");
    int size = filesize(fp);
    char buffer[256];
    fread(buffer, sizeof(char), size / sizeof(char), fp);
    fclose(fp);
    printf("%s", buffer);

    // However, the output you observe is somewhat nonsensical:

    // "pmocgro lur 1!ze"

    // Can you determine what the original secret string is and speculate on what might the issue be with Sally's program?

    // She encoded the string but both our machines run on little endian, that means that the memory is stored with the lowest address as the lowest significance and the highest with the higest
}
