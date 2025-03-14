#include "struct.h"
#include "header.h"
#include "function.h"

void check_in()
{
    FILE* date;
    date = fopen("user_date", "rt+");
    if (date == NULL)
    {
        printf("数据库打开失败。");
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
    while (!feof(date) && !check)//从文件里找该账号
    {
        fgets(id_check, 30, date);//读取id
        if (!strcmp(id_check, id))
        {
            check = 1;//1为成功找到账号
        }
        else
        {

        }
    }
    if (!check)
    {
        printf("未找到账号！请检查账户名是否拼写错误\n");
        goto getinstart;
    }
    else
    {
        int try = 3;
        while (try)
        {
            if (strcmp(password_check, password))
            {
                printf("密码错误，请重新输入！\n");
                printf("password:");
                scanf("%s", password);
                try--;
            }
            else
            {
                printf("登录成功！欢迎回来，%s", &id);
                if (user_type == 0)
                    menu_manger();
                else if (user_type == 1)
                    menu_front();
                else if (user_type == 2)
                    menu_custom();
                else
                {
                    printf("账户类型错误！");
                    break;
                }
            }
        }
        printf("错误次数过多！");
    }
    fclose(date);
}
