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
void drawButton(const Button &btn);
void change_room_UI();
int get_room_id();
int get_room_new_data(int* id1, int* id2, int* id3, int* id4, int* id5);
const char *get_type_name(int type);
int compare_room(const void *a, const void *b);
void showRoom_administrator(struct room *head);
void changePassword_administrator(const char* username, const char* newPassword);
void changePassword_administrator_UI();
void showAdministratorMenu_search_UI();
struct strbook* sortStrbookList(struct strbook* head);
int display_booking_table_administrator(struct strbook *head);
char *get_user_id();
struct live_record search_record(char* user_id, int room_no, int room_type, int arrive_time);
void update_leave_time(struct live_record* record) ;
int display_live_table_administrator(struct live_record *head);
struct live_record* sortLiveRecords(struct live_record* head);
struct live_record* filter_by_id(const char* id, struct live_record* head);

typedef struct
{
	int x, y;
	int width, height;
	char text[50];
	struct live_record temp;
} BBButton;
struct InputBox
{
	int x, y, width, height;
	char text[256];
	int has_focus;
};

void showAdministratorMenu()
{
	closegraph();
	initgraph(800, 600);
	setcaption("管理员界面");
	setbkcolor(EGERGB(240, 240, 240));
	cleardevice();
	
	// 按钮
	const int btnWidth = 220;
	const int btnHeight = 45;
	const int startX = (800 - btnWidth) / 2;
	int currentY = 120;
	const int verticalSpacing = 30;
	
	Button buttons[5] = {
		{startX, currentY, btnWidth, btnHeight, "修改房间信息"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "查询信息"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "统计信息"},
		{startX, currentY /*+= btnHeight + verticalSpacing*/, btnWidth, btnHeight, "修改密码"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "查看房间信息"}};
	
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				for (int i = 0; i < 5; ++i)
				{
					if(i==3){
						continue;
					}
					const Button &btn = buttons[i];
					if (isInArea(msg.x, msg.y, btn.x, btn.y, btn.width, btn.height))
					{
						switch (i)
						{
						case 0:
							{
								closegraph();
								// 功能代码
								change_room_UI();
								
								initgraph(800, 600);
								setcaption("管理员界面");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 1:
							{
								closegraph();
								// 功能代码
								showAdministratorMenu_search_UI();
								
								initgraph(800, 600);
								setcaption("管理员界面");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 2:
							{
								closegraph();
								// 功能代码
								
								initgraph(800, 600);
								setcaption("管理员界面");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 3:
							{
								closegraph();
								// 功能代码
								changePassword_administrator_UI();
								
								initgraph(800, 600);
								setcaption("管理员界面");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 4:
							{
								closegraph();
								// 功能代码
								showRoom_administrator(load_rooms("room.txt"));
								
								initgraph(800, 600);
								setcaption("管理员界面");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;	
							}
						}
					}
				}
			}
		}
		
		cleardevice();
		setcolor(BLACK);
		setfont(36, 0, "宋体");
		outtextxy(350, 40, "主菜单");
		
		for (int i = 0; i < 5; ++i)
		{
			if(i==3)
			{
				continue;
			}
			drawButton(buttons[i]);
		}
	}
	closegraph();
}

void change_room_UI()
{
	int num=get_room_id();
	if(num==-1)
	{
		return ;
	}
	if(!num)
	{
		show_message_window("数据不合法111");
		return;
	}
	else
	{
		int num2, type, price, size, state;
		
		if(get_room_new_data(&num2,&type,&price,&size,&state)==-2)
		{
			show_message_window("数据不合法222");
			return;
		}
		
		if(change_room(load_rooms("room.txt"),num, num2, type, price, size, state))
		{
			show_message_window("房间号不正确");
			return;
		}
		show_message_window("修改成功");
	}
}

int get_room_id()
{
	const int input_width = 400;
	const int input_height = 30;
	const int input_x = (WIDTH - input_width) / 2;
	const int input_y = 100;
	const int button_width = 80;
	const int button_height = 30;
	const int query_btn_x = (WIDTH - button_width * 2 - 20) / 2;
	const int query_btn_y = 200;
	const int return_btn_x = query_btn_x + button_width + 20;
	const int return_btn_y = 200;
	
	bool is_input_active = false;
	char id[256] = {0};
	int id_len = 0;
	
	initgraph(WIDTH, HEIGHT, INIT_NOBORDER);
	setcaption("房间号输入");
	
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				if (msg.x >= input_x && msg.x <= input_x + input_width &&
					msg.y >= input_y && msg.y <= input_y + input_height)
				{
					is_input_active = true;
				}
				else
				{
					is_input_active = false;
				}
				
				if (msg.x >= query_btn_x && msg.x <= query_btn_x + button_width &&
					msg.y >= query_btn_y && msg.y <= query_btn_y + button_height)
				{
					closegraph();
					if (id_len == 0) return 0;  
					
					char* endptr;
					errno = 0;
					long val = strtol(id, &endptr, 10);
					
					if (errno == ERANGE) {
						return val > 0 ? INT_MAX : INT_MIN;  
					}
					return (int)val;
				}
				
				if (msg.x >= return_btn_x && msg.x <= return_btn_x + button_width &&
					msg.y >= return_btn_y && msg.y <= return_btn_y + button_height)
				{
					closegraph();
					return -1; 
				}
			}
		}
		
		if (is_input_active)
		{
			while (kbmsg())
			{
				key_msg kmsg = getkey();
				if (kmsg.msg == key_msg_down)
				{
					if (kmsg.key == 8) 
					{
						if (id_len > 0)
						{
							id[--id_len] = '\0';
						}
					}
					else if (kmsg.key >= '0' && kmsg.key <= '9' && id_len < 255)  
					{
						id[id_len++] = kmsg.key;
						id[id_len] = '\0';
					}
				}
			}
		}
		
		cleardevice();
		setbkcolor(WHITE);
		setcolor(BLACK);
		
		setfont(18, 0, "SimSun");
		outtextxy(input_x, input_y - 30, "请输入房间号");  
		
		setfillcolor(WHITE);
		bar(input_x, input_y, input_x + input_width, input_y + input_height);
		setcolor(is_input_active ? BLACK : BLACK);
		rectangle(input_x, input_y, input_x + input_width, input_y + input_height);
		outtextxy(input_x + 5, input_y + 8, id);
		
		setfillcolor(0xDDDDDD);
		bar(query_btn_x, query_btn_y, query_btn_x + button_width, query_btn_y + button_height);
		rectangle(query_btn_x, query_btn_y, query_btn_x + button_width, query_btn_y + button_height);
		outtextxy(query_btn_x + 20, query_btn_y + 8, "修改");
		
		bar(return_btn_x, return_btn_y, return_btn_x + button_width, return_btn_y + button_height);
		rectangle(return_btn_x, return_btn_y, return_btn_x + button_width, return_btn_y + button_height);
		outtextxy(return_btn_x + 20, return_btn_y + 8, "返回");
	}
	
	closegraph();
	return -1;
}

