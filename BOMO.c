#define _CRT_SECURE_NO_WARNINGS

#include "BBB.h"
#include "struct.h"
#include "header.h"
#include "function.h"
/*struct room* findemptyroom(int type1)
{
    struct room* head = load_rooms("room.txt");	
    struct room* ret_head = NULL;
    struct room* ret_now = NULL;
	printf("1");
	
    while (1)
    {
       if (head->type == type1 && head->state == 0)
	   {
		   ret_head = head;
		   ret_now = head;
		   break;
	   }
		else
		{
			head = head->next;
		}
    }
	printf("2");
	
    while (head->next !=NULL && ret_head != NULL)
    {
        if (head->type == type1 && head->state == 0)
        {
            ret_now->next = head;
            ret_now = ret_now->next;
            head = head->next;
			
        }
        else
        {
            head = head->next;
			printf("4");
			
        }
		if(head->next == NULL)
			break;
		
    }
	printf("3");
	
    ret_now->next = NULL;
    return ret_head;
}*/
struct room* findemptyroom(int type1) {
	struct room* head = load_rooms("room.txt");
	printf("%d",head->num);
	
	struct room* ret_head = NULL;
	struct room* ret_tail = NULL;
	struct room* current = head;
	
	while (current != NULL) {
		if (current->type == type1 && current->state == 0) {
			struct room* new_node = (struct room*)malloc(sizeof(struct room));
			new_node->type = current->type;
			new_node->state = current->state;
			new_node->num = current->num;
			new_node->price = current->price;
			new_node->size = current->size;
			new_node->next = NULL;
			
			if (ret_head == NULL) {
				ret_head = ret_tail = new_node;
			} else {
				ret_tail->next = new_node;
				ret_tail = new_node;
			}
		}
		current = current->next; 
	}
	printf("%d",ret_head->num);
	return ret_head;
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
        printf("数据库打开失败111。\n");
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


        int result = fscanf(file, "%lld %d %d %d %s %d", &load_room->book_id,&load_room->time, &load_room->roomtype, &load_room->last,load_room->id,&load_room->status);
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
        printf("数据库打开失败222。\n");
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
        printf("数据库打开失败333。\n");
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


        int result = fscanf(file, "%s %d %d %d %d %d", load_room->ID, &load_room->room, &load_room->type, &load_room->arrive_time, &load_room->time_live, &load_room->leave_time);
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
    struct room *roomnow = load_rooms("room.txt");
	
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
int custom_book(char *userid,int in_roomtype,int in_time,int getin_time,int clock_check) //clock_check输入1是钟点房，0按天预订。参数分别为：用户id 房间类型 居住时长 入住时间 是不是钟点房;如果不是钟点房那个，输入的居住时长请传入天数 * 24 - 1;
{
	FILE *file_t = fopen("booklist.txt", "r");
	char line[1024];
	char *last_line = NULL;
	long long last_book_id;
	
	while (fgets(line, sizeof(line), file_t)) {
		last_line = strdup(line);
	}
	fclose(file_t);
	
	last_book_id = strtoll(last_line, NULL, 10);
	last_book_id++;
	free(last_line);
    struct time timein = timestamp_to_time(getin_time);
    int timein_stamp;
    int typein = in_roomtype;
	//int lastin;
	int timeroom=clock_check;

    if (timeroom == 1)
	{
        int lasttime = in_time;
	    if (lasttime < 1 && lasttime > 4 && timein.hour < 6 && timein.hour > 18)
	    {
	        return -1;
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
	            return -2;
	            break;
	        }
	    }
	    if (check)
	    {
	        FILE* file = fopen("booklist.txt", "at");
	        fprintf(file, "%lld %d %d %d %s %d\n",last_book_id, timein_stamp, typein, lasttime, userid,1);
	        fclose(file);
			
	        return 0;
	    }
	}
    else if (timeroom == 0)
	{
        int lasttime = in_time;
        timein.hour = 13;

        int sum = findroomcount(typein);
        timein_stamp = time_to_timestamp(timein);
        int roomremain[20000] = { sum };
        int check = 1;
        roombookcheck(roomremain, typein,sum);
        roomlivecheck(roomremain, typein, sum);

        for (int i = timein_stamp;i < timein_stamp + lasttime;i++)
        {
            if (roomremain[i] == 0)
            {
                check = 0;
                return -2;
                break;
            }
        }
        if (check)
        {
            FILE* file = fopen("booklist.txt", "at");
            fprintf(file, "%lld %d %d %d %s %d\n", last_book_id, timein_stamp, typein, lasttime, userid, 1);
            fclose(file);

            return 0;
        }

	}
	else
	{
        return -1;
	}
	return 0;
}
struct room* give_room(int in_type,char* in_userid,int in_time,int live_time,int clock_check)//传入1是钟点房 0是按天，按天请传入天数 * 24 -1
{
    int needtype = in_type;
    char userid[30];
    strcpy(userid, in_userid);
    struct time timein = timestamp_to_time(in_time);
    int timein_stamp;
    //int timefor = 0;
    int livetype = clock_check;
    if (livetype == 0)
    {
		
        int lasttime = live_time;
        int sum = findroomcount(needtype);
        timein_stamp = time_to_timestamp(timein);
        int roomremain[20000] = { sum };
        int check = 1;
        roombookcheck(roomremain, needtype, sum);
        roomlivecheck(roomremain, needtype, sum);
        int fix = timein.hour - 13;
        for (int i = timein_stamp;i < timein_stamp + lasttime - fix;i++)
        {

            if (roomremain[i] == 0)
            {
                check = 0;
                return NULL;
                break;
            }
        }
        if (check)
        {
            return findemptyroom(needtype);
        }
    }
    else if (livetype == 1)
    {
        if (timein.hour < 6 && timein.hour > 18)
        {
            return NULL;
        }
        int lasttime = live_time;
        if (lasttime < 1 && lasttime > 4 )
        {
            return NULL;
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
                return NULL;
                break;
            }
        }
        if (check)
        {
            return findemptyroom(needtype);
        }


    }
    else
    {
        return NULL;
    }
	
	return NULL;
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
        printf("身份证号：%s  房间号：%d  房间类型：%d  入住时间：%04d年%02d月%02d日%02d时 入住时长：%02d  ", head->ID, head->room, head->type, thetime.year, thetime.month, thetime.day, thetime.hour, head->time_live);
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
