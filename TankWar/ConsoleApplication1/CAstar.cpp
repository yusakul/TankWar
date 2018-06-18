#include "CAstar.h"

CAstar::PVIR_INFO CAstar::m_pVir;
CAstar::CAstar()
{
}


CAstar::~CAstar()
{
}

//初始化地图信息
void CAstar::InitMapInfo(CMap* pMap, const CTank& tank)//
{
	/*m_pMap = pMap->GameMap[g_level];*/

	memcpy(Astar_Map.GameMap ,  pMap->GameMap, sizeof(Astar_Map.GameMap));
	
	for (int level = 0; level <= 5; level++)
	{
		for (int i = 1; i < 40; i++)
		{
			for (int j = 1; j < 40; j++)
			{
				if (pMap->GameMap[level][i][j] == 0|| pMap->GameMap[level][i][j] == WALL3|| pMap->GameMap[level][i][j] >=200&& pMap->GameMap[level][i][j] <302)
				{
					Astar_Map.GameMap[level][i][j] = 0;
				}
				else
				{
					Astar_Map.GameMap[level][i][j] = 1;
				}
			}
		}
	}
	

	m_pVir = new VIR_INFO[m_MapHigh*m_MapWidth]{};

	m_bInitMapInfo = true;
}

//初始化坐标
void CAstar::InitCoord(const CTank& tank, const vector<CTank>& vecTank)
{
	m_Start.X = tank.x;
	m_Start.Y = tank.y;

	m_End.X = vecTank[0].x;
	m_End.Y = vecTank[0].y;

	m_MapWidth = 40;
	m_MapHigh = 40;

	m_bInitCoordInfo = true; //初始化起始坐标信息=true
}

//寻路
bool CAstar::FindPath(CTank tank)
{
	//是否初始化完毕
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	/*
	1.  把起点坐标保存到Open表中
	2.1 判断Open表是否为空，空了说明此路不同
	2.2 找出Open表中F值最小的点
	2.3 进行扩散
	2.4 把扩散的点保存到Close表中，从Open表中删除
	2.5 判断新扩散出来的点是否合格
	2.5.1 是否是终点，是就直接返回
	是不是障碍物
	是不是越界
	是否在Open表中
	是否在Close表中
	2.6 把合格的点存进Open表中
	2.7 重复2.1 -- 2.6
	*/

	//清空Open和Close表
	m_Open.clear();
	m_Close.clear();
	//=============清空m_pVir的原有标识==============
	ZeroMemory(m_pVir, m_MapWidth*m_MapHigh);
	//===============================================

	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//开始循环查找

	while (true)
	{
		//Open表是否为空
		if (m_Open.empty())
		{
			return false;
		}
		//找Open表中F值最小的点
		int nIndex = 0;
		for (unsigned i = 0; i < m_Open.size(); i++)
		{
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}
		//扩散
		NODE_INFO nodeNew[4];

		//上
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//下
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y ;
		//左
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//右
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;

		for (int i = 0; i < 4; i++)
		{
			nodeNew[i].codParent = m_Open[nIndex].codSelf;
			nodeNew[i].g = m_Open[nIndex].g + 1;
			nodeNew[i].SetH_F(nodeNew[i].codSelf, m_End);
			nodeNew[i].codSelf.dir = i;

		}
		//=============
		int x1 = m_Open[nIndex].codSelf.X;//行
		int y1 = m_Open[nIndex].codSelf.Y;
 		m_pVir[x1 * m_MapWidth + y1].isClose = true;
		m_pVir[x1 * m_MapWidth + y1].isOpen = false;
		//=============

		//把扩散过的点保存到Close表，并从Open表中删除
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);
/*		WriteChar(y1, x1, "  ", 7, 1);*/

		//检测扩散出来的点是否合格，是否是终点
		for (int i = 0; i < 4; i++)
		{

			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//是不是终点
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);//==============================================================终点
				return true;
			}
			//是否越界
			if (x <= 0 || y <= 0 ||
				x >= m_MapWidth ||
				y >= m_MapHigh)
			{
				continue;
			}

			bool flag1 = x == m_End.X && y== m_End.Y - 2;	//上;
			bool flag2 = x == m_End.X && y== m_End.Y + 2;	//下;
			bool flag3 = y == m_End.Y && x == m_End.X - 2;	//左;
			bool flag4 = y == m_End.Y && x == m_End.X + 2;	//右;


			if (flag1 || flag2 || flag3 || flag4)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}

			//是否是障碍物

			if (i == 0)
			{
				if (isUP(x1, y1, i, Astar_Map))//0能 1不能
				{
					continue;
				}

			}
			else if (i == 1)
			{
				if (isDOWN(x1, y1, i, Astar_Map))
				{
					continue;
				}
			}
			else if (i == 2)
			{
				if (isLEFT(x1, y1, i, Astar_Map))//0能 1不能
				{
					continue;
				}
			}
			else if (i == 3)
			{
				if (isRIGHT(x1, y1, i, Astar_Map))//0能 1不能
				{
					continue;
				}
			}

			//判断是否在Open表和Close表中
			if (m_pVir[x * m_MapWidth + y].isClose ||
				m_pVir[x * m_MapWidth + y].isOpen)
			{
				continue;
			}
			
			//将合格的点保存到Open表中
			m_Open.push_back(nodeNew[i]);

			//  打印 加入到open表中的 点 
		//	WriteChar(y, x, "@", 7, 1);

			//============
			m_pVir[x * m_MapWidth + y].isOpen = true;
			//============
		}

	}//while
}