int get_room_new_data(int* id1, int* id2, int* id3, int* id4, int* id5)
{
	const int input_width = 200;
	const int input_height = 30;
	const int input_x = (WIDTH - input_width) / 2;
	const int input_y_offset = 50;
	const int input_spacing = 60;
	
	const int button_width = 80;
	const int button_height = 30;
	const int button_x = (WIDTH - button_width * 2 - 20) / 2;
	const int button_y = 350;
	
	bool is_input_active[5] = {false, false, false, false, false};
	char ids[5][256] = {{0}, {0}, {0}, {0}, {0}};
	int id_lens[5] = {0, 0, 0, 0, 0};
	vector<string> name= {"房间号", "房间类型", "价格", "面积", "状态"};
	
	initgraph(WIDTH, HEIGHT, INIT_NOBORDER);
	setcaption("房间号输入");
	
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				for (int i = 0; i < 5; i++)
				{
					int input_y = input_y_offset + i * input_spacing;
					if (msg.x >= input_x && msg.x <= input_x + input_width &&
						msg.y >= input_y && msg.y <= input_y + input_height)
					{
						is_input_active[i] = true;
						for (int j = 0; j < 5; j++) {
							if (j != i) is_input_active[j] = false;
						}
					}
				}

				if (msg.x >= button_x && msg.x <= button_x + button_width &&
					msg.y >= button_y && msg.y <= button_y + button_height)
				{
					closegraph();

					for (int i = 0; i < 5; i++) {
						char* endptr;
						errno = 0;
						long val = strtol(ids[i], &endptr, 10);
						
						if (errno == ERANGE) {
							*id1 = *id2 = *id3 = *id4 = *id5 = val > 0 ? INT_MAX : INT_MIN;
							return -2;
						}
						switch (i) {
							case 0: *id1 = (int)val; break;
							case 1: *id2 = (int)val; break;
							case 2: *id3 = (int)val; break;
							case 3: *id4 = (int)val; break;
							case 4: *id5 = (int)val; break;
						}
					}
					return 0;
				}

				if (msg.x >= button_x + button_width + 20 && msg.x <= button_x + button_width * 2 + 20 &&
					msg.y >= button_y && msg.y <= button_y + button_height)
				{
					closegraph();
					return -1;
				}
			}
		}

		for (int i = 0; i < 5; i++) {
			if (is_input_active[i]) {
				while (kbmsg()) {
					key_msg kmsg = getkey();
					if (kmsg.msg == key_msg_down) {
						if (kmsg.key == 8) { 
							if (id_lens[i] > 0) {
								ids[i][--id_lens[i]] = '\0';
							}
						} else if ((kmsg.key >= '0' && kmsg.key <= '9') && id_lens[i] < 255) {
							ids[i][id_lens[i]++] = kmsg.key;
							ids[i][id_lens[i]] = '\0';
						}
					}
				}
			}
		}

		cleardevice();
		setbkcolor(WHITE);
		setcolor(BLACK);

		setfont(18, 0, "SimSun");
		for (int i = 0; i < 5; i++) {
			int input_y = input_y_offset + i * input_spacing;

			char label[20];
			sprintf(label, "%s", name[i].c_str());
			outtextxy(input_x - 100, input_y+3, label);

			setfillcolor(WHITE);
			bar(input_x, input_y, input_x + input_width, input_y + input_height);

			setcolor(BLACK);
			rectangle(input_x, input_y, input_x + input_width, input_y + input_height);

			outtextxy(input_x + 5, input_y + 8, ids[i]);
		}
		
		setfillcolor(0xDDDDDD);
		bar(button_x, button_y, button_x + button_width, button_y + button_height);
		rectangle(button_x, button_y, button_x + button_width, button_y + button_height);
		outtextxy(button_x + 20, button_y + 8, "修改");
		
		bar(button_x + button_width + 20, button_y, button_x + button_width * 2 + 20, button_y + button_height);
		rectangle(button_x + button_width + 20, button_y, button_x + button_width * 2 + 20, button_y + button_height);
		outtextxy(button_x + button_width + 40, button_y + 8, "返回");
	}
	
	closegraph();
	return -1;
}

