#pragma once
#include <stdio.h>
#include <stdlib.h>
#define type_1 = "大床房"
#define type_2 = "双床房"
#define type_3 = "电竞房" //？

typedef struct user
{
    char ID[30];            // id
    int type;               // 用户类型 0=>管理员 1=>用户 2=>客人
    char card[15];          // 卡片类型
    char password[30];      // 密码
    char email[30];         // 邮箱
    char name[30];          // 姓名
    struct user* next;      // 指向下一个节点的指针


};
typedef struct custom
{
    char name[30];          // 名字
    int age;                // 年龄
    char call[20];          // 电话
    char time_in[30];       // 入住时间
    int time_live;          // 入住时长
    char card[15];          // 卡片类型
    char booktime[30];       // 预定时间


};
typedef struct room
{
    int type;           // 客房类型 用数字替代 用函数判定
    int price;          // 客房价格
    int state;          // 客房状态 0=>空闲 1=>已预定 2=>已入住
    struct user* custom;// 入住客人的数据
    struct room* next;  // 指向下一个节点的指针
};
struct room* createroom(int type,int price)   //创建新房间
{
    struct room* newroom = (struct room*)malloc(sizeof(struct room));
    if (!newroom) {
        printf("内存分配失败\n");
        exit(1);
    }
    newroom->next = NULL;
    newroom->custom = NULL;
    newroom->type = type;
    newroom->price = price;
    newroom->state = 0;
    return newroom;
}
struct user* createuser(int type, char ID[30], char password[30],char email[30],char name[30] )   //创建账户
{
    struct user* newuser = (struct user*)malloc(sizeof(struct user));
    if (!newuser) {
        printf("内存分配失败\n");
        exit(1);
    }
    newuser->next = NULL;
    newuser->ID[30] = ID;
    newuser->type = type;
    newuser->password[30] = password[30];
    newuser->email[30] = email[30];
    newuser->name[30] = name[30];
    newuser->card[15] = "none";
    return newuser;
}
