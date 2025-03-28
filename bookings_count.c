#include "header.h"
#include "function.h"
#include "struct.h"

// [预约] 统计：-1不指定

int bookings_count_times(long long book_id, int time, int roomtype, int last, char id[30], int status) // [预约] 次数统计：-1不指定
{
    return bookings_count_times_range(book_id, book_id, time, time, roomtype, roomtype, last, last, id[30], id[30], status);
}

int bookings_count_times_range(long long m_book_id, long long M_book_id, int m_time, int M_time, int m_roomtype, int M_roomtype, int m_last, int M_last, char m_id[30], char M_id[30], int status) // [预约] 范围次数统计：-1不指定
{
    FILE* book_record;
    book_record = fopen(BOOK_FILE, "r");
    if (book_record == NULL)
    {
        printf("读取预约数据失败。\n");
        return -1;
    }

    int times = 0;
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

        times++;
    }

    fclose(BOOK_FILE);
    return times;
}

int bookings_count_guest(long long book_id, int time, int roomtype, int last, int status) // [预约] 人数统计：-1不指定
{
    return bookings_count_guestnum_range(book_id, book_id, time, time, roomtype, roomtype, lsat, last, status);
}

int bookings_count_guest_range(long long m_book_id, long long M_book_id, int m_time, int M_time, int m_roomtype, int M_roomtype, int m_last, int M_last, int status) // [预约] 范围人数统计：-1不指定
{

}

