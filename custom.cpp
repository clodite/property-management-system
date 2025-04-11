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


void drawButton(const Button &btn);
char *get_user_id();
int display_booking_table(struct strbook *head);
void change_password(const char *username, const char *old_password, const char *new_password);
void change_password_UI();
int book_room_UI();
struct strbook* sortStrbookList(struct strbook* head);

void displayString(const char *str)
{ // 调试用代码（ai写的）
	setlocale(LC_ALL, "");

	initgraph(640, 480);

	setbkcolor(WHITE);
	setcolor(BLACK);
	cleardevice();

	setfont(24, 0, "宋体");

	wchar_t wstr[256];
	mbstowcs(wstr, str, 256);

	int textWidth = textwidth(wstr);
	int x = (640 - textWidth) / 2;
	int y = 240;
	outtextxy(x, y, wstr);

	for (; is_run(); delay_fps(60))
	{
		if (kbhit())
		{
			getch();
			break;
		}
		if (!is_run())
			break;
	}

	closegraph();
}

/*
预约状态参数含义

1 已预约
2 已预约未入住
3 已取消

*/
// 主菜单窗口
void showCustomMenu()
{
	closegraph();
	initgraph(800, 600);
	setcaption("客户预约");
	setbkcolor(EGERGB(240, 240, 240));
	cleardevice();

	// 按钮
	const int btnWidth = 180;
	const int btnHeight = 45;
	const int startX = (800 - btnWidth) / 2;
	int currentY = 120;
	const int verticalSpacing = 30;

	Button buttons[5] = {
		{startX, currentY, btnWidth, btnHeight, "所有房间"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "预约房间"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "我的预约"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "修改密码"},
		{startX, currentY += btnHeight + verticalSpacing, btnWidth, btnHeight, "我的会员"}};

	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				for (int i = 0; i < 5; ++i)
				{
					const Button &btn = buttons[i];
					if (isInArea(msg.x, msg.y, btn.x, btn.y, btn.width, btn.height))
					{
						switch (i)
						{
						case 0:
						{
							struct room *head = load_rooms("room.txt");
							closegraph();
							// 功能代码
							showRoom(head);

							initgraph(800, 600);
							setcaption("客户预约");
							setbkcolor(EGERGB(240, 240, 240));
							cleardevice();
							free_rooms(head);
							break;
						}
						case 1:
						{
							closegraph();
							// 功能代码
							book_room_UI();
							
							initgraph(800, 600);
							setcaption("客户预约");
							setbkcolor(EGERGB(240, 240, 240));
							cleardevice();
							break;
						}
						case 2:
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
									if (display_booking_table(head))
									{
										goto again;
									}
								}
							}

							initgraph(800, 600);
							setcaption("客户预约");
							setbkcolor(EGERGB(240, 240, 240));
							cleardevice();
							break;
						}
						case 3:
						{
							closegraph();
							// 功能代码
							change_password_UI();
							initgraph(800, 600);
							setcaption("客户预约");
							setbkcolor(EGERGB(240, 240, 240));
							cleardevice();
							break;
						}
						case 4:
						{
							closegraph();
							// 功能代码
							
							initgraph(800, 600);
							setcaption("客户预约");
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

		for (int i = 0; i < 4; ++i)
		{
			drawButton(buttons[i]);
		}
	}
	closegraph();
}

int compare_room(const void *a, const void *b)
{
	const struct room *roomA = (const struct room *)a;
	const struct room *roomB = (const struct room *)b;
	if(roomA->type - roomB->type)
	{
		return roomA->type - roomB->type;
	}
	else
	{
		return roomA->num - roomB->num;
	}
}

const char *get_type_name(int type)
{
	switch (type)
	{
	case 1:
		return "单人间";
	case 2:
		return "双人间";
	case 3:
		return "套房";
	case 4:
		return "豪华套房";
	case 5:
		return "家庭房";
	default:
		return "未知类型";
	}
}

