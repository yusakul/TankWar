#include "CMap.h"

//游戏地图拷贝原始地图
void CMap::InitGameMapfromG_Map(CMap* pMap)
{
	memcpy(pMap->GameMap, g_Map, sizeof(pMap->GameMap));
}

//初始化自定义地图
void CMap::InitUserMapformG_Map(CMap* pMap)
{
	
	memcpy(g_UserMap, g_Map, sizeof(pMap->GameMap));//复制给自定义地图
	
}

//游戏地图拷贝自定义地图
void CMap::InitGameMapfromUser(CMap* pMap)
{
	memcpy(pMap->GameMap, g_UserMap, sizeof(pMap->GameMap));
}

//绘制自定义地图
void CMap::DrawUserMap(int level)
{
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (g_UserMap[g_level][i][j] == WALL0) {
				WriteChar(i, j, "■", Wall0_color, 0);//钢墙		
			}
			else if (g_UserMap[g_level][i][j] == WALL1) {
				WriteChar(i, j, "▓", Wall1_color, 1);//砖墙
			}
			else if (g_UserMap[g_level][i][j] == WALL2) {
				WriteChar(i, j, "〓", Wall2_color, 1);//河流		
			}
			else if (g_UserMap[g_level][i][j] == BASE) {
				WriteChar(i, j, "★", BASE_color, 1);//基地
			}
			else if (g_UserMap[g_level][i][j] == WALL3) {
				WriteChar(i, j, "※", Wall3_color, 1);//树
			}
		}
	}
}

//绘制地图
void CMap::DrawMap(CMap Map)
{
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (Map.GameMap[g_level][i][j] == WALL0) {
				WriteChar(i, j, "■", Wall0_color, 0);//钢墙		
			}
			else if (Map.GameMap[g_level][i][j] == WALL1) {
				WriteChar(i, j, "▓", Wall1_color, 1);//砖墙
			}
			else if (Map.GameMap[g_level][i][j] == WALL2) {
				WriteChar(i, j, "〓", Wall2_color, 1);//河流		█≈
			}
			else if (Map.GameMap[g_level][i][j] == BASE) {
				WriteChar(i, j, "★", BASE_color, 1);//基地
			}
			else if (Map.GameMap[g_level][i][j] == WALL3)
			{
				WriteChar(i, j, "※", Wall3_color, 1);//树林	
			}
		}
	}
}

//还原地形与物体
void CMap::returnMap(int y, int x, int WAll)
{
	switch (WAll)
	{
	case 0:WriteChar(y, x, "  ", 7, 1); break;
	case WALL0:WriteChar(y, x, "■", Wall0_color, 0); break;	  //铁墙■
	case WALL1:WriteChar(y, x, "▓", Wall1_color, 1); break;	  //砖墙▓
	case WALL2:WriteChar(y, x, "〓", Wall2_color, 1); break;	  //河流≈
	case WALL3:WriteChar(y, x, "※", Wall3_color, 1); break;	  //树林※
	case WALL5:WriteChar(y, x, "¤", Wall3_color, 1); break;	  //树林&&NPC子弹
	case WALL6:WriteChar(y, x, "◎", Wall3_color, 1); break;	  //树林&&Player子弹
	case BASE:WriteChar(y, x, "☆", BASE_color, 1); break;	  //基地被打爆
	case PLAYER_0:WriteChar(y, x, "■", 7, 1); break;	  //玩家坦克
	case PLAYER_1:WriteChar(y, x, "■", 2, 1); break;	  //玩家坦克
	}
}

//控制台输出绘制地图坐标;
void CMap::OutPutPos(int nPosX, int nPoxY)
{
	char szBuff[100] = { 0 };
	sprintf_s(szBuff, sizeof(szBuff), "x=%2d, y=%2d", nPosX / 2, nPoxY);
	SetConsoleTitleA(szBuff);
	WriteChar(0, 0, szBuff, 0x50, 1);
	return;
}

