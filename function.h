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

// C
int cancel_my_booking(long long my_book_id);         // 取消自己的预约
struct strbook* view_my_booking(char my_id[30]);     // 查询某人所有预约
struct strbook* view_all_bookings();                 // 查询所有客人预约


struct strbook* load_strbook();                      // 加载预约信息

struct user* load_users(const char* users);  //将用户数据全部读取存入链表，返回首地址
void write_users(const char* users, struct user* head); //将链表数据写入users文件中 
void freelist_user(struct user* head);     //释放用户信息这个链表的内存 
void change_password(struct user* temp);   //给客人和前台使用的更改密码函数，只能修改自己的账户，需要提前知道账户的地址 
struct user* search_account(struct user* head);    //遍历链表查找ID对应结构体的函数，返回账户结构体地址 
void super_change_password(struct user* head);     //给管理员用的改密码函数，可以输入任意ID以更改其对应的密码
void change_card(struct user* head);               //管理员用的更改客户等级的函数，输入ID更改对应等级
void print_user(struct user* head);                //管理员使用的查询全部用户信息,只是输出可能还得考虑前端
void register_user(struct user* head);             //注册系统,因为还没考虑前端所以只是个可以跑的丐版
struct user* load_in(struct user* head);    //暂时没啥用 不过登录可能会用到的先搜寻账户，然后核对密码正确才返回对应账号指针的函数 

