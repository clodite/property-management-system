#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "function.h"
#include "struct.h"
#include <bits/stdc++.h>
#include <math.h>
#include <EGE.h>
#define WIDTH 600
#define HEIGHT 400
using namespace std;

struct InputBox
{
	int x, y, width, height;
	char text[256];
	int has_focus;
};
char *get_user_id();
int display_booking_table_front_edition(struct strbook *head);
void change_password(const char *username, const char *old_password, const char *new_password);
void change_password_UI();
void drawButton(const Button &btn);
struct strbook* find_book_by_id(long long target_book_id);
void showRoom_front(struct room *head,long long book_id);
int compare_room(const void *a, const void *b);
const char *get_type_name(int type);
int bookings_check(long long my_book_id);
void write_liverecord(int troom,struct strbook *thestr);
struct strbook* sortStrbookList(struct strbook* head);
int display_live_table_front_edition(struct live_record *head);
struct live_record* sortLiveRecords(struct live_record* head);
struct live_record* filter_by_id(const char* id, struct live_record* head);

void showFrontMenu()
{
	start:
	closegraph();
	initgraph(800, 600);
	setcaption("前台");
	setbkcolor(EGERGB(240, 240, 240));
	cleardevice();
	
	// 按钮
	const int btnWidth = 180;
	const int btnHeight = 45;
	const int startX = (800 - btnWidth) / 2;
	int currentY = 200;
	const int verticalSpacing = 30;
	
	Button buttons[3] = {
		{startX, currentY, btnWidth, btnHeight, "查询预约"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "办理退房"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "修改密码"}};
	
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				for (int i = 0; i < 3; ++i)
				{
					const Button &btn = buttons[i];
					if (isInArea(msg.x, msg.y, btn.x, btn.y, btn.width, btn.height))
					{
						switch (i)
						{
						case 0:
						{
							closegraph();
							//功能代码
							char *iii = NULL;
							iii = get_user_id();
							if (iii != NULL)
							{
								again:
								struct strbook *head = read_booklist_file(iii);
								head = sortStrbookList(head);
								if (head != NULL)
								{
									if (display_booking_table_front_edition(head))
									{
										goto again;
									}
								}
							}
							
							initgraph(800, 600);
							setcaption("前台");
							setbkcolor(EGERGB(240, 240, 240));
							cleardevice();
							break;
						}
						case 1:
							{
								closegraph();
								// 办理退房
								againn:
								struct live_record* head = load_lives("liveinlist.txt");
								char* resid=NULL;
								resid = get_user_id();
								if(resid==NULL)
								{
									goto start;
								}
								head = filter_by_id(resid,head);
								
								head = sortLiveRecords(head);
								int res=display_live_table_front_edition(head);
								if(res==5||res==4)
								{
									goto againn;
								}
								
								initgraph(800, 600);
								setcaption("前台");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 2:
							closegraph();
							// 修改密码
							change_password_UI();
							
							initgraph(800, 600);
							setcaption("前台");
							setbkcolor(EGERGB(240, 240, 240));
							cleardevice();
							break;
						}
					}
				}
			}
		}
		
		cleardevice();
		setcolor(BLACK);
		setfont(36, 0, "宋体");
		outtextxy(350, 40, "主菜单");
		
		for (int i = 0; i < 3; ++i)
		{
			drawButton(buttons[i]);
		}
	}
	closegraph();
}

typedef struct
{
	int x, y;
	int width, height;
	char text[50];
	long long book_id;
} BButton;

typedef struct
{
	int x, y;
	int width, height;
	char text[50];
	struct live_record temp;
} BBButton;

