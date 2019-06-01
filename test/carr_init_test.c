/// \file 
/// \brief Unit tests for carr_init.
///

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{
    /// carr_init test
    /// \req  1: Verify elem_size==0 return NULL pointer
    /// \req  2: Verify max_size==0 returns valid pointer
    /// \req  3: Verify max_size>0 returns valid pointer
    /// \req  4: Verify max_size is set to max_size
    /// \req  5: Verify elem_size is set to elem_size
    /// \req  6: Verify size is set to len+1;
    /// \req  7: Verify it is set to len;
    /// \req  8: Verify arr is set to valid pointer
    /// \req  9: Verify len is set to lenth of array
    /// \req 10: Verify arr[size]==0
    /// \req 11: Verify arr = init_arr 
    
    /// \req 12: Verify len==0 when init_arr==NULL
    /// \req 13: Verify len=init_len when init_len > 0
    /// \req 14: Verify len>0 when init_len==0 (null-terminated)

//  carr_t* carr_init(uint32_t max_size, uint32_t elem_size, const void* init_arr, int32_t init_len);

    carr_t* s1 = carr_init(100,1,"hello",0);
    // \req 1.1 cstra_new shall initialize max_size to the max_size argument.
    NEQP(s1,           NULL, "r3: Verify valid pointer when max_size>0");
    EQ  (s1->max_size,  100, "r4: Verify max_size")
    EQ  (s1->elem_size,   1, "r5: Verify elem_size")
    EQ  (s1->size,        6, "r6: Verify size")
    EQ  (s1->it,          5, "r7: Verify it")
    NEQP(s1->arr,      NULL, "r8: Verify arr is not NULL")
    EQ  (s1->len,         5, "r9: Verify len")
    EQ  (s1->arr[6],      0, "r10: Verify arr[size]==0")
    EQS (s1->arr,   "hello", "r11: Verify arr==init_arr")

    carr_t* s2 = carr_init(100,0,"hello",0);
    EQP (s2,           NULL, "r1: Verify NULL pointer when elem_size--0");

    char str[] = "hello world";
    carr_t* s3 = carr_init(0,1,"hello world",0);
    NEQP(s3,           NULL, "r2: Verify valid pointer when max_size==0");
    EQ  (s3->max_size,    0, "r4: Verify max_size")
    EQ  (s3->elem_size,   1, "r5: Verify elem_size")
    EQ  (s3->size,       12, "r6: Verify size")
    EQ  (s3->it,         11, "r7: Verify it")
    NEQP(s3->arr,      NULL, "r8: Verify arr is not NULL")
    EQ  (s3->len,        11, "r9: Verify len")
    EQ  (s3->arr[12],     0, "r10: Verify arr[size]==0")
    EQS (s3->arr,       str, "r11: Verify arr==init_arr")
    return 0;
}

