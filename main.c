#include <stdio.h>
#include <stdlib.h>
#include "nb.h"





struct room* createNode(int data)//�����·���
{
    struct room* newroom = (struct room*)malloc(sizeof(struct room));
    if (!newroom) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newroom->next = NULL;
    return newroom;
}
int main() 
{
   

   

    return 0;
}