// 鼠标处理事件
int CMap::MouseEventProc(MOUSE_EVENT_RECORD StcMouse)
{
	
	switch (StcMouse.dwEventFlags)
	{
	case 0:
		if (StcMouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键
		{
			WriteChar(0, 0, "左键单击", 0x50, 1);
			if (MouseClick(StcMouse) == 1)//切换地图1
			{
				return 1;
			}
			if (MouseClick(StcMouse) == 2)//重置地图2
			{
				return 2;
			}
		}
		else if (StcMouse.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键
		{
			WriteChar(0, 0, "右键单击", 0x50, 1);
		}
		break;
	case  DOUBLE_CLICK:	//0x0002
		break;
	case MOUSE_MOVED://       0x0001
		MouseMove(StcMouse);  
		OutPutPos(StcMouse.dwMousePosition.X, StcMouse.dwMousePosition.Y);
		break;
	default:
		break;
	}
	return 0;
}

//鼠标拖动事件
bool CMap::MouseMove(MOUSE_EVENT_RECORD &StcMouse)
{
	int x = (StcMouse.dwMousePosition.X) / 2;
	int y = StcMouse.dwMousePosition.Y;
	//左键拖动;
	if (StcMouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		//界定绘制范围;
		if (flag_switch < 6 && x < 39 && y  < 39 && x > 0 && y > 0)
		{
			//根据地图值绘制相应图形;
			switch (flag_switch)
			{
			case 2:
				WriteChar(x, y, "■", 7, 0);//创建铁墙	
				//根据笔刷扩大;
				BrushDraw(StcMouse, "■", 7,0);
				break;
			case 3:
				WriteChar(x, y, "▓", 6, 1);//创建砖墙
				//根据笔刷扩大;
				BrushDraw(StcMouse, "▓", 6,1);
				break;
			case 4:
				WriteChar(x, y, "※", Wall3_color, 1);//树
				//根据笔刷扩大;
				BrushDraw(StcMouse, "※", Wall3_color, 1);
				break;
			case 5:
				WriteChar(x, y, "≈", Wall2_color, 1);//河流	
				//根据笔刷扩大;
				BrushDraw(StcMouse, "≈", Wall2_color, 1);
				break;
			case 0:
				WriteChar(x, y, "  ", 7, 1);//删除
				//根据笔刷扩大;
				BrushDraw(StcMouse, "  " , 7, 1);
				break;
			default:
				break;
			}
			//输出坐标;
			g_UserMap[g_level][x][y] = m_nMapVlue;

			//输出笔刷扩大的坐标;
			switch (m_nBrush)
			{
			case 3:
				if (x < 36 && x > 3 && y < 36 && y > 3)
				{
					for (int i = -3; i <= 3; i++)
					{
						for (int j = -3; j <= 3; j++)
						{
							g_UserMap[g_level][x + i][y + j] = m_nMapVlue;
						}
					}
				}
			case 2:
				if (x < 37 && x > 2 && y < 37 && y > 2)
				{
					for (int i = -2; i <= 2; i++)
					{
						for (int j = -2; j <= 2; j++)
						{
							g_UserMap[g_level][x + i][y + j] = m_nMapVlue;
						}
					}
				}
			case 1:
				if (x < 38 && x > 1 && y < 38 && y > 1)
				{
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							g_UserMap[g_level][x + i][y + j] = m_nMapVlue;
						}
					}
				}
			default:
				break;
			}
		}
	}

	return true;
}

// 鼠标点击事件
int CMap::MouseClick(MOUSE_EVENT_RECORD &StcMouse)
{
	//获取XY坐标;
	int x = (StcMouse.dwMousePosition.X) / 2;
	int y = StcMouse.dwMousePosition.Y;

	if (x > 39)
	{
		if (x == 42 || x == 43)
		{
			if (y == 5 || y == 6)
			{
				flag_switch = 2;
				m_nMapVlue = WALL0;//铁墙
			}
			else if (y == 9 || y == 10)
			{
				flag_switch = 4;
				m_nMapVlue = WALL3;//树林
			}
			else if (y == 13 || y == 14)
			{
				if (m_nBrush > 1) { m_nBrush--; }//笔刷--
			}
			else if (y == 17 || y == 18)
			{
				if (g_level > 1)
				{
					g_level--;//关卡--
					return 1;
				}
			}
			else if (y == 21 || y == 22)
			{
				flag_switch = 0;
				m_nMapVlue = 0;//删除
			}
		}
		else if (x == 46 || x == 47)
		{
			
			if (y == 5 || y == 6)
			{
				flag_switch = 3;
				m_nMapVlue = WALL1;//砖墙
			}
			else if (y == 9 || y == 10)
			{
				flag_switch = 5;
				m_nMapVlue = WALL2;//河流
			}
			else if (y == 13 || y == 14)
			{
				if (m_nBrush < 3) {
					m_nBrush++;//笔刷++
				}
			}
			else if (y == 17 || y == 18)
			{
				if (g_level < 5)
				{
					g_level++;//关卡++
					return 1;
				}	
			}
			else if (y == 21 || y == 22)
			{
				return 2;
				m_nMapVlue = 0;//重置
			}
		}
	}
	return 0;
}

