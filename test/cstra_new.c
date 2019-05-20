/// \file 
/// \brief This file provides unit tests for carr.
///

#include "carr.h"
#include "test.h"

int main(int argc, char* argv[])
{
    carr_t* s1 = cstra_new(10,"the quick");
    // \req 1.1 cstra_new shall initialize max_size to the max_size argument.
    EQ(s1->max_size, 10, "1000 Verify s1->max_size == 10 after str_new")
    // \req 1.2 cstra_new shall initialize size to the length+1 of the str argument.
    EQ(s1->size, 10, "1001 Verify s1->size == 10 after str_new")
    // \req 1.3 cstra_new shall initialize len the length of the str argument.
    EQ(s1->len, 9,   "1002 Verify s1->len == 9 after str_new")
    // \req 1.4 cstra_new shall initialize the next pointer to NULL.
    EQP(s1->next, NULL, "1003 Verify s1->next == NULL after str_new")
    // \req 1.5 cstra_new shall intialize str to the argument string.
    EQS(s1->arr, "the quick", "1004 Verify s1->arr == 'the quick' after str_new")      

    s1 = carr_free(s1);
    // \req 1.6 carr_free shall return NULL.
    EQP(s1, NULL, "Verify s1 is NULL after str_free")

    char str2[] = "Four score and seven years ago";
    int str2_len = strlen(str2);
    int str2_size = str2_len + 1;
    carr_t* s2 = cstra_new(0, "Four score and seven years ago");
    // \req 1.7 cstra_new shall initialize max_size to 0 when the max_size argument is 0.
    EQ(s2->max_size, 0, "1010 Vereify s2->max_size == 0 after str_new")
    // \req 1.8 cstra_new shall initialize size to len+1 of str argument when max_size is 0.
    EQ(s2->size, str2_size, "1011 Verify s2->size == 31 after str_new")
    // \req 1.9 cstra_new shall initialize len to len of str argument when max_size is 0.
    EQ(s2->len,  str2_len,  "1012 Verify s2->len == 9 after str_new")
    // \req 1.10 cstra_new shall initialize next to NULL when max_size is 0.
    EQP(s2->next, NULL, "1013 Verify s2->next == NULL after str_new")
    // \req 1.11 cstra_new shall initialize str to str arg when max_size is 0.
    EQS(s2->arr, str2, "1014 Verify s2->arr == 'the quick' after str_new")
    carr_free(s2);

    carr_t* s3 = cstra_new(0, "");
    // \req 1.12 cstra_new shall initialize max_size=max_size if str argument has len=0.
    EQ(s3->max_size, 0, "1015 Verify max_size=0 when str='' ") 
    // \req 1.13 cstra_new shall initialize size=1 if str argument has len=0.
    EQ(s3->size, 1, "1016 Verify size=1 when str='' ")
    // \req 1.14 cstra_new shall initialize len=0 if str argument has len=0.
    EQ(s3->len, 0, "1017 Verify len=0 when str='' ")
    // \req 1.15 cstra_new shall initialize str="" if str argument has len=0.
    EQS(s3->arr, "", "1018 Verify str='' if str arg is ''")
    carr_free(s3);

    carr_t* s4 = cstra_new(32, NULL);
    // \req 1.16 cstra_new shall initialize max_size=max_size if str argment is NULL.
    EQ(s4->max_size, 32, "1019 Verify max_size=max_size when str=NULL")
    // \req 1.17 cstra_new shall initialize size=1 if str argment is NULL.
    EQ(s4->size, 1, "1020 Verify size=1 when str=NULL")
    // \req 1.18 cstra_new shall initialize len=0 if str argment is NULL.
    EQ(s4->len, 0, "1021 Verify len=0 when str=NULL")
    // \req 1.19 cstra_new shall initialize str to "" str argment is NULL.
    EQS(s4->arr, "", "1022 Verify str='' when str=NULL")
    carr_free(s4);

    carr_t* s5 = cstra_new(4,"Four score and seven");
    // \req 1.20 cstra_new shall not let str grow beyond max_size.
    EQ(s5->max_size, 4, "Verify max_size=max_size when str is too long")
    // \req 1.21 cstra_new shall not let size be larger than max_size.
    EQ(s5->size, 4, "Verify size=max_size when str is too long")
    // \req 1.22 cstra_new shall not let len be as large as max_size.
    EQ(s5->len, 3, "Verify len=max_size-1 when str is too long")
    // \req 1.23 cstra_new shall chomp str to len=max_size-1 if it is too long.
    EQS(s5->arr, "Fou", "Verify str is the first letters of arg str")  
    carr_free(s5);


    return 0;
}
