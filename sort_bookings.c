#include "header.h"
#include "function.h"
#include "struct.h"

// 按条件排序预约：

// 增/减/1/-1，整个函数都是这个逻辑。
// 排序条件：1.book_id 2.入住时间 3.房间类型 4.居住多久 5.预约人id 6.预约状态

struct strbook* sort_bookings(int type, int order)
{
    if (type < 1 || type > 6 || order < -1 || order > 1)
    {
        printf("无法完成排序：不支持的排序方式。\n");
        return NULL;
    }

    struct strbook* raw_bookings = view_bookings(-1, -1, -1, -1, "-1", -1);
    return bookings_merge_sort(raw_bookings, type, order);
}

struct strbook* bookings_merge_sort(struct strbook* head, int type, int order)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct strbook *left, *right;
    bookings_split(head, &left, &right);

    left = bookings_merge_sort(left, type, order);
    right = bookings_merge_sort(right, type, order);

    return bookings_merge(left, right, type, order);
}

void bookings_split(struct strbook* head, struct strbook** left, struct strbook** right)
{
    struct strbook* fast = head->next;
    struct strbook* slow = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

struct strbook* bookings_merge(struct strbook* left, struct strbook* right, int type, int order)
{
    struct strbook dummy;
    struct strbook* tail = &dummy;

    while (left && right)
    {
        int cmp_nodes = book_compare_nodes(left, right, type, order);
        if (cmp_nodes == 1)
        {
            tail->next = left;
            left = left->next;
        }
        else if (cmp_nodes == -1)
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    tail->next = (left != NULL) ? left : right;
    return dummy.next;
}

int book_compare_nodes(struct strbook* a, struct strbook* b, int type, int order)
{
    int result = 0;
    switch (type)
    {
        case 1:
            result = (a->book_id < b->book_id) ? 1 : -1;
            break;
        case 2:
            result = (a->time < b->time) ? 1 : -1;
            break;
        case 3:
            result = (a->roomtype < b->roomtype) ? 1 : -1;
            break;
        case 4:
            result = (a->last < b->last) ? 1 : -1;
            break;
        case 5:
            result = book_compare_nodes_str(a->id, b->id);
            break;
        case 6:
            result = (a->status < b->status) ? 1 : -1;
            break;
        default:
            result = 0;
    }
    return (order == 1) ? result : -result;
}

int book_compare_nodes_str(const char* a, const char* b)
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
