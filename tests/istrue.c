#include <stdio.h>
#include <stddef.h>
#include <time.h>
#define ISTRUE_DEFINITION
#include "istrue.h"

#define COLOR_PASS "\033[32m"
#define COLOR_FAIL "\033[31m"
#define COLOR_RESET "\033[0m"

#define test(name, value, size, expected)                                                          \
    do                                                                                             \
    {                                                                                              \
        clock_t start      = clock();                                                              \
        int     result     = istrue((void*) value, size);                                          \
        clock_t end        = clock();                                                              \
        double  time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;                            \
        if (result == expected)                                                                    \
            printf("(%d) %-50s: " COLOR_PASS "PASS" COLOR_RESET " (Time: %.6f s)\n", result, name, \
                   time_taken);                                                                    \
        else                                                                                       \
            printf("(X) %-50s: " COLOR_FAIL "FAIL (Expected %d, got %d)" COLOR_RESET               \
                   " (Time: %.6f s)\n",                                                            \
                   name, expected, result, time_taken);                                            \
    } while (0)

int main()
{
    printf("---------------------------------------\n");
    printf("Testing 'istrue' function:\n\n");
    test("Test with NULL pointer", NULL, 0, 0);
    test("Test with integer value 0", &(int){0}, 1, 0);
    test("Test with integer value 1", &(int){1}, 1, 1);
    test("Test with non-zero float", &(float){3.14}, sizeof(float), 1);
    test("Test with pointer to non-null, non-zero value", &(int){5}, 1, 1);
    test("Test with array of integers, all zero", ((int[]){0, 0, 0, 0, 0}), sizeof(int) * 5, 0);
    test("Test with array of integers, some non-zero", ((int[]){0, 0, 1, 0, 0}), sizeof(int) * 5,
         1);
    printf("---------------------------------------\n");
    return 0;
}
