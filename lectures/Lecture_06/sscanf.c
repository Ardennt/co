#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
void main()
	{
		FILE *myfile;
		int i, j, k;
		char buffer[1024];
		char name[80];
		if( NULL == (myfile = fopen("myfile.txt", "w")))
			{
			perror("fopen failed in main");
			exit(-1);
			}
		fgets(buffer, 1024, myfile);
		sscanf(buffer, "%d %d %d %s", &i, &j, &k, name);
		fclose(myfile);

		/* could check for error here, but usually not needed */
	}
