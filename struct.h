#pragma once
#include "header.h"
#define type_1 "�󴲷�"
#define type_2 "˫����"
#define type_3 "�羺��" // ��

struct time
{
    int year;
    int month;
    int day;
    int hour;
};

struct user
{
    char ID[30];       // id
    int type;          // �û����� 0=>����Ա 1=>�û� 2=>����
    char card[15];     // ��Ƭ����
    char password[30]; // ����
    char email[30];    // ����
    char name[30];     // ����
    struct user *next; // ָ����һ���ڵ��ָ��
};

struct custom
{
    char name[30];   // ����
    int age;         // ����
    char call[20];   // �绰
    int room;        // ��ס�����
    int arrive_time; // ��סʱ�� ��ʱ�������
    int time_live;   // ��סʱ�� �ڰ�����סʱ����
    int leave_time;  // �˷�ʱ�� δ�˷�����-1
    int card;        // �ͻ��ȼ�
    // char booktime[30];  // Ԥ��ʱ��
    struct custom *next; // ָ����һ���ڵ��ָ��
};

struct room
{
    int num;   // ����
    int type;  // �ͷ����� ��������� �ú����ж�
    int price; // �ͷ��۸�
    // int state;          // �ͷ�״̬ 0=>���� 1=>��Ԥ�� 2=>����ס
    // struct user *custom;// ��ס���˵�����
    struct room *next; // ָ����һ���ڵ��ָ��
};

struct room *create_room(int num, int type, int price) // �����·���
{
    struct room *newroom = (struct room *)malloc(sizeof(struct room));
    if (!newroom)
    {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newroom->num = num;
    // newroom->custom = NULL;
    newroom->type = type;
    newroom->price = price;
    // newroom->state = 0;
    newroom->next = NULL;
    return newroom;
}

struct user *create_user(int type, char ID[30], char password[30], char email[30], char name[30]) // �����˻�
{
    struct user *newuser = (struct user *)malloc(sizeof(struct user));
    if (!newuser)
    {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newuser->next = NULL;
    strcpy(newuser->ID, ID);
    newuser->type = type;
    newuser->password[30] = password[30];
    newuser->email[30] = email[30];
    newuser->name[30] = name[30];
    strcpy(newuser->card, "none");
    return newuser;
}

struct custom *create_custom(char name[30], int age, char call[20], int room, int arrive_time, int time_live, int leave_time, int card) // ��������
{
    struct custom *newcustom = (struct custom *)malloc(sizeof(struct custom));
    if (!newcustom)
    {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    strcpy(newcustom->name, name);
    newcustom->age = age;
    strcpy(newcustom->call, call);
    newcustom->room = room;
    newcustom->arrive_time = arrive_time;
    newcustom->time_live = time_live;
    newcustom->leave_time = leave_time;
    newcustom->card = card;
    newcustom->next = NULL;
    return newcustom;
}