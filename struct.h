#pragma once
#include "header.h"
#define type_1 "大床房"
#define type_2 "双床房"
#define type_3 "电竞房" // ？

struct time
{
    int year;
    int month;
    int day;
    int hour;
};

struct user
{
    char ID[30];       // id
    int type;          // 用户类型 0=>管理员 1=>用户 2=>客人
    char card[15];     // 卡片类型
    char password[30]; // 密码
    char email[30];    // 邮箱
    char name[30];     // 姓名
    struct user *next; // 指向下一个节点的指针
};

struct custom
{
    char name[30];   // 名字
    int age;         // 年龄
    char call[20];   // 电话
    int room;        // 入住房间号
    int arrive_time; // 入住时间 按时间戳计算
    int time_live;   // 入住时长 在办理入住时计算
    int leave_time;  // 退房时间 未退房记作-1
    int card;        // 客户等级
    // char booktime[30];  // 预定时间
    struct custom *next; // 指向下一个节点的指针
};

struct room
{
    int num;   // 房号
    int type;  // 客房类型 用数字替代 用函数判定
    int price; // 客房价格
    // int state;          // 客房状态 0=>空闲 1=>已预定 2=>已入住
    // struct user *custom;// 入住客人的数据
    struct room *next; // 指向下一个节点的指针
};

struct room *create_room(int num, int type, int price) // 创建新房间
{
    struct room *newroom = (struct room *)malloc(sizeof(struct room));
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

struct user *create_user(int type, char ID[30], char password[30], char email[30], char name[30]) // 创建账户
{
    struct user *newuser = (struct user *)malloc(sizeof(struct user));
    if (!newuser)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    newuser->next = NULL;
    strcpy(newuser->ID, ID);
    newuser->type = type;
    newuser->password[30] = password[30];
    newuser->email[30] = email[30];
    newuser->name[30] = name[30];
    strcpy(newuser->card, "none");
    return newuser;
}

struct custom *create_custom(char name[30], int age, char call[20], int room, int arrive_time, int time_live, int leave_time, int card) // 创建客人
{
    struct custom *newcustom = (struct custom *)malloc(sizeof(struct custom));
    if (!newcustom)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    strcpy(newcustom->name, name);
    newcustom->age = age;
    strcpy(newcustom->call, call);
    newcustom->room = room;
    newcustom->arrive_time = arrive_time;
    newcustom->time_live = time_live;
    newcustom->leave_time = leave_time;
    newcustom->card = card;
    newcustom->next = NULL;
    return newcustom;
}