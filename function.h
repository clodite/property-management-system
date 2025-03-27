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

int cancel_my_booking(long long my_book_id); // 取消自己的预约
struct strbook* view_bookings(long long book_id, int time, int roomtype, int last, char id[30], int status);   // 按条件查询预约（-1不指定）
struct strbook* sort_bookings(int type_x, int order_x, int type_y, int order_y); // 按条件排序预约：一二排序条件；增/减/不排序/1/-1/0
int count_bookings(); // 统计预约（功能建设中）

void write_room(const char* room, struct room* head); //将链表数据写入users文件中
void freelist_room(struct room* head); //释放房间信息链表内存
int change_room(struct room* head); //改变房间数据
struct room* search_room(struct room* head, int num); //遍历链表查找ID对应结构体的函数，返回账户结构体地址
void init_rooms(const char* roomdate); //初始化房间