//寻路1
bool CAstar::FindPath1(CTank tank)
{
	//是否初始化完毕
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	/*
	1.  把起点坐标保存到Open表中
	2.1 判断Open表是否为空，空了说明此路不同
	2.2 找出Open表中F值最小的点
	2.3 进行扩散
	2.4 把扩散的点保存到Close表中，从Open表中删除
	2.5 判断新扩散出来的点是否合格
	2.5.1 是否是终点，是就直接返回
	是不是障碍物
	是不是越界
	是否在Open表中
	是否在Close表中
	2.6 把合格的点存进Open表中
	2.7 重复2.1 -- 2.6
	*/

	//清空Open和Close表
	m_Open.clear();
	m_Close.clear();
	//=============清空m_pVir的原有标识==============
	ZeroMemory(m_pVir, m_MapWidth*m_MapHigh);
	//===============================================

	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//开始循环查找

	while (true)
	{
		//Open表是否为空
		if (m_Open.empty())
		{
			return false;
		}
		//找Open表中F值最小的点
		int nIndex = 0;
		for (unsigned i = 0; i < m_Open.size(); i++)
		{
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}
		//扩散
		NODE_INFO nodeNew[4];

		//上
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//下
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//左
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//右
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;

		for (int i = 0; i < 4; i++)
		{
			nodeNew[i].codParent = m_Open[nIndex].codSelf;
			nodeNew[i].g = m_Open[nIndex].g + 1;
			nodeNew[i].SetH_F(nodeNew[i].codSelf, m_End);
			nodeNew[i].codSelf.dir = i;

		}
		//=============
		int x1 = m_Open[nIndex].codSelf.X;//行
		int y1 = m_Open[nIndex].codSelf.Y;
		m_pVir[x1 * m_MapWidth + y1].isClose = true;
		m_pVir[x1 * m_MapWidth + y1].isOpen = false;
		//=============

		//把扩散过的点保存到Close表，并从Open表中删除
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);
		/*		WriteChar(y1, x1, "  ", 7, 1);*/

		//检测扩散出来的点是否合格，是否是终点
		for (int i = 0; i < 4; i++)
		{

			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//是不是终点
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);//==============================================================终点
				return true;
			}
			//是否越界
			if (x <= 0 || y <= 0 ||
				x >= m_MapWidth ||
				y >= m_MapHigh)
			{
				continue;
			}

			bool flag1 = x == m_End.X && y == m_End.Y - 4;	//上;
			bool flag2 = x == m_End.X && y == m_End.Y + 4;	//下;
			bool flag3 = y == m_End.Y && x == m_End.X - 4;	//左;
			bool flag4 = y == m_End.Y && x == m_End.X + 4;	//右;


			if (flag1 || flag2 || flag3 || flag4)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}

			//是否是障碍物
			if (isBOSSmove(x, y, i, Astar_Map, tank))
			{
				continue;
			}

			//判断是否在Open表和Close表中
			if (m_pVir[x * m_MapWidth + y].isClose ||
				m_pVir[x * m_MapWidth + y].isOpen)
			{
				continue;
			}

			//将合格的点保存到Open表中
			m_Open.push_back(nodeNew[i]);

			//  打印 加入到open表中的 点 
			//	WriteChar(y, x, "@", 7, 1);

			//============
			m_pVir[x * m_MapWidth + y].isOpen = true;
			//============
		}

	}//while
}

//得到路径
void CAstar::GetPath()
{
	//回溯父节点
	m_Path.clear();//清空原来的路径
	int nSize = m_Close.size();
	int nIndex = nSize - 1;
	while (true)
	{
		for (int i = 0; i < nSize; i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				return;
			}
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				m_Path.push_back(m_Close[i].codSelf);
				//画出 最终 路线
/*				WriteChar(m_Close[nIndex].codParent.Y, m_Close[nIndex].codParent.X, "*", 7, 1);*/
				nIndex = i;
				break;
			}
		}
	}
}

//得到路径1
void CAstar::GetPath1()
{
	//回溯父节点
	m_Path.clear();//清空原来的路径
	int nSize = m_Close.size();
	int nIndex = nSize - 1;
	while (true)
	{
		for (int i = 0; i < nSize; i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				return;
			}
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				m_Path.push_back(m_Close[i].codSelf);
				//画出 最终 路线
				//WriteChar(m_Close[nIndex].codParent.Y, m_Close[nIndex].codParent.X, "*", 7, 1);
				nIndex = i;
				break;
			}
		}
	}
}


