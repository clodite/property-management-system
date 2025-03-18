#define _CRT_SECURE_NO_WARNINGS
#include "struct.h"
#include "header.h"
#include "function.h"
// ���ļ��ж�ȡ�û���Ϣ����������
struct user *load_users(const char *userdate)
{
    FILE *file = fopen(userdate, "rt");
    if (file == NULL)
    {
        printf("���ݿ��ʧ�ܡ�\n");
        return NULL;
    }

    struct user *head = NULL;
    struct user *tail = NULL;

    while (!feof(file))
    {
        struct user *load_user = (struct user *)malloc(sizeof(struct user));
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
            free(load_user); // �����ȡʧ�ܣ��ͷ��ڴ�
            break;
        }
    }

    fclose(file);
    return head;
}

// �ͷ������ڴ�
void free_users(struct user *head)
{
    while (head != NULL)
    {
        struct user *temp = head;
        head = head->next;
        free(temp);
    }
}

// ��¼����
void check_in()
{
    struct user *user_list = load_users("userdate");
    if (user_list == NULL)
    {
        return;
    }

    char id[30];
    char password[30];
    int try = 3;

    while (try > 0)
    {
        printf("user name: ");
        scanf("%s", id);
        printf("password: ");
        scanf("%s", password);

        struct user *current = user_list;
        while (current != NULL)
        {
            if (strcmp(current->ID, id) == 0 && strcmp(current->password, password) == 0)
            {
                printf("��¼�ɹ�����ӭ������%s\n", current->name);
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
                    printf("�˻����ʹ���\n");

                free_users(user_list); // �ͷ������ڴ�
                return;
            }
            current = current->next;
        }

        try--;
        if (try > 0)
        {
            printf("�û�����������������ԡ�ʣ�ೢ�Դ�����%d\n", try);
        }
    }

    printf("����������࣬��¼ʧ�ܣ�\n");
    free_users(user_list); // �ͷ������ڴ�
}