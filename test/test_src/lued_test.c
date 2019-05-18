/// \file 
/// \brief This file provides unit tests for carr.
///

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cis.h"
#include "ctest.h"
#include "carr.h"
#include "lued.h"

/// \brief Test program for carr.
/// \return Failure code
/// \todo Implement failure code.
      
int lued_test(const int argc, char* argv[])
{
   CTEST_INIT(argc, argv)
   CTEST_MODE(CTEST_PRINT_TOTAL)

   CTEST_UNIT("str_new")
   {
      carr_t* s1 = cstra_new(10,"the quick");
      // \req 1.1 cstra_new shall initialize max_size to the max_size argument.
      EQ(s1->max_size, 10, "1000 Vereify s1->max_size == 10 after str_new")
      // \req 1.2 cstra_new shall initialize size to the length+1 of the str argument.
      EQ(s1->size, 10, "1001 Verify s1->size == 10 after str_new")
      // \req 1.3 cstra_new shall initialize len the length of the str argument.
      EQ(s1->len, 9,   "1002 Verify s1->len == 9 after str_new")
      // \req 1.4 cstra_new shall initialize the next pointer to NULL.
      EQ((int)(s1->next), (int)NULL, "1003 Verify s1->next == NULL after str_new")
      // \req 1.5 cstra_new shall intialize str to the argument string.
      EQS(s1->arr, "the quick", "1004 Verify s1->arr == 'the quick' after str_new")      

      s1 = carr_free(s1);
      // \req 1.6 carr_free shall return NULL.
      EQ((int)s1, (int)NULL, "Verify s1 is NULL after str_free")

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
      EQ((int)(s2->next), (int)NULL, "1013 Verify s2->next == NULL after str_new")
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
   }

   CTEST_UNIT("carr_copy")
   {
      // \req 2.1 carr_copy shall copy src to dest when src length is less than or equal to len.
      char s1[] = "Give three cheers and";
      char d1[30];
      for (int i = 0; i < 30; i++) d1[i] = 'x';
      carr_copy(d1, s1, 29, 1);
      EQS(d1, s1, "2000 Verify carr_copy copies srt to dest")
      // \req 2.3 carr_copy shall write '\0' to position len.
      EQ((int)d1[29], (int)'\0', "2010 Verify '\\0' is written to last pos of string")

      // \req 2.2 carr_copy shall copy len-1 char from src to des when src length is greater than len.
      char d2[20];
      for (int i = 0; i < 19; i++) d2[i] = 'y';
      d2[19] = '\0';
      carr_copy(d2, s1, 10-1, 1);
      EQS(d2, "Give thre", "2020 Verify len-1 char copied from src to dest when src is too long")
      EQS(&d2[10], "yyyyyyyyy", "2030 Verify char after len is unchanged")

      // \req 2.4 carr_copy shall return err (1) when dest = NULL.
      char* d3 = NULL;
      int err1 = carr_copy(d3, s1, 0, 1);
      EQ(err1, 1, "2031 Verify carr_copy returns err (1) when dest=NULL")

      // \req 2.5 carr_copy shall return no-error (0) when dest != NULL.
      char d4[2] = "x";
      char s4[] = "B";
      int err2 = carr_copy(d4, s4, 1, 1);
      EQ(err2, 0, "2032 Verify carr_copy returns no-err (0) when src=NULL")
      EQS(d4, "B", "2033 Verify carr_copy creates empty string when src=NULL")

      // \req 2.6 carr_copy shall not modify dest when len=0
      char d5[2] = "z";
      char s5[2] = "a";
      carr_copy(d5, s5, 0, 1);
      EQS(d5, "", "2034 Verify carr_copy forces dest[0]='\\0' when len=0")

      // \req 2.7 carr_copy shall write '\0' to dest[0] when src=NULL.
      char d6[] = "D6";
      char* s6 = NULL;
      carr_copy(d6, s6, 3, 1);
      EQS(d6, "", "2035 Verify dest=\"\" when src=NULL")
   }


   CTEST_UNIT("carr_resize")
   {
      const char* a1 = "One fish, two fish";
      const uint32_t len1 = strlen(a1);
      const uint32_t size1 = len1 + 1;
      carr_t* s1 = cstra_new(0, a1);
      EQS(s1->arr, a1,"3000 Verify cstra_new str")
      EQ(s1->len, len1, "3001 Verify cstra_new len")
      EQ(s1->size, size1, "3002 Verify cstra_new size")
      EQ(s1->max_size, 0, "3003 Verify cstra_new max_size")

      // \req 3.1 carr_resize shall return err (1) on malloc failure.
      int err1 = carr_resize(s1, UINT32_MAX);
      EQ(err1, 1, "3010 Verify carr_resize return err (1) on malloc error")
      EQS(s1->arr, a1,"3011 Verify carr_resize with err str")
      EQ(s1->len, len1, "3012 Verify carr_resize with err len")
      EQ(s1->size, size1, "3013 Verify carr_resize with err size")
      EQ(s1->max_size, 0, "3014 Verify carr_resize with err max_size")

      // \req 3.2 carr_resize shall retain str value if str length is less than new_size.
      char* ptr2 = s1->arr;
      int err2 = carr_resize(s1, 30);
      EQ(err2, 0, "3020 Verify carr_resize return no-err (0) on malloc success")
      EQS(s1->arr, a1,"3021 Verify carr_resize without err str")
      EQ(s1->len, len1, "3022 Verify carr_resize without err len")
      EQ(s1->size, 30, "3023 Verify carr_resize without err size")
      EQ(s1->max_size, 0, "3024 Verify carr_resize without err max_size")
      const int ptr2_changed = ptr2 != s1->arr;
      EQ(ptr2_changed, 1, "3034 Verify str pointer changed after carr_resize increases size")

      // \req 3.3 carr_resize shall allow size to get smaller.
      // \req 3.4 carr_resize shall truncate str if string is longer than new_size.
      char* ptr3 = s1->arr;
      int err3 = carr_resize(s1, 5);
      EQ(err3, 0, "3030 Verify err code returned from carr_resize shrinks size")
      EQS(s1->arr, "One ", "3031 Verify str after carr_resize shrinks size")
      EQ(s1->len, 4, "3032 Verify len after carr_resize shrinks size")
      EQ(s1->size, 5, "3033 Verify size after carr_resize shrinks size")
      EQ(s1->max_size, 0, "3034 Verify max_size after carr_resize shrinks size")
      const int ptr3_changed = ptr3 != s1->arr;
      EQ(ptr3_changed, 1, "3034 Verify str pointer changed after carr_resize shrinks size")

      // \req 3.5 carr_resize shall keep str unchanged if new_size = original size.
      char* ptr4 = s1->arr;
      int err4 = carr_resize(s1, 5);
      EQ(err4, 0, "3040 Verify err code returned from carr_resize same size")
      EQS(s1->arr, "One ", "3041 Verify str after carr_resize same size")
      EQ(s1->len, 4, "3042 Verify len after carr_resize same size")
      EQ(s1->size, 5, "3043 Verify size after carr_resize same size")
      EQ(s1->max_size, 0, "3044 Verify max_size after carr_resize same size")
      const int ptr4_changed = ptr4 != s1->arr;
      EQ(ptr4_changed, 0, "3034 Verify str pointer didn't change after carr_resize same size")
      carr_free(s1);
   }

   CTEST_UNIT("carr_import")
   {
      // \req carr_import shall return err (1) if orig is NULL, else return no-err (0).
      const int err0 = carr_import(NULL, "Hello", 0);
      EQ(err0, 1, "4010 Verify carr_import returns err (1) when orig is NULL")
      // \req carr_import shall not modify orig if str is NULL.
      carr_t* s1 = cstra_new(0, "Mares eat oats");
      const int err1 = carr_import(s1, NULL, 0);
      EQ(err1, 0, "4011 Verify carr_import returns no error when str is NULL")
      EQS(s1->arr, "Mares eat oats", "4012 Verify str is unchanged when str is NULL")
      carr_free(s1);
 
      // \req carr_import shall not modify orig if str is "".
      carr_t* s2 = cstra_new(0, "and goats eat oats");
      const int err2 = carr_import(s2, "", 0);
      EQ(err2, 0, "4013 Verify carr_import returns no error when str is ''")
      EQS(s2->arr, "and goats eat oats", "4014 Verify str is unchanged when str is ''")
      carr_free(s2);

      // \req carr_import shall malloc a 1-char vector if orig->arr is NULL.
      carr_t* s3 = cstra_new(0,"dummy");
      free(s3->arr);
      s3->arr = NULL;
      const int err3 = carr_import(s3, NULL, 0);
      const int is_null3 = isNULL(s3->arr);
      EQ(err3, 0, "4015 Verify carr_import returns no error when str is ''")
      EQ(is_null3, 0, "4016 Verify carr_import mallocs vector if str=NULL")
      EQS(s3->arr, "", "4017 Verify carr_import inits vector to ''")
      carr_free(s3);

      // \req carr_import shall return err (1) if orig->arr malloc fails.
      // not tested

      // \req carr_import shall return err (1) if resize malloc error.
      // not tested
   }

   // \req carr_import shall append str to the orig string.
   // \req carr_import shall keeps size the same if new length is not lt size.
   CTEST_UNIT("carr_import - append smaller string to larger string")
   {
      carr_t* s = cstra_new(0, "The very quick");
      carr_import(s, "brown fox", 0);
      const char* str1 = "The very quick";
      const int len1   = strlen(str1);
      const int size1  = len1 + 1;
      const char* expect_str = "The very quickbrown fox";
      const int expect_len = strlen(expect_str);
      const int expect_size = 2 * size1;
      EQS(s->arr, expect_str, "1020 Verify carr_import worked")
      EQ(s->len, expect_len, "1021 Verify len after carr_import")
      EQ(s->size, expect_size, "1022 Verify size doubled")
      s = carr_free(s);
   }

   // \req carr_import shall grow size if new length is ge size.
   CTEST_UNIT("carr_import - append larger string to smaller string")
   {
      carr_t* s = cstra_new(0, "The quick");
      carr_import(s, "brown wolverine", 0);
      const char* expect_str = "The quickbrown wolverine";
      const int expect_len = strlen(expect_str);
      const int expect_size = expect_len + 1;
      EQS(s->arr, expect_str, "1030 Verify carr_import worked")
      EQ(s->len, expect_len, "1031 Verify len after carr_import")
      EQ(s->size, expect_size, "1032 Verify size more than doubled")
      s = carr_free(s);
   }


   CTEST_UNIT("cstr iterators carr_firsti, carr_validi, carr_nexti)")
   {
      char* expect = "The quick brown fox";
      carr_t* s1 = cstra_new(0, expect);
      int i = 0;
      for (carr_firsti(s1); carr_validi(s1); carr_nexti(s1)) {
         char ch;
         carr_geti(s1, &ch);
         EQ(ch, expect[i++], "8000 Verify iterator")
      }
   }

   CTEST_UNIT("carr_count")
   {
      char* expect = "the quick brown fox\n";
      carr_t* s1 = cstra_new(0, expect);
      uint32_t count = carr_count(s1, " \n");
      EQ(count, 4, "8100 Verify carr_count")
   }

   CTEST_UNIT("carr_filesize")
   {
      // \req carr_filesize shall return 0 if fopen fails
      uint32_t const filesize1 = carr_filesize("bogusfilename.txt");
      EQ(filesize1, 0, "6000 Verify filesize=0 when fopen fails")

      // \req carr_filesize shall return 0 if ftell fails
      // no test

      // \req carr_filesize shall return filesize of the specified file
      uint32_t const filesize2 = carr_filesize("files/testfile.txt");
      EQ(filesize2, 4, "6001 Verify filesize")
   }

   CTEST_UNIT("carr_read")
   {
      // \req carr_read shall return NULL if the filesize is 0.
      carr_t* const s1 = carr_read("non_existent_file.txt");
      bool const is_null1 = isNULL(s1);
      EQ(is_null1, 1, "7000 Verify invalid file returns NULL")
      carr_free(s1);

      // \req carr_read shall return NULL if fopen/fread fails.
      // no test

      // \req carr_read shall return NULL if malloc fails. 
      // no test

      carr_t* const s2 = carr_read("files/testfile.txt");
      // \req carr_read shall malloc 4KBytes more than filesize, (cstr->size).
      EQ(s2->size, 4100, "7001 Verify size is 4k+filesize")

      // \req carr_read shall set cstr->len to filesize - 1.
      EQ(s2->len, 3, "7002 Verify len is filesize - 1")

      // \req carr_read shall set cstr->max_size=0 (for unlimited size growth)
      EQ(s2->max_size, 0, "7003 Verify max_size is 0")

      // \req carr_read shall set cstr->str to the contents of the file.
      EQS(s2->arr, "the\n", "7004 Verify str contains the file contents")
      carr_free(s2);
   }

   CTEST_UNIT("carr_findi")
   {
      char* filename = "files/testfile2.txt";

      uint32_t filesize = carr_filesize(filename);
      EQ(filesize, 46, "8000 Verify carr_filesize works correctly")

      carr_t* const s1 = carr_read(filename);
      // \req carr_read shall malloc 4KBytes more than filesize, (cstr->size).
      EQ(s1->size, 4096 + filesize, "8001 Verify size is 4k+filesize")
     
      uint32_t const len1 = carr_len(s1);
      EQ(len1 , filesize - 1, "8002 Verify carr_len returns length-1 if last char is null") 

      carr_t* delims = carrs_init("e");
      carr_firsti(s1);
      carr_findi(s1, delims);
      EQ(carr_i(s1), 2, "Verify carr_findi found delimiter")
      
   }

   CTEST_UNIT("carr_split")
   {
      char* filename = "files/testfile2.txt";

      uint32_t filesize = carr_filesize(filename);
      EQ(filesize, 46, "8000 Verify carr_filesize works correctly")

      carr_t* const s1 = carr_read(filename);
      // \req carr_read shall malloc 4KBytes more than filesize, (cstr->size).
      EQ(s1->size, 4096 + filesize, "8001 Verify size is 4k+filesize")
     
      uint32_t const len1 = carr_len(s1);
      EQ(len1 , filesize-1, "8002 Verify carr_len returns length-1 if last char is null") 

      uint32_t line_count = carr_count(s1, "\n");
      EQ(line_count, 4, "Verify carr_count counts number of lines")

      int match = 0;
      carr_t* delims = carrs_init("\n");
      carr_firsti(s1);
      match = carr_findi(s1, delims);
      EQ(match, 1, "Verify carr_findi return 1 on match");
      EQ(carr_validi(s1), 1, "Verify carr_validi returns true after carr_findi match")
      EQ(carr_i(s1), 9, "Verify carr_i returns index of carr_fini match") 

      carr_nexti(s1);
      match = carr_findi(s1, delims);
      EQ(match, 1, "Verify carr_findi return 1 on match");
      EQ(carr_validi(s1), 1, "Verify carr_validi returns true after carr_findi match")
      EQ(carr_i(s1), 19, "Verify carr_i returns index of carr_fini match") 

      carr_nexti(s1);
      match = carr_findi(s1, delims);
      EQ(match, 1, "Verify carr_findi return 1 on match");
      EQ(carr_validi(s1), 1, "Verify carr_validi returns true after carr_findi match")
      EQ(carr_i(s1), 31, "Verify carr_i returns index of carr_fini match") 

      carr_nexti(s1);
      match = carr_findi(s1, delims);
      EQ(match, 1, "Verify carr_findi return 1 on match");
      EQ(carr_validi(s1), 1, "Verify carr_validi returns true after carr_findi match")
      EQ(carr_i(s1), 40, "Verify carr_i returns index of carr_fini match") 

      carr_nexti(s1);
      match = carr_findi(s1, delims);
      EQ(match, 0, "Verify carr_findi return 0 on no match");
      EQ(carr_validi(s1), 0, "Verify carr_validi returns falseafter carr_findi match")
      EQ(carr_i(s1), 45, "Verify carr_i returns index of carr_fini match") 

      carr_nexti(s1);
      match = carr_findi(s1, delims);
      EQ(match, 0, "Verify carr_findi return 0 on no match");
      EQ(carr_validi(s1), 0, "Verify carr_validi returns falseafter carr_findi match")
      EQ(carr_i(s1), 45, "Verify carr_i returns index of carr_fini match") 

      char* expect_lines[] = {
         "the quick",
         "brown fox",
         "jumped over",
         "the lazy",
         "dog.",
         "SHOULD NOT GET HEre1",
         "SHOULD NOT GET HEre2",
         "SHOULD NOT GET HEre3",
         "SHOULD NOT GET HEre4",
         "SHOULD NOT GET HEre5",
         "SHOULD NOT GET HEre6"
      };

      carr_t* lines = carrp_new();
      carr_split(lines, s1, delims);

      uint32_t num_pieces = carr_len(lines); 
      EQ( num_pieces, line_count + 1, "Verify carr_split carr_len")

      int i = 0;
      for_carr(lines) {
         char* line = (char*)carr_getsi(lines);
         printf("IN FOR lines=%p line = %p lines->len=%d '%s'\n", lines, line, lines->len,line);
         EQS( line , expect_lines[i++], "Verify car_getsi");
      }

      {
         char* fname = "files/bigfile.txt";
         carr_t* const s3 = carr_read(fname);
         if isNULL(s3) {
            printf("Error opening file '%s'\n\n",filename);
            return 0;
         }

#if 0
         carr_t* line_array = carrp_new();
         carr_t* eol = carrs_init("\n");
         carr_split(line_array, s3, eol); 
         uint32_t num_lines = carr_len(line_array);
         for_carr (line_array) {
            // uint32_t linelen = cline->len;
            // carr_t** line_array_arr = (carr_t**)line_array->arr;
            // carr_t* line_array_it = (carr_t*)line_array_arr[line_array->it];
            // char* line_array_str = (char*)line_array_it->arr;
            // printf("line_array_str = '%s'\n",line_array_str);
            carr_t* cline;
            carr_geti(line_array, &cline);
            printf("%i: %s\n", carr_i(line_array), (char*)cline->arr);
         }
         printf("num_lines = %i\n", num_lines);     
#endif

      }    
   }

   CTEST_MODE(CTEST_PRINT_ALL)

   CTEST_UNIT("carr_make_space")
   {
      carr_t* cstr = carrs_init("abcdefghij");
      EQ( carr_len(cstr), 10, "Verify len if vector")
      carr_make_space(cstr, 3, 2);
      EQ( carr_len(cstr), 13, "Verify len if vector")
      EQS( (char*)cstr->arr, "abcdecdefghij", "Verify carr_make_space made the space")
      carr_make_space(cstr, 1, 0);
      EQ( carr_len(cstr), 14, "Verify len if vector")
      EQS( (char*)cstr->arr, "aabcdecdefghij", "Verify carr_make_space made the space")
   }

   CTEST_UNIT("carr_overwrite")
   {
      // void carr_overwrite(carr_t* ca, char* arr, uint32_t len, uint32_t const at);

      carr_t* cstr = carrs_init("abcdefghij");
      EQ( carr_len(cstr), 10, "Verify len if vector")
      carr_overwrite(cstr, "ABC", 0, 0); 
      EQS( (char*)cstr->arr, "ABCdefghij", "Verify carr_overwrite over wrote")
      carr_overwrite(cstr, "XYZ", 0, 10);
      EQS( (char*)cstr->arr, "ABCdefghijXYZ", "Verify carr_overwrite increased len if needed")
      EQ( carr_len(cstr), 13, "Verify length increased");
   }

   CTEST_UNIT("carr_insert")
   {
      carr_t* cstr = carrs_init("abcdef");
      EQ( carr_len(cstr), 6, "Verrify len after carrs_init")
      carr_insert(cstr, "123", 0, 3);
      EQS( (char*)cstr->arr, "abc123def", "Verify carr_insert")
      carr_insert(cstr, "ABC", 2, 3);
      EQS( (char*)cstr->arr, "abcAB123def", "Verify carr_insert")
      carr_insert(cstr, "9876", 0, 0);
      EQS( (char*)cstr->arr, "9876abcAB123def", "Verify carr_insert")

      char* expect_lines[] = {
         "the quick",
         "brown fox",
         "jumped over",
         "the lazy",
         "dog."
      };
      char* st0 = expect_lines[0];
      char* st1 = expect_lines[1];
      char* st2 = expect_lines[2];
      char* st3 = expect_lines[3];
      char* st4 = expect_lines[4];
      printf("dddd\n%s\n%s\n%s\n%s\n%s\neeee\n",st0,st1,st2,st3,st4);

      char* filename = "files/testfile2.txt";
      carr_t* lines = carr_read_lines(filename);
      EQ(carr_len(lines), 5, "Verify number of lines in file after carr_read_lines")
      uint32_t count = 0;
      for_carr (lines) {
         EQ(carr_i(lines), count, "Verify iterator")
         char* line;
         carr_getarri(lines, (void**)&line);
         EQS(line, expect_lines[count], "Verify line");
         count++;
      }
      EQ(count, 5, "Verify number of lines actually in lines");

      carr_make_space(lines, 5, 0);
      carr_make_space(lines, 5, 0);
      carr_make_space(lines, 5, 0);
      carr_make_space(lines, 5, 0);

      // carr_t* ca = (carr_t*)lines->arr;
      // carr_t* ca0 = (carr_t*)ca->arr;
      // char*   ss0 = (char*)(ca0->arr);

      // carr_overwrite(lines, (void*)expect_lines, 5, 2);
      char* insert_lines[] = {
         "Rachel Armington",
         "Jacob Brown",
         "Walter Brown",
         "Tickles",
         "MOE!!!!"
      };
      carr_insert2(lines, (void*)insert_lines, 5, 2);

      EQ(carr_len(lines), 30, "Verify number of lines after carr_make_space")
      count = 0;
      for_carr (lines) {
         // EQ(carr_i(lines), count, "Verify iterator")
         char* line;
         carr_getarri(lines, (void**)&line);
         printf("xxx %i: %s\n", carr_i(lines), line );
         fflush(stdin);
         count++;
      }

   }

#if 1 
   CTEST_UNIT("lued_main")
   {
      lued_main(argc,argv);
   }
#endif

   CTEST_UNIT("lued_open")
   {
      char* filename = "files/testfile2.txt";
      lued_t* l = lued_open(NULL,filename);
      int open_successful = isNULL(l) ? 0 : 1;
      EQ(open_successful, 1, "Verify lued_open opened the file")
      uint32_t len = get_numchar(l);
      EQ(len, 45, "Verify get_numchar")

      uint32_t line_count;
      get_numlines(l, &line_count);
      EQ(line_count, 5, "Verify get_numline")

      luedc_overwrite(l, 2, 3, "Hello Rei-Rei###");
      luedc_insert(l, 3, 4, "*** Tickles ***");

      char screen[8096];
      luedc_get_page(l, 1, 3, screen, 8096);
      printf("+++++\nafter luedc_get_page\n%s+++++\n", screen);

      uint32_t r = 0;
      uint32_t c = 0;
      int f = 0;

      find_string(l, r, c, "zx", &r, &c, &f);
      EQ(f, 0, "Verify 'zx' not found in file")

      find_string(l, r, c, "e", &r, &c, &f);
      EQ(f, 1, "Verify 'e' found in file")
      EQ(r, 0, "Verify 'e' found on row 0")
      EQ(c, 2, "Verify 'e' found on column 2");

      find_string(l, r, c, "e", &r, &c, &f);
      EQ(f, 1, "Verify 'e' found in file")
      EQ(r, 0, "Verify 'e' found on row 0 again because c not advanced")
      EQ(c, 2, "Verify 'e' found on column 2 again because c not advanced");

      find_string(l, r, c+1, "e", &r, &c, &f);
      EQ(f, 1, "Verify 'e' found 2nd time in file")
      EQ(r, 2, "Verify 'e' found on row 2")
      EQ(c, 4, "Verify 'e' found on column 4");

      find_string(l, r, c+1, "T", &r, &c, &f);
      EQ(f, 1, "Verify 'T' found in file")
      EQ(r, 3, "Verify 'T' found on row 3")
      EQ(c, 8, "Verify 'T' found on column 8");

      find_string(l, r, c+1, "T", &r, &c, &f);
      EQ(f, 0, "Verify 'T' not found 2nd time in file")
      EQ(r, 3, "Verify r is unchanged on not found")
      EQ(c, 8, "Verify c is unchanged on not found");

      r = c = f = 0;
      find_string(l, r, c, "Rei", &r, &c, &f);
      EQ(f, 1, "Verify 'Rei' found in file")
      EQ(r, 2, "Verify 'Rei' found on row 3")
      EQ(c, 9, "Verify 'Rei' found on column 8");

      find_string(l, r, c+1, "Rei", &r, &c, &f);
      EQ(f, 1, "Verify 'Rei' found in file")
      EQ(r, 2, "Verify 'Rei' found on row 3")
      EQ(c, 13, "Verify 'Rei' found on column 8");

      find_string(l, r, c+1, "Rei", &r, &c, &f);
      EQ(f, 0, "Verify 'Rei' not found 3rd time in file")
      EQ(r, 2, "Verify r is unchanged on not found")
      EQ(c, 13, "Verify c is unchanged on not found");

      strcpy(l->filename, "files/testfile2.txt.save");
      save_session(l);
           

   }

   CTEST_DONE()
   return 0;
}

