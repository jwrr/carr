/// \file
/// \brief Unit test for arrlen

/// \req 1 - Return 0 if arr pointer is null
/// \req 2 - Return 0 if elem_size is 0
/// \req 3 - Return size when size!=0 and 0 not found
/// \req 4 - Return index of first zero
/// uint32_t arrlen(const void* arr, uint32_t elem_size, uint32_t size)

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{

  {const char* msg = "REQ 1. VERIFY 0 IS RETURNED WHEN ARR ARGUMENT IS NULL";
  char str[20] = "hello";
  int len = arrlen(NULL,1,20);
  EQ  (len, 0, msg)
  }

  {const char* msg = "REQ 2. VERIFY 0 IS RETURNED WHEN ELEM_SIZE ARGUMENT IS 0";
  char str[20] = "hello";
  int len = arrlen(str,0,20);
  EQ  (len, 0, msg)
  }

  {const char* msg = "REQ 3. VERIFY SIZE IS RETURNED WHEN NULL ISN'T FOUND IN FIRST 'SIZE' ELEMENTS";
  char str[20] = "hello";
  int len = arrlen(str,1,3);
  EQ  (len, 3, msg)
  }


  {const char* msg = "REQ 4. VERIFY INDEX OF FIRST NULL IS RETURNED";
  char str[20] = "hello";
  int len = arrlen(str,1,20);
  EQ  (len, 5, msg)
  }

  return 0;

}
