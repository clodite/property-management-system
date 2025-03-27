#define _CRT_SECURE_NO_WARNINGS

#include "BBB.h"
#include "struct.h"
#include "header.h"
#include "function.h"
struct room* findemptyroom(int type)
{
    struct room* head = load_rooms("room");
    struct room* roomnow = head;
    while (1)
    {
        if (roomnow->type == type && roomnow->state == 0)
        {
            roomnow->state = 2;
            save_rooms("room", head);

            return roomnow;
        }
        else
        {
            roomnow = roomnow->next;
        }
        if (roomnow->next == NULL)
        {
            printf("无此类型的空房间！\n");
            break;
            return NULL;
        }
    }
}
void save_rooms(const char* room, struct room* head) 
{
    FILE* file = fopen(room, "wt");
    if (file == NULL) 
    {
        printf("文件打开失败。\n");
        return;
    }

    struct room* current = head;
    while (current != NULL) 
    {
        fprintf(file, "%d %d %d %d %d\n",
            current->num, current->type, current->price, current->size, current->state);
        current = current->next;
    }

    fclose(file);
    printf("房间数据已保存到文件。\n");
}
void roombookcheck(int* rooms, int type,int sum)
{
    for (int i = 0;i < 20000;i++)
        rooms[i] = sum;
    struct strbook* booknow = load_books("booklist.txt");
    while(1)
    {
        if (booknow->roomtype == type)
            for (int i = booknow->time;i < booknow->time + booknow->last;i++)
                if(i > 0 && i < 20000)
                    rooms[i]--;
        if (booknow->next != NULL)
            booknow = booknow->next;
        else
            break;
    }



}
void roomlivecheck(int* rooms, int type, int sum)
{

    struct live_record* livenow = load_lives("liveinlist.txt");
    while (1)
    {
        if (livenow->type == type)
        {
            if(livenow->leave_time == -1)
            {
                for (int i = livenow->arrive_time;i < livenow->arrive_time + livenow->time_live;i++)
                    if (i > 0 && i < 20000)
                        rooms[i]--;
            }
            else
            {
                for (int i = livenow->arrive_time;i < livenow->leave_time;i++)
                    if (i > 0 && i < 20000)
                        rooms[i]--;
            }
                    
        }
           
        if (livenow->next != NULL)
            livenow = livenow->next;
        else
            break;
    }



}
struct strbook* load_books(const char* bookdate)
{
    FILE* file = fopen(bookdate, "rt");
    if (file == NULL)
    {
        printf("数据库打开失败。\n");
        return NULL;
    }

    struct strbook* head = NULL;
    struct strbook* tail = NULL;

    while (1)
    {
        struct strbook* load_room = (struct strbook*)malloc(sizeof(struct strbook));
        if (load_room == NULL)
        {
            printf("内存分配失败。\n");
            fclose(file);
            return head;
        }


        int result = fscanf(file, "%d %d %d %s", &load_room->time, &load_room->roomtype, &load_room->last,&load_room->id);
        if (result != 4)
        {
            free(load_room);
            break;
        }

        load_room->next = NULL;

        if (head == NULL)
        {
            head = load_room;
            tail = load_room;
        }
        else
        {
            tail->next = load_room;
            tail = load_room;
        }
    }

    fclose(file);
    return head;
}
void free_books(struct strbook* head)
{
    while (head != NULL)
    {
        struct strbook* temp = head;
        head = head->next;
        free(temp);
    }
}
struct room* load_rooms(const char* roomdate) 
{
    FILE* file = fopen(roomdate, "rt");
    if (file == NULL) 
    {
        printf("数据库打开失败。\n");
        return NULL;
    }

    struct room* head = NULL;
    struct room* tail = NULL;

    while (1) 
    {
        struct room* load_room = (struct room*)malloc(sizeof(struct room));
        if (load_room == NULL) 
        {
            printf("内存分配失败。\n");
            fclose(file);
            return head; 
        }

        
        int result = fscanf(file, "%d %d %d %d %d", &load_room->num, &load_room->type, &load_room->price, &load_room->size, &load_room->state);
        if (result != 5) 
        {
            free(load_room);
            break;
        }

        load_room->next = NULL;

        if (head == NULL) 
        {
            head = load_room;
            tail = load_room;
        }
        else 
        {
            tail->next = load_room;
            tail = load_room;
        }
    }

