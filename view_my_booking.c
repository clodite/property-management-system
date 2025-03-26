#include "header.h"
#include "function.h"
#include "struct.h"

struct strbook* view_my_booking(char my_id[30])
{
    FILE* book_record;
    book_record = fopen(BOOK_FILE, "r");
    if (book_record == NULL)
    {
        printf("读取预约文件失败。\n");
        return NULL;
    }

    struct strbook *head = NULL;
    struct strbook *tail = NULL;
    char line[256];
    int bug = 0; // 暂时没啥用

    while (fgets(line, sizeof(line), book_record))
    {
        long long book_id;
        int time, roomtype, last, status;
        char id[30];

        if (sscanf(line, "%lld %d %d %d %c %d", &book_id, &time, &roomtype, &last, id, &status) != 6)
        {
            bug++;
            // continue; //考虑要不要跳过这行数据
        }

        if (strcmp(id, my_id) == 0)
        {
            struct strbook *new_node = (struct strbook*)malloc(sizeof(struct strbook));
            if (new_node == NULL)
            {
                printf("内存分配失败。\n");
                fclose(BOOK_FILE);
                return head;
            }

            new_node->book_id = book_id;
            new_node->time = time;
            new_node->roomtype = roomtype;
            new_node->last = last;
            strncpy(new_node->id, id, sizeof(id));
            new_node->status = status;

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
        }
    }

    fclose(BOOK_FILE);
    return head;
}
