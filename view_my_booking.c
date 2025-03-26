# include "header.h"
# include "function.h"
# include "struct.h"

struct strbook* view_my_booking(char my_id[30])
{
    FILE* book_record;
    book_record = fopen(BOOK_FILE, "r");
    if (book_record == NULL)
    {
        printf("读取预约文件失败。\n");
    }
}
