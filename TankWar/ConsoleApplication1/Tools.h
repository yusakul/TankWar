#pragma once
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")
#include "Data.h"

/*��������:���ô�����Ϣ ����1:�������� ����2:���ڿ�� ����3:���ڸ߶� ����ֵ:�ɹ�������*/
int SetWindowsSize(char* pszWindowsTitle, short nX, short nY);

//��ĳ�����ӡ
void WriteChar(short x, short y, const char* pStr, WORD color, int isback);

//��������
void SetPosition(int x, int y);


void Sound(int i);//��Ч

void SetBackColor();//�����ı�����ɫ

void WriteNum(short x, short y, int pnum, WORD color, int isback);//��ĳ�����ӡint��
