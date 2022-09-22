#include <stdio.h>
#include <stdlib.h>

int main()
{
  // Note: consider the binary representation in 32 bits = 4 bytes
  // ==> 00000100 00000011 00000010 00000001
  unsigned lil_endy_boi = 1 + 2*256 + 3*256*256 + 4*256*256*256;
  char* pointy_boi = (char*)&lil_endy_boi;
  printf("%u %u %u %u\n", pointy_boi[0], pointy_boi[1], pointy_boi[2], pointy_boi[3]);
  return 0;
}