    fclose(file);
    return head;
}
struct live_record* load_lives(const char* roomdate)
{
    FILE* file = fopen(roomdate, "rt");
    if (file == NULL)
    {
        printf("数据库打开失败。\n");
        return NULL;
    }

    struct live_record* head = NULL;
    struct live_record* tail = NULL;

    while (1)
    {
        struct live_record* load_room = (struct live_record*)malloc(sizeof(struct live_record));
        if (load_room == NULL)
        {
            printf("内存分配失败。\n");
            fclose(file);
            return head;
        }


        int result = fscanf(file, "%s %d %d %d %d %d", &load_room->ID, &load_room->room, &load_room->type, &load_room->arrive_time, &load_room->time_live, &load_room->leave_time);
        if (result != 6)
        {
            free(load_room);
            break;
        }

        load_room->next = NULL;

        if (head == NULL)
        {
            head = load_room;
            tail = load_room;
        }
        else
        {
            tail->next = load_room;
            tail = load_room;
        }
    }

    fclose(file);
    return head;
}
void free_rooms(struct room* head)
{
    while (head != NULL)
    {
        struct room* temp = head;
        head = head->next;
        free(temp);
    }
}
int findroomcount(int type)
{
    struct room *roomnow = load_rooms("room");
    int sum = 0;
    while(1)
    {
        if (roomnow->type == type)
            sum++;
        if (roomnow->next != NULL)
            roomnow = roomnow->next;
        else
            break;
    } 
    return sum;
    
}
void custom_book(char *userid) 
{
	struct time timein;
    int timein_stamp;
	int typein;
	int lastin;
	int timeroom;

	printf("请输入预约时间（年 月 日）\n");
	scanf("%d %d %d", &timein.year, &timein.month, &timein.day);
	printf("预约房间类型编号：");
	scanf("%d", &typein);
	restart:
	printf("是否预约钟点房？\n");
	printf("[1]是\n");
	printf("[2]否\n");
	scanf("%d", &timeroom);
	    if (timeroom == 1)
	{
		int lasttime = 0;
        timein.hour = 0;
    faq:
        printf("请输入居住时长与入住时间\n");
        scanf("%d %d", &lasttime, &timein.hour);
        if (lasttime < 1 && lasttime > 4 && timein.hour < 6 && timein.hour > 18)
        {
            printf("时长或入住时间不符合约定，请重新输入！");
            goto faq;
        }
        int sum = findroomcount(typein);
        timein_stamp = time_to_timestamp(timein);
        int roomremain[20000] = { sum };
        int check = 1;
        roombookcheck(roomremain, typein, sum);
        roomlivecheck(roomremain, typein, sum);

        for (int i = timein_stamp;i < timein_stamp + lasttime;i++)
        {
            if (roomremain[i] == 0)
            {
                check = 0;
                printf("您选择的时间段已无空房。");
                break;
            }
        }
        if (check)
        {
            FILE* file = fopen("booklist.txt", "at");
            if (file == NULL)
            {
                printf("文件打开失败。\n");
            }
            else
            {
                printf("预约成功！\n");
            }
            fprintf(file, "%d %d %d %s\n", timein_stamp, typein, lasttime, userid);
            fclose(file);

            return 0;
        }


	}
	    else if (timeroom == 2)
	{
		int lasttime = 0;
        timein.hour = 13;

		printf("请输入居住天数\n");
		scanf("%d", &lasttime);
        int sum = findroomcount(typein);
        timein_stamp = time_to_timestamp(timein);
        int roomremain[20000] = { sum };
        int check = 1;
        roombookcheck(roomremain, typein,sum);
        roomlivecheck(roomremain, typein, sum);

        for (int i = timein_stamp;i < timein_stamp + lasttime * 24 - 1;i++)
        {
            if (roomremain[i] == 0)
            {
                check = 0;
                printf("您选择的时间段已无空房。");
                break;
            }
        }
        if (check)
        {
            FILE* file = fopen("booklist.txt", "at");
            if (file == NULL) 
            {
                printf("文件打开失败。\n");
            }
            else
            {
                printf("预约成功！\n");
            }
            fprintf(file, "%d %d %d %s\n", timein_stamp, typein, lasttime * 24 - 1,userid);
            fclose(file);

            return 0;
        }

	}
	else
	{
		printf("选择错误！请输入正确数字");
		goto restart;
	}

}
void service_find(char* userid,int type,int liveintime,int livefortime)
{
    struct room *theroom = findemptyroom(type);
    printf("已成功分配该类型房间！\n");
    printf("房间号：%d\n",theroom->num);
    printf("房间价格：%d\n", theroom->price);
    printf("房间面积：%d\n", theroom->size);
    FILE* file = fopen("liveinlist.txt", "at");
    if (file == NULL)
    {
        printf("文件打开失败。\n");
    }
    else
    {
        printf("入住信息记录成功！！\n");
    }
    fprintf(file, "%s %d %d %d %d -1\n", userid, theroom->num,type, liveintime, livefortime);
    fclose(file);
}
void give_room()
{
    printf("输入1查询空房间\n");
    int needtype = 0;
    char userid[30];
    struct time timein;
    int timein_stamp;
    int timefor = 0;
    printf("请输入预定客人的身份证号\n");
    scanf("%s", userid);
    printf("请输入预定客人所需要的房间类型\n");
    scanf("%d", &needtype);
    printf("请输入现在的年 月 日 时\n");
    scanf("%d %d %d %d", &timein.year, &timein.month, &timein.day, &timein.hour);
restart:
    printf("客人所选择的是？\n");
    printf("[1]钟点房\n");
    printf("[2]正常房\n");
    int livetype = 0;
    scanf("%d", &livetype);
    if (livetype == 2)
    {
        int lasttime = 0;
        printf("请输入居住天数\n");
        scanf("%d", &lasttime);
        int sum = findroomcount(needtype);
        timein_stamp = time_to_timestamp(timein);
        int roomremain[20000] = { sum };
        int check = 1;
        roombookcheck(roomremain, needtype, sum);
        roomlivecheck(roomremain, needtype, sum);
        int fix = timein.hour - 13;
        for (int i = timein_stamp;i < timein_stamp + lasttime * 24 - 1 - fix;i++)
        {
            if (roomremain[i] == 0)
            {
                check = 0;
                printf("无符合条件的剩余房间");
                break;
            }
        }
        if (check)
        {
            service_find(userid, needtype, timein_stamp, lasttime * 24 - 1 - fix);
            return 0;
        }
    }
    else if (livetype == 1)
    {
        if (timein.hour < 6 && timein.hour > 18)
        {
            printf("当前时间无法入住钟点房！");
            goto end;
        }
        int lasttime = 0;
    faq:
        printf("请输入入住时间\n");
        scanf("%d", &lasttime);
        if (lasttime < 1 && lasttime > 4 )
        {
            printf("时长不符合约定，请重新输入！");
            goto faq;
        }
        int sum = findroomcount(needtype);
        timein_stamp = time_to_timestamp(timein);
        int roomremain[20000] = { sum };
        int check = 1;
        roombookcheck(roomremain, needtype, sum);
        roomlivecheck(roomremain, needtype, sum);

        for (int i = timein_stamp;i < timein_stamp + lasttime;i++)
        {
            if (roomremain[i] == 0)
            {
                check = 0;
                printf("您选择的时间段已无空房。");
                break;
            }
        }
        if (check)
        {
            service_find(userid, needtype, timein_stamp, lasttime);
            end:
            return 0;
        }


    }
    else
    {
        printf("选择错误！请输入正确数字");
        goto restart;
    }
}
struct live_record* live_p_leave()
{
    struct live_record* livenow = load_lives("liveinlist.txt");
    struct live_record* head = livenow;
    int size = 1;
    while (head->next != NULL)
    {
        size++;
        head = head->next;
    }
    head = livenow;
    for (int i = 0;i < size - 1;i++)
    {
        livenow = head;
        for (int j = 0;j < size - 1 - i;j++)
        {
            if (livenow->leave_time < livenow->next->leave_time)
            {
                char tmpc[30];
                strcpy(tmpc, livenow->ID);
                strcpy(livenow->ID, livenow->next->ID);
                strcpy(livenow->next->ID, tmpc);
                int tmpi = livenow->room;
                livenow->room = livenow->next->room;
                livenow->next->room = tmpi;
                tmpi = livenow->type;
                livenow->type = livenow->next->type;
                livenow->next->type = tmpi;
                tmpi = livenow->time_live;
                livenow->time_live = livenow->next->time_live;
                livenow->next->time_live = tmpi;
                tmpi = livenow->leave_time;
                livenow->leave_time = livenow->next->leave_time;
                livenow->next->leave_time = tmpi;
                tmpi = livenow->arrive_time;
                livenow->arrive_time = livenow->next->arrive_time;
                livenow->next->arrive_time = tmpi;
            }
            if (livenow->next != NULL)
                livenow = livenow->next;
        }
    }
    return head;
}

