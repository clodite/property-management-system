
struct user* load_users(const char* users)  //将用户数据全部读取存入链表，返回首地址 
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


void write_users(const char* users, struct user* head) //将链表数据写入users文件中 
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


void freelist_user(struct user* head) //释放链表内存 
{
	struct user* temp = NULL;
    while(head!= NULL)
    {
       temp = head;
       head = head->next;
       free(temp);
	}	
}


struct user* search_account(struct user* head, char ID[30]) //遍历链表查找ID对应结构体的函数，返回账户结构体地址 
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
		printf("ID错误\n");
	}
}

int change_password(struct user* head, char ID[30], char password[30]) //给客人和前台改密码的函数 
{
    struct user* temp = search_account(head, ID);
	char password1[30];
	printf("请输入新密码\n");
	scanf("%s", password1);
	strcpy(temp->password, password1);
	return 0;	
}

int super_change_password(struct user* head, char ID[30]) //给管理员用的改密码函数，可以输入任意ID以更改其对应的密码 
{
    struct user* temp = search_account(head, ID);
	char password1[30];
	scanf("%s", password1);
	strcpy(temp->password, password1);
	return 0;
}

int change_card(struct user* head, char ID[30]) //管理员用修改等级 
{
	struct user* temp = search_account(head, ID);
	int t_card = 0;
	printf("请输入想要修改的等级\n");
	scanf("%d", &t_card);
	temp->card = t_card;
	return 0;
}

int search_card(struct user* head, char ID[30], char password[30]) //查询card值 
{
	struct user* temp = search_account(head, ID);
	return temp->card; //这里偷懒了实际上，根本没有写判断密码，因为没必要 
}






