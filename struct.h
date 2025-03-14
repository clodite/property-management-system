#pragma once
#include "header.h"

struct time
{
    int year;
    int month;
    int day;
    int hour;
};

struct room
{
    int num;   // 房号
    int type;  // 客房类型 用数字替代 用函数判定
    int price; // 客房价格
    int size;  // 客房面积
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

struct user
{
    char ID[30];       // id
    int type;          // 用户类型 0=>管理员 1=>用户 2=>客人
    char password[30]; // 密码
    char email[30];    // 邮箱
    char name[30];     // 姓名
    int age;           // 年龄
    char call[20];     // 电话
    int room;          // 入住房间号
    int arrive_time;   // 入住时间 按时间戳计算
    int time_live;     // 入住时长 在办理入住时计算
    int leave_time;    // 退房时间 未退房记作-1
    int card;          // 客户等级
    // char booktime[30];  // 预定时间
    struct user *next; // 指向下一个节点的指针
};
struct user *create_user(int type, char ID[30], char password[30], char email[30], char name[30], int age, char call[20], int room, int arrive_time, int time_live, int leave_time, int card) // 创建账户
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
    strcpy(newuser->name, name);
    newuser->age = age;
    strcpy(newuser->call, call);
    newuser->room = room;
    newuser->arrive_time = arrive_time;
    newuser->time_live = time_live;
    newuser->leave_time = leave_time;
    newuser->card = card;
    newuser->next = NULL;
    return newuser;
}
