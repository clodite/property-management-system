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

int cancel_bookings(long long my_book_id); // [预约] 取消
void free_bookings(struct strbook* head); // [预约] 释放内存
struct strbook* view_bookings(long long book_id, int time, int roomtype, int last, char id[30], int status);   // [预约] 查询：-1不指定
struct strbook* sort_bookings(int type, int order); // [预约] 排序：[type]: 1.预约唯一id 2.入住时间 3.房间类型 4.居住多久 5.预约人id 6.预约状态 [order]: 增/减/1/-1
struct strbook* bookings_merge_sort(struct strbook* head, int type, int order); // [预约] 归并排序
void bookings_split(struct strbook* head, struct strbook** left, struct strbook** right); // [预约] 归并排序之一
struct strbook* bookings_merge(struct strbook* left, struct strbook* right, int type, int order); // [预约] 归并排序之二
int book_compare_nodes(struct strbook* a, struct strbook* b, int type, int order); // [预约] 节点比较
int book_compare_nodes_str(const char* a, const char* b); // [预约] 字符串节点比较
int count_bookings(long long book_id, int time, int roomtype, int last, char id[30], int status); // [预约] 点统计：-1不指定
int count_bookings_range(long long m_book_id, long long M_book_id, int m_time, int M_time, int m_roomtype, int M_roomtype, int m_last, int M_last, char m_id[30], char M_id[30], int included_status) // [预约] 范围统计：-1不指定

void write_room(const char* room, struct room* head); //将链表数据写入users文件中
void freelist_room(struct room* head); //释放房间信息链表内存
int change_room(struct room* head); //改变房间数据
struct room* search_room(struct room* head, int num); //遍历链表查找ID对应结构体的函数，返回账户结构体地址
void init_rooms(const char* roomdate); //初始化房间
struct user* load_users(const char* users);  //将用户数据全部读取存入链表，返回首地址
void write_users(const char* users, struct user* head); //将链表数据写入users文件中
void freelist_user(struct user* head); //释放链表内存
struct user* search_account(struct user* head, char ID[30]); //遍历链表查找ID对应结构体的函数，返回账户结构体地址 
int change_password(struct user* head, char ID[30], char password[30]); //给客人和前台改密码的函数
int search_card(struct user* head, char ID[30], char password[30]); //查询card值
int change_card(struct user* head, char ID[30]); //管理员用修改等级
int super_change_password(struct user* head, char ID[30]); //给管理员用的改密码函数，可以输入任意ID以更改其对应的密码 