void showRoom_administrator(struct room *head)
{
	// 滚动相关变量
	int scrollY = 0;			   // 当前滚动位置
	const int visibleRows = 15;	   // 可见行数
	const int scrollBarWidth = 20; // 滚动条宽度
	bool isDragging = false;	   // 是否正在拖动滚动条
	int dragStartY = 0;			   // 拖动起始位置
	int totalRows = 0;
	
	Button returnBtn = {20, 20, 100, 40, "返回"};
	
	struct room *p = head;
	while (p)
	{
//		if(p->state)
//		{
//			p = p->next;
//			continue;
//		}
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
//		if(p->state)
//		{
//			p = p->next;
//			array[i].next = NULL;
//			i--;
//			continue;
//		}
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
		const int col_width[] = {100, 150, 100, 100,50};
		
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
		outtextxy(text_x + 5, start_y + 5, "状态");
		
		int startRow = max(0, scrollY);
		int endRow = min(startRow + visibleRows, totalRows);
		
		// 数据
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
			
			sprintf(buffer, "%d", array[i].state);
			outtextxy(x + 5, currentY + 5, buffer);
		}
		
		setfillcolor(EGERGB(200, 200, 200));
		bar(800, 0, 800 + scrollBarWidth, 600);
		
		float thumbHeight = (float)visibleRows / totalRows * 600;
		float thumbY = (float)scrollY / totalRows * 600;
		setfillcolor(EGERGB(150, 150, 150));
		fillellipse(800 + scrollBarWidth / 2, thumbY + thumbHeight / 2,
			scrollBarWidth / 2 - 2, thumbHeight / 2);
		
		// 表格线
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

void changePassword_administrator(const char* username, const char* newPassword) 
{
	const char* filename = "user.txt";
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("无法打开文件");
		return;
	}
	
	char** lines = NULL;
	int num_lines = 0;
	char buffer[256];
	
	while (fgets(buffer, sizeof(buffer), file))
	{
		buffer[strcspn(buffer, "\n")] = '\0'; 
		char** temp = (char**)realloc(lines, (num_lines + 1) * sizeof(char*));
		if (!temp) {
			fclose(file);
			for (int i = 0; i < num_lines; ++i) free(lines[i]);
			free(lines);
			return;
		}
		lines = temp;
		lines[num_lines] = strdup(buffer);
		if (!lines[num_lines]) {
			fclose(file);
			for (int i = 0; i < num_lines; ++i) free(lines[i]);
			free(lines);
			return;
		}
		num_lines++;
	}
		fclose(file);
		
		int found = 0;
		for (int i = 0; i < num_lines; i += 3) {
			if (i + 1 >= num_lines || i + 2 >= num_lines) continue; 
			
			if (strcmp(lines[i], username) == 0) {
				free(lines[i + 1]);
				lines[i + 1] = strdup(newPassword);
				if (!lines[i + 1]) { 
					for (int j = 0; j < num_lines; ++j) free(lines[j]);
					free(lines);
					return;
				}
				found = 1;
				break;
			}
		}
		
		if (!found) { 
			for (int i = 0; i < num_lines; ++i) free(lines[i]);
			free(lines);
			return;
		}
		
		file = fopen(filename, "w");
		if (!file) {
			perror("无法写入文件");
			for (int i = 0; i < num_lines; ++i) free(lines[i]);
			free(lines);
			return;
		}
		
		for (int i = 0; i < num_lines; ++i)
			fprintf(file, "%s\n", lines[i]);
		fclose(file);
		
		for (int i = 0; i < num_lines; ++i)
			free(lines[i]);
		free(lines);
}

