/// \file 
/// \brief This file provides unit tests for cstr.
///
/// \main 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cis.h"
#include "ctest.h"
#include "cstr.h"


/// \brief Test program for cstr.
/// \return Failure code
/// \todo Implement failure code.
      
int cstr_test(const int argc, char* argv[])
{
   CTEST_INIT(argc, argv)
   ctest_mode(t, CTEST_PRINT_TOTAL);

   ctest_unit(t,"str_new");
   {
      cstr_t* s1 = cstr_new(10,"the quick");
      // \req 1.1 cstr_new shall initialize max_size to the max_size argument.
      ctest_eqi(t, s1->max_size, 10, "1000 Vereify s1->max_size == 10 after str_new");
      // \req 1.2 cstr_new shall initialize size to the length+1 of the str argument.
      ctest_eqi(t, s1->size, 10, "1001 Verify s1->size == 10 after str_new");
      // \req 1.3 cstr_new shall initialize len the length of the str argument.
      ctest_eqi(t, s1->len, 9,   "1002 Verify s1->len == 9 after str_new");
      // \req 1.4 cstr_new shall initialize the next pointer to NULL.
      ctest_eqi(t, (int)(s1->next), (int)NULL, "1003 Verify s1->next == NULL after str_new");
      // \req 1.5 cstr_new shall intialize str to the argument string.
      ctest_eqs(t, s1->str, "the quick", "1004 Verify s1->str == 'the quick' after str_new");      

      s1 = cstr_free(s1);
      // \req 1.6 cstr_free shall return NULL.
      ctest_eqi(t, (int)s1, (int)NULL, "Verify s1 is NULL after str_free");

      char str2[] = "Four score and seven years ago";
      int str2_len = strlen(str2);
      int str2_size = str2_len + 1;
      cstr_t* s2 = cstr_new(0, "Four score and seven years ago");
      // \req 1.7 cstr_new shall initialize max_size to 0 when the max_size argument is 0.
      ctest_eqi(t, s2->max_size, 0, "1010 Vereify s2->max_size == 0 after str_new");
      // \req 1.8 cstr_new shall initialize size to len+1 of str argument when max_size is 0.
      ctest_eqi(t, s2->size, str2_size, "1011 Verify s2->size == 31 after str_new");
      // \req 1.9 cstr_new shall initialize len to len of str argument when max_size is 0.
      ctest_eqi(t, s2->len,  str2_len,  "1012 Verify s2->len == 9 after str_new");
      // \req 1.10 cstr_new shall initialize next to NULL when max_size is 0.
      ctest_eqi(t, (int)(s2->next), (int)NULL, "1013 Verify s2->next == NULL after str_new");
      // \req 1.11 cstr_new shall initialize str to str arg when max_size is 0.
      ctest_eqs(t, s2->str, str2, "1014 Verify s2->str == 'the quick' after str_new");
      cstr_free(s2);

      cstr_t* s3 = cstr_new(0, "");
      // \req 1.12 cstr_new shall initialize max_size=max_size if str argument has len=0.
      ctest_eqi(t, s3->max_size, 0, "1015 Verify max_size=0 when str='' "); 
      // \req 1.13 cstr_new shall initialize size=1 if str argument has len=0.
      ctest_eqi(t, s3->size, 1, "1016 Verify size=1 when str='' ");
      // \req 1.14 cstr_new shall initialize len=0 if str argument has len=0.
      ctest_eqi(t, s3->len, 0, "1017 Verify len=0 when str='' ");
      // \req 1.15 cstr_new shall initialize str="" if str argument has len=0.
      ctest_eqs(t, s3->str, "", "1018 Verify str='' if str arg is ''");
      cstr_free(s3);
 
      cstr_t* s4 = cstr_new(32, NULL);
      // \req 1.16 cstr_new shall initialize max_size=max_size if str argment is NULL.
      ctest_eqi(t, s4->max_size, 32, "1019 Verify max_size=max_size when str=NULL");
      // \req 1.17 cstr_new shall initialize size=1 if str argment is NULL.
      ctest_eqi(t, s4->size, 1, "1020 Verify size=1 when str=NULL");
      // \req 1.18 cstr_new shall initialize len=0 if str argment is NULL.
      ctest_eqi(t, s4->len, 0, "1021 Verify len=0 when str=NULL");
      // \req 1.19 cstr_new shall initialize str to "" str argment is NULL.
      ctest_eqs(t, s4->str, "", "1022 Verify str='' when str=NULL");
      cstr_free(s4);

      cstr_t* s5 = cstr_new(4,"Four score and seven");
      // \req 1.20 cstr_new shall not let str grow beyond max_size.
      ctest_eqi(t, s5->max_size, 4, "Verify max_size=max_size when str is too long");
      // \req 1.21 cstr_new shall not let size be larger than max_size.
      ctest_eqi(t, s5->size, 4, "Verify size=max_size when str is too long");
      // \req 1.22 cstr_new shall not let len be as large as max_size.
      ctest_eqi(t, s5->len, 3, "Verify len=max_size-1 when str is too long");
      // \req 1.23 cstr_new shall chomp str to len=max_size-1 if it is too long.
      ctest_eqs(t, s5->str, "Fou", "Verify str is the first letters of arg str");  
      cstr_free(s5);
   }

   ctest_unit(t, "cstr_copy");
   {
      // \req 2.1 cstr_copy shall copy src to dest when src length is less than or equal to len.
      char s1[] = "Give three cheers and";
      char d1[30];
      for (int i = 0; i < 30; i++) d1[i] = 'x';
      cstr_copy(d1, s1, 29);
      ctest_eqs(t, d1, s1, "2000 Verify cstr_copy copies srt to dest");
      // \req 2.3 cstr_copy shall write '\0' to position len.
      ctest_eqi(t, (int)d1[29], (int)'\0', "2010 Verify '\\0' is written to last pos of string");

      // \req 2.2 cstr_copy shall copy len-1 char from src to des when src length is greater than len.
      char d2[20];
      for (int i = 0; i < 19; i++) d2[i] = 'y';
      d2[19] = '\0';
      cstr_copy(d2, s1, 10-1);
      ctest_eqs(t, d2, "Give thre", "2020 Verify len-1 char copied from src to dest when src is too long");
      ctest_eqs(t, &d2[10], "yyyyyyyyy", "2030 Verify char after len is unchanged");

      // \req 2.4 cstr_copy shall return err (1) when dest = NULL.
      char* d3 = NULL;
      int err1 = cstr_copy(d3, s1, 0);
      ctest_eqi(t, err1, 1, "2031 Verify cstr_copy returns err (1) when dest=NULL");

      // \req 2.5 cstr_copy shall return no-error (0) when dest != NULL.
      char d4[2] = "x";
      char s4[] = "B";
      int err2 = cstr_copy(d4, s4, 1);
      ctest_eqi(t, err2, 0, "2032 Verify cstr_copy returns no-err (0) when src=NULL");
      ctest_eqs(t, d4, "B", "2033 Verify cstr_copy creates empty string when src=NULL");

      // \req 2.6 cstr_copy shall not modify dest when len=0
      char d5[2] = "z";
      char s5[2] = "a";
      cstr_copy(d5, s5, 0);
      ctest_eqs(t, d5, "", "2034 Verify cstr_copy forces dest[0]='\\0' when len=0");

      // \req 2.7 cstr_copy shall write '\0' to dest[0] when src=NULL.
      char d6[] = "D6";
      char* s6 = NULL;
      cstr_copy(d6, s6, 3);
      ctest_eqs(t, d6, "", "2035 Verify dest=\"\" when src=NULL");
   }

   ctest_unit(t, "cstr_resize");
   {
      const char* a1 = "One fish, two fish";
      const uint32_t len1 = strlen(a1);
      const uint32_t size1 = len1 + 1;
      cstr_t* s1 = cstr_new(0, a1);
      ctest_eqs(t, s1->str, a1,"3000 Verify cstr_new str");
      ctest_eqi(t, s1->len, len1, "3001 Verify cstr_new len");
      ctest_eqi(t, s1->size, size1, "3002 Verify cstr_new size");
      ctest_eqi(t, s1->max_size, 0, "3003 Verify cstr_new max_size");

      // \req 3.1 cstr_resize shall return err (1) on malloc failure.
      int err1 = cstr_resize(s1, UINT32_MAX);
      ctest_eqi(t, err1, 1, "3010 Verify cstr_resize return err (1) on malloc error");
      ctest_eqs(t, s1->str, a1,"3011 Verify cstr_resize with err str");
      ctest_eqi(t, s1->len, len1, "3012 Verify cstr_resize with err len");
      ctest_eqi(t, s1->size, size1, "3013 Verify cstr_resize with err size");
      ctest_eqi(t, s1->max_size, 0, "3014 Verify cstr_resize with err max_size");

      // \req 3.2 cstr_resize shall retain str value if str length is less than new_size.
      char* ptr2 = s1->str;
      int err2 = cstr_resize(s1, 30);
      ctest_eqi(t, err2, 0, "3020 Verify cstr_resize return no-err (0) on malloc success");
      ctest_eqs(t, s1->str, a1,"3021 Verify cstr_resize without err str");
      ctest_eqi(t, s1->len, len1, "3022 Verify cstr_resize without err len");
      ctest_eqi(t, s1->size, 30, "3023 Verify cstr_resize without err size");
      ctest_eqi(t, s1->max_size, 0, "3024 Verify cstr_resize without err max_size");
      const int ptr2_changed = ptr2 != s1->str;
      ctest_eqi(t, ptr2_changed, 1, "3034 Verify str pointer changed after cstr_resize increases size");

      // \req 3.3 cstr_resize shall allow size to get smaller.
      // \req 3.4 cstr_resize shall truncate str if string is longer than new_size.
      char* ptr3 = s1->str;
      int err3 = cstr_resize(s1, 5);
      ctest_eqi(t, err3, 0, "3030 Verify err code returned from cstr_resize shrinks size");
      ctest_eqs(t, s1->str, "One ", "3031 Verify str after cstr_resize shrinks size");
      ctest_eqi(t, s1->len, 4, "3032 Verify len after cstr_resize shrinks size");
      ctest_eqi(t, s1->size, 5, "3033 Verify size after cstr_resize shrinks size");
      ctest_eqi(t, s1->max_size, 0, "3034 Verify max_size after cstr_resize shrinks size");
      const int ptr3_changed = ptr3 != s1->str;
      ctest_eqi(t, ptr3_changed, 1, "3034 Verify str pointer changed after cstr_resize shrinks size");

      // \req 3.5 cstr_resize shall keep str unchanged if new_size = original size.
      char* ptr4 = s1->str;
      int err4 = cstr_resize(s1, 5);
      ctest_eqi(t, err4, 0, "3040 Verify err code returned from cstr_resize same size");
      ctest_eqs(t, s1->str, "One ", "3041 Verify str after cstr_resize same size");
      ctest_eqi(t, s1->len, 4, "3042 Verify len after cstr_resize same size");
      ctest_eqi(t, s1->size, 5, "3043 Verify size after cstr_resize same size");
      ctest_eqi(t, s1->max_size, 0, "3044 Verify max_size after cstr_resize same size");
      const int ptr4_changed = ptr4 != s1->str;
      ctest_eqi(t, ptr4_changed, 0, "3034 Verify str pointer didn't change after cstr_resize same size");
      cstr_free(s1);
   }

   ctest_unit(t, "cstr_append");
   {
      // \req cstr_append shall return err (1) if orig is NULL, else return no-err (0).
      const int err0 = cstr_append(NULL, "Hello");
      ctest_eqi(t, err0, 1, "4010 Verify cstr_append returns err (1) when orig is NULL");
      // \req cstr_append shall not modify orig if str is NULL.
      cstr_t* s1 = cstr_new(0, "Mares eat oats");
      const int err1 = cstr_append(s1, NULL);
      ctest_eqi(t, err1, 0, "4011 Verify cstr_append returns no error when str is NULL");
      ctest_eqs(t, s1->str, "Mares eat oats", "4012 Verify str is unchanged when str is NULL");
      cstr_free(s1);
 
      // \req cstr_append shall not modify orig if str is "".
      cstr_t* s2 = cstr_new(0, "and goats eat oats");
      const int err2 = cstr_append(s2, "");
      ctest_eqi(t, err2, 0, "4013 Verify cstr_append returns no error when str is ''");
      ctest_eqs(t, s2->str, "and goats eat oats", "4014 Verify str is unchanged when str is ''");
      cstr_free(s2);

      // \req cstr_append shall malloc a 1-char vector if orig->str is NULL.
      cstr_t* s3 = cstr_new(0,"dummy");
      free(s3->str);
      s3->str = NULL;
      const int err3 = cstr_append(s3, NULL);
      const int is_null3 = isNULL(s3->str);
      ctest_eqi(t, err3, 0, "4015 Verify cstr_append returns no error when str is ''");
      ctest_eqi(t, is_null3, 0, "4016 Verify cstr_append mallocs vector if str=NULL");
      ctest_eqs(t, s3->str, "", "4017 Verify cstr_append inits vector to ''");
      cstr_free(s3);

      // \req cstr_append shall return err (1) if orig->str malloc fails.
      // not tested

      // \req cstr_append shall return err (1) if resize malloc error.
      // not tested
   }

   // \req cstr_append shall append str to the orig string.
   // \req cstr_append shall keeps size the same if new length is not lt size.
   ctest_unit(t, "cstr_append - append smaller string to larger string");
   {
      cstr_t* s = cstr_new(0, "The very quick");
      cstr_append(s, "brown fox");
      const char* str1 = "The very quick";
      const int len1   = strlen(str1);
      const int size1  = len1 + 1;
      const char* expect_str = "The very quickbrown fox";
      const int expect_len = strlen(expect_str);
      const int expect_size = 2 * size1;
      ctest_eqs(t, s->str, expect_str, "1020 Verify cstr_append worked");
      ctest_eqi(t, s->len, expect_len, "1021 Verify len after cstr_append");
      ctest_eqi(t, s->size, expect_size, "1022 Verify size doubled");
      s = cstr_free(s);
   }

   // \req cstr_append shall grow size if new length is ge size.
   ctest_unit(t, "cstr_append - append larger string to smaller string");
   {
      cstr_t* s = cstr_new(0, "The quick");
      cstr_append(s, "brown wolverine");
      const char* expect_str = "The quickbrown wolverine";
      const int expect_len = strlen(expect_str);
      const int expect_size = expect_len + 1;
      ctest_eqs(t, s->str, expect_str, "1030 Verify cstr_append worked");
      ctest_eqi(t, s->len, expect_len, "1031 Verify len after cstr_append");
      ctest_eqi(t, s->size, expect_size, "1032 Verify size more than doubled");
      s = cstr_free(s);
   }

   ctest_unit(t, "cstr_get_filesize");
   {
      // \req cstr_get_filesize shall return 0 if fopen fails
      uint32_t const filesize1 = cstr_get_filesize("bogusfilename.txt");
      ctest_eqi(t, filesize1, 0, "6000 Verify filesize=0 when fopen fails");

      // \req cstr_get_filesize shall return 0 if ftell fails
      // no test

      // \req cstr_get_filesize shall return filesize of the specified file
      uint32_t const filesize2 = cstr_get_filesize("files/testfile.txt");
      ctest_eqi(t, filesize2, 4, "6001 Verify filesize");
   }

   ctest_unit(t, "cstr_read");
   {
      // \req cstr_read shall return NULL if the filesize is 0.
      cstr_t* const s1 = cstr_read("non_existent_file.txt");
      bool const is_null1 = isNULL(s1);
      ctest_eqi(t, is_null1, 1, "7000 Verify invalid file returns NULL");
      cstr_free(s1);

      // \req cstr_read shall return NULL if fopen/fread fails.
      // no test

      // \req cstr_read shall return NULL if malloc fails. 
      // no test

      cstr_t* const s2 = cstr_read("files/testfile.txt");
      // \req cstr_read shall malloc 4KBytes more than filesize, (cstr->size).
      ctest_eqi(t, s2->size, 4100, "7001 Verify size is 4k+filesize");

      // \req cstr_read shall set cstr->len to filesize - 1.
      ctest_eqi(t, s2->len, 3, "7002 Verify len is filesize - 1");
     
      // \req cstr_read shall set cstr->max_size=0 (for unlimited size growth)
      ctest_eqi(t, s2->max_size, 0, "7003 Verify max_size is 0");

      // \req cstr_read shall set cstr->str to the contents of the file.
      ctest_eqs(t, s2->str, "the\n", "7004 Verify str contains the file contents");
      cstr_free(s2);
   }

   ctest_unit(t, "cstr iterators cstr_firsti, cstr_validi, cstr_nexti)");
   {
      char* expect = "The quick brown fox";
      cstr_t* s1 = cstr_new(0, expect);
      int i = 0;
      for (cstr_firsti(s1); cstr_validi(s1); cstr_nexti(s1)) {
         char const ch = cstr_geti(s1);
         ctest_eqi(t, ch, expect[i++], "8000 Verify iterator");
      }
   }

   ctest_unit(t, "cstr_count");
   {
      char* expect = "the quick brown fox\n";
      cstr_t* s1 = cstr_new(0, expect);
      uint32_t count = cstr_count(s1, " \n");
      ctest_eqi(t, count, 4, "8100 Verify cstr_count");
   }

   ctest_total_result(t);

   return 0;
}
