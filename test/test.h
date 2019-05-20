/// @file 
/// @brief Header file for ctest.h
///
/// @main

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define isEQ(A, B) ((A) == (B))
#define isZERO(A) isEQ(A, 0)
#define isFALSE(A) isEQ(A, 0)
#define isNULL(A) isEQ(A, NULL)
#define isEQS(A, B) ( (isNULL(A) || isNULL(B)) ? 0 : (strcmp(A,B) == 0) )
#define MIN(A, B) ( ( (A) < (B) ) ? (A) : (B) )
#define MAX(A, B) ( ( (A) > (B) ) ? (A) : (B) )
#define safe_strncpy(D,S,N) D[0]='\0'; if (S) strncpy(D,S,N-1); D[N-1]='\0';

#define TEST_START int TEST_FAIL_CNT=0; int TEST_PASS_CNT=0;
#define TEST_DONE if (TEST_FAIL_CNT) return TEST_FAIL_CNT;

#define EQ(A,E,M) if (A!=E) {printf("FAIL: %d != %d - %s (File: %s:%d)\n",A,E,M,__FILE__,__LINE__); return 1;} 
#define EQD(A,E,M) EQ(A,E,M)
#define EQI(A,E,M) EQ(A,E,M)
#define EQP(A,E,M) if (A!=E) {printf("FAIL: %p != %p - %s (File: %s:%d)\n",A,E,M,__FILE__,__LINE__); return 1;} 
#define EQS(A,E,M) if (!isEQS(A,E)) {printf("FAIL: '%s' != '%s' - %s File: %s Line: %d\n",A,E,M,__FILE__,__LINE__); return 1;} 

#define NEQ (A,E,M) if (A==E) {printf("FAIL: %d == %d - %s (File: %s:%d)\n",A,E,M,__FILE__,__LINE__); return 1;} 
#define NEQD(A,E,M) EQ(A,E,M)
#define NEQI(A,E,M) EQ(A,E,M)
#define NEQP(A,E,M) if (A==E) {printf("FAIL: %p == %p - %s (File: %s:%d)\n",A,E,M,__FILE__,__LINE__); return 1;} 
#define NEQS(A,E,M) if (isEQS(A,E)) {printf("FAIL: '%s' == '%s' - %s File: %s Line: %d\n",A,E,M,__FILE__,__LINE__); return 1;} 

#endif
