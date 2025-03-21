# include "header.h"
# include "function.h"
# include "struct.h"
void view_my_booking(char ID[30])
{
    char seeked_id[30] = {0};
    int times = 0, seeked_room = 0;
    int booking_y = 0, booking_m = 0, booking_d = 0;
    int staying_
    
    FILE *book_record, *live_record;
    if ((book_record = fopen("book_record.txt", "r")) == NULL || (live_record = fopen("live_record.txt", "r")) == NULL)
    {
        printf("Can't open files\n");
        exit (-1);
    }
    
    printf("房间号 | Booking Time | Staying Time\n");

    fgets(seeked_id, 31, fp);
    while(seeked_id != NULL)
    {
        if (seeked_id == ID)
        {
            
    
}
