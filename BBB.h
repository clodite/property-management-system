#pragma once
struct strbook* create_book(int num, int type, int last); // ������ԤԼ
int findroomcount(int type); // ����ĳ�����͵ķ���һ�����ٸ�
void roombookcheck(int *rooms[],int type); // ����ĳ�����͵ķ���һ�����ٸ�
struct strbook* load_books(const char* bookdate);

void custom_book();
// ԤԼ���� ע�⣺ֻ�ܴ�6~18��ԤԼ���ӵ㷿ֻ��ԤԼ1~4Сʱ������ԤԼ������1�㵽�ڶ���12�㡣



struct strbook
{
    int time;       //  ��סʱ��
    int roomtype;   //  ��������
    int last;       //  ��ס���
    char id[30];    //  ԤԼ��id
    struct strbook* next; //    �������
};