#define _CRT_SECURE_NO_WARNINGS
#include "struct.h"
#include "header.h"
#include "function.h"
// 从文件中读取用户信息并构建链表
struct user* load_users(const char* userdate)
{
    FILE* file = fopen(userdate, "rt");
    if (file == NULL) {
        printf("数据库打开失败。\n");
        return NULL;
    }

    struct user* head = NULL;
    struct user* tail = NULL;

    while (!feof(file))
    {
        struct user* load_user = (struct user*)malloc(sizeof(struct user));
        if (fscanf(file, "%s %s %d %s %d %s %d",
            load_user->ID, load_user->password, &load_user->type,
            load_user->name, &load_user->age, load_user->call, &load_user->card) == 7)
        {
            load_user->next = NULL;
            if (head == NULL)
            {
                head = load_user;
                tail = load_user;
            }
            else
            {
                tail->next = load_user;
                tail = load_user;
            }
        }
        else
        {
            free(load_user); // 如果读取失败，释放内存
            break;
        }
    }

    fclose(file);
    return head;
}

// 释放链表内存
void free_users(struct user* head)
{
    while (head != NULL)
    {
        struct user* temp = head;
        head = head->next;
        free(temp);
    }
}

// 登录功能
// 打印欢迎界面
void print_welcome_ui() {
    printf("========================================\n");
    printf("|       欢迎使用千恋万花酒店系统        |\n");
    printf("========================================\n\n");
    printf("[1]用户登录\n");
    printf("[2]注册账号\n");
    printf("[3]退出系统\n");
}

// 打印登录界面
void print_login_ui() {
    printf("\n");
    printf("========================================\n");
    printf("|              用户登录                |\n");
    printf("========================================\n");
}

// 打印登录成功界面
void print_login_success_ui(char* name) {
    printf("\n");
    printf("========================================\n");
    printf("|          登录成功！欢迎回来，%s          |\n", name);
    printf("========================================\n");
}

// 打印登录失败界面
void print_login_fail_ui(int try) {
    printf("\n");
    printf("========================================\n");
    printf("|  用户名或密码错误，请重试。剩余尝试次数：%d  |\n", try);
    printf("========================================\n");
}

// 打印错误次数过多界面
void print_too_many_attempts_ui() {
    printf("\n");
    printf("========================================\n");
    printf("|        错误次数过多，登录失败！       |\n");
    printf("========================================\n");
}

// 登录功能
void check_in() {
    struct user* user_list = load_users("userdate.txt");
    if (user_list == NULL) {
        return;
    }

    char id[30];
    char password[30];
    int try = 3;


    while (try > 0) {
        print_login_ui();
        printf("user name: ");
        scanf("%s", id);
        printf("password: ");
        scanf("%s", password);

        struct user* current = user_list;
        while (current != NULL) {
            if (strcmp(current->ID, id) == 0 && strcmp(current->password, password) == 0) {
                print_login_success_ui(current->name);
                if (current->type == 0)
                    menu_manager(current->ID, current->password, &current->type,
                        current->name, &current->age, current->call, &current->card);
                else if (current->type == 1)
                    menu_front(current->ID, current->password, &current->type,
                        current->name, &current->age, current->call, &current->card);
                else if (current->type == 2)
                    menu_custom(current->ID, current->password, &current->type,
                        current->name, &current->age, current->call, &current->card);
                else
                    printf("账户类型错误！\n");

                free_users(user_list); // 释放链表内存
                return;
            }
            current = current->next;
        }

        try--;
        if (try > 0) {
            print_login_fail_ui(try);
        }
    }

    print_too_many_attempts_ui();
    free_users(user_list); // 释放链表内存
}
