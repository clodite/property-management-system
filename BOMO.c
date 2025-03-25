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
    for (int i = 0;i < 20000;i++)
        rooms[i] = sum;
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
    if (livetype == 1)
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
    else if (livetype == 2)
    {
        ;
    }
    else
    {
        printf("选择错误！请输入正确数字");
        goto restart;
    }
}
