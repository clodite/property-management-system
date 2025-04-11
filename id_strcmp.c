#include "header.h"
#include "function.h"
#include "struct.h"

// [ID] 字符串比较：递增返回1,递减返回-1,相等返回0

int id_strcmp(const char* a, const char* b)
{
    while (*a == '0') a++;
    while (*b == '0') b++;

    int len_a = strlen(a);
    int len_b = strlen(b);

    if (len_a < len_b) return 1;
    if (len_a > len_b) return -1;

    while (*a && *b) {
        if (*a < *b) return 1;
        if (*a > *b) return -1;
        a++;
        b++;
    }
    return 0;
}
