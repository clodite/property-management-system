// 在这里放函数声明喵
#pragma once
#include "struct.h"
struct time timestamp_to_time(int t);
int time_to_timestamp(struct time);
struct room *create_room(int num, int type, int price);                                                                                                                                                        // 创建新房间
struct user *create_user(int type, char ID[30], char password[30], char email[30], char name[30], int age, char call[20], char IDnum[30], int room, int arrive_time, int time_live, int leave_time, int card); // 创建账户
int Count_BasicYear(struct time time1);
int Count_EndYear(struct time time1);
int JudgeYear(int x);
void check_in();
void menu_manager(char ID[30], char password[30], int type, char name[30], int age, char call[20], int card);
void menu_front(char ID[30], char password[30], int type, char name[30], int age, char call[20], int card);
void menu_custom(char ID[30], char password[30], int type, char name[30], int age, char call[20], int card);

// 客人

// 取消自己的预约
void cancel_my_booking (char ID[30]);
// 查询自己预约信息
void view_my_booking (char ID[30]);

// 前台

// 查询所有预约信息
void view_all_bookings ();

// 管理员

// 统计预约信息
void function_under_construction ();