int display_booking_table_front_edition(struct strbook *head)
{
	//init_console();
	// 窗口参数
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int ROW_HEIGHT = 40;
	const int COL_WIDTH[] = {120, 150, 100, 80, 120, 100}; // 列宽设置
	
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	setrendermode(RENDER_MANUAL);
	// initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	//init_console();
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setlinecolor(BLACK);
	setcolor(BLACK);
	
	// 表头
	setfillcolor(0xDDDDDD);
	//	setfillcolor(BLUE);
	bar(0, 0, WINDOW_WIDTH, ROW_HEIGHT);
	
	setfont(16, 0, "SimSun");
	const char *headers[] = {"预订ID", "入住时间", "房间类型", "居住时长", "身份证号", "状态"};
	int x = 10;
	for (int i = 0; i < 6; ++i)
	{
		outtextxy(x + 5, 10, headers[i]);
		x += COL_WIDTH[i];
	}
	
	int y_pos = ROW_HEIGHT;
	
	//遍历链表
	struct strbook *current = head;
	y_pos = ROW_HEIGHT + 10;
	
	while (current != NULL)
	{
		setbkmode(TRANSPARENT);
		setfillcolor(WHITE);
		bar(0, y_pos - 5, WINDOW_WIDTH, y_pos + ROW_HEIGHT - 5);
		
		settextcolor(BLACK);
		
		x = 10;
		char buffer[100];
		
		sprintf(buffer, "%lld", current->book_id);
		outtextxy(x + 5, y_pos, buffer);
		x += COL_WIDTH[0];
		
		struct time in_time = timestamp_to_time(current->time);
		
		sprintf(buffer, "%4d年%02d月%02d日%d时", in_time.year,in_time.month,in_time.day,14);
		outtextxy(x + 5, y_pos, buffer);
		x += COL_WIDTH[1];
		
		switch (current->roomtype)
		{
		case 1:
			outtextxy(x + 5, y_pos, "单人间");
			break;
		case 2:
			outtextxy(x + 5, y_pos, "双人间");
			break;
		case 3:
			outtextxy(x + 5, y_pos, "套房");
			break;
		case 4:
			outtextxy(x + 5, y_pos, "豪华套房");
			break;
		case 5:
			outtextxy(x + 5, y_pos, "家庭房");
			break;
		default:
			outtextxy(x + 5, y_pos, "未知类型");
			break;
		}
		x += COL_WIDTH[2];
		
		sprintf(buffer, "%d 天", (current->last+1)/24);
		outtextxy(x + 5, y_pos, buffer);
		x += COL_WIDTH[3];
		
		outtextxy(x + 5, y_pos, current->id);
		x += COL_WIDTH[4];
		
		switch (current->status)
		{
		case 1:
			outtextxy(x + 5, y_pos, "已预约");
			break;
		case 2:
			outtextxy(x + 5, y_pos, "已入住");
			break;
		default:
			outtextxy(x + 5, y_pos, "已取消");
			break;
		}
		
		y_pos += ROW_HEIGHT;
		current = current->next;
		//		printf("%d\n",y_pos);
		delay_ms(1);
	}
	
	// 按钮
	BButton return_btn = {WINDOW_WIDTH - 120, WINDOW_HEIGHT - 50, 100, 40, "返回"};
	BButton *row_btns = NULL;
	int btn_count = 0;
	
	current = head;
	y_pos = ROW_HEIGHT + 10;
	
	while (current != NULL)
	{
		BButton btn = {WINDOW_WIDTH - 110, y_pos, 100, 30, "办理"};
		btn.book_id = current->book_id;
		row_btns = (BButton *)realloc(row_btns, (btn_count + 1) * sizeof(BButton));
		row_btns[btn_count++] = btn;
		
		y_pos += ROW_HEIGHT;
		current = current->next;
	}
	
	for (; is_run(); delay_fps(60))
	{
		// 返回按钮
		setfillcolor(0x0099FF);
		bar(return_btn.x, return_btn.y,
			return_btn.x + return_btn.width,
			return_btn.y + return_btn.height);
		setcolor(WHITE);
		outtextxy(return_btn.x + 35, return_btn.y + 12, return_btn.text);
		
		// 行按钮
		for (int i = 0; i < btn_count; ++i)
		{
			setfillcolor(0x00CC99);
			bar(row_btns[i].x, row_btns[i].y,
				row_btns[i].x + row_btns[i].width,
				row_btns[i].y + row_btns[i].height);
			setcolor(BLACK);
			outtextxy(row_btns[i].x + 35, row_btns[i].y + 8, row_btns[i].text);
		}
		
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				// 返回按钮
				if (msg.x >= return_btn.x && msg.x <= return_btn.x + return_btn.width &&
					msg.y >= return_btn.y && msg.y <= return_btn.y + return_btn.height)
				{
					free(row_btns);
					closegraph();
					return 0;
				}
				
				// 行按钮
				for (int i = 0; i < btn_count; ++i)
				{
					if (msg.x >= row_btns[i].x && msg.x <= row_btns[i].x + row_btns[i].width &&
						msg.y >= row_btns[i].y && msg.y <= row_btns[i].y + row_btns[i].height)
					{	//办理入住
						struct strbook traget_book = *find_book_by_id(row_btns[i].book_id);
						if(traget_book.status!=1)
						{
							show_message_window("这是一个无效预约喵");
							return 1;
						}
						else
						{
							struct room* empty_room = give_room(traget_book.roomtype,traget_book.id,traget_book.time,traget_book.last,0);
							long long book_id=row_btns[i].book_id;
							showRoom_front(empty_room,book_id);
							
						}
						return 1;
						break;
					}
				}
			}
		}
	}
	
	free(row_btns);
	closegraph();
	return 0;
}

