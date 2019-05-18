/// @file 
/// @brief Header file for ctest.h
///
/// @main

#ifndef CTEST_H
#define CTEST_H
#include <stdint.h>

#define CTEST_NAME_LEN 64

#define CTEST_PRINT_NONE  0
#define CTEST_PRINT_TOTAL 1
#define CTEST_PRINT_UNIT  2
#define CTEST_PRINT_FAIL  3
#define CTEST_PRINT_ALL   4

typedef struct ctest_struct {
   uint32_t test_pass_count;
   uint32_t test_fail_count;
   uint32_t total_pass_count;
   uint32_t total_fail_count;
   uint32_t mode;
   char     test_name[CTEST_NAME_LEN];
} ctest_type;

ctest_type* ctest_new(int argc, char* argv[]);
void ctest_mode(ctest_type* test, uint32_t mode);
int  ctest_unit(ctest_type* test, const char* name);
void ctest_eqi(ctest_type* test, const int actual, const int expect, const char* description);
void ctest_eqs(ctest_type* test, const char* actual, const char* expect, const char* description);
void ctestfl_eqi(ctest_type* test, const int actual, const int expect, const char* description, char const* const file, int const ln);
void ctestfl_eqs(ctest_type* test, const char* actual, const char* expect, const char* description, char const* const file, int const ln);
void ctest_test_result(ctest_type* test);
void ctest_total_result(ctest_type* test);
void ctest_free(ctest_type* test);

#define CTEST_UNIT(N) if (ctest_unit(t, N))
#define CTEST_INIT(ARGC,ARGV) ctest_type* t = ctest_new(argc, argv);
#define CTEST_MODE(S) ctest_mode(t, S);
#define CTEST_DONE() ctest_total_result(t);
#define EQ(A,E,M) ctestfl_eqi(t, A, E, M, __FILE__, __LINE__);
#define EQS(A,E,M) ctestfl_eqs(t, A, E, M, __FILE__, __LINE__);

#endif