bool CAstar::AStarSearch(CMap* pMap, const  CTank& tank,const vector<CTank>& vecTank)
{
	//初始化坐标
	InitCoord(tank, vecTank);
	InitMapInfo(pMap, tank);
	FindPath(tank);
	GetPath();
	return 1;
}

bool CAstar::AStarSearch1(CMap* pMap, const  CTank& tank, const vector<CTank>& vecTank)
{
	//初始化坐标
	InitCoord(tank, vecTank);
	InitMapInfo(pMap, tank);
	FindPath1(tank);
	GetPath1();
	return 1;
}



//判断否上行能返回0  不能上行但能转向返回1   不能前进不能转向返回2
int CAstar::isUP(int x, int y, int dir, CMap MapObj)
{

	int flag1 = (MapObj.GameMap[g_level][y][x - 2] == 0);
	int flag2 = (MapObj.GameMap[g_level][y - 1][x - 2] == 0);
	int flag3 = (MapObj.GameMap[g_level][y + 1][x - 2] == 0);


	int flag11 = (MapObj.GameMap[g_level][y][x - 2] == WALL3);
	int flag22 = (MapObj.GameMap[g_level][y - 1][x - 2] == WALL3);
	int flag33 = (MapObj.GameMap[g_level][y + 1][x - 2] == WALL3);
	int flag111 = flag1 || flag11;
	int flag222 = flag2 || flag22;
	int flag333 = flag3 || flag33;
	if (flag111&&flag222&&flag333)
	{
		return 0;
	}
	return 1;
	
}

//判断否下行 能返回0
int CAstar::isDOWN(int x, int y, int dir, CMap MapObj)
{


	int flag1 = (MapObj.GameMap[g_level][y][x + 2] == 0);
	int flag2 = (MapObj.GameMap[g_level][y - 1][x + 2] == 0);
	int flag3 = (MapObj.GameMap[g_level][y + 1][x + 2] == 0);

	int flag11 = (MapObj.GameMap[g_level][y][x + 2] == WALL3);
	int flag22 = (MapObj.GameMap[g_level][y - 1][x + 2] == WALL3);
	int flag33 = (MapObj.GameMap[g_level][y + 1][x + 2] == WALL3);

	int flag111 = flag1 || flag11;
	int flag222 = flag2 || flag22;
	int flag333 = flag3 || flag33;

	if (flag111&&flag222&&flag333)
	{
		return 0;
	}
	return 1;
	
}

//判断否左行 能返回0
int CAstar::isLEFT(int x, int y, int dir, CMap MapObj)
{

	int flag1 = (MapObj.GameMap[g_level][y - 2][x] == 0);
	int flag2 = (MapObj.GameMap[g_level][y - 2][x - 1] == 0);
	int flag3 = (MapObj.GameMap[g_level][y - 2][x + 1] == 0);



	int flag11 = (MapObj.GameMap[g_level][y - 2][x] == WALL3);
	int flag22 = (MapObj.GameMap[g_level][y - 2][x - 1] == WALL3);
	int flag33 = (MapObj.GameMap[g_level][y - 2][x + 1] == WALL3);


	int flag111 = flag1 || flag11;
	int flag222 = flag2 || flag22;
	int flag333 = flag3 || flag33;


	if (flag111&&flag222&&flag333)
	{
		return 0;
	}
	return 1;
	
	
}

//判断右行 
int CAstar::isRIGHT(int x, int y, int dir, CMap MapObj)
{
	
	int flag1 = (MapObj.GameMap[g_level][y + 2][x] == 0);
	int flag2 = (MapObj.GameMap[g_level][y + 2][x - 1] == 0);
	int flag3 = (MapObj.GameMap[g_level][y + 2][x + 1] == 0);


	int flag11 = (MapObj.GameMap[g_level][y + 2][x] == WALL3);
	int flag22 = (MapObj.GameMap[g_level][y + 2][x - 1] == WALL3);
	int flag33 = (MapObj.GameMap[g_level][y + 2][x + 1] == WALL3);


	int flag111 = flag1 || flag11;
	int flag222 = flag2 || flag22;
	int flag333 = flag3 || flag33;

	if (flag111&&flag222&&flag333)
	{
		return 0;
	}
	return 1;

}


int CAstar::isBOSSmove(int x, int y, int dir, CMap MapObj, CTank tank)
{
	for (int i = -3; i <= 3;i++)
	{
		for (int j = -3; j <= 3; j++)
		{
			int posX = x + i;
			int posY = y + i;
			if (MapObj.GameMap[g_level][posY][posX] != 0 && MapObj.GameMap[g_level][posY][posX] != tank.tankID && MapObj.GameMap[g_level][posY][posX] != WALL3 && MapObj.GameMap[g_level][posY][posX] != WALL8)
			{
				return 1;
			}
		}

	}
	return 0;
}