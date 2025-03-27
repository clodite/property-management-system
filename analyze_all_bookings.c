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
    int bugs = 0; // 没用

    while (fgets(line, sizeof(line), book_record))
    {
        long long current_book_id;
        int current_time, current_roomtype, current_last, current_status;
        char current_id [30];

        if ()
    }
}

// 统计所有预约

// count_all_bookings()
{

}

// 排序所有预约

// sort_all_bookings(int order)
{

}
