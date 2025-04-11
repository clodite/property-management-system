#pragma once
struct strbook *create_book(int num, int type, int last); // 创建新预约
int findroomcount(int type);                              // 检索某个类型的房间一共多少个
void roombookcheck(int *rooms, int type, int sum);        // 检索某个类型的房间一共多少个
struct strbook *load_books(const char *bookdate);
struct live_record* load_lives(const char* roomdate);
int custom_book(char *userid,int in_roomtype,int in_time,int getin_time,int clock_check);
void liveprint(struct live_record *head);
// 预约房间 注意：只能从6~18点预约，钟点房只能预约1~4小时。正常预约是下午1点到第二天12点。
