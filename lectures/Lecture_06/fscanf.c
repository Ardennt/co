#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
void main()
	{
		FILE *myfile;
		int i, j, k;
		char buffer[80];
		if( NULL == (myfile = fopen("myfile.txt", "r")))
			{
			perror("fopen failed in main");
			exit(-1);
			}
		fscanf(myfile, "%d %d %d %s", &i, &j, &k, buffer);
		fclose(myfile);
		/* could check for error here, but usually not needed */
	}
