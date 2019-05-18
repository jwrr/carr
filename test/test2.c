#include <stdio.h>
#include "carr.h"

int main()
{
  carr_t*  str1 = carrs_new();
  carr_t*  str2 = carrs_init("initial string");
  carr_print(str2);

  printf("hello\n");
  return 1;
}

