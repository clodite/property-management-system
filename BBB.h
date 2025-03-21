#pragma once
struct strbook* create_book(int num, int type, int last); // 创建新预约
int findroomcount(int type); // 检索某个类型的房间一共多少个
void roombookcheck(int *rooms[],int type); // 检索某个类型的房间一共多少个
struct strbook* load_books(const char* bookdate);

void custom_book();
// 预约房间 注意：只能从6~18点预约，钟点房只能预约1~4小时。正常预约是下午1点到第二天12点。



struct strbook
{
    int time;       //  入住时间
    int roomtype;   //  房间类型
    int last;       //  居住多久
    char id[30];    //  预约人id
    struct strbook* next; //    无需多言
};