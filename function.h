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
struct user* load_users(const char* users);  //将用户数据全部读取存入链表，返回首地址
void write_users(const char* users, struct user* head); //将链表数据写入users文件中 
void freelist_user(struct user* head);     //释放用户信息这个链表的内存 
struct user* search_account(struct user* head, char ID[30]); //遍历链表查找ID对应结构体的函数，返回账户结构体地址
int change_password(struct user* head, char ID[30], char password[30]); //给客人和前台改密码的函数
int super_change_password(struct user* head, char ID[30]); //给管理员用的改密码函数，可以输入任意ID以更改其对应的密码 
int change_card(struct user* head, char ID[30]); //管理员用修改等级
int search_card(struct user* head, char ID[30], char password[30]); //查询card值
