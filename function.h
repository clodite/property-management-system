// 在这里放函数声明喵
#pragma once
#include "struct.h"
// #include "header.h"
//struct time timestamp_to_time(int t);
//int time_to_timestamp(struct time);
struct room *create_room(int num, int type, int price);																																						   // 创建新房间
struct user *create_user(int type, char ID[30], char password[30], char email[30], char name[30], int age, char call[20], char IDnum[30], int room, int arrive_time, int time_live, int leave_time, int card); // 创建账户
int Count_BasicYear(struct time time1);
int Count_EndYear(struct time time1);
int JudgeYear(int x);
void check_in();
void menu_manager(char ID[30], char password[30], int type, char name[30], int age, char call[20], int card);
void menu_front(char ID[30], char password[30], int type, char name[30], int age, char call[20], int card);
void menu_custom(char ID[30], char password[30], int type, char name[30], int age, char call[20], int card);

int id_strcmp(const char *a, const char *b); // [ID] 字符串比较：小->大：1；大->小：-1；相等：0

// int bookings_cancel(long long my_book_id); // [预约] 取消
void bookings_free(struct strbook *head); // [预约] 释放内存
// struct strbook* bookings_view(long long book_id, int time, int roomtype, int last, char id[30], int status);   // [预约] 查询：-1不指定
struct strbook *bookings_sort(int type, int order);																																					// [预约] 排序：[type]: 1.预约唯一id 2.入住时间 3.房间类型 4.居住多久 5.预约人id 6.预约状态 [order]: 增/减/1/-1
struct strbook *bookings_sort_merge_sort(struct strbook *head, int type, int order);																												// [预约] 归并排序
void bookings_sort_split(struct strbook *head, struct strbook **left, struct strbook **right);																										// [预约] 归并排序之一
struct strbook *bookings_sort_merge(struct strbook *left, struct strbook *right, int type, int order);																								// [预约] 归并排序之二
int bookings_sort_cmp_nodes(struct strbook *a, struct strbook *b, int type, int order);																												// [预约] 节点比较
int bookings_count_times(long long book_id, int time, int roomtype, int last, char id[30], int status);																								// [预约] 次数统计：-1不指定
int bookings_count_times_range(long long m_book_id, long long M_book_id, int m_time, int M_time, int m_roomtype, int M_roomtype, int m_last, int M_last, char m_id[30], char M_id[30], int status); // [预约] 范围次数统计：-1不指定
int bookings_count_guest(long long book_id, int time, int roomtype, int last, int status);																											// [预约] 人数统计：-1不指定
int bookings_count_guest_range(long long m_book_id, long long M_book_id, int m_time, int M_time, int m_roomtype, int M_roomtype, int m_last, int M_last, int status);								// [预约] 范围人数统计：-1不指定

void write_room(const char *room, struct room *head);					// 将链表数据写入users文件中
void freelist_room(struct room *head);									// 释放房间信息链表内存

struct room *search_room(struct room *head, int num);					// 遍历链表查找ID对应结构体的函数，返回账户结构体地址
void init_rooms(const char *roomdate);									// 初始化房间
struct user *load_users(const char *users);								// 将用户数据全部读取存入链表，返回首地址
void write_users(const char *users, struct user *head);					// 将链表数据写入users文件中
void freelist_user(struct user *head);									// 释放链表内存
struct user *search_account(struct user *head, char ID[30]);			// 遍历链表查找ID对应结构体的函数，返回账户结构体地址
int change_password(struct user *head, char ID[30], char password[30]); // 给客人和前台改密码的函数
int search_card(struct user *head, char ID[30], char password[30]);		// 查询card值
int change_card(struct user *head, char ID[30]);						// 管理员用修改等级
int super_change_password(struct user *head, char ID[30]);				// 给管理员用的改密码函数，可以输入任意ID以更改其对应的密码

int get_account_type(const char *username, const char *password);
int add_account(const char *username, const char *password);
void showCustomMenu();
bool isInArea(int x, int y, int areaX, int areaY, int width, int height);
void showRoom(struct room *head);
//void show_message_window(const char *message);
void showFrontMenu();
void showAdministratorMenu();
struct room* findemptyroom(int type);

#ifdef __cplusplus
extern "C"
{
#endif
	struct room *load_rooms(const char *roomdate);
	void free_rooms(struct room *head);
	struct strbook *bookings_view(long long book_id, int ttime, int roomtype, int last, char id[30], int status);
	struct strbook *read_booklist_file(const char *target_id);
	int bookings_cancel(long long my_book_id);
	int custom_book(char *userid,int in_roomtype,int in_time,int getin_time,int clock_check);
	struct time timestamp_to_time(int t);
	int time_to_timestamp(struct time);
	int change_room(struct room *head,int num1,int num2,int type,int price,int size,int state) ;// 改变房间数据
	struct room* give_room(int in_type,char* in_userid,int in_time,int live_time,int clock_check);
	void show_message_window(const char *message);
	struct live_record* load_lives(const char* roomdate);
#ifdef __cplusplus
}
#endif
