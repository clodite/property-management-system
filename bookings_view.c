#include "header.h"
#include "function.h"
#include "struct.h"

// [预约] 查询：-1不指定

struct strbook *bookings_view(long long book_id, int ttime, int roomtype, int last, char id[30], int status)
{
    FILE *book_record;
    book_record = fopen(BOOK_FILE, "r");
    if (book_record == NULL)
    {
        printf("读取预约数据失败。\n");
        return NULL;
    }

    struct strbook *head = NULL;
    struct strbook *tail = NULL;
    char line[256];
    int bug = 0; // 没用

    while (fgets(line, sizeof(line), book_record))
    {
        long long current_book_id;
        int current_time, current_roomtype, current_last, current_status;
        char current_id[30];

        if (sscanf(line, "%lld %d %d %d %s %d", &current_book_id, &current_time, &current_roomtype, &current_last, current_id, &current_status) != 6)
        {
            bug++;
            continue;
        }

        if ((current_book_id != book_id && book_id != -1) || (current_time != ttime && ttime != -1) || (current_roomtype != roomtype && roomtype != -1) || (current_last != last && last != -1) || (strcmp(current_id, id) && strcmp(id, "-1")) || (current_status != status && status != -1))
        {
            continue;
        }

        struct strbook *new_node = (struct strbook *)malloc(sizeof(struct strbook));
        if (new_node == NULL)
        {
            printf("分配内存失败。\n");
            fclose(book_record);
            return head;
        }

        new_node->book_id = current_book_id;
        new_node->time = current_time;
        new_node->roomtype = current_roomtype;
        new_node->last = current_last;
        strncpy(new_node->id, current_id, sizeof(current_id));
        new_node->status = current_status;

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

    fclose(book_record);
    return head;
}

void bookings_free(struct strbook *head) // [预约] 释放内存
{
    struct strbook *current = head;
    while (current != NULL)
    {
        struct strbook *temp = current;
        current = current->next;
        free(temp);
    }
}

struct strbook *read_booklist_file(const char *target_id)
{
    FILE *file = fopen("booklist.txt", "r");
    if (file == NULL)
    {
        perror("无法打开文件");
        return NULL;
    }

    struct strbook *head = NULL;
    struct strbook *tail = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        struct strbook *new_node = (struct strbook *)calloc(1, sizeof(struct strbook));
        if (new_node == NULL)
        {
            perror("内存分配失败");

            while (head)
            {
                struct strbook *tmp = head;
                head = head->next;
                free(tmp);
            }
            fclose(file);
            return NULL;
        }

        int parsed = sscanf(line, "%lld %d %d %d %20s %d",
                            &new_node->book_id,
                            &new_node->time,
                            &new_node->roomtype,
                            &new_node->last,
                            new_node->id,
                            &new_node->status);

        if (parsed != 6)
        {
            free(new_node);
            continue;
        }

        if (strcmp(new_node->id, target_id) == 0)
        {
            new_node->next = NULL;
            if (!head)
            {
                head = tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
        else
        {
            free(new_node);
        }
    }

    fclose(file);
    return head;
}
