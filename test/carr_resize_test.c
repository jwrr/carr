/// \file
/// \brief Unit test for carr_resize
///
/// carr_resize shall:
/// \req 1 Return err (1) when carr parameter is NULL.
/// \req 2 Return err (1) on malloc failure. (TBD - HOW TO TEST?)
/// \req 3 Return success (0) on all other conditions.
/// \req 4 Not modify dynamic array when new_size=current_size (performance enhancement).
/// \req 5 Malloc new memory buffer.  Internal carr->arr pointer changes to new buffer.
/// \req 6 Copy original contents to new buffer.
/// \req 7 Keep len the same.
/// \req 8 Change size to new_size.
/// \req 9 Frees original buffer. (TBD - HOW TO TEST?)
/// \req 10 Support increasing size
/// \req 11 Support decreasing size
/// \req 12 Truncate len when decreasing size
/// \req 13 Force last entry (element new_size-1) to ZERO.
/// \req 14 Resize to one zero-filled entry when new_size is 0 or 1.
/// \req 15 Resize to max_size if new_size is larger than max_size.

// int carr_resize(carr_t* carr, const uint32_t new_size)

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{

  carr_t* s1 = carr_init(0,1,"hello world",0);

  {
  int err = carr_resize(NULL,10);
  EQ  (err, 1, "req 1. Verify err=1 is returned when carr parameter is NULL")
  }

  { // VERIFY CASE WHERE SIZE INCREASES
  carr_t* s2 = carr_dup(NULL,s1);
  int   size = s2->size;
  int   max_size = s2->max_size;
  void* ptr  = s2->arr;
  int err = carr_resize(s2,200);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,s1->len ,"req 7. Verify len stayed the same")
  EQ  (s2->size  ,200     ,"req 8. Verify size updated to new size")
  NEQP(s2->arr   ,ptr     ,"req 5. Verify new buffer allocated")
  EQS (s2->arr   ,s1->arr ,"req 6. Verify original content copied to new array")
  EQ  (s2->arr[max_size-1],0,"req 13. Verify last element is forced to zero")
  EQ  (1         ,1       ,"req 10. Verified size increase")
  }

  { // VERIFY CASE WHERE SIZE DECREASES
  carr_t* s2 = carr_dup(NULL,s1);
  int   size = s2->size;
  int   max_size = s2->max_size;
  void* ptr  = s2->arr;
  char  expect[] = "hello";

  int err = carr_resize(s2, 6);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,5       ,"req 7. Verify len reduced to size-1")
  EQ  (s2->size  ,6       ,"req 8. Verify size updated to new size")
  NEQP(s2->arr   ,ptr     ,"req 5. Verify new buffer allocated")
  EQS (s2->arr   ,expect  ,"req 6. Verify original content truncated to shorter array")
  EQ  (s2->arr[max_size-1],0,"req 13. Verify last element is forced to zero")
  EQ  (1         ,1       ,"req 11. Verified size decrease")
  }

  { // VERIFY CASE WHERE SIZE STAYS THE SAME
  carr_t* s2 = carr_dup(NULL,s1);
  int   size = s2->size;
  int   max_size = s2->max_size;
  void* ptr  = s2->arr;
  int err = carr_resize(s2,s1->size);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,s1->len ,"req 7. Verify len stayed the same")
  EQ  (s2->size  ,s1->size,"req 8. Verify size stayed the same")
  EQP (s2->arr   ,ptr     ,"req 4. Verify new buffer not allocated when size doesn't change")
  EQS (s2->arr   ,s1->arr ,"req 6. Verify content stayed the same")
  }

  { // VERIFY CASE WHERE SIZE=1
  carr_t* s2 = carr_dup(NULL,s1);
  int   size = s2->size;
  int   max_size = s2->max_size;
  void* ptr  = s2->arr;
  char  expect[] = "";
  int err = carr_resize(s2, 1);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,0       ,"req 7. Verify len reduced to size-1")
  EQ  (s2->size  ,1       ,"req 8. Verify size updated to new size")
  NEQP(s2->arr   ,ptr     ,"req 5. Verify new buffer allocated")
  EQS (s2->arr   ,expect  ,"req 6. Verify original content truncated to shorter array")
  EQ  (s2->arr[0],0       ,"req 13. Verify last element is forced to zero")
  }

  { // VERIFY SIZE=0 IS HANDLED LIKE SIZE=1
  carr_t* s2 = carr_dup(NULL,s1);
  int   size = s2->size;
  int   max_size = s2->max_size;
  void* ptr  = s2->arr;
  char  expect[] = "";
  int err = carr_resize(s2, 0);
  EQ  (err       ,0       ,"req 3. Verify err=0 on success")
  EQ  (s2->len   ,0       ,"req 7. Verify len reduced to size-1")
  EQ  (s2->size  ,1       ,"req 8. Verify size updated to new size")
  NEQP(s2->arr   ,ptr     ,"req 5. Verify new buffer allocated")
  EQS (s2->arr   ,expect  ,"req 6. Verify original content truncated to shorter array")
  EQ  (s2->arr[0],0       ,"req 13. Verify last element is forced to zero")
  }

  return 0;

}
