
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

//int judge_by_ 

void change_password(struct user* temp) //给客人和前台使用的更改密码函数，只能修改自己的账户 
{
	char password1[30];
	printf("请输入新密码\n");
	scanf("%s", password1);
	strcpy(temp->password, password1);
}

struct user* search_account(struct user* head) //遍历链表查找ID对应结构体的函数，返回账户结构体地址 
{
	char ID[30];
	printf("请输入ID\n");
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
		printf("ID错误\n");
	}
}

void super_change_password(struct user* head) //给管理员用的改密码函数，可以输入任意ID以更改其对应的密码 
{
    struct user* temp = search_account(head);
	change_password(temp);
}

void change_card(struct user* head) //管理员用的更改客户等级的函数，输入ID更改对应等级 
{
	struct user* temp = search_account(head);
	int t_card = 0;
	printf("请输入想要修改的等级\n");
	scanf("%d", &t_card);
	temp->card = t_card;
}


void print_user(struct user* head) //管理员使用的查询全部用户信息 
{
	struct user* temp = head;
    while(temp!= NULL)
    {
 	   printf("%s %s %d %s %d %s %d\n", temp->ID, temp->password, temp->type, temp->name, temp->age, temp->call, temp->card);
       temp = temp->next;
	}  
}
 
void register_user(struct user* head)  //注册系统 
{
	struct user* temp = (struct user*)malloc(sizeof(struct user));
	struct user* temp1 = head;
	while(temp1->next != NULL)
	{
		temp1 = temp1->next;
	}
	temp1->next = temp;
	temp->next = NULL;
	int flag = 0;                //计数以判断是否完成注册 
	printf("请输入您的ID （不超过30位）\n"); 
	scanf("%s", temp->ID);
	flag++;
	printf("请输入您的密码\n");
	scanf("%s", temp->password);
	flag++;
	printf("请输入您的姓名 年龄\n");
	scanf("%s %d", temp->name, &temp->age); 
	flag++;
	printf("请输入电话号码\n");
	scanf("%s", temp->call);
	temp->type = 2;   
	temp->card = 1;
	if(flag == 3)
	printf("注册成功\n");
}

struct user* load_in(struct user* head) //暂时没啥用 不过登录可能会用到的先搜寻账户，然后核对密码正确才返回对应账号指针的函数 
{
	struct user* temp = search_account(head);
	char password1[30];
	printf("请输入密码\n");
	scanf("%s", password1);
	if(strcmp(password1, temp->password) == 0) //密码正确
	   return temp;
	else
	{
	  printf("error!\n");
	  return NULL;
    }
}
