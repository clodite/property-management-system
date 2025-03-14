// 在这里放函数声明喵
#pragma once
#include "struct.h"
struct time timestamp_to_time(int t);
int time_to_timestamp(struct time);
struct room *create_room(int num, int type, int price);                                                                                  // 创建新房间
struct user *create_user(int type, char ID[30], char password[30], char email[30], char name[30]);                                       // 创建账户
struct custom *create_custom(char name[30], int age, char call[20], int room, int arrive_time, int time_live, int leave_time, int card); // 创建客人