#include "nb.h"

void check_in()
{
    FILE* date;
    date = fopen("date", "rt+");
    if (date == NULL)
    {
        printf("���ݿ��ʧ�ܡ�");
        return 0;
    }



getinstart:
    printf("user name:");
    char id[30];
    char password[30];
    int check = 0;
    char id_check[30];
    int user_type;
    char password_check[30];
    scanf("%s", &id);
    printf("password:");
    scanf("%s", &password);
    while (!feof(date) && !check)//���ļ����Ҹ��˺�
    {
        fgets(id_check, 30, date);//��ȡid
        if (!strcmp(id_check, id))
        {
            check = 1;//1Ϊ�ɹ��ҵ��˺�
        }
        else
        {

        }
    }
    if (!check)
    {
        printf("δ�ҵ��˺ţ������˻����Ƿ�ƴд����\n");
        goto getinstart;
    }
    else
    {
        int try = 3;
        while (try)
        {
            if (strcmp(password_check, password))
            {
                printf("����������������룡\n");
                printf("password:");
                scanf("%s", password);
                try--;
            }
            else
            {
                printf("��¼�ɹ�����ӭ������%s", &id);
                if (user_type == 0)
                    menu_manger();
                else if (user_type == 1)
                    menu_front();
                else if (user_type == 2)
                    menu_custom();
                else
                {
                    printf("�˻����ʹ���");
                    break;
                }
            }
        }
        printf("����������࣡");
    }
    fclose(date);
}
