#include <easyx.h>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

ExMessage msg;

bool inArea(int mx, int my, int x, int y, int w, int h)
{
	return mx > x && mx < x + w && my > y && my < y + h;
}

bool button(int x, int y, int w, int h, const char* text)
{
	setfillcolor(RGB(230, 231, 232));
	fillroundrect(x, y, x + w, y + h, 5, 5);
	int hSpace = (w - textwidth(text)) / 2;
	int vSpace = (h - textheight(text)) / 2;
	outtextxy(x + hSpace, y + vSpace, text);

	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
		return true;
	return false;
}

void rectangular_border(int x, int y, int w, int h, int thick)
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, thick);
	rectangle(x, y, x + w, y + h);
}

int main() 
{
	initgraph(1000, 600);
	IMAGE img;
	loadimage(&img, "logo.jpg", 1000, 600);
	putimage(0, 0, &img);

	mciSendString("open bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);

	Sleep(1000);

	mciSendString("close bgm", NULL, 0, NULL);

	closegraph();

	initgraph(500, 340);

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "Fatal Error!");

	HICON hIcon = LoadIcon(NULL, IDI_ERROR);
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

	while (true)
	{
		BeginBatchDraw();

		setbkcolor(WHITE);
		cleardevice();

		settextcolor(BLACK);
		setbkmode(TRANSPARENT);

		settextstyle(16, 0, "ºÚÌå");
		outtextxy(5, 15, "An unexpected error has occured! Pressing 'Send Reoprt' will");
		outtextxy(5, 32, "send us helpful debugging information that may help us resolve");
		outtextxy(5, 49, "this issue in the future.");
		outtextxy(5, 66, "");
		outtextxy(5, 80, "You can also contact us directly at feedback@popcamp.com.");

		settextstyle(16, 0, "ËÎÌå");
		rectangular_border(2, 100, 478, 200, 1);
		outtextxy(5, 105, "Exception: Access Violation (code 0xc0000005) at address");
		outtextxy(5, 122, "0041c980 in thread C4A8");
		outtextxy(5, 139, "Mdoule: PlantsVsZombies.exe");
		outtextxy(5, 156, "Logical address: 0001:0001B980");
		outtextxy(5, 173, "");
		outtextxy(5, 187, "0019F9EC 0041C980 0001:0001B980 PlantsVsZombies.exe");
		outtextxy(5, 204, "Params: 435BAFF4 42A9C020 0019FA20 00000913");
		outtextxy(5, 221, "");
		outtextxy(5, 235, "");
		outtextxy(5, 252, "");
		outtextxy(5, 266, "EAX:000B0919 EBX:00000000 ECX:21557F81 EDX:21594020");
		outtextxy(5, 283, "ESI:0019F99C EDI:FFFF0000");

		rectangular_border(5, 310, 240, 20, 2);
		rectangular_border(255, 310, 240, 20, 2);

		peekmessage(&msg, EX_MOUSE);

		settextstyle(16, 0, "ºÚÌå");
		
		if (button(5, 310, 240, 20, "Send Report"))
			break;
		if (button(255, 310, 240, 20, "Close Now"))
			break;

		EndBatchDraw();
	}
	closegraph();
	return 0;
}
