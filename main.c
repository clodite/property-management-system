#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "header.h"
#include "struct.h"

int main()
{
    print_welcome_ui();
    int input = 0;
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        check_in();
        break;
    case 2:
        ;
        break;
    case 3:
        break;
    }

    return 0;
}