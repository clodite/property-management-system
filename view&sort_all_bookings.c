#include "header.h"
#include "function.h"
#include "struct.h"

// 查询所有预约

struct strbook* view_all_bookings(long long book_id, int time, int roomtype, int last, char id[30], int status)
{
    FILE* book_record;
    book_record = fopen(BOOK_FILE, "r");
    if (book_record == NULL)
    {
        printf("读取预约数据失败。\n");
        return NULL;
    }

    struct strbook* head = NULL;
    struct strbook* tail = NULL;
    char line[256];
    int bug = 0; // 没用

    while (fgets(line, sizeof(line), book_record))
    {
        long long current_book_id;
        int current_time, current_roomtype, current_last, current_status;
        char current_id [30];

        if (sscanf(line, "%lld %d %d %d %c %d", &current_book_id, &current_time, &current_roomtype, &current_last, current_id, &current_status) != 6)
        {
            bug++;
            continue;
        }

        if ((current_book_id != book_id && book_id != -1) || (current_time != time && time != -1) || (current_roomtype != roomtype && roomtype != -1) || (current_last != last && last != -1) || (strcmp(current_id, id) && strcmp(id, "-1")) || (current_status != status && status != -1))
        {
            continue;
        }

        struct strbook* new_node = (struct strbook*)malloc(sizeof(struct strbook));
        if (new_node == NULL)\
        {
            printf("分配内存失败。\n");
            fclose(BOOK_FILE);
            return head;
        }

        new_node->book_id = current_book_id;
        new_node->time = current_time;
        new_node->roomtype = current_roomtype;
        new_node->last = current_last;
        strncpy(new_node->id, current_id, sizeof(current_id));
        new_node->status = current_status;

        if(head == NULL)
        {
            head = new_node;
            tail = new_node;
        }

        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    fclose(BOOK_FILE);
    return head;
}

// 排序所有预约：-1/0/1 倒序/不排序/正序

// sort_all_bookings(int book_id_order, int time_order, int roomtype_order, int last_order, int id_order, int status_order)
{

}
