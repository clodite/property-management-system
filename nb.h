#pragma once
#include <stdio.h>
#include <stdlib.h>
#define type_1 = "�󴲷�"
#define type_2 = "˫����"
#define type_3 = "�羺��" //��

typedef struct user
{
    char ID[30];            // id
    int type;               // �û����� 0=>����Ա 1=>�û� 2=>����
    char card[15];          // ��Ƭ����
    char password[30];      // ����
    char email[30];         // ����
    char name[30];          // ����
    struct user* next;      // ָ����һ���ڵ��ָ��


};
typedef struct custom
{
    char name[30];          // ����
    int age;                // ����
    char call[20];          // �绰
    char time_in[30];       // ��סʱ��
    int time_live;          // ��סʱ��
    char card[15];          // ��Ƭ����
    char booktime[30];       // Ԥ��ʱ��


};
typedef struct room
{
    int type;           // �ͷ����� ��������� �ú����ж�
    int price;          // �ͷ��۸�
    int state;          // �ͷ�״̬ 0=>���� 1=>��Ԥ�� 2=>����ס
    struct user* custom;// ��ס���˵�����
    struct room* next;  // ָ����һ���ڵ��ָ��
};
struct room* createroom(int type,int price)   //�����·���
{
    struct room* newroom = (struct room*)malloc(sizeof(struct room));
    if (!newroom) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newroom->next = NULL;
    newroom->custom = NULL;
    newroom->type = type;
    newroom->price = price;
    newroom->state = 0;
    return newroom;
}
struct user* createuser(int type, char ID[30], char password[30],char email[30],char name[30] )   //�����˻�
{
    struct user* newuser = (struct user*)malloc(sizeof(struct user));
    if (!newuser) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newuser->next = NULL;
    newuser->ID[30] = ID;
    newuser->type = type;
    newuser->password[30] = password[30];
    newuser->email[30] = email[30];
    newuser->name[30] = name[30];
    newuser->card[15] = "none";
    return newuser;
}
