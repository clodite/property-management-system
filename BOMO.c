#define _CRT_SECURE_NO_WARNINGS

#include "BBB.h"
#include "struct.h"
#include "header.h"
#include "function.h"
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
struct strbook* load_books(const char* bookdate)
{
    FILE* file = fopen(bookdate, "rt");
    if (file == NULL)
    {
        printf("���ݿ��ʧ�ܡ�\n");
        return NULL;
    }

    struct strbook* head = NULL;
    struct strbook* tail = NULL;

    while (1)
    {
        struct strbook* load_room = (struct strbook*)malloc(sizeof(struct strbook));
        if (load_room == NULL)
        {
            printf("�ڴ����ʧ�ܡ�\n");
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
        printf("���ݿ��ʧ�ܡ�\n");
        return NULL;
    }

    struct room* head = NULL;
    struct room* tail = NULL;

    while (1) 
    {
        struct room* load_room = (struct room*)malloc(sizeof(struct room));
        if (load_room == NULL) 
        {
            printf("�ڴ����ʧ�ܡ�\n");
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

	printf("������ԤԼʱ�䣨�� �� �գ�\n");
	scanf("%d %d %d", &timein.year, &timein.month, &timein.day);
	printf("ԤԼ�������ͱ�ţ�");
	scanf("%d", &typein);
	restart:
	printf("�Ƿ�ԤԼ�ӵ㷿��\n");
	printf("[1]��\n");
	printf("[2]��\n");
	scanf("%d", &timeroom);
	    if (timeroom == 1)
	{
		int lasttime = 0;
        timein.hour = 0;
    faq:
        printf("�������סʱ������סʱ��\n");
        scanf("%d %d", &lasttime, &timein.hour);
        if (lasttime < 1 && lasttime > 4 && timein.hour < 6 && timein.hour > 18)
        {
            printf("ʱ������סʱ�䲻����Լ�������������룡");
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
                printf("��ѡ���ʱ������޿շ���");
                break;
            }
        }
        if (check)
        {
            FILE* file = fopen("booklist.txt", "at");
            if (file == NULL)
            {
                printf("�ļ���ʧ�ܡ�\n");
            }
            else
            {
                printf("ԤԼ�ɹ���\n");
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

		printf("�������ס����\n");
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
                printf("��ѡ���ʱ������޿շ���");
                break;
            }
        }
        if (check)
        {
            FILE* file = fopen("booklist.txt", "at");
            if (file == NULL) 
            {
                printf("�ļ���ʧ�ܡ�\n");
            }
            else
            {
                printf("ԤԼ�ɹ���\n");
            }
            fprintf(file, "%d %d %d %s\n", timein_stamp, typein, lasttime * 24 - 1,userid);
            fclose(file);

            return 0;
        }

	}
	else
	{
		printf("ѡ�������������ȷ����");
		goto restart;
	}

}
