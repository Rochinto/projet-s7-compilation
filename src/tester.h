
#ifndef _TESTER_H_
#define _TESTER_H_

#include "Attribut.h"

#define TEST_PREFIX "\33[96m\33[1m[TEST]\33[0m\33[97m "
#define SUCCESS_SUFFIX "\33[92m\33[1m\33[7mpassed\33[0m\33[97m "
#define FAIL_SUFFIX "\33[31m\33[1m\33[7mfailed\33[0m\33[97m "
#define RESET_LINE "\33[0m\n"

#define TEST_NUMBER 10
char* test_paths[] =   {"tst/test0.ml",
                        "tst/test1.ml",
                        "tst/test1.2.ml",
                        "tst/test2.ml",
                        "tst/test2.2.ml",
                        "tst/test3.ml",
                        "tst/test4.ml",
                        "tst/test5.ml",
                        "tst/test5.2.ml",
                        "tst/test6.ml"};
// deprecated
/*char* answer_paths[] = {"tst/answer/test0.p",
                        "tst/answer/test1.p",
                        "tst/answer/test1.2.p",
                        "tst/answer/test2.p",
                        "tst/answer/test2.2.p",
                        "tst/answer/test3.p",
                        "tst/answer/test4.p"};*/

#endif