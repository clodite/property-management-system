# include "header.h"
# include "function.h"
# include "struct.h"
int cancel_my_booking(long long my_book_id)
{
    FILE* book_record, *temp_file;
    if ((book_record = fopen ("book.txt", "a")) == NULL)
    {
        printf("预约记录读取失败。");
        exit (-1);
    }
    if ((temp_file = fopen ("temp_book_record.txt", "w")) == NULL)
    {
        printf("无法创建临时文件。");
        exit (-1);
    }

}
