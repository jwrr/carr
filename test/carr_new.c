/// \file 
/// \brief This file provides unit tests for carr.
///

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{
    /// carr_new test
    /// \req  1: Verify elem_size==0 return NULL pointer
    /// \req  2: Verify max_size==0 returns valid pointer
    /// \req  3: Verify max_size>0 returns valid pointer
    /// \req  4: Verify ptr->max_size is set to max_size
    /// \req  5: Verify ptr->elem_size is set to elem_size
    /// \req  6: Verify ptr->size is set to 1;
    /// \req  7: Verify ptr->it is set to 0;
    /// \req  8: Verify ptr->arr is set to valid pointer
    /// \req  9: Verify ptr->len is set to 0
    /// \req 10: Verify ptr->


//      carr_t* carr_new(uint32_t max_size, uint32_t elem_size);

    carr_t* s1 = carr_new(100,1);
    // \req 1.1 cstra_new shall initialize max_size to the max_size argument.
    NEQP(s1,           NULL, "r3: Verify valid pointer when max_size>0");
    EQ  (s1->max_size,  100, "r4: Verify max_size")
    EQ  (s1->elem_size,   1, "r5: Verify elem_size")
    EQ  (s1->size,        1, "r6: Verify size")
    EQ  (s1->it,          0, "r7: Verify it")
    NEQP(s1->arr,      NULL, "r8: Verify arr is not NULL")
    EQ  (s1->len,         0, "r9: Verify len")

    carr_t* s2 = carr_new(100,0);
    EQP (s2,           NULL, "r1: Verify NULL pointer when elem_size--0");

    carr_t* s3 = carr_new(0,1);
    NEQP(s3,           NULL, "r2: Verify valid pointer when max_size==0");
    EQ  (s3->max_size,    0, "r4: Verify max_size")
    EQ  (s3->elem_size,   1, "r5: Verify elem_size")
    EQ  (s3->size,        1, "r6: Verify size")
    EQ  (s3->it,          0, "r7: Verify it")
    NEQP(s3->arr,      NULL, "r8: Verify arr is not NULL")
    EQ  (s3->len,         0, "r9: Verify len")
    return 0;
}
