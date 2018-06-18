#include "Tools.h"

//函数功能:设置窗口信息
int SetWindowsSize(char* pszWindowsTitle, short nX, short nY)
{
	//设置控制台标题
	SetConsoleTitleA(pszWindowsTitle);
	HANDLE hStdin, hStdOut;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获得最大控制台窗口大小
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X + 1,pos.Y + 1 };
	//设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(hStdOut, BufferSize))
	{
		//设置控制台窗口缓冲区失败
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return 0;
	}
	SMALL_RECT srctWindow = { 0,0,nX,nY };
	if (!SetConsoleWindowInfo(hStdOut, 1, &srctWindow))
	{
		//设置控制台窗口大小
		printf("size err %d\n", GetLastError());
		return 0;
	}
	COORD Buffer = { nX + 1,nY + 1 };
	//设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(hStdOut, Buffer))
	{	//设置控制台窗口缓冲区失败
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return 0;
	}
	return 1;
}

//在某坐标打印字符
void WriteChar(short x, short y, const char* pStr, WORD color, int isback)
{
	//设置光标属性
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;//是否显示光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	//修改光标在控制台中的坐标位置
	COORD pos = { x * 2,y };//保存光标位置
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	SetConsoleCursorPosition(hOutStd, pos);//设置当前的光标位置
	SetConsoleTextAttribute(hOutStd, color);//设置输出文本的颜色
	if (!isback)//是否设置背景色 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);
	}
	printf("%s", pStr);
}

void SetPosition(int x, int y)
{
	COORD pos = { (short)x * 2, (short)y };//保存光标位置
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	SetConsoleCursorPosition(hOutStd, pos);//设置当前的光标位置
}

//在某坐标打印int型
void WriteNum(short x, short y, int pnum, WORD color, int isback)
{
	//设置光标属性
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;//是否显示光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	//修改光标在控制台中的坐标位置
	COORD pos = { x * 2,y };//保存光标位置
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	SetConsoleCursorPosition(hOutStd, pos);//设置当前的光标位置
	SetConsoleTextAttribute(hOutStd, color);//设置输出文本的颜色
	if (!isback) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);
	}
	printf("%d", pnum);
}

//设置背景色
void SetBackColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
}

//音效
void Sound(int i)
{
	switch (i)
	{
	case 1:
		PlaySoundA("sound\\gameover.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 2:
		PlaySoundA("sound\\超级马里奥-级别_3(level_3).wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 3:
		PlaySoundA("sound\\超级马里奥-bad_1.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 4:
		PlaySoundA("sound\\Win.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 5:
		PlaySoundA("sound\\坦克大战战前背景音乐.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 6:
		PlaySoundA("sound\\坦克大战-fire.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 7:
		
		break;
	case 8:
		PlaySoundA("sound\\菜单(menu).wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	default:
		break;
	}
}