void changePassword_administrator_UI()
{
	// init_console();
	initgraph(550, 500);
	setbkcolor(WHITE);
	cleardevice();
	
	// 输入框参数
	struct InputBox boxes[2] = {
		{140, 100, 300, 30, {0}, 0}, // 账户
//		{140, 200, 300, 30, {0}, 0}, // 原密码
		{140, 300, 300, 30, {0}, 0}	 // 新密码
	};
	
	// 按钮
	struct Button btn = {250, 400, 100, 30, "确认"};
	
	setfont(20, 0, "宋体");
	settextcolor(BLACK);
	
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				int mx = msg.x, my = msg.y;
				
				// 输入框
				for (int i = 0; i < 2; i++)
				{
					boxes[i].has_focus = (mx >= boxes[i].x && mx <= boxes[i].x + boxes[i].width &&
						my >= boxes[i].y && my <= boxes[i].y + boxes[i].height);
				}
				
				// 按钮
				if (mx >= btn.x && mx <= btn.x + btn.width &&
					my >= btn.y && my <= btn.y + btn.height)
				{
					changePassword_administrator(boxes[0].text, boxes[1].text);
					show_message_window("修改成功！");
					return;
				}
			}
		}
		
		while (kbmsg())
		{
			key_msg k = getkey();
			if (k.msg == key_msg_down)
			{
				for (int i = 0; i < 2; i++)
				{
					if (boxes[i].has_focus)
					{
						size_t len = strlen(boxes[i].text);
						if (k.key == VK_BACK)
						{
							if (len > 0)
								boxes[i].text[len - 1] = '\0';
						}
						else if (k.key >= 32 && k.key <= 126 && len < 255)
						{
							boxes[i].text[len] = k.key;
							boxes[i].text[len + 1] = '\0';
						}
					}
				}
			}
		}
		
		cleardevice();
		
		outtextxy(50, 105, "账  户:");
		//outtextxy(50, 205, "原密码:");
		outtextxy(50, 305, "新密码:");
		
		for (int i = 0; i < 2; i++)
		{
			setcolor(boxes[i].has_focus ? RED : BLACK);
			rectangle(boxes[i].x, boxes[i].y, boxes[i].x + boxes[i].width, boxes[i].y + boxes[i].height);
			outtextxy(boxes[i].x + 5, boxes[i].y + 5, boxes[i].text);
		}
		
		setcolor(BLACK);
		rectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);
		int tw = textwidth(btn.text);
		int th = textheight(btn.text);
		outtextxy(btn.x + (btn.width - tw) / 2, btn.y + (btn.height - th) / 2, btn.text);
	}
	
	closegraph();
}

