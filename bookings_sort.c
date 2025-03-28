#include "header.h"
#include "function.h"
#include "struct.h"

// [预约] 排序
// [type]: 1.预约唯一id 2.入住时间 3.房间类型 4.居住多久 5.预约人id 6.预约状态 [order]: 增/减/1/-1

struct strbook* sort_bookings(int type, int order)
{
    if (type < 1 || type > 6 || order < -1 || order > 1)
    {
        printf("无法完成排序：不支持的排序方式。\n");
        return NULL;
    }

    struct strbook* raw_bookings = view_bookings(-1, -1, -1, -1, "-1", -1);
    return bookings_sort_merge_sort(raw_bookings, type, order);
}

struct strbook* bookings_sort_merge_sort(struct strbook* head, int type, int order) // [预约] 归并排序
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct strbook *left, *right;
    bookings_sort_split(head, &left, &right);

    left = bookings_sort_merge_sort(left, type, order);
    right = bookings_sort_merge_sort(right, type, order);

    return bookings_sort_merge(left, right, type, order);
}

void bookings_sort_split(struct strbook* head, struct strbook** left, struct strbook** right) // [预约] 归并排序之一
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

struct strbook* bookings_sort_merge(struct strbook* left, struct strbook* right, int type, int order) // [预约] 归并排序之二
{
    struct strbook dummy;
    struct strbook* tail = &dummy;

    while (left && right)
    {
        int cmp_nodes = bookings_sort_cmp_nodes(left, right, type, order);
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

int bookings_sort_cmp_nodes(struct strbook* a, struct strbook* b, int type, int order) // [预约] 节点比较
{
    int result = 0;
    switch (type)
    {
        case 1:
            if (a->book_id < b->book_id) result = 1;
            else if (a->book_id > b->book_id) result = -1;
            else result = 0;
            break;
        case 2:
            if (a->time < b->time) result = 1;
            else if (a->time > b->time) result = -1;
            else result = 0;
            break;
        case 3:
            if (a->roomtype < b->roomtype) result = 1;
            else if (a->roomtype > b->roomtype) result = -1;
            else result = 0;
        case 4:
            if (a->last < b->last) result = 1;
            else if (a->last > b->last) result = -1;
            else result = 0;
            break;
        case 5:
            result = id_strcmp(a->id, b->id);
            break;
        case 6:
            if (a->status < b->status) result = 1;
            else if (a->status > b->status) result = -1;
            else result = 0;
            break;
        default:
            result = 0;
    }
    return (order == 1) ? result : -result;
}

