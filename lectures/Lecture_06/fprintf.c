#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
void main()
	{
		FILE *myfile;
		int i, j, k;
		char buffer[80];
		if(NULL == (myfile = fopen("myfile.txt", "w+")))
			{
			perror("fopen failed in main");
			exit(-1);
			}
		fscanf(myfile, "%d %d %d %s", &i, &j, &k, buffer);
		fprintf(myfile, "%d %d %d %s", i, j, k, buffer);
    printf("%d %d %d %s", i, j, k, buffer);
		fclose(myfile);

		/* could check for error here, but usually not needed */
	}