void showAdministratorMenu_search_UI()
{
	closegraph();
	initgraph(800, 600);
	setcaption("查询信息");
	setbkcolor(EGERGB(240, 240, 240));
	cleardevice();
	
	// 按钮
	const int btnWidth = 220;
	const int btnHeight = 45;
	const int startX = (800 - btnWidth) / 2;
	int currentY = 120;
	const int verticalSpacing = 30;
	
	Button buttons[3] = {  
		{startX, currentY, btnWidth, btnHeight, "查询预约信息"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "查询入住信息"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "返回"}
	};
	
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
								// 功能代码
								char *iii = NULL;
								iii = get_user_id();
								if (iii != NULL)
								{
									again:
									struct strbook *head = read_booklist_file(iii);
									head = sortStrbookList(head);
									if (head != NULL)
									{
										if (display_booking_table_administrator(head))
										{
											goto again;
										}
									}
								}
								
								initgraph(800, 600);
								setcaption("查询信息");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 1:
							{
								closegraph();
								// 功能代码
								struct live_record* head = load_lives("liveinlist.txt");
								head = filter_by_id(get_user_id(),head);
								head = sortLiveRecords(head);
								display_live_table_administrator(head);
								
								initgraph(800, 600);
								setcaption("查询信息");
								setbkcolor(EGERGB(240, 240, 240));
								cleardevice();
								break;
							}
						case 2:
							{
								closegraph();
								return;
								break;
							}
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

int get_book_state()
{
	const int input_width = 400;
	const int input_height = 30;
	const int input_x = (WIDTH - input_width) / 2;
	const int input_y = 100;
	const int button_width = 80;
	const int button_height = 30;
	const int query_btn_x = (WIDTH - button_width * 2 - 20) / 2;
	const int query_btn_y = 200;
	const int return_btn_x = query_btn_x + button_width + 20;
	const int return_btn_y = 200;
	
	bool is_input_active = false;
	char id[256] = {0};
	int id_len = 0;
	
	initgraph(WIDTH, HEIGHT, INIT_NOBORDER);
	setcaption("预约状态修改");
	
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				if (msg.x >= input_x && msg.x <= input_x + input_width &&
					msg.y >= input_y && msg.y <= input_y + input_height)
				{
					is_input_active = true;
				}
				else
				{
					is_input_active = false;
				}
				
				if (msg.x >= query_btn_x && msg.x <= query_btn_x + button_width &&
					msg.y >= query_btn_y && msg.y <= query_btn_y + button_height)
				{
					closegraph();
					if (id_len == 0) return 0;  
					
					char* endptr;
					errno = 0;
					long val = strtol(id, &endptr, 10);
					
					if (errno == ERANGE) {
						return val > 0 ? INT_MAX : INT_MIN;  
					}
					return (int)val;
				}
				
				if (msg.x >= return_btn_x && msg.x <= return_btn_x + button_width &&
					msg.y >= return_btn_y && msg.y <= return_btn_y + button_height)
				{
					closegraph();
					return -1; 
				}
			}
		}
		
		if (is_input_active)
		{
			while (kbmsg())
			{
				key_msg kmsg = getkey();
				if (kmsg.msg == key_msg_down)
				{
					if (kmsg.key == 8) 
					{
						if (id_len > 0)
						{
							id[--id_len] = '\0';
						}
					}
					else if (kmsg.key >= '0' && kmsg.key <= '9' && id_len < 255)  
					{
						id[id_len++] = kmsg.key;
						id[id_len] = '\0';
					}
				}
			}
		}
		
		cleardevice();
		setbkcolor(WHITE);
		setcolor(BLACK);
		
		setfont(18, 0, "SimSun");
		outtextxy(input_x, input_y - 60, "输入想修改的状态");  
		outtextxy(input_x, input_y - 30, "1：已预约  2：已入住  3：已取消");  
		
		setfillcolor(WHITE);
		bar(input_x, input_y, input_x + input_width, input_y + input_height);
		setcolor(is_input_active ? BLACK : BLACK);
		rectangle(input_x, input_y, input_x + input_width, input_y + input_height);
		outtextxy(input_x + 5, input_y + 8, id);
		
		setfillcolor(0xDDDDDD);
		bar(query_btn_x, query_btn_y, query_btn_x + button_width, query_btn_y + button_height);
		rectangle(query_btn_x, query_btn_y, query_btn_x + button_width, query_btn_y + button_height);
		outtextxy(query_btn_x + 20, query_btn_y + 8, "修改");
		
		bar(return_btn_x, return_btn_y, return_btn_x + button_width, return_btn_y + button_height);
		rectangle(return_btn_x, return_btn_y, return_btn_x + button_width, return_btn_y + button_height);
		outtextxy(return_btn_x + 20, return_btn_y + 8, "返回");
	}
	
	closegraph();
	return -1;
}