void showRoom(struct room *head)
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
		if(p->state)
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
		if(p->state)
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
		const int col_width[] = {100, 150, 100, 100};

		// 表头
		setfillcolor(EGERGB(220, 220, 220));
		bar(start_x, start_y,
			start_x + col_width[0] + col_width[1] + col_width[2] + col_width[3],
			start_y + row_height);

		int text_x = start_x;
		outtextxy(text_x + 5, start_y + 5, "房号");
		text_x += col_width[0];
		outtextxy(text_x + 5, start_y + 5, "类型");
		text_x += col_width[1];
		outtextxy(text_x + 5, start_y + 5, "价格(元)");
		text_x += col_width[2];
		outtextxy(text_x + 5, start_y + 5, "面积(m^2)");

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
		for (int i = 0; i <= 4; i++)
		{
			line(x, start_y, x, start_y + row_height * (visibleRows + 1));
			if (i < 4)
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

char *get_user_id()
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
	setcaption("用户ID输入");

	for (; is_run(); delay_fps(60))
	{
		// 鼠标
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				// 输入框
				if (msg.x >= input_x && msg.x <= input_x + input_width &&
					msg.y >= input_y && msg.y <= input_y + input_height)
				{
					is_input_active = true;
				}
				else
				{
					is_input_active = false;
				}

				// 查询
				if (msg.x >= query_btn_x && msg.x <= query_btn_x + button_width &&
					msg.y >= query_btn_y && msg.y <= query_btn_y + button_height)
				{
					closegraph();
					return strdup(id);
				}

				// 返回
				if (msg.x >= return_btn_x && msg.x <= return_btn_x + button_width &&
					msg.y >= return_btn_y && msg.y <= return_btn_y + button_height)
				{
					closegraph();
					return NULL;
				}
			}
		}

		// 键盘
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
					else if (kmsg.key >= 32 && kmsg.key <= 126 && id_len < 255)
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
		outtextxy(input_x, input_y - 30, "请输入ID");

		setfillcolor(WHITE);
		bar(input_x, input_y, input_x + input_width, input_y + input_height);
		setcolor(is_input_active ? BLACK : BLACK);
		rectangle(input_x, input_y, input_x + input_width, input_y + input_height);
		outtextxy(input_x + 5, input_y + 8, id);

		setfillcolor(0xDDDDDD);
		bar(query_btn_x, query_btn_y, query_btn_x + button_width, query_btn_y + button_height);
		rectangle(query_btn_x, query_btn_y, query_btn_x + button_width, query_btn_y + button_height);
		outtextxy(query_btn_x + 20, query_btn_y + 8, "确认");

		bar(return_btn_x, return_btn_y, return_btn_x + button_width, return_btn_y + button_height);
		rectangle(return_btn_x, return_btn_y, return_btn_x + button_width, return_btn_y + button_height);
		outtextxy(return_btn_x + 20, return_btn_y + 8, "返回");
	}

	closegraph();
	return NULL;
}

typedef struct
{
	int x, y;
	int width, height;
	char text[50];
	long long book_id;
} BButton;

int display_booking_table(struct strbook *head) 
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

	//	setlinecolor(BLACK);
	//	setlinestyle(PS_SOLID, 1); // 设置线条样式和宽度

	//	x = 0;
	//	for (int i = 0; i < 6; ++i) {
	//		line(x, 0, x, WINDOW_HEIGHT);
	//		x += COL_WIDTH[i];
	//	}
	//	line(x, 0, x, WINDOW_HEIGHT); // 最后一列

	int y_pos = ROW_HEIGHT;
	//	while (y_pos < WINDOW_HEIGHT) {
	//		line(0, y_pos, WINDOW_WIDTH, y_pos);
	//		y_pos += ROW_HEIGHT;
	//	}

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
		BButton btn = {WINDOW_WIDTH - 110, y_pos, 100, 30, "取消"};
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
						bookings_cancel(row_btns[i].book_id);
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

void change_password(const char *username, const char *old_password, const char *new_password)
{
	// init_console();
	FILE *original_file = fopen("user.txt", "r");
	if (!original_file)
	{
		return;
	}

	char temp_filename[256];
	snprintf(temp_filename, sizeof(temp_filename), "%s.tmp", "user.txt");
	FILE *temp_file = fopen(temp_filename, "w");
	if (!temp_file)
	{
		fclose(original_file);
		return;
	}

	char line_user[256];
	char line_pass[256];
	char line_level[256];
	int found = 0;

	while (fgets(line_user, sizeof(line_user), original_file))
	{
		if (!fgets(line_pass, sizeof(line_pass), original_file))
			break;
		if (!fgets(line_level, sizeof(line_level), original_file))
			break;

		// 去除换行符
		char current_user[256], current_pass[256];
		strcpy(current_user, line_user);
		current_user[strcspn(current_user, "\n")] = '\0';
		strcpy(current_pass, line_pass);
		current_pass[strcspn(current_pass, "\n")] = '\0';

		if (strcmp(current_user, username) == 0 && strcmp(current_pass, old_password) == 0)
		{
			fprintf(temp_file, "%s%s\n%s", line_user, new_password, line_level);
			found = 1;
		}
		else
		{
			fputs(line_user, temp_file);
			fputs(line_pass, temp_file);
			fputs(line_level, temp_file);
		}
	}

	fclose(original_file);
	fclose(temp_file);

	if (!found)
	{
		remove(temp_filename);
		printf("222");
		show_message_window("用户名或密码不正确呦");
		return;
	}

	remove("user.txt");
	if (rename(temp_filename, "user.txt") != 0)
	{
		remove(temp_filename);
		printf("111");
	}
	show_message_window("修改成功！");
}