struct strbook* find_book_by_id(long long target_book_id) 
{
	FILE *file = fopen("booklist.txt", "r");
	if (file == NULL) {
		perror("无法打开文件");
		return NULL;
	}
	
	struct strbook *result = NULL;
	char line[256];
	
	while (fgets(line, sizeof(line), file)) {
		line[strcspn(line, "\n")] = '\0';
		
		struct strbook *new_node = (struct strbook *)calloc(1, sizeof(struct strbook));
		if (new_node == NULL) {
			perror("内存分配失败");
			fclose(file);
			return NULL;
		}
		
		int parsed = sscanf(line, "%lld %d %d %d %29s %d",
			&new_node->book_id,
			&new_node->time,
			&new_node->roomtype,
			&new_node->last,
			new_node->id,
			&new_node->status);
		
		if (parsed != 6) {
			free(new_node);
			continue;
		}
		
		if (new_node->book_id == target_book_id) {
			result = new_node;
			break;
		} else {
			free(new_node);
		}
	}
	
	fclose(file);
	
	if (result == NULL) {
		// 如果没有找到匹配的 book_id，返回一个 book_id 为 -1 的结构体
		result = (struct strbook *)calloc(1, sizeof(struct strbook));
		if (result == NULL) {
			perror("内存分配失败");
			return NULL;
		}
		result->book_id = -1;
	}
	
	return result;
}