struct live_record* live_p_time()
{
    struct live_record* livenow = load_lives("liveinlist.txt");
    struct live_record* head = livenow;
    int size = 1;
    while (head->next != NULL)
    {
        size++;
        head = head->next;
    }
    head = livenow;
    for (int i = 0;i < size - 1;i++)
    {
        livenow = head;
        for (int j = 0;j < size - 1 - i;j++)
        {
            if (livenow->time_live < livenow->next->time_live)
            {
                char tmpc[30];
                strcpy(tmpc, livenow->ID);
                strcpy(livenow->ID, livenow->next->ID);
                strcpy(livenow->next->ID, tmpc);
                int tmpi = livenow->room;
                livenow->room = livenow->next->room;
                livenow->next->room = tmpi;
                tmpi = livenow->type;
                livenow->type = livenow->next->type;
                livenow->next->type = tmpi;
                tmpi = livenow->time_live;
                livenow->time_live = livenow->next->time_live;
                livenow->next->time_live = tmpi;
                tmpi = livenow->leave_time;
                livenow->leave_time = livenow->next->leave_time;
                livenow->next->leave_time = tmpi;
                tmpi = livenow->arrive_time;
                livenow->arrive_time = livenow->next->arrive_time;
                livenow->next->arrive_time = tmpi;
            }
            if (livenow->next != NULL)
                livenow = livenow->next;
        }
    }
    return head;
}
struct live_record* live_p_id()
{
    struct live_record* livenow = load_lives("liveinlist.txt");
    struct live_record* head = livenow;
    int size = 1;
    while (head->next != NULL)
    {
        size++;
        head = head->next;
    }
    head = livenow;
    for (int i = 0;i < size - 1;i++)
    {
        livenow = head;
        for (int j = 0;j < size - 1 - i;j++)
        {
            if (livenow->ID < livenow->next->ID)
            {
                char tmpc[30];
                strcpy(tmpc, livenow->ID);
                strcpy(livenow->ID, livenow->next->ID);
                strcpy(livenow->next->ID, tmpc);
                int tmpi = livenow->room;
                livenow->room = livenow->next->room;
                livenow->next->room = tmpi;
                tmpi = livenow->type;
                livenow->type = livenow->next->type;
                livenow->next->type = tmpi;
                tmpi = livenow->time_live;
                livenow->time_live = livenow->next->time_live;
                livenow->next->time_live = tmpi;
                tmpi = livenow->leave_time;
                livenow->leave_time = livenow->next->leave_time;
                livenow->next->leave_time = tmpi;
                tmpi = livenow->arrive_time;
                livenow->arrive_time = livenow->next->arrive_time;
                livenow->next->arrive_time = tmpi;
            }
            if (livenow->next != NULL)
                livenow = livenow->next;
        }
    }
    return head;
}
struct live_record* live_p_room()
{
    struct live_record* livenow = load_lives("liveinlist.txt");
    struct live_record* head = livenow;
    int size = 1;
    while (head->next != NULL)
    {
        size++;
        head = head->next;
    }
    head = livenow;
    for (int i = 0;i < size - 1;i++)
    {
        livenow = head;
        for (int j = 0;j < size - 1 - i;j++)
        {
            if (livenow->room < livenow->next->room)
            {
                char tmpc[30];
                strcpy(tmpc, livenow->ID);
                strcpy(livenow->ID, livenow->next->ID);
                strcpy(livenow->next->ID, tmpc);
                int tmpi = livenow->room;
                livenow->room = livenow->next->room;
                livenow->next->room = tmpi;
                tmpi = livenow->type;
                livenow->type = livenow->next->type;
                livenow->next->type = tmpi;
                tmpi = livenow->time_live;
                livenow->time_live = livenow->next->time_live;
                livenow->next->time_live = tmpi;
                tmpi = livenow->leave_time;
                livenow->leave_time = livenow->next->leave_time;
                livenow->next->leave_time = tmpi;
                tmpi = livenow->arrive_time;
                livenow->arrive_time = livenow->next->arrive_time;
                livenow->next->arrive_time = tmpi;
            }
            if (livenow->next != NULL)
                livenow = livenow->next;
        }
    }
    return head;
}
struct live_record* live_p_type()
{
    struct live_record* livenow = load_lives("liveinlist.txt");
    struct live_record* head = livenow;
    int size = 1;
    while (head->next != NULL)
    {
        size++;
        head = head->next;
    }
    head = livenow;
    for (int i = 0;i < size - 1;i++)
    {
        livenow = head;
        for (int j = 0;j < size - 1 - i;j++)
        {
            if (livenow->type < livenow->next->type)
            {
                char tmpc[30];
                strcpy(tmpc, livenow->ID);
                strcpy(livenow->ID, livenow->next->ID);
                strcpy(livenow->next->ID, tmpc);
                int tmpi = livenow->room;
                livenow->room = livenow->next->room;
                livenow->next->room = tmpi;
                tmpi = livenow->type;
                livenow->type = livenow->next->type;
                livenow->next->type = tmpi;
                tmpi = livenow->time_live;
                livenow->time_live = livenow->next->time_live;
                livenow->next->time_live = tmpi;
                tmpi = livenow->leave_time;
                livenow->leave_time = livenow->next->leave_time;
                livenow->next->leave_time = tmpi;
                tmpi = livenow->arrive_time;
                livenow->arrive_time = livenow->next->arrive_time;
                livenow->next->arrive_time = tmpi;
            }
            if (livenow->next != NULL)
                livenow = livenow->next;
        }
    }
    return head;
}
struct live_record* live_p_live()
{
    struct live_record* livenow = load_lives("liveinlist.txt");
    struct live_record* head = livenow;
    int size = 1;
    while (head->next != NULL)
    {
        size++;
        head = head->next;
    }
    head = livenow;
    for (int i = 0;i < size - 1;i++)
    {
        livenow = head;
        for (int j = 0;j < size - 1 - i;j++)
        {
            if (livenow->time_live < livenow->next->time_live)
            {
                char tmpc[30];
                strcpy(tmpc, livenow->ID);
                strcpy(livenow->ID, livenow->next->ID);
                strcpy(livenow->next->ID, tmpc);
                int tmpi = livenow->room;
                livenow->room = livenow->next->room;
                livenow->next->room = tmpi;
                tmpi = livenow->type;
                livenow->type = livenow->next->type;
                livenow->next->type = tmpi;
                tmpi = livenow->time_live;
                livenow->time_live = livenow->next->time_live;
                livenow->next->time_live = tmpi;
                tmpi = livenow->leave_time;
                livenow->leave_time = livenow->next->leave_time;
                livenow->next->leave_time = tmpi;
                tmpi = livenow->arrive_time;
                livenow->arrive_time = livenow->next->arrive_time;
                livenow->next->arrive_time = tmpi;
            }
            if (livenow->next != NULL)
                livenow = livenow->next;
        }
    }
    return head;
}
void livedatecheck()
{
    printf("请选择入住信息的排序方式！\n");
    printf("[1]按时间顺序排序\n");
    printf("[2]按用户id排序\n");
    printf("[3]按房间号排序\n");
    printf("[4]按入住时长排序\n");
    printf("[5]按是否退房排序\n");
    printf("[6]按房间类型排序\n");

    int need;
    struct live_record* head = NULL;
    scanf("%d", &need);
    switch (need)
    {
        case 1:
            head = live_p_time();
            break;
        case 2:
            head = live_p_id();
            break;
        case 3:
            head = live_p_room();
            break;
        case 4:
            head = live_p_live();
            break;
        case 5:
            head = live_p_leave();
            break;
        case 6:
            head = live_p_type();
            break;
        default:
            printf("error!\n");
            break;
    }
    liveprint(head);
}
void liveprint(struct live_record *head)
{
    while (1)
    {
        struct time thetime = timestamp_to_time(head->arrive_time);
        printf("身份证号：%-030s  房间号：%d  房间类型：%d  入住时间：%-04d年%-02d月%-02d日%-02d时 入住时长：%-02d  ", head->ID, head->room, head->type, thetime.year, thetime.month, thetime.day, thetime.hour, head->time_live);
        if (head->leave_time == -1)
        {
            printf("退房时间：未退房\n");

        }
        else
        {
            thetime = timestamp_to_time(head->leave_time);
            printf("退房时间：%4d年%2d月%2d日%2d时\n", thetime.year, thetime.month, thetime.day, thetime.hour);

        }
        if (head->next == NULL)
            break;
        else
            head = head->next;
    }
}