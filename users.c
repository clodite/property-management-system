
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

//int judge_by_ 

void change_password(struct user* temp) //�����˺�ǰ̨ʹ�õĸ������뺯����ֻ���޸��Լ����˻� 
{
	char password1[30];
	printf("������������\n");
	scanf("%s", password1);
	strcpy(temp->password, password1);
}

struct user* search_account(struct user* head) //�����������ID��Ӧ�ṹ��ĺ����������˻��ṹ���ַ 
{
	char ID[30];
	printf("������ID\n");
	scanf("%s", ID);
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

void super_change_password(struct user* head) //������Ա�õĸ����뺯����������������ID�Ը������Ӧ������ 
{
    struct user* temp = search_account(head);
	change_password(temp);
}

void change_card(struct user* head) //����Ա�õĸ��Ŀͻ��ȼ��ĺ���������ID���Ķ�Ӧ�ȼ� 
{
	struct user* temp = search_account(head);
	int t_card = 0;
	printf("��������Ҫ�޸ĵĵȼ�\n");
	scanf("%d", &t_card);
	temp->card = t_card;
}


void print_user(struct user* head) //����Աʹ�õĲ�ѯȫ���û���Ϣ 
{
	struct user* temp = head;
    while(temp!= NULL)
    {
 	   printf("%s %s %d %s %d %s %d\n", temp->ID, temp->password, temp->type, temp->name, temp->age, temp->call, temp->card);
       temp = temp->next;
	}  
}
 
void register_user(struct user* head)  //ע��ϵͳ 
{
	struct user* temp = (struct user*)malloc(sizeof(struct user));
	struct user* temp1 = head;
	while(temp1->next != NULL)
	{
		temp1 = temp1->next;
	}
	temp1->next = temp;
	temp->next = NULL;
	int flag = 0;                //�������ж��Ƿ����ע�� 
	printf("����������ID ��������30λ��\n"); 
	scanf("%s", temp->ID);
	flag++;
	printf("��������������\n");
	scanf("%s", temp->password);
	flag++;
	printf("�������������� ����\n");
	scanf("%s %d", temp->name, &temp->age); 
	flag++;
	printf("������绰����\n");
	scanf("%s", temp->call);
	temp->type = 2;   
	temp->card = 1;
	if(flag == 3)
	printf("ע��ɹ�\n");
}

struct user* load_in(struct user* head) //��ʱûɶ�� ������¼���ܻ��õ�������Ѱ�˻���Ȼ��˶�������ȷ�ŷ��ض�Ӧ�˺�ָ��ĺ��� 
{
	struct user* temp = search_account(head);
	char password1[30];
	printf("����������\n");
	scanf("%s", password1);
	if(strcmp(password1, temp->password) == 0) //������ȷ
	   return temp;
	else
	{
	  printf("error!\n");
	  return NULL;
    }
}
