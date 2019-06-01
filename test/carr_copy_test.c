/// \file
/// \brief Unit test for carr_copy
///

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{
    //   int carr_copy(void* dest, const void* const src, uint32_t const len, uint32_t const elem_size)

    /// carr_copy shall:
    /// \reg 1 Return error=1 when dest==NULL else return 0
    /// \req 2 Set dest[0]=0 when src==NULL
    /// \req 3 Set dest[0]=0 when len==0
    /// \req 4 Set dest[0]=0 when elem_size=0
    /// \req 5 copy len*elem_size bytes from src to dest
    /// \req 6 Set dest[len*elem_size]=0 

    char s1[101] = "Talc Borium Corrundum";

    {
    int err = carr_copy(NULL, s1, 100, 1);
    EQ  (err,           1, "r1. Verify err=1 is returned when dest==NULL");
    }
    
    {
    char dest[101];
    int err = carr_copy(dest, NULL, 100, 1);
    EQ  (err,           0, "r1. Verify err=0 is returned when dest!=NULL")
    EQ  (dest[0],       0, "r2. Verify dest[0]==0 when src==NULL")
    }
    
    {
    char dest[101];
    int err = carr_copy(dest, s1, 0, 1);
    EQ  (err,           0, "r1. Verify err=0 is returned when dest!=NULL")
    EQ  (dest[0],       0, "r3. Verify dest[0]==0 when len==0")
    }
    
    {
    char dest[101];
    int err = carr_copy(dest, s1, 100, 0);
    EQ  (err,           0, "r1. Verify err=0 is returned when dest!=NULL")
    EQ  (dest[0],       0, "r4. Verify dest[0]==0 when elem_len==0")
    }
    
    {
    char dest[101];
    int err = carr_copy(dest, s1, 100, 1);
    EQ  (err,           0, "r1. Verify err=0 is returned when dest!=NULL")
    EQS (dest,         s1, "r5. Verify dest==src valid inputs")
    }
    
    {
    char dest[11];
    dest[10] = 'x';
    const char* exp = "Talc Boriu";
    int err = carr_copy(dest, s1, 10, 1);
    EQ  (err,            0, "r1. Verify err=0 is returned when dest!=NULL");
    EQ  (dest[10],       0, "r6. Verify dest[len]=0 even when src[len]!=0");
    EQS (dest,         exp, "r5. Verify dest[0..len-1]==src when src longer than len")
    }
    
    return 0;
}