int CMap::KeyEventProc(KEY_EVENT_RECORD &StcKeyEvent)
{
	flag_kb = 0;//键盘事件回车判断
	key = 0;//记录选中项,初始为第一个
	flag_enter = 0;//选项菜单循环内回车判断
	if (StcKeyEvent.bKeyDown)
	{
		if (StcKeyEvent.wVirtualKeyCode == 0xD)
		{
			flag_kb = 1;
			
			WriteChar(43, 29, "选择选项", 7, 0);//高亮
		}
	}
	while (flag_kb && (ch = _getch()))
	{
		switch (ch)
		{
		case 224:
			switch (_getch())
			{
			case 72://上
				if (key == 1)
				{
					WriteChar(43, 31, "单人游戏", 7, 1);
					WriteChar(43, 35, "返回菜单", 7, 0);//高亮
					
					key = 3;
				}
				else if (key == 2)
				{
					WriteChar(43, 33, "双人游戏", 7, 1);
					WriteChar(43, 31, "单人游戏", 7, 0);//高亮
					
					key = 1;
				}
				else if (key == 3)
				{
					WriteChar(43, 35, "返回菜单", 7, 1);
					WriteChar(43, 33, "双人游戏", 7, 0);//高亮
					
					key = 2;
				}
				else if (key == 0)
				{
					WriteChar(43, 29, "选择选项", 7, 1);
					WriteChar(43, 35, "返回菜单", 7, 0);//高亮
					
					key = 3;
				}
				break;
			case 80://下方向键
				if (key == 1)//
				{
					WriteChar(43, 31, "单人游戏", 7, 1);
					WriteChar(43, 33, "双人游戏", 7, 0);//高亮
					
					key = 2;
				}
				else if (key == 2)//
				{
					WriteChar(43, 33, "双人游戏", 7, 1);
					WriteChar(43, 35, "返回菜单", 7, 0);//高亮
					
					key = 3;
				}
				else if (key == 3)//
				{
					WriteChar(43, 35, "返回菜单", 7, 1);
					WriteChar(43, 31, "单人游戏", 7, 0);//高亮
					
					key = 1;
				}
				else if (key == 0)
				{
					WriteChar(43, 29, "选择选项", 7, 1);
					WriteChar(43, 31, "单人游戏", 7, 0);//高亮
					
					key = 1;
				}
				break;
			}
			break;
		case 13:	//enter回车键		
			
			flag_enter = 1;
			break;
		default:
			continue;
		}
		if (flag_enter)//回车确认,退出循环
		{
			break;
		}
	}
	switch (key)
	{
	case 1://单人游戏
		return 1;
		break;
	case 2://双人游戏
		return 2;
		break;
	case 3://返回菜单
		return 3;
		break;
	default:
		break;
	}
	return 0;

}
// 			//键盘上方的1,2,3,4，5,ASCII码值 关卡选择
// 		case 0x31:
// 			g_level = 1;
// 			break;
// 		case 0x32:
// 			g_level = 2;
// 			break;
// 		case 0x33:
// 			g_level = 3;
// 			break;
// 		case 0x34:
// 			g_level = 4;
// 			break;
// 		case 0x35:
// 			g_level = 5;
// 			break;
	


// 笔刷绘制扩展区;
void CMap::BrushDraw(MOUSE_EVENT_RECORD &StcMouse, char *Pstr, WORD color, int isback/*背景色 0是 1否*/)
{
	int x = (StcMouse.dwMousePosition.X) / 2;
	int y = StcMouse.dwMousePosition.Y;
	switch (m_nBrush)
	{
	case 3:
		if (x < 36 && x > 3 && y< 36 && y > 3)
		{
			for (int i = -3; i <= 3; i++)
			{
				for (int j = -3; j <= 3; j++)
				{
					if (isback == 0){
						WriteChar(x + i, y + j, Pstr, color, 0);
					}
					else{
						WriteChar(x + i, y + j, Pstr, color, 1);
					}
				}
			}
		}
	case 2:
		if (x < 37 && x > 2 && y< 37 && y > 2)
		{
			for (int i = -2; i <= 2; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					if (isback == 0) {
						WriteChar(x + i, y + j, Pstr, color, 0);
					}
					else {
						WriteChar(x + i, y + j, Pstr, color, 1);
					}
				}
			}
		}
	case 1:
		if (x < 38 && x > 1 && y< 38 && y > 1)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (isback == 0) {
						WriteChar(x + i, y + j, Pstr, color, 0);
					}
					else {
						WriteChar(x + i, y + j, Pstr, color, 1);
					}
				}
			}
			
		}
	default:
		break;
	}
	return;
}

// 保存地图;

// void CMap::SaveMap()
// {
// 	//打开文件;
// 	FILE *pFile;
// 	errno_t err = fopen_s(&pFile, "map.txt", "wb");
// 	if (err != 0)
// 	{
// 		return;
// 	}
// 
// 	//读写文件;
// 	fwrite(g_UserMap, sizeof(g_UserMap), 1, pFile);	//将地图数组存入文件;
// 
// 	//关闭文件;
// 	fclose(pFile);
// }


int CMap::MessageLoop()
{
	m_nBrush = 0;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD StcRecord = {0};
	DWORD dwRead;
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	while (1)
	{
		//等待事件
		ReadConsoleInput(hStdin, &StcRecord, 1, &dwRead);
		if (StcRecord.EventType == KEY_EVENT)//键盘事件0x0001
		{
			WriteChar(0, 0, "键盘按下", 0x50, 1);
			switch (KeyEventProc(StcRecord.Event.KeyEvent))//返回：1单人 2双人 3返回菜单 
			{
			case 1:
				return 1;
			case 2:
				return 2;
			case 3:
				return 3;
			default:
				break;
			}	
		}
		else if (StcRecord.EventType == MOUSE_EVENT)//0x0002
		{
			if (MouseEventProc(StcRecord.Event.MouseEvent)==1)//返回1则切换地图
			{
				return 4;//返回：4切换地图
			}
			if (MouseEventProc(StcRecord.Event.MouseEvent) == 2)//返回2则重置地图
			{
				return 5;//返回：4重置当前关卡地图
			}

		}

	}
	return 0;
}
