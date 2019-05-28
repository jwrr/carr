/// \file
/// \brief Unit test for carr_dup
///

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{
    //  carr_t* carr_dup(carr_t* dest, carr_t* src);
    /// carr_dup
    /// \req 1. Return NULL if src is NULL
    /// \req 2. Return dest if dest is not NULL
    /// \req 3. Return dest!=NULL if dest is NULL
    /// \req 4. Return duplicate of src

    carr_t* s1 = carr_init(0,1,"hello world",0);
    carr_t* s2 = carr_dup(s1,NULL);
    EQP (s2,           NULL, "r1. Verify NULL is returned with src is NULL")

    carr_t* s3 = carr_dup(NULL,s1);
    NEQP(s3,           NULL, "r3. Verify NULL isn't returned when src isn't NULL")
    EQ  (s3->len,   s1->len, "r4. Verify return's len matches src's len")
    EQS (s3->arr,   s1->arr, "r4. Verify return's array contents matches src")
    
    carr_t* s4 = carr_dup(s3,s1);
    EQP (s4,             s3, "r2. Verify return ptr matches dest's ptr address")
    EQ  (s4->len,   s1->len, "r4. Verify return's len matches src's len")
    EQS (s4->arr,   s1->arr, "r4. Verify return's array contents matches src")
    
    return 0;
}

