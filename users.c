
struct user* load_users(const char* users)  //���û�����ȫ����ȡ�������������׵�ַ 
{
	FILE*file = fopen(users, "rt");
	if(file==NULL)
	{
		perror("fail to open\n");
	}
	struct user* head =	NULL;
	struct user* tail =	NULL;
	while(1)
	{
		struct user* load =	(struct user*)malloc(sizeof(struct user));
		load->next = NULL;
		if(load == NULL)
		{
            printf("fail to allocate\n");
            fclose(file);
            return head;  
			break;			
		}
		int result = fscanf(file, "%s %s %d %s %d %s %d", load->ID, load->password, &load->type, load->name, &load->age, load->call, &load->card);
        if(result != 7)
        {
        	free(load);
        	break;
		}
		if(head == NULL)
		{
			head = load;
			tail = load;
		}
		else
		{
			tail->next = load;
			tail = load;
		}
	}
	tail->next = NULL;
	fclose(file);
	return head;
}


void write_users(const char* users, struct user* head) //����������д��users�ļ��� 
{
	FILE*file = fopen(users, "wt");
	if(file==NULL)
	{
		perror("fail to open\n");
	}
	struct user* temp = head;
    while(temp!= NULL)
    {
 	   fprintf(file, "%s %s %d %s %d %s %d\n", temp->ID, temp->password, temp->type, temp->name, temp->age, temp->call, temp->card);
       temp = temp->next;
	}  
	fclose(file);
}


void freelist_user(struct user* head) //�ͷ������ڴ� 
{
	struct user* temp = NULL;
    while(head!= NULL)
    {
       temp = head;
       head = head->next;
       free(temp);
	}	
}


struct user* search_account(struct user* head, char ID[30]) //�����������ID��Ӧ�ṹ��ĺ����������˻��ṹ���ַ 
{
	struct user* temp = head;
	int flag = 1;
	while(strcmp(ID,temp->ID) != 0)
	{
		temp =  temp->next;
		if(temp->next == NULL)
		{
			printf("error\n");
			flag = 0;
			break;
		}
	}
	if(flag == 1)
	{
		return temp;
	}
	else
	{
		printf("ID����\n");
	}
}

int change_password(struct user* head, char ID[30], char password[30]) //�����˺�ǰ̨������ĺ��� 
{
    struct user* temp = search_account(head, ID);
	char password1[30];
	printf("������������\n");
	scanf("%s", password1);
	strcpy(temp->password, password1);
	return 0;	
}

int super_change_password(struct user* head, char ID[30]) //������Ա�õĸ����뺯����������������ID�Ը������Ӧ������ 
{
    struct user* temp = search_account(head, ID);
	char password1[30];
	scanf("%s", password1);
	strcpy(temp->password, password1);
	return 0;
}

int change_card(struct user* head, char ID[30]) //����Ա���޸ĵȼ� 
{
	struct user* temp = search_account(head, ID);
	int t_card = 0;
	printf("��������Ҫ�޸ĵĵȼ�\n");
	scanf("%d", &t_card);
	temp->card = t_card;
	return 0;
}

int search_card(struct user* head, char ID[30], char password[30]) //��ѯcardֵ 
{
	struct user* temp = search_account(head, ID);
	return temp->card; //����͵����ʵ���ϣ�����û��д�ж����룬��Ϊû��Ҫ 
}






