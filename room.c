#include "function.h"
#include "header.h"
#include "struct.h"

void write_room(const char *room, struct room *head) // 将链表数据写入users文件中
{
	FILE *file = fopen(room, "wt");
	if (file == NULL)
	{
		perror("fail to open\n");
	}
	struct room *temp = head;
	while (temp != NULL)
	{
		fprintf(file, "%d %d %d %d %d\n", temp->num, temp->type, temp->price, temp->size, temp->state);
		temp = temp->next;
	}
	fclose(file);
}

void freelist_room(struct room *head) // 释放房间信息链表内存
{
	struct room *temp = NULL;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

void init_rooms(const char *roomdate) // 初始化房间
{
	FILE *file = fopen(roomdate, "wt");
	if (file == NULL)
	{
		printf("数据库打开失败。\n");
		return;
	}
	int n = 0;
	printf("房间总数？\n");
	scanf("%d", &n);
	// int arr[1000][5];
	int i = 0;
	int num, type, price, size, state;
	for (i = 0; i < n; i++)
	{
		scanf("%d %d %d %d %d", &num, &type, &price, &size, &state);
		fprintf(file, "%d %d %d %d %d\n", num, type, price, size, state);
	}
	fclose(file);
}

struct room *search_room(struct room *head, int num) // 遍历链表查找ID对应结构体的函数，返回账户结构体地址
{
	struct room *temp = head;
	int flag = 1;
	while (num != temp->num)
	{
		temp = temp->next;
		if (temp->next == NULL)
		{
			printf("error\n");
			flag = 0;
			break;
		}
	}
	if (flag == 1)
	{
		return temp;
	}
	else
	{
		printf("ID错误\n");
	}
	return NULL;
}

int change_room(struct room *head,int num1,int num2,int type,int price,int size,int state) // 改变房间数据
{
	//printf("输入？");
	//scanf("%d", &num1);
	struct room *temp = search_room(head, num1);
	if(temp==NULL)
	{
		return 1;
	}
	//scanf("%d %d %d %d %d", &num2, &type, &price, &size, &state);
	temp->num = num2;
	temp->type = type;
	temp->price = price;
	temp->size = size;
	temp->state = state;
	write_room("room.txt",head);
	
	return 0;
}

void write_room(const char *room, struct room *head); // 将链表数据写入users文件中
void freelist_room(struct room *head);				  // 释放房间信息链表内存
int change_room(struct room *head,int num1,int num2,int type,int price,int size,int state);					  // 改变房间数据
struct room *search_room(struct room *head, int num); // 遍历链表查找ID对应结构体的函数，返回账户结构体地址
void init_rooms(const char *roomdate);				  // 初始化房间
