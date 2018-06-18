#pragma once
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")
#include "Data.h"

/*函数功能:设置窗口信息 参数1:窗口名称 参数2:窗口宽度 参数3:窗口高度 返回值:成功返回真*/
int SetWindowsSize(char* pszWindowsTitle, short nX, short nY);

//在某坐标打印
void WriteChar(short x, short y, const char* pStr, WORD color, int isback);

//设置坐标
void SetPosition(int x, int y);


void Sound(int i);//音效

void SetBackColor();//设置文本背景色

void WriteNum(short x, short y, int pnum, WORD color, int isback);//在某坐标打印int型
