#include <graphics.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include "function.h"
#include "struct.h"
const int WIDTH = 400;
const int HEIGHT = 300;
enum AppState
{
	LOGIN,
	REGISTER
};
AppState currentState = LOGIN;

// 输入框结构体
struct InputBox
{
	int x, y, width, height;
	std::string text;
	bool hasFocus;
	bool isPassword;
};

void drawInputBox(const InputBox &box)
{
	setcolor(EGERGB(0, 0, 0));
	rectangle(box.x, box.y, box.x + box.width, box.y + box.height);

	// 密码显示为*
	std::string showText = box.text;
	if (box.isPassword && !box.text.empty())
	{
		showText = std::string(box.text.length(), '*');
	}
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(EGERGB(0, 0, 0));
	setfont(24, 0, "宋体");
	outtextxy(box.x + 5, box.y + 5, showText.c_str());

	if (box.hasFocus)
	{
		setlinewidth(2);
		rectangle(box.x - 2, box.y - 2, box.x + box.width + 2, box.y + box.height + 2);
		setlinewidth(1);
	}
}

void drawButton(const Button &btn)
{
	setfillcolor(EGERGB(200, 200, 200));
	bar(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);

	setcolor(EGERGB(0, 0, 0));
	outtextxy(btn.x + (btn.width - textwidth(btn.text)) / 2,
			  btn.y + (btn.height - textheight(btn.text)) / 2,
			  btn.text);
}

InputBox regUserBox = {120, 100, 180, 30, "", false, false};
InputBox regPassBox = {120, 150, 180, 30, "", false, true};

void drawRegisterWindow()
{
	setfillcolor(EGERGB(200, 200, 200));
	bar(50, 50, WIDTH - 50, HEIGHT - 50);

	setcolor(BLACK);
	setfont(24, 0, "Arial");
	outtextxy(140, 60, "注册");
	setfont(12, 0, "Arial");

	drawInputBox(regUserBox);
	drawInputBox(regPassBox);
	setfont(24, 0, "宋体");
	outtextxy(60, 100, "账户:");
	outtextxy(60, 150, "密码:");

	// 按钮
	Button okBtn = {120, 200, 80, 30, "确定"};
	Button cancelBtn = {220, 200, 80, 30, "取消"};
	drawButton(okBtn);
	drawButton(cancelBtn);
}

bool isInArea(int x, int y, int areaX, int areaY, int width, int height)
{
	return x >= areaX && x <= areaX + width &&
		   y >= areaY && y <= areaY + height;
}

int main()
{
again:
	initgraph(WIDTH, HEIGHT);
	setcaption("欢迎来到千恋万花的世界~");
	setbkcolor(EGERGB(255, 255, 255));
	cleardevice();

	setbkmode(TRANSPARENT);

	// 输入框
	InputBox usernameBox = {100, 80, 200, 30, "", false, false};
	InputBox passwordBox = {100, 140, 200, 30, "", false, true};
	Button loginBtn = {150, 200, 100, 40, "登录"};
	Button regBtn = {220, 200, 100, 40, "注册"};

	// 文字
	setcolor(EGERGB(0, 0, 0));
	outtextxy(20, 90, "账户:");
	outtextxy(20, 150, "密码:");

	for (; is_run(); delay_fps(60))
	{
		while (kbmsg())
		{
			key_msg msg = getkey();
			if (msg.msg == key_msg_down)
			{
				if (currentState == LOGIN)
				{
					InputBox *currentBox = nullptr;
					if (usernameBox.hasFocus)
						currentBox = &usernameBox;
					else if (passwordBox.hasFocus)
						currentBox = &passwordBox;

					if (currentBox)
					{
						if (msg.key == 8)
						{
							if (!currentBox->text.empty())
							{
								currentBox->text.pop_back();
							}
						}
						else if (msg.key >= 32 && msg.key <= 126)
						{
							currentBox->text += (char)msg.key;
						}
					}
				}
				else if (currentState == REGISTER)
				{
					InputBox *currentBox = nullptr;
					if (regUserBox.hasFocus)
						currentBox = &regUserBox;
					else if (regPassBox.hasFocus)
						currentBox = &regPassBox;

					if (currentBox)
					{
						if (msg.key == 8)
						{ // 退格
							if (!currentBox->text.empty())
							{
								currentBox->text.pop_back();
							}
						}
						else if (msg.key >= 32 && msg.key <= 126)
						{
							currentBox->text += (char)msg.key;
						}
					}
				}
			}
		}

		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{
				if (currentState == LOGIN)
				{
					usernameBox.hasFocus = isInArea(msg.x, msg.y,
													usernameBox.x, usernameBox.y,
													usernameBox.width, usernameBox.height);

					passwordBox.hasFocus = isInArea(msg.x, msg.y,
													passwordBox.x, passwordBox.y,
													passwordBox.width, passwordBox.height);

					if (isInArea(msg.x, msg.y, loginBtn.x, loginBtn.y,
								 loginBtn.width, loginBtn.height))
					{
						// 登录逻辑
						switch (get_account_type(usernameBox.text.c_str(), passwordBox.text.c_str()))
						{
						case 1:
							// closegraph();
							showCustomMenu();
							break;
						case 2:
							showFrontMenu();
							break;
						case 3:
							showAdministratorMenu();
							break;
						case -1:
							closegraph();
							show_message_window("账号或密码不正确");
							goto again;
							break;
						}

						//						char buf[256];
						//						sprintf(buf, "type:%d", get_account_type(usernameBox.text.c_str(),passwordBox.text.c_str()));
						//						MessageBox(getHWnd(), buf, "Login Info", MB_OK);
					}
					else if (isInArea(msg.x, msg.y, regBtn.x, regBtn.y,
									  regBtn.width, regBtn.height))
					{
						// 注册界面
						currentState = REGISTER;
						regUserBox.text.clear();
						regPassBox.text.clear();
					}
				}
				else if (currentState == REGISTER)
				{
					regUserBox.hasFocus = isInArea(msg.x, msg.y,
												   regUserBox.x, regUserBox.y,
												   regUserBox.width, regUserBox.height);

					regPassBox.hasFocus = isInArea(msg.x, msg.y,
												   regPassBox.x, regPassBox.y,
												   regPassBox.width, regPassBox.height);

					// 确认按钮
					if (isInArea(msg.x, msg.y, 120, 200, 80, 30))
					{
						if (!regUserBox.text.empty() && !regPassBox.text.empty())
						{
							char buf[256];
							
							int res = add_account(regUserBox.text.c_str(), regUserBox.text.c_str());
							if(res==-1){
								show_message_window("注册失败");
							}
							else if(res==1)
							{
								show_message_window("注册成功");
							}
							//sprintf(buf, "result:%d", add_account(regUserBox.text.c_str(), regUserBox.text.c_str()));
							//MessageBox(getHWnd(), buf, "Register Success", MB_OK);
							currentState = LOGIN;
							goto again;
						}
					}
					// 取消按钮
					else if (isInArea(msg.x, msg.y, 220, 200, 80, 30))
					{
						currentState = LOGIN;
					}
				}
			}
		}

		cleardevice();

		if (currentState == LOGIN)
		{
			outtextxy(20, 90, "账户:");
			outtextxy(20, 150, "密码:");
			drawInputBox(usernameBox);
			drawInputBox(passwordBox);
			drawButton(loginBtn);
			drawButton(regBtn);
		}
		else if (currentState == REGISTER)
		{
			drawRegisterWindow();
		}
	}

	closegraph();
	return 0;
}
