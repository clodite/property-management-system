#define _CRT_SECURE_NO_WARNINGS
#include "struct.h"
#include "header.h"
#include "function.h"
struct user* create_user(int type, char ID[30], char password[30], char email[30], char name[30], int age, char call[20], int room, int arrive_time, int time_live, int leave_time, int card) // 创建账户
{
    struct user* newuser = (struct user*)malloc(sizeof(struct user));
    if (!newuser)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    newuser->next = NULL;
    strcpy(newuser->ID, ID);
    newuser->type = type;
    newuser->password[30] = password[30];
    newuser->name[30] = name[30];
    strcpy(newuser->name, name);
    newuser->age = age;
    strcpy(newuser->call, call);
    newuser->card = card;
    newuser->next = NULL;
    return newuser;
}
struct room* create_room(int num, int type, int price) // 创建新房间
{
    struct room* newroom = (struct room*)malloc(sizeof(struct room));
    if (!newroom)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    newroom->num = num;
    // newroom->custom = NULL;
    newroom->type = type;
    newroom->price = price;
    // newroom->state = 0;
    newroom->next = NULL;
    return newroom;
}