typedef struct
{
	int x, y;
	int width, height;
	char text[50];
	long long book_id;
} BButton;

int bookings_change(long long my_book_id,int state)
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
			real_found++;
			fprintf(temp_file, "%lld %d %d %d %s %d\n", book_id, time, roomtype, last, id, state);
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
		show_message_window("修改该预约完成！");
		return 0;
	}
	
	return -1;
}

int display_booking_table_administrator(struct strbook *head) 
{
	// 窗口参数
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int ROW_HEIGHT = 40;
	const int COL_WIDTH[] = {120, 150, 100, 80, 120, 100}; // 列宽设置
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	setrendermode(RENDER_MANUAL);
	// initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	//	init_console();
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

	// 遍历链表显示数据
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
		BButton btn = {WINDOW_WIDTH - 110, y_pos, 100, 30, "修改"};
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
					{
						bookings_change(row_btns[i].book_id,get_book_state());
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

int display_live_table_administrator(struct live_record *head)
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
		/*
		//行按钮
		for (int i = 0; i < btn_count; ++i)
		{
			setfillcolor(0x00CC99);
			bar(row_btns[i].x, row_btns[i].y,
				row_btns[i].x + row_btns[i].width,
				row_btns[i].y + row_btns[i].height);
			setcolor(BLACK);
			outtextxy(row_btns[i].x + 15, row_btns[i].y + 8, row_btns[i].text);
		}*/ 
		
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
					return 0;
				}
				
				/*// 退房
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
				}*/
			}
		}
	}
	
	free(row_btns);
	closegraph();
	return 0;
}
