#include "header.h"
#include "function.h"
#include "struct.h"

// [预约] 统计：-1不指定

int bookings_count_times(long long book_id, int time, int roomtype, int last, char id[30], int status) // [预约] 次数统计：-1不指定
{
    return bookings_count_times_range(book_id, book_id, time, time, roomtype, roomtype, last, last, id, id, status);
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

        int m_id_strcmp_result = id_strcmp(current_id, m_id);
        int M_id_strcmp_result = id_strcmp(current_id, M_id);
        int m_strcmp_result = strcmp(m_id, "-1");
        int M_strcmp_result = strcmp(M_id, "-1");

        // WARNING: SHIT IS COOMING //

        if (((current_book_id >= m_book_id && current_book_id <= M_book_id && m_book_id != -1 && M_book_id != -1) || (current_book_id >= m_book_id && m_book_id != -1 && M_book_id == -1) || (current_book_id <= M_book_id || M_book_id != -1 && m_book_id == -1) || (m_book_id == -1 && M_book_id == -1)) && ((current_time >= m_time && current_time <= M_time && m_time != -1 && M_time != -1) || (current_time >= m_time && m_time != -1 && M_time == -1) || (current_time <= M_time || M_time != -1 && m_time == -1) || (m_time == -1 && M_time == -1)) && ((current_roomtype >= m_roomtype && current_roomtype <= M_roomtype && m_roomtype != -1 && M_roomtype != -1) || (current_roomtype >= m_roomtype && m_roomtype != -1 && M_roomtype == -1) || (current_roomtype <= M_roomtype || M_roomtype != -1 && m_roomtype == -1) || (m_roomtype == -1 && M_roomtype == -1)) && ((current_last >= m_last && current_last <= M_last && m_last != -1 && M_last != -1) || (current_last >= m_last && m_last != -1 && M_last == -1) || (current_last <= M_last || M_last != -1 && m_last == -1) || (m_last == -1 && M_last == -1)) && ((m_id_strcmp_result != 1 && M_id_strcmp_result != -1 && m_strcmp_result != 0 && M_strcmp_result != 0) || (m_id_strcmp_result != 1 && m_strcmp_result != 0 && M_strcmp_result == 0) || (M_id_strcmp_result != -1 && M_strcmp_result != 0 && m_strcmp_result == 0) || (m_strcmp_result == 0 && M_strcmp_result == 0)) && (current_status == status || status == -1))
        {
            times++;
        }
    }

    fclose(book_record);
    return times;
}

int bookings_count_guest(long long book_id, int time, int roomtype, int last, int status) // [预约] 人数统计：-1不指定
{
    return bookings_count_guest_range(book_id, book_id, time, time, roomtype, roomtype, last, last, status);
}

int bookings_count_guest_range(long long m_book_id, long long M_book_id, int m_time, int M_time, int m_roomtype, int M_roomtype, int m_last, int M_last, int status) // [预约] 范围人数统计：-1不指定
{
    FILE* book_record;
    book_record = fopen(BOOK_FILE, "r");
    if (book_record == NULL)
    {
        printf("读取预约数据失败。\n");
        return -1;
    }

    int num = 0;
    char line[256];
    int bug = 0; // 没用

    struct guest_times
    {
        char id[30];
        int times; // 暂作冗余功能
        struct guest_times *next;
    };

    struct guest_times* head = NULL;
    struct guest_times* tail = NULL;

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

        if (((current_book_id >= m_book_id && current_book_id <= M_book_id && m_book_id != -1 && M_book_id != -1) || (current_book_id >= m_book_id && m_book_id != -1 && M_book_id == -1) || (current_book_id <= M_book_id || M_book_id != -1 && m_book_id == -1) || (m_book_id == -1 && M_book_id == -1)) && ((current_time >= m_time && current_time <= M_time && m_time != -1 && M_time != -1) || (current_time >= m_time && m_time != -1 && M_time == -1) || (current_time <= M_time || M_time != -1 && m_time == -1) || (m_time == -1 && M_time == -1)) && ((current_roomtype >= m_roomtype && current_roomtype <= M_roomtype && m_roomtype != -1 && M_roomtype != -1) || (current_roomtype >= m_roomtype && m_roomtype != -1 && M_roomtype == -1) || (current_roomtype <= M_roomtype || M_roomtype != -1 && m_roomtype == -1) || (m_roomtype == -1 && M_roomtype == -1)) && ((current_last >= m_last && current_last <= M_last && m_last != -1 && M_last != -1) || (current_last >= m_last && m_last != -1 && M_last == -1) || (current_last <= M_last || M_last != -1 && m_last == -1) || (m_last == -1 && M_last == -1)) && (current_status == status || status == -1))
        {
            struct guest_times* nodes = head;
            while(nodes != NULL && id_strcmp(nodes->id, current_id) != 0)
            {
                nodes = nodes->next;
            }

            if(id_strcmp(nodes->id, current_id) == 0)
            {
                nodes->times++;
            }

            else if(nodes == NULL)
            {
                struct guest_times* new_node = (struct guest_times*)malloc(sizeof(struct guest_times));
                if (new_node == NULL)
                {
                    printf("分配内存失败。\n");
                    fclose(book_record);
                    return -1;
                }
                strcpy(new_node->id, current_id);
                new_node->times = 1;

                if (head == NULL)
                {
                    head = new_node;
                    tail = new_node;
                }
                else
                {
                    tail->next = new_node;
                    tail = new_node;
                }

                num++;
            }
        }
    }

    fclose(book_record);
    struct guest_times* current = head;
    while (current != NULL)
    {
        struct guest_times* temp = current;
        current = current->next;
        free(temp);
    }

    return num;
}