void showRoom_front(struct room *head, long long book_id)
{
	// 滚动相关变量
	int scrollY = 0;               // 当前滚动位置
	const int visibleRows = 15;    // 可见行数
	const int scrollBarWidth = 20; // 滚动条宽度
	bool isDragging = false;       // 是否正在拖动滚动条
	int dragStartY = 0;            // 拖动起始位置
	int totalRows = 0;
	
	Button returnBtn = {20, 20, 100, 40, "返回"};
	
	struct room *p = head;
	while (p)
	{
		if (p->state)
		{
			p = p->next;
			continue;
		}
		totalRows++;
		p = p->next;
	}
	
	if (totalRows == 0)
	{
		initgraph(400, 200);
		setbkcolor(WHITE);
		cleardevice();
		setcolor(BLACK);
		outtextxy(150, 90, "无房间数据");
		getch();
		closegraph();
		return;
	}
	
	// 排序数组
	struct room *array = (struct room *)malloc(totalRows * sizeof(struct room));
	p = head;
	for (int i = 0; i < totalRows; i++)
	{
		if (p->state)
		{
			p = p->next;
			array[i].next = NULL;
			i--;
			continue;
		}
		array[i] = *p;
		array[i].next = NULL;
		p = p->next;
	}
	qsort(array, totalRows, sizeof(struct room), compare_room);
	
	initgraph(800 + scrollBarWidth, 600);
	setbkcolor(WHITE);
	cleardevice();
	
	bool shouldExit = false;
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			
			// 返回按钮
			if (msg.is_left() && msg.is_down())
			{
				if (isInArea(msg.x, msg.y, returnBtn.x, returnBtn.y,
					returnBtn.width, returnBtn.height))
				{
					shouldExit = true;
					break;
				}
			}
			
			// 滚动条
			if (msg.is_left())
			{
				int scrollAreaHeight = 600 - returnBtn.y - returnBtn.height;
				if (msg.x >= 800 && msg.x <= 800 + scrollBarWidth)
				{
					if (msg.is_down())
					{
						isDragging = true;
						dragStartY = msg.y;
					}
					if (isDragging)
					{
						int deltaY = msg.y - dragStartY;
						scrollY += deltaY * totalRows / scrollAreaHeight;
						scrollY = max(0, min(scrollY, totalRows - visibleRows));
						dragStartY = msg.y;
					}
				}
			}
			if (msg.is_up())
			{
				isDragging = false;
			}
			
			// 鼠标滚轮
			if (msg.is_wheel())
			{
				if (msg.wheel > 0)
				{
					scrollY = max(0, scrollY - 3); // 每次滚动3行
				}
				else if (msg.wheel < 0)
				{
					scrollY = min(scrollY + 3, totalRows - visibleRows);
				}
			}
			
			// 按钮
			int start_x = 50;
			const int start_y = 70;
			const int row_height = 30;
			const int col_width[] = {100, 150, 100, 100, 80}; 
			
			int startRow = max(0, scrollY);
			int endRow = min(startRow + visibleRows, totalRows);
			
			for (int i = startRow; i < endRow; i++)
			{
				int currentY = start_y + (i - startRow) * row_height;
				int x = start_x + col_width[0] + col_width[1] + col_width[2] + col_width[3];
				
				if (msg.is_left() && msg.is_down())
				{
					if (msg.x >= x && msg.x <= x + col_width[4] && msg.y >= currentY && msg.y <= currentY + row_height)
					{
						int roomNumber = array[i].num;
						// 办理入住
						bookings_check(book_id);
						write_liverecord(roomNumber,find_book_by_id(book_id));
						return;
					}
				}
			}
		}
		
		if (shouldExit)
		{
			closegraph();
			free(array);
			return;
		}
		
		cleardevice();
		
		drawButton(returnBtn);
		setfont(18, 0, "宋体");
		
		// 表格参数
		const int start_x = 50;
		const int start_y = 70;
		const int row_height = 30;
		const int col_width[] = {100, 150, 100, 100, 80};
		
		// 表头
		setfillcolor(EGERGB(220, 220, 220));
		bar(start_x, start_y,
			start_x + col_width[0] + col_width[1] + col_width[2] + col_width[3] + col_width[4],
			start_y + row_height);
		
		int text_x = start_x;
		outtextxy(text_x + 5, start_y + 5, "房号");
		text_x += col_width[0];
		outtextxy(text_x + 5, start_y + 5, "类型");
		text_x += col_width[1];
		outtextxy(text_x + 5, start_y + 5, "价格(元)");
		text_x += col_width[2];
		outtextxy(text_x + 5, start_y + 5, "面积(m^2)");
		text_x += col_width[3];
		outtextxy(text_x + 5, start_y + 5, "操作");
		
		int startRow = max(0, scrollY);
		int endRow = min(startRow + visibleRows, totalRows);
		
		// 数据和按钮
		char buffer[50];
		int y = start_y + row_height;
		for (int i = startRow; i < endRow; i++)
		{
			int currentY = y + (i - startRow) * row_height;
			int x = start_x;
			
			sprintf(buffer, "%04d", array[i].num);
			outtextxy(x + 5, currentY + 5, buffer);
			x += col_width[0];
			
			outtextxy(x + 5, currentY + 5, get_type_name(array[i].type));
			x += col_width[1];
			
			sprintf(buffer, "%d", array[i].price);
			outtextxy(x + 5, currentY + 5, buffer);
			x += col_width[2];
			
			sprintf(buffer, "%d", array[i].size);
			outtextxy(x + 5, currentY + 5, buffer);
			x += col_width[3];
			
			setfillcolor(EGERGB(200, 220, 240));
			bar(x, currentY, x + col_width[4], currentY + row_height);
			outtextxy(x + 5, currentY + 5, "办理入住");
		}
		
		setfillcolor(EGERGB(200, 200, 200));
		bar(800, 0, 800 + scrollBarWidth, 600);
		
		float thumbHeight = (float)visibleRows / totalRows * 600;
		float thumbY = (float)scrollY / totalRows * 600;
		setfillcolor(EGERGB(150, 150, 150));
		fillellipse(800 + scrollBarWidth / 2, thumbY + thumbHeight / 2,
			scrollBarWidth / 2 - 2, thumbHeight / 2);
		
		int x = start_x;
		for (int i = 0; i <= 5; i++)
		{
			line(x, start_y, x, start_y + row_height * (visibleRows + 1));
			if (i < 5)
				x += col_width[i];
		}
		
		y = start_y;
		for (int i = 0; i <= visibleRows + 1; i++)
		{
			line(start_x, y, x, y);
			y += row_height;
		}
	}
	
	closegraph();
	free(array);
}

