/// \file
/// \brief Unit test for mem_is_zero
/// \req 1. Return 0 if pointer is NULL
/// \req 2. Return 1 if size is 0
/// \req 3. Return 0 if first byte is  not zero
/// \req 4. Return 1 if size is 1 and first byte is zero
/// \req 5. Return 1 if all bytes are zero
/// \req 6. Return 0 if all bytes not zero

/// int mem_is_zero(const void* const ptr, uint32_t size)

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{

  carr_t* s1 = carr_init(40,1,"hello world",0);

  {const char* msg = "REQ 1. VERIFY 0 IS RETURNED WHEN PTR IS NULL";
  int is_zero = mem_is_zero(NULL,10);
  EQ  (is_zero, 0, msg)
  }

  {const char* msg = "REQ 2. VERIFY 1 IS RETURNED WHEN SIZE IS 0";
  int is_zero = mem_is_zero(s1->arr,0);
  EQ  (is_zero, 1, msg)
  }

  {const char* msg = "REQ 3. VERIFY 0 IS RETURN WHEN FIRST BYTE IS NOT ZERO";
  int is_zero = mem_is_zero(s1->arr,7);
  EQ  (is_zero, 0, msg)
  }

  {const char* msg = "REQ 4. VERIFY 1 IS RETURN WHEN FIRST BYTE IS ZERO AND SIZE=1";
  int is_zero = mem_is_zero("",1);
  EQ  (is_zero, 1, msg)
  }

  {const char* msg = "REQ 5. VERIFY 1 IS RETURN WHEN ALL BYTES ARE ZERO";
  char str[20] = "hello there";
  for (int i=0;i<5;i++) str[i]='\0';
  int is_zero = mem_is_zero(str,5);
  EQ  (is_zero, 1, msg)
  }

  {const char* msg = "REQ 6. VERIFY 0 IS RETURN WHEN ALL BYTES ARE NOT ZERO";
  char* str="hello there";
  int is_zero = mem_is_zero(str,5);
  EQ  (is_zero, 0, msg)
  }

  return 0;

}
