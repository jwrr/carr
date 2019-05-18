 
/// \file 
/// \brief This file provides support for dynamic strings in C.
///
/// \main Main stuff

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "ctest.h"
#include "cis.h"


/// \brief Create a new test.
/// This is typically one time near the start of the test program.
/// \return returns a pointer to the new test data structure.

ctest_type* ctest_new(int argc, char* argv[]) 
{
   ctest_type* test = malloc(sizeof(ctest_type));
   if isNULL(test) return NULL;

   test->test_pass_count = 0;
   test->test_fail_count = 0;
   test->total_pass_count = 0;
   test->total_fail_count = 0;
   test->mode = CTEST_PRINT_ALL;
   test->test_name[0] = '\0';

   return test;
}

/// \brief Set verbosity mode for print statements
/// \param test The test data structure.
/// \param mode CTEST_PRINT_NONE, CTEST_PRINT_TOTAL, CTEST_PRINT_UNIT, CTEST_PRINT_FAIL, CTEST_PRINT_ALL
void ctest_mode(ctest_type* test, uint32_t mode)
{
   if isNULL(test) return;
   test->mode = (mode > CTEST_PRINT_ALL) ? CTEST_PRINT_ALL : mode;
}


/// \brief Define a new sub-test in the test program.
/// A test program is typically made up of multiple sub-tests. The `ctest_unit
/// function should be placed at the start of each sub-test.
/// \param test The test data structure.
/// \param name The name of the sub-test
/// \return Return 1 if test is enabled. Return 0 if test is disabled
/// \todo ctest_unit always returns 1 (test enabled).
 
int ctest_unit(ctest_type* test, const char* name)
{
   if isNULL(test) return 0;
   if (test->test_pass_count || test->test_fail_count) {
      ctest_test_result(test);
   }

   test->test_name[0] = '\0';
   test->test_pass_count = 0;
   test->test_fail_count = 0;
   if isNULL(name) return 0;
   strncpy(test->test_name, name, CTEST_NAME_LEN);
   test->test_name[CTEST_NAME_LEN-1] = '\0';
   if (test->mode > CTEST_PRINT_UNIT) {
      printf("Test %s\n", test->test_name);
   }
   return 1;
}

/// \brief Verify two integers are the same
/// Compare the actual value with the expected value. The descriptive message
/// is printed if the comparison fails or if the `mode is `CTEST_PRINT_ALL.
/// \param test Pointer to the test data structure
/// \param actual The actual value
/// \param expect The expected value
/// \param description A brief description of the test
/// \return void

void ctestfl_eqi(ctest_type* test, const int actual, const int expect, const char* description, char const* const file, int const ln)
{
   const bool pass = isEQ(actual, expect);
   if (!isNULL(test)) {
      if (pass) {
         test->test_pass_count++;
         test->total_pass_count++;
      } else {
         test->test_fail_count++;
         test->total_fail_count++;
      }
   }


   if (!pass || (!isNULL(test) && isEQ(test->mode,CTEST_PRINT_ALL)) ) {
      const char pass_str[5] = "pass";
      const char fail_str[5] = "fail";
      const char* result_str = pass ? pass_str : fail_str; 
      printf("%s - actual = %i, expect = %i, %s (%s:%i)\n", 
         result_str, actual, expect, description, file, ln);
   }
}

/// \brief Wrapper for ctestfl_eqi
void ctest_eqi(ctest_type* test, const int actual, const int expect, const char* description)
{
   ctestfl_eqi(test, actual, expect, description, NULL, 0);
}

/// \brief Verify two character strings are the same
/// Compare the actual value with the expected value. The descriptive message
/// is printed if the comparison fails or if the `mode is `CTEST_PRINT_ALL.
/// \param test Pointer to the test data structure
/// \param actual The actual value
/// \param expect The expected value
/// \param description A brief description of the test
/// \return void
 
void ctestfl_eqs(ctest_type* test, const char* actual, const char* expect, const char* description, char const* const file, int const ln)
{
   const bool pass = isEQS(actual, expect);
   if (!isNULL(test)) {
      if (pass) {
         test->test_pass_count++;
         test->total_pass_count++;
      } else {
         test->test_fail_count++;
         test->total_fail_count++;
      }
   }

   if (!pass || (!isNULL(test) && isEQ(test->mode,CTEST_PRINT_ALL)) ) {
      const char pass_str[5] = "pass";
      const char fail_str[5] = "fail";
      const char* result_str = pass ? pass_str : fail_str; 
      printf("%s - actual = '%s', expect = '%s', %s  (%s:%i)\n",
         result_str, actual, expect, description, file, ln);
   }
}

/// \brief Wrapper for ctestfl_eqi
void ctest_eqs(ctest_type* test, const char* const actual, const char* const expect, const char* description)
{
   ctestfl_eqs(test, actual, expect, description, NULL, 0);
}

/// \brief Print the results of a sub-test
/// A test program is typically made up of multiple sub-tests defined by 
/// `ctest_unit. This function prints the results of the sub-test.  The results
/// of a failing test will always be printed.  For a passing test the results
/// will only be printed if `mode is CTEST_PRINT_UNIT or greater.
/// \param test Pointer to the test data structure.
/// \return void

void ctest_test_result(ctest_type* test)
{
   if isNULL(test) return;
   const char pass = isZERO(test->test_fail_count);

   if (!pass || (test->mode >= CTEST_PRINT_UNIT) ) {
      const char num_fails = test->test_fail_count;
      const char num_tests = test->test_fail_count + test->test_pass_count;
      if (pass) {
         printf("Pass = Test %s all %i tests passed\n", test->test_name, num_tests);
      } else {
         printf("Fail = Test %s %i of %i tests failed\n", test->test_name, num_fails, num_tests);
      }
   }
   test->test_pass_count = 0;
   test->test_fail_count = 0;
}


/// \brief Print the results for the entire test
/// Print the pass/fail result for the entire test.
/// \param test Pointer to the test data structure
/// \return void

int ctest_total_result(ctest_type* test)
{
   if isNULL(test) return;
   if (test->test_pass_count || test->test_fail_count) {
      ctest_test_result(test);
   }

   const char pass = isZERO(test->total_fail_count);

   if (!pass || (test->mode >= CTEST_PRINT_TOTAL) ) {
      const char num_fails = test->total_fail_count;
      const char num_tests = test->total_fail_count + test->total_pass_count;
      if (pass) {
         printf("PASS * FINAL TEST RESULTS - ALL %i TESTS PASSED\n", num_tests);
      } else {
         printf("FAIL * Final Test Results - %i of %i tests FAILED\n", num_fails, num_tests);
      }
   }
   ctest_free(test);
   return test->total_fail_count;
}

/// \brief Free the test data structure
/// This is typically called at the end of the test program.
/// \param test Pointer to the test data structure
/// \return void

void ctest_free(ctest_type* test)
{
   if isNULL(test) return;
   free(test);
}


