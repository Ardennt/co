#include <stdio.h>
#include <stdlib.h>

int main()
{
  // open up our text files
  char* file_in1 = "text1.txt";
  char* file_in2 = "text2.txt";
  FILE* file1 = fopen(file_in1, "r");
  FILE* file2 = fopen(file_in2, "r");
  
  // Get size of text1 - note that we need to 'reset' the file pointer back
  // to the beginning of the file, as we're going to be reading from it.
  fseek(file1, 0L, SEEK_END);
  int file_size1 = ftell(file1);
  fseek(file1, 0L, SEEK_SET);
  
  // Get size of text2
  fseek(file2, 0L, SEEK_END);
  int file_size2 = ftell(file2);
  fseek(file1, 0L, SEEK_SET);
  
  printf("File sizes (in bytes): text1.txt: %d, text2.txt: %d\n", 
    file_size1, file_size2);
  
  // Read in our info - note that in practice we'd want to use a dynamic array.
  // For this example, we know there is only 20 values in each file
  int values1[20];
  int values2[20];
  char values3[20];
  char buffer[256];
  
  for (int i = 0; i < 20; ++i) {
    fgets(buffer, 256, file1);
    values1[i] = atoi(buffer); // covert a C string to an integer
    fgets(buffer, 256, file2);
    values2[i] = atoi(buffer);
    values3[i] = (char)(unsigned)values1[i];
  }
  
  fclose(file1);
  fclose(file2);
  
  // write the files as binary
  char* file_out1 = "text1.bin";
  char* file_out2 = "text2.bin";
  char* file_out3 = "text3.bin";
  
  FILE* output1 = fopen(file_out1, "w");
  FILE* output2 = fopen(file_out2, "w");
  FILE* output3 = fopen(file_out3, "w");
  
  fwrite(values1, sizeof(int), 20, output1);
  fwrite(values2, sizeof(int), 20, output2);
  fwrite(values3, sizeof(char), 20, output3);
  
  // what's the new file sizes? 
  fseek(output1, 0L, SEEK_END);
  int file_size_out1 = ftell(output1);
  fseek(output2, 0L, SEEK_END);
  int file_size_out2 = ftell(output2);
  fseek(output3, 0L, SEEK_END);
  int file_size_out3 = ftell(output3);
  
  printf("File sizes (in bytes): text1.bin: %d, text2.bin: %d, 3: %d\n", 
    file_size_out1, file_size_out2, file_size_out3);
  
  fclose(output1);
  fclose(output2);
  
  return 0;
}
