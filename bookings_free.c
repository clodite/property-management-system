#include "header.h"
#include "function.h"
#include "struct.h"

// [预约] 释放内存

void bookings_free(struct strbook* head)
{
    struct strbook* current = head;
    while (current != NULL)
    {
        struct strbook* temp = current;
        current = current->next;
        free(temp);
    }
}
