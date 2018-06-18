#include "Tools.h"

//��������:���ô�����Ϣ
int SetWindowsSize(char* pszWindowsTitle, short nX, short nY)
{
	//���ÿ���̨����
	SetConsoleTitleA(pszWindowsTitle);
	HANDLE hStdin, hStdOut;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//���������̨���ڴ�С
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X + 1,pos.Y + 1 };
	//���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(hStdOut, BufferSize))
	{
		//���ÿ���̨���ڻ�����ʧ��
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return 0;
	}
	SMALL_RECT srctWindow = { 0,0,nX,nY };
	if (!SetConsoleWindowInfo(hStdOut, 1, &srctWindow))
	{
		//���ÿ���̨���ڴ�С
		printf("size err %d\n", GetLastError());
		return 0;
	}
	COORD Buffer = { nX + 1,nY + 1 };
	//���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(hStdOut, Buffer))
	{	//���ÿ���̨���ڻ�����ʧ��
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return 0;
	}
	return 1;
}

//��ĳ�����ӡ�ַ�
void WriteChar(short x, short y, const char* pStr, WORD color, int isback)
{
	//���ù������
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;//�Ƿ���ʾ���
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	//�޸Ĺ���ڿ���̨�е�����λ��
	COORD pos = { x * 2,y };//������λ��
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���
	SetConsoleCursorPosition(hOutStd, pos);//���õ�ǰ�Ĺ��λ��
	SetConsoleTextAttribute(hOutStd, color);//��������ı�����ɫ
	if (!isback)//�Ƿ����ñ���ɫ 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);
	}
	printf("%s", pStr);
}

void SetPosition(int x, int y)
{
	COORD pos = { (short)x * 2, (short)y };//������λ��
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���
	SetConsoleCursorPosition(hOutStd, pos);//���õ�ǰ�Ĺ��λ��
}

//��ĳ�����ӡint��
void WriteNum(short x, short y, int pnum, WORD color, int isback)
{
	//���ù������
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;//�Ƿ���ʾ���
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	//�޸Ĺ���ڿ���̨�е�����λ��
	COORD pos = { x * 2,y };//������λ��
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���
	SetConsoleCursorPosition(hOutStd, pos);//���õ�ǰ�Ĺ��λ��
	SetConsoleTextAttribute(hOutStd, color);//��������ı�����ɫ
	if (!isback) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_BLUE | BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);
	}
	printf("%d", pnum);
}

//���ñ���ɫ
void SetBackColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
}

//��Ч
void Sound(int i)
{
	switch (i)
	{
	case 1:
		PlaySoundA("sound\\gameover.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 2:
		PlaySoundA("sound\\���������-����_3(level_3).wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 3:
		PlaySoundA("sound\\���������-bad_1.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 4:
		PlaySoundA("sound\\Win.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 5:
		PlaySoundA("sound\\̹�˴�սսǰ��������.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 6:
		PlaySoundA("sound\\̹�˴�ս-fire.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case 7:
		
		break;
	case 8:
		PlaySoundA("sound\\�˵�(menu).wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	default:
		break;
	}
}
