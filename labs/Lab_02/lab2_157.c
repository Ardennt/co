#include <stdio.h>
#include <string.h>

int main(void) {

   /* Type your code here. */

   // title
   char title[100];
   printf("Enter a title for the data:\n");
   fgets(title, 100, stdin);
   printf("You entered: %s\n", title);

    // col 1 header
    const int n = 50;
    char col1h[n];
    printf("Enter the column 1 header:\n");
    fgets(col1h, n, stdin);
    printf("You entered: %s\n", col1h);

    // col 2 header
    char col2h[n];
    printf("Enter the column 2 header:\n");
    fgets(col2h, n, stdin);
    printf("You entered: %s\n", col2h);

    // data points
    int commacount = 0;
    char data_str[2][50];
    int data_int = -1;

    int keepGoing = 0;
    while (keepGoing == 0){
        printf("Enter a data point (-1 to stop input):\n");
        int checkInput = 0;
        if (scanf("%d", &checkInput) == 1 && checkInput == -1) {
            break;
        }
        
        scanf("%s", data_str[0]);
        scanf("%s %d", data_str[1], &data_int);

        // commacount
        int i = 0;
        while (data_str[0][i] != '\0') {
            if (data_str[0][i] == ',') commacount += 1;
            i++;
        }
        while (data_str[1][i] != '\0') {
            if (data_str[1][i] == ',') commacount += 1;
            i++;
        }

        int hasError = 0;
        if (commacount < 1){
            printf("Error: No comma in string.\n");
            hasError = 1;
        }
        if (commacount > 1){
            printf("Error: Too many commas in input.\n");
            hasError = 1;
        }
        if (data_int == -1){
            printf("Error: Comma not followerd by an integer.\n");
        }

        if (hasError == 0){
            printf("Data string: %s %s\n", data_str[0], data_str[1]);
            printf("Data integer: %d\n", data_int);
        }
    }
    

    // output to a table

   return 0;
}