int bookings_check(long long my_book_id)
{
	FILE *book_record, *temp_file;
	
	book_record = fopen(BOOK_FILE, "r");
	if (book_record == NULL)
	{
		printf("预约记录读取失败。\n");
		return -1;
	}
	
	temp_file = fopen("canceling_temp.txt", "w");
	if (temp_file == NULL)
	{
		printf("无法创建临时文件。\n");
		fclose(book_record);
		return -1;
	}
	
	char line[256];
	int found = 0;      // 预约记录条数
	int real_found = 0; // `- 未入住（1）条数
	int bug = 0;        // 找到的bug数量，暂时没啥用
	
	while (fgets(line, sizeof(line), book_record))
	{
		long long book_id;
		int time, roomtype, last, status;
		char id[30];
		
		if (sscanf(line, "%lld %d %d %d %s %d", &book_id, &time, &roomtype, &last, id, &status) != 6)
		{
			bug++; // 名字中含空格也会这样
			continue;
		}
		
		if (book_id == my_book_id)
		{
			found++;
			
			if (status == 1)
			{
				real_found++;
				fprintf(temp_file, "%lld %d %d %d %s %d\n", book_id, time, roomtype, last, id, 2);
			}
			
			if (status == 2)
			{
				printf("该预约已结单，无法操作。\n");
				fputs(line, temp_file);
			}
			
			if (status == 3)
			{
				printf("该预约已经取消过啦。\n");
				fputs(line, temp_file);
			}
		}
		
		else
		{
			fputs(line, temp_file);
		}
	}
	
	fclose(temp_file);
	fclose(book_record);
	
	if (found > 1)
	{
		bug++;
	}
	
	if (!real_found)
	{
		if (!found)
		{
			remove("canceling_temp.txt");
			show_message_window("未找到预约记录，无法完成");
		}
		return -1;
	}
	
	if (real_found)
	{
		remove(BOOK_FILE);
		rename("canceling_temp.txt", BOOK_FILE);
		show_message_window("成功办理入住！！");
		return 0;
	}
	
	return -1;
}

