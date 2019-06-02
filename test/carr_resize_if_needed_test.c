/// \file
/// \brief Unit test for carr_resize_if_needed
/// carr_resize_if_needed shall:
/// \req 1. Return err=1 if ca is NULL
/// \req 2. Return err=1 if new_len>=max_size
/// \req 3. Return err=1 on carr_resize error (NOT tested)
/// \req 4. Return err=0 on success.
/// \req 5. Update if new_size is larger than current size
/// \req 6. Allocate double the memory requested
/// \req 7. Allocate max_size when 2*(new_len+1) > max_size
/// \req 8. Do not update if new_size is LE current size

// int carr_resize_if_needed(carr_t* ca, uint32_t new_len)

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{

  carr_t* s1 = carr_init(40,1,"hello world",0);

  { // VERIFY ERR=1 RETURNED WHEN CA IS NULL
  int err = carr_resize_if_needed(NULL,10);
  EQ  (err, 1, "req 1. Verify err=1 is returned when ca parameter is NULL")
  }

  { // VERIFY ERR=1 RETURNED WHEN NEW_LEN >= MAX_SIZE
  int err = carr_resize_if_needed(s1,60);
  EQ  (err, 1, "req 2. Verify err=1 is returned when new_len >= max_size")
  }

  { // VERIFY CASE WHERE SIZE INCREASES
  carr_t* s2 = carr_dup(NULL,s1);
  s2->max_size = 0;
  void* ptr  = s2->arr;
  int new_size = (30+1)*2;
  int err = carr_resize_if_needed(s2,30);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,s1->len ,"req x. Verify len stayed the same")
  EQ  (s2->size  ,new_size,"req 6. Verify size updated to new size")
  NEQP(s2->arr   ,ptr     ,"req 5. Verify new buffer allocated")
  EQS (s2->arr   ,s1->arr ,"req 5. Verify original content copied to new array")
  }


  { // VERIFY CASE WHERE SIZE INCREASE IS CLAMPED BY MAX_SIZE
  carr_t* s2 = carr_dup(NULL,s1);
  s2->max_size = 40;
  void* ptr  = s2->arr;
  int new_size = (30+1)*2;
  int err = carr_resize_if_needed(s2,30);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,s1->len ,"req x. Verify len stayed the same")
  EQ  (s2->size  ,40      ,"req 7. Verify size updated to new size")
  NEQP(s2->arr   ,ptr     ,"req 5. Verify new buffer allocated")
  EQS (s2->arr   ,s1->arr ,"req 5. Verify original content copied to new array")
  }


  { // VERIFY CASE WHERE SIZE DECREASES
  carr_t* s2 = carr_dup(NULL,s1);
  s2->max_size = 40;
  void* ptr  = s2->arr;
  int cur_size = s2->size;
  int new_size = 5;
  int err = carr_resize_if_needed(s2, new_size);
  EQ  (err       ,0        ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,s1->len  ,"req x. Verify len stayed the same")
  EQ  (s2->size  ,cur_size ,"req 7. Verify size doesn't decrease")
  EQP (s2->arr   ,ptr      ,"req 5. Verify ptr stays the same when new_size < size")
  EQS (s2->arr   ,s1->arr  ,"req 5. Verify content not changed")
  }


  { // VERIFY CASE WHERE NEW_LEN EQUALS LEN
  carr_t* s2 = carr_dup(NULL,s1);
  s2->max_size = 40;
  void* ptr  = s2->arr;
  int cur_size = s2->size;
  int new_len = cur_size;
  int new_size = 2*(new_len+1);
  int err = carr_resize_if_needed(s2, new_len);
  EQ  (err       ,0        ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,s1->len  ,"req x. Verify len stayed the same")
  EQ  (s2->size  ,new_size ,"req 7. Verify size doesn't decrease")
  NEQP(s2->arr   ,ptr      ,"req 5. Verify ptr stays the same when new_size < size")
  EQS (s2->arr   ,s1->arr  ,"req 5. Verify content not changed")
  }


  return 0;

}
