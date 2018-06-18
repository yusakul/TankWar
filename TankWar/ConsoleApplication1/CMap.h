#pragma once
#include "Data.h"
#include "Tools.h"

class CMap
{
public:

	//游戏地图拷贝原始地图
	void InitGameMapfromG_Map(CMap* pMap);

	//初始化自定义地图
	void InitUserMapformG_Map(CMap* pMap);

	//游戏地图拷贝自定义地图
	void InitGameMapfromUser(CMap* pMap);

	//绘制自定义地图
	void DrawUserMap(int level);

	//绘制地图
	void DrawMap(CMap Map);

	//地形还原
	void returnMap(int y, int x, int WAll);

	//游戏内使用的地图
	int GameMap[7][40][40];

	//控制台输出绘制地图坐标;
	void OutPutPos(int nPosX, int nPoxY);

	// 鼠标处理事件
	int MouseEventProc(MOUSE_EVENT_RECORD StcMouse);

	//鼠标拖动事件
	bool MouseMove(MOUSE_EVENT_RECORD &StcMouse);
	
	// 鼠标点击事件
	int MouseClick(MOUSE_EVENT_RECORD &StcMouse);
 
 	// 键盘处理事件
 	int KeyEventProc(KEY_EVENT_RECORD &StcKeyEvent);

	// 笔刷绘制扩展区;
	void BrushDraw(MOUSE_EVENT_RECORD &StcMouse, char *Pstr, WORD color, int isback/*背景色 0是 1否*/);


	//消息处理函数
	int MessageLoop();

	
private:
	int m_nMapVlue;	//自定义写入地图值;
	int flag_switch;	//鼠标事件选项开关

	//键盘

	int key;//记录选中项,初始为第一个
	int flag_kb;//键盘事件回车判断
	int ch;//输入按键
	int flag_enter;//选项菜单循环内回车判断
	int m_nBrush;	//笔刷的大小
	
};