void write_liverecord(int troom,struct strbook *thestr)
{
	FILE* fp = fopen("liveinlist.txt", "a"); 
	if (fp == NULL) 
	{
		printf("找不到文件");
		return;
	}
	
	fprintf(fp, "%s %d %d %d %d -1\n",
		thestr->id, troom, thestr->roomtype,thestr->time, thestr->last);
	
	fclose(fp);
}

struct strbook* sortStrbookList(struct strbook* head) {
	if (head == NULL || head->next == NULL) {
		return head; // 如果链表为空或只有一个节点，直接返回
	}
	
	struct strbook *current, *prev, *temp;
	int swapped;
	
	do {
		swapped = 0;
		current = head;
		prev = NULL;
		
		while (current->next != NULL) {
			// 如果当前节点的 time 小于下一个节点的 time，则交换它们
			if (current->time < current->next->time) {
				// 保存下一个节点
				temp = current->next;
				
				// 调整指针
				if (prev == NULL) {
					// 如果当前节点是头节点
					head = temp;
				} else {
					prev->next = temp;
				}
				
				current->next = temp->next;
				temp->next = current;
				
				// 更新指针
				if (prev == NULL) {
					head = temp;
				} else {
					prev->next = temp;
				}
				
				prev = temp;
				swapped = 1;
			} else {
				prev = current;
				current = current->next;
			}
		}
	} while (swapped);
	
	return head;
}

struct live_record search_record(char* user_id, int room_no, int room_type, int arrive_time) {
	struct live_record record;
	FILE* file = fopen("liveinlist.txt", "r"); 
	if (file == NULL)
	{
		printf("无法打开文件");
		return (struct live_record){0};
	}
	
	char line[256];
	while (fgets(line, sizeof(line), file)) { 
		struct live_record temp;
		if (sscanf(line, "%s %d %d %d %d %d", temp.ID, &temp.room, &temp.type, &temp.arrive_time, &temp.time_live, &temp.leave_time) == 6) {
			if (strcmp(temp.ID, user_id) == 0 && temp.room == room_no && temp.type == room_type && temp.arrive_time == arrive_time) {
				strcpy(record.ID, temp.ID);
				record.room = temp.room;
				record.type = temp.type;
				record.arrive_time = temp.arrive_time;
				record.time_live = temp.time_live;
				record.leave_time = temp.leave_time;
				record.next = NULL;
				fclose(file);
				return record;
			}
		}
	}
	
	fclose(file);
	return (struct live_record){0};
}

void update_leave_time(struct live_record* record) {
	const char* filename="liveinlist.txt";
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("无法打开文件");
		return;
	}
	
	char temp_file[L_tmpnam];
	tmpnam(temp_file);
	
	FILE* temp = fopen(temp_file, "w");
	if (temp == NULL) {
		perror("无法创建临时文件");
		fclose(file);
		return;
	}
	
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		char id[30];
		int room, type, arrive_time, time_live, leave_time;
		
		if (sscanf(line, "%29s %d %d %d %d %d", id, &room, &type, &arrive_time, &time_live, &leave_time) != 6) {
			fprintf(temp, "%s", line);
			continue;
		}
		
		if (strcmp(id, record->ID) == 0 && room == record->room && type == record->type &&
			arrive_time == record->arrive_time && time_live == record->time_live) {
			fprintf(temp, "%s %d %d %d %d %d\n", record->ID, record->room, record->type, record->arrive_time, record->time_live, record->leave_time);
		} else {
			fprintf(temp, "%s", line);
		}
	}
	
	fclose(file);
	fclose(temp);
	
	if (remove(filename) != 0) {
		perror("无法删除原文件");
		return;
	}
	if (rename(temp_file, filename) != 0) {
		perror("无法重命名临时文件");
		return;
	}
}