void change_password_UI()
{
	// init_console();
	initgraph(550, 500);
	setbkcolor(WHITE);
	cleardevice();

	// 输入框参数
	struct InputBox boxes[3] = {
		{140, 100, 300, 30, {0}, 0}, // 账户
		{140, 200, 300, 30, {0}, 0}, // 原密码
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
				for (int i = 0; i < 3; i++)
				{
					boxes[i].has_focus = (mx >= boxes[i].x && mx <= boxes[i].x + boxes[i].width &&
										  my >= boxes[i].y && my <= boxes[i].y + boxes[i].height);
				}

				// 按钮
				if (mx >= btn.x && mx <= btn.x + btn.width &&
					my >= btn.y && my <= btn.y + btn.height)
				{
					change_password(boxes[0].text, boxes[1].text, boxes[2].text);
					return;
				}
			}
		}

		while (kbmsg())
		{
			key_msg k = getkey();
			if (k.msg == key_msg_down)
			{
				for (int i = 0; i < 3; i++)
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
		outtextxy(50, 205, "原密码:");
		outtextxy(50, 305, "新密码:");

		for (int i = 0; i < 3; i++)
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

extern "C" void show_message_window(const char *message)
{
	initgraph(200, 100);
	setbkcolor(WHITE);
	cleardevice();

	setcolor(BLACK);
	int text_width = textwidth(message);
	int text_height = textheight(message);
	outtextxy((200 - text_width) / 2,
			  (100 - text_height) / 2 - 10,
			  message);

	struct Button confirm_btn = {(200 - 80) / 2, 100 - 30 - 10, 80, 30, "确认"};

	setfillcolor(EGEARGB(0xFF, 0xDD, 0xDD, 0xDD));
	bar(confirm_btn.x, confirm_btn.y,
		confirm_btn.x + confirm_btn.width,
		confirm_btn.y + confirm_btn.height);

	setcolor(BLACK);
	rectangle(confirm_btn.x + 1, confirm_btn.y + 1,
			  confirm_btn.x + confirm_btn.width - 1,
			  confirm_btn.y + confirm_btn.height - 1);

	int btn_text_w = textwidth(confirm_btn.text);
	int btn_text_h = textheight(confirm_btn.text);
	outtextxy(confirm_btn.x + (confirm_btn.width - btn_text_w) / 2,
			  confirm_btn.y + (confirm_btn.height - btn_text_h) / 2,
			  confirm_btn.text);

	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				if (msg.x >= confirm_btn.x &&
					msg.x <= confirm_btn.x + confirm_btn.width &&
					msg.y >= confirm_btn.y &&
					msg.y <= confirm_btn.y + confirm_btn.height)
				{
					closegraph();
					return;
				}
			}
		}
	}
}

const int INPUT_COUNT=5;

typedef struct {
	int x, y, width, height;
	char buffer[256];
	int is_active;
	int input_type; 
} IInputBox;

void drawInputBox(IInputBox *ib) {
	setcolor(EGERGB(0, 0, 0));
	rectangle(ib->x, ib->y, ib->x + ib->width, ib->y + ib->height);
	
	setfillcolor(WHITE);
	bar(ib->x + 1, ib->y + 1, ib->x + ib->width - 1, ib->y + ib->height - 1);
	
	setcolor(BLACK);
	outtextxy(ib->x + 5, ib->y + (ib->height - textheight(ib->buffer)) / 2, ib->buffer);
	
	if (ib->is_active) {
		int text_w = textwidth(ib->buffer);
		line(ib->x + 5 + text_w + 1, ib->y + 5,
			ib->x + 5 + text_w + 1, ib->y + ib->height - 5);
	}
}

int get_type_from_name(const char *name)
{	
	if (strcmp(name, "单人间") == 0) {
		return 1;
	} else if (strcmp(name, "双人间") == 0) {
		return 2;
	} else if (strcmp(name, "套房") == 0) {
		return 3;
	} else if (strcmp(name, "豪华套房") == 0) {
		return 4;
	} else if (strcmp(name, "家庭房") == 0) {
		return 5;
	} else {
		return 0; 
	}
}

