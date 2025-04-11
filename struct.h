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
    int num;           // 房号
    int type;          // 客房类型 用数字替代 用函数判定
    int price;         // 客房价格
    int size;          // 客房面积
    int state;         // 客房状态 0=>空闲 1=>已预定 2=>已入住
    struct room *next; // 指向下一个节点的指针
};

struct user
{
    char ID[30]; // 身份证号
    // char password[30];   // 密码
    // int type;            // 用户类型 0=>管理员 1=>用户 2=>客人
    char name[30];     // 真实姓名
    int age;           // 真实年龄
    char call[20];     // 用户电话
    int card;          // 客户等级
    struct user *next; // 指向下一个节点的指针
};

struct living
{
    char ID[30];           // id
    int room;              // 房间号
    int checking_in_time;  // 入住时间 按时间戳计算
    int staying_time;      // 入住时长 在办理入住时填写
    int checking_out_time; // 退房时间 未退房记作-1
};

struct strbook
{
    long long book_id;
    int time;             //  入住时间
    int roomtype;         //  房间类型
    int last;             //  居住多久
    char id[30];          //  预约人id
    int status;           //  预约状态
    struct strbook *next; //    无需多言
};

struct Button
{
    int x, y, width, height;
    const char *text;
};

struct live_record
{
	char ID[30];       // id
	int room;          // 入住房间号
	int type;           //入住房间类型
	int arrive_time;   // 入住时间 按时间戳计算
	int time_live;     // 入住时长 在办理入住时计算
	int leave_time;    // 退房时间 未退房记作-1
	struct live_record* next; // 指向下一个节点的指针
};