int display_live_table_front_edition(struct live_record *head)
{
	// 窗口参数
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int ROW_HEIGHT = 40;
	const int COL_WIDTH[] = {150, 80, 100, 150, 100, 150}; // 调整后的列宽
	
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	setrendermode(RENDER_MANUAL);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setlinecolor(BLACK);
	setcolor(BLACK);
	
	// 表头
	setfillcolor(0xDDDDDD);
	bar(0, 0, WINDOW_WIDTH, ROW_HEIGHT);
	
	setfont(16, 0, "SimSun");
	const char *headers[] = {"身份证号", "房间号", "房间类型", "入住时间", "入住时长", "退房时间"};
	int x = 10;
	for (int i = 0; i < 6; ++i)
	{
		outtextxy(x + 5, 10, headers[i]);
		x += COL_WIDTH[i];
	}
	
	int y_pos = ROW_HEIGHT;
	struct live_record *current = head;
	y_pos = ROW_HEIGHT + 10;
	
	while (current != NULL)
	{
		setbkmode(TRANSPARENT);
		setfillcolor(WHITE);
		bar(0, y_pos - 5, WINDOW_WIDTH, y_pos + ROW_HEIGHT - 5);
		settextcolor(BLACK);
		
		x = 10;
		char buffer[100];
		
		// 身份证号
		outtextxy(x + 5, y_pos, current->ID);
		x += COL_WIDTH[0];
		
		// 房间号
		sprintf(buffer, "%d", current->room);
		outtextxy(x + 5, y_pos, buffer);
		x += COL_WIDTH[1];
		
		// 房间类型
		switch (current->type)
		{
		case 1:
			outtextxy(x + 5, y_pos, "单人间");
			break;
		case 2:
			outtextxy(x + 5, y_pos, "双人间");
			break;
		case 3:
			outtextxy(x + 5, y_pos, "套房");
			break;
		case 4:
			outtextxy(x + 5, y_pos, "豪华套房");
			break;
		case 5:
			outtextxy(x + 5, y_pos, "家庭房");
			break;
		default:
			outtextxy(x + 5, y_pos, "未知类型");
			break;
		}
		x += COL_WIDTH[2];
		
		// 入住时间
		struct time arrive_time = timestamp_to_time(current->arrive_time);
		sprintf(buffer, "%4d年%02d月%02d日%02d时",
			arrive_time.year, arrive_time.month,
			arrive_time.day, arrive_time.hour);
		outtextxy(x + 5, y_pos, buffer);
		x += COL_WIDTH[3];
		
		// 入住时长
		sprintf(buffer, "%d 天", (current->time_live+1)/24);
		outtextxy(x + 5, y_pos, buffer);
		x += COL_WIDTH[4];
		
		// 退房时间
		if (current->leave_time == -1)
		{
			outtextxy(x + 5, y_pos, "未退房");
		}
		else
		{
			struct time leave_time = timestamp_to_time(current->leave_time);
			sprintf(buffer, "%4d年%02d月%02d日%02d时",
				leave_time.year, leave_time.month,
				leave_time.day, leave_time.hour);
			outtextxy(x + 5, y_pos, buffer);
		}
		
		y_pos += ROW_HEIGHT;
		current = current->next;
		delay_ms(1);
	}
	
	// 按钮
	BBButton return_btn = {WINDOW_WIDTH - 120, WINDOW_HEIGHT - 50, 100, 40, "返回"};
	BBButton *row_btns = NULL;
	int btn_count = 0;
	
	current = head;
	y_pos = ROW_HEIGHT + 10;
	
	while (current != NULL)
	{
		BBButton btn = {WINDOW_WIDTH - 60, y_pos-5, 60, 30, "退房"};
		btn.temp = *current; 
		row_btns = (BBButton *)realloc(row_btns, (btn_count + 1) * sizeof(BBButton));
		row_btns[btn_count++] = btn;
		
		y_pos += ROW_HEIGHT;
		current = current->next;
	}
	
	for (; is_run(); delay_fps(60))
	{
		setfillcolor(0x0099FF);
		bar(return_btn.x, return_btn.y,
			return_btn.x + return_btn.width,
			return_btn.y + return_btn.height);
		setcolor(WHITE);
		outtextxy(return_btn.x + 35, return_btn.y + 10, return_btn.text);
		
		//行按钮
		for (int i = 0; i < btn_count; ++i)
		{
			setfillcolor(0x00CC99);
			bar(row_btns[i].x, row_btns[i].y,
				row_btns[i].x + row_btns[i].width,
				row_btns[i].y + row_btns[i].height);
			setcolor(BLACK);
			outtextxy(row_btns[i].x + 15, row_btns[i].y + 8, row_btns[i].text);
		}
		
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				// 返回
				if (msg.x >= return_btn.x && msg.x <= return_btn.x + return_btn.width &&
					msg.y >= return_btn.y && msg.y <= return_btn.y + return_btn.height)
				{
					free(row_btns);
					closegraph();
					return 4;
				}
				
				// 退房
				for (int i = 0; i < btn_count; ++i)
				{
					if (msg.x >= row_btns[i].x && msg.x <= row_btns[i].x + row_btns[i].width &&
						msg.y >= row_btns[i].y && msg.y <= row_btns[i].y + row_btns[i].height)
					{
						struct live_record target = search_record(row_btns[i].temp.ID,row_btns[i].temp.room,row_btns[i].temp.type,row_btns[i].temp.arrive_time);
						if (target.leave_time != -1)
						{
							show_message_window("该房间已退房");
						}
						else
						{
							//init_console();
							time_t now = time(NULL);
							struct tm* local_time = localtime(&now);
							struct time leave_time = {local_time->tm_year-1,local_time->tm_mon+1,local_time->tm_mday,local_time->tm_hour};
							target.leave_time = time_to_timestamp(leave_time);
							update_leave_time(&target);
							show_message_window("退房成功");
							return 5;
						}
						return 1;
					}
				}
			}
		}
	}
	
	free(row_btns);
	closegraph();
	return 0;
}