int book_room_UI() {
	initgraph(WIDTH, HEIGHT);
	setbkcolor(WHITE); 
//	init_console();
	IInputBox inputs[INPUT_COUNT] = {
		{50, 100, 100, 30, "", 0, 0},  
		{180, 100, 100, 30, "", 0, 0},  
		{310, 100, 100, 30, "", 0, 0},  
		{50, 200, 200, 30, "", 0, 1}, 
		{260, 200, 200, 30, "", 0, 0}  
	};
	
	struct Button confirm = {(WIDTH - 100)/2-50, HEIGHT - 100, 80, 40, "确认"};
	struct Button ret = {(WIDTH - 100)/2+50, HEIGHT - 100, 80, 40, "返回"};
	
	for (;;) {
		cleardevice();
		
		setfont(20,0,"宋体");
		
		outtextxy(50, 50, "入住时间");
		outtextxy(160, 105, "年");
		outtextxy(285, 105, "月");
		outtextxy(410, 105, "日");
		outtextxy(50, 180, "房间类型"); 
		outtextxy(260, 180, "入住时长（天）"); 
		
		for (int i = 0; i < INPUT_COUNT; i++) {
			drawInputBox(&inputs[i]);
		}
		
		drawButton(confirm);
		drawButton(ret);
		
		while (kbhit()) {
			int ch = getch();
			for (int i = 0; i < INPUT_COUNT; i++) {
				if (inputs[i].is_active) {
					if (ch == '\b') {  
						if (strlen(inputs[i].buffer) > 0) {
							if (inputs[i].input_type == 1 && strlen(inputs[i].buffer) >= 2) {
								unsigned char last_char = inputs[i].buffer[strlen(inputs[i].buffer) - 1];
								if (last_char >= 0x40 && last_char <= 0xFE) {  
									inputs[i].buffer[strlen(inputs[i].buffer) - 2] = '\0';  
								} else {
									inputs[i].buffer[strlen(inputs[i].buffer) - 1] = '\0';  
								}
							} else {
								inputs[i].buffer[strlen(inputs[i].buffer) - 1] = '\0'; 
							}
						}
					}
					else if (ch >= 32 && ch <= 126) {  
						if (inputs[i].input_type == 0 && (ch < '0' || ch > '9'))
							continue;
						
						if ((inputs[i].input_type == 1 && strlen(inputs[i].buffer) < 20) ||
							(inputs[i].input_type == 0 && strlen(inputs[i].buffer) < 11)) 
						{
							strncat(inputs[i].buffer, (char*)&ch, 1);
						}
					}
					else if (ch >= 0x81 && ch <= 0xFE) {  
						if (inputs[i].input_type == 1 && strlen(inputs[i].buffer) < 19) {
							int ch2 = getch();  
							char temp[3] = {0};
							temp[0] = ch;
							temp[1] = ch2;
							strncat(inputs[i].buffer, temp, 2);
						}
					}
				}
			}
		}
		
		if (mousemsg()) {
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down()) {
				for (int i = 0; i < INPUT_COUNT; i++) {
					IInputBox *ib = &inputs[i];
					if (msg.x >= ib->x && msg.x <= ib->x + ib->width &&
						msg.y >= ib->y && msg.y <= ib->y + ib->height) 
					{
						for (int j = 0; j < INPUT_COUNT; j++)
							inputs[j].is_active = 0;
						ib->is_active = 1;
						break;
					}
				}
				
				if (msg.x >= confirm.x && msg.x <= confirm.x + confirm.width &&
					msg.y >= confirm.y && msg.y <= confirm.y + confirm.height) 
				{
					int values[4];
					char str_value[21] = {0};
					
					for (int i = 0; i < 3; i++)
						values[i] = atoi(inputs[i].buffer);
					
					strncpy(str_value, inputs[3].buffer, 20);
					values[3] = atoi(inputs[4].buffer);
					
					//功能代码
					time_t now = time(NULL);
					struct tm* local_time = localtime(&now);
					if(values[0]<local_time->tm_year+1900)
					{
						show_message_window("时间不正确哟");
					}
					else if(values[0]==local_time->tm_year+1900&&values[1]<local_time->tm_mon+1)
					{
						show_message_window("时间不正确哟");
					}
					else if(values[0]==local_time->tm_year+1900&&values[1]==local_time->tm_mon+1&&values[2]<local_time->tm_mday)
					{
						show_message_window("时间不正确哟");
					}
					else if(values[1]>12||values[2]>32)
					{
						show_message_window("你jb要干啥");
					}
					else
					{
						struct time ttime={values[0],values[1],values[2],14};
						int type=get_type_from_name(str_value);
						int live_time=values[3]*24-1;
						char* user_id=get_user_id();
						int result=custom_book(user_id,type,live_time,time_to_timestamp(ttime),0);
						if(result==-2)
						{
							show_message_window("没有空房间了喵");
						}
						if(result==0)
						{
							show_message_window("预约成功！");
						}
					}
					
					printf("收到数据：%d, %d, %d, %s, %d\n",
						values[0], values[1], values[2], str_value, values[3]);
					
					return 0;
				}
				else if (msg.x >= ret.x && msg.x <= ret.x + ret.width &&
					msg.y >= ret.y && msg.y <= ret.y + ret.height) 
				{
					closegraph();
					return 0;
				}
			
			}
		}
		
		delay_ms(1);
	}
	
	closegraph();
	return 0;
}
