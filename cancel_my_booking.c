# include "header.h"
# include "function.h"
# include "struct.h"
int cancel_my_booking(long long my_book_id)
{
    FILE* book_record, *temp_file;

    book_record = fopen (BOOK_FILE, "a");
    if (book_record == NULL)
    {
        printf("预约记录读取失败。\n");
        return -1;
    }

    temp_file = fopen ("canceling_temp.txt", "w");
    if (temp_file == NULL)
    {
        printf("无法创建临时文件。\n");
        return -1;
    }

    char line[256];
    int found = 0;      // 预约记录条数
    int real_found = 0; // `- 未入住（0）条数
    int bug = 0;        // 找到的bug数量，暂时没啥用
    while (fgets(line, sizeof(line), book_record))
    {
        long long book_id;
        int time, roomtype, last, status;
        char id[30];

        if (sscanf(line, "%lld %d %d %d %s %d", &book_id, &time, &roomtype, &last, id, &status) != 6)
        {
            bug++; // 名字中含空格也会这样
        }

        if (book_id == my_book_id)
        {
            found ++;

            if (status == 0)
            {
                real_found++;
                fprintf(temp_file, "%lld %d %d %d %s %d\n", book_id, time, roomtype, last, id, 2);
            }

            if (status == 1)
            {
                printf("该预约已结单，无法操作。\n");
                fputs(line, temp_file);
            }

            if (status == 2)
            {
                printf("该预约已经取消过啦。\n");
                fputs(line, temp_file);
            }

        }

        else
        {
            fputs(line, temp_file);
        }
    }

    fclose (temp_file);
    fclose (book_record);

    if (found > 1)
    {
        bug++;
    }

    if (!real_found)
    {
        if (!found)
        {
            remove ("canceling_temp.txt");
            printf("未找到预约记录，无法完成。\n");
        }
        return -1;
    }

    if (real_found)
    {
        remove (BOOK_FILE);
        rename ("canceling_temp.txt", BOOK_FILE);
        printf("取消该预约完成！\n");
        return 0;
    }

}