struct live_record* filter_by_id(const char* id, struct live_record* head) {
	struct live_record dummy;
	dummy.next = head;
	struct live_record* prev = &dummy;
	struct live_record* current = head;
	
	while (current != NULL) {
		if (strcmp(current->ID, id) != 0) {
			prev->next = current->next;
			struct live_record* temp = current;
			current = current->next;
			free(temp);
		} else {
			prev = current;
			current = current->next;
		}
	}
	
	return dummy.next;
}

struct live_record* split(struct live_record* head) {
	if (head == NULL || head->next == NULL) {
		return NULL;
	}
	struct live_record* slow = head;
	struct live_record* fast = head->next;
	
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	
	struct live_record* mid = slow->next;
	slow->next = NULL; 
	return mid;
}

struct live_record* merge(struct live_record* left, struct live_record* right) {
	struct live_record dummy;
	struct live_record* tail = &dummy;
	dummy.next = NULL;
	
	while (left != NULL && right != NULL) {
		if (left->arrive_time >= right->arrive_time) {
			tail->next = left;
			left = left->next;
		} else {
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}
	
	if (left != NULL) {
		tail->next = left;
	} else {
		tail->next = right;
	}
	
	return dummy.next;
}

struct live_record* merge_sort(struct live_record* head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	
	struct live_record* mid = split(head);
	struct live_record* left = merge_sort(head);
	struct live_record* right = merge_sort(mid);
	
	return merge(left, right);
}

struct live_record* sortLiveRecords(struct live_record* head) {
	return merge_sort(head);
}
