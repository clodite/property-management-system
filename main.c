#include <stdio.h>
#include <stdlib.h>
#include "nb.h"





struct room* createNode(int data)//创建新房间
{
    struct room* newroom = (struct room*)malloc(sizeof(struct room));
    if (!newroom) {
        printf("内存分配失败\n");
        exit(1);
    }
    newroom->next = NULL;
    return newroom;
}
int main() 
{
   

   

    return 0;
}