#include "CAstar.h"

CAstar::PVIR_INFO CAstar::m_pVir;
CAstar::CAstar()
{
}


CAstar::~CAstar()
{
}

//��ʼ����ͼ��Ϣ
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

//��ʼ������
void CAstar::InitCoord(const CTank& tank, const vector<CTank>& vecTank)
{
	m_Start.X = tank.x;
	m_Start.Y = tank.y;

	m_End.X = vecTank[0].x;
	m_End.Y = vecTank[0].y;

	m_MapWidth = 40;
	m_MapHigh = 40;

	m_bInitCoordInfo = true; //��ʼ����ʼ������Ϣ=true
}

//Ѱ·
bool CAstar::FindPath(CTank tank)
{
	//�Ƿ��ʼ�����
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	/*
	1.  ��������걣�浽Open����
	2.1 �ж�Open���Ƿ�Ϊ�գ�����˵����·��ͬ
	2.2 �ҳ�Open����Fֵ��С�ĵ�
	2.3 ������ɢ
	2.4 ����ɢ�ĵ㱣�浽Close���У���Open����ɾ��
	2.5 �ж�����ɢ�����ĵ��Ƿ�ϸ�
	2.5.1 �Ƿ����յ㣬�Ǿ�ֱ�ӷ���
	�ǲ����ϰ���
	�ǲ���Խ��
	�Ƿ���Open����
	�Ƿ���Close����
	2.6 �Ѻϸ�ĵ���Open����
	2.7 �ظ�2.1 -- 2.6
	*/

	//���Open��Close��
	m_Open.clear();
	m_Close.clear();
	//=============���m_pVir��ԭ�б�ʶ==============
	ZeroMemory(m_pVir, m_MapWidth*m_MapHigh);
	//===============================================

	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//��ʼѭ������

	while (true)
	{
		//Open���Ƿ�Ϊ��
		if (m_Open.empty())
		{
			return false;
		}
		//��Open����Fֵ��С�ĵ�
		int nIndex = 0;
		for (unsigned i = 0; i < m_Open.size(); i++)
		{
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}
		//��ɢ
		NODE_INFO nodeNew[4];

		//��
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//��
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y ;
		//��
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//��
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
		int x1 = m_Open[nIndex].codSelf.X;//��
		int y1 = m_Open[nIndex].codSelf.Y;
 		m_pVir[x1 * m_MapWidth + y1].isClose = true;
		m_pVir[x1 * m_MapWidth + y1].isOpen = false;
		//=============

		//����ɢ���ĵ㱣�浽Close������Open����ɾ��
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);
/*		WriteChar(y1, x1, "  ", 7, 1);*/

		//�����ɢ�����ĵ��Ƿ�ϸ��Ƿ����յ�
		for (int i = 0; i < 4; i++)
		{

			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//�ǲ����յ�
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);//==============================================================�յ�
				return true;
			}
			//�Ƿ�Խ��
			if (x <= 0 || y <= 0 ||
				x >= m_MapWidth ||
				y >= m_MapHigh)
			{
				continue;
			}

			bool flag1 = x == m_End.X && y== m_End.Y - 2;	//��;
			bool flag2 = x == m_End.X && y== m_End.Y + 2;	//��;
			bool flag3 = y == m_End.Y && x == m_End.X - 2;	//��;
			bool flag4 = y == m_End.Y && x == m_End.X + 2;	//��;


			if (flag1 || flag2 || flag3 || flag4)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}

			//�Ƿ����ϰ���

			if (i == 0)
			{
				if (isUP(x1, y1, i, Astar_Map))//0�� 1����
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
				if (isLEFT(x1, y1, i, Astar_Map))//0�� 1����
				{
					continue;
				}
			}
			else if (i == 3)
			{
				if (isRIGHT(x1, y1, i, Astar_Map))//0�� 1����
				{
					continue;
				}
			}

			//�ж��Ƿ���Open���Close����
			if (m_pVir[x * m_MapWidth + y].isClose ||
				m_pVir[x * m_MapWidth + y].isOpen)
			{
				continue;
			}
			
			//���ϸ�ĵ㱣�浽Open����
			m_Open.push_back(nodeNew[i]);

			//  ��ӡ ���뵽open���е� �� 
		//	WriteChar(y, x, "@", 7, 1);

			//============
			m_pVir[x * m_MapWidth + y].isOpen = true;
			//============
		}

	}//while
}

//Ѱ·1
bool CAstar::FindPath1(CTank tank)
{
	//�Ƿ��ʼ�����
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	/*
	1.  ��������걣�浽Open����
	2.1 �ж�Open���Ƿ�Ϊ�գ�����˵����·��ͬ
	2.2 �ҳ�Open����Fֵ��С�ĵ�
	2.3 ������ɢ
	2.4 ����ɢ�ĵ㱣�浽Close���У���Open����ɾ��
	2.5 �ж�����ɢ�����ĵ��Ƿ�ϸ�
	2.5.1 �Ƿ����յ㣬�Ǿ�ֱ�ӷ���
	�ǲ����ϰ���
	�ǲ���Խ��
	�Ƿ���Open����
	�Ƿ���Close����
	2.6 �Ѻϸ�ĵ���Open����
	2.7 �ظ�2.1 -- 2.6
	*/

	//���Open��Close��
	m_Open.clear();
	m_Close.clear();
	//=============���m_pVir��ԭ�б�ʶ==============
	ZeroMemory(m_pVir, m_MapWidth*m_MapHigh);
	//===============================================

	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//��ʼѭ������

	while (true)
	{
		//Open���Ƿ�Ϊ��
		if (m_Open.empty())
		{
			return false;
		}
		//��Open����Fֵ��С�ĵ�
		int nIndex = 0;
		for (unsigned i = 0; i < m_Open.size(); i++)
		{
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}
		//��ɢ
		NODE_INFO nodeNew[4];

		//��
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//��
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//��
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//��
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
		int x1 = m_Open[nIndex].codSelf.X;//��
		int y1 = m_Open[nIndex].codSelf.Y;
		m_pVir[x1 * m_MapWidth + y1].isClose = true;
		m_pVir[x1 * m_MapWidth + y1].isOpen = false;
		//=============

		//����ɢ���ĵ㱣�浽Close������Open����ɾ��
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);
		/*		WriteChar(y1, x1, "  ", 7, 1);*/

		//�����ɢ�����ĵ��Ƿ�ϸ��Ƿ����յ�
		for (int i = 0; i < 4; i++)
		{

			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//�ǲ����յ�
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);//==============================================================�յ�
				return true;
			}
			//�Ƿ�Խ��
			if (x <= 0 || y <= 0 ||
				x >= m_MapWidth ||
				y >= m_MapHigh)
			{
				continue;
			}

			bool flag1 = x == m_End.X && y == m_End.Y - 4;	//��;
			bool flag2 = x == m_End.X && y == m_End.Y + 4;	//��;
			bool flag3 = y == m_End.Y && x == m_End.X - 4;	//��;
			bool flag4 = y == m_End.Y && x == m_End.X + 4;	//��;


			if (flag1 || flag2 || flag3 || flag4)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}

			//�Ƿ����ϰ���
			if (isBOSSmove(x, y, i, Astar_Map, tank))
			{
				continue;
			}

			//�ж��Ƿ���Open���Close����
			if (m_pVir[x * m_MapWidth + y].isClose ||
				m_pVir[x * m_MapWidth + y].isOpen)
			{
				continue;
			}

			//���ϸ�ĵ㱣�浽Open����
			m_Open.push_back(nodeNew[i]);

			//  ��ӡ ���뵽open���е� �� 
			//	WriteChar(y, x, "@", 7, 1);

			//============
			m_pVir[x * m_MapWidth + y].isOpen = true;
			//============
		}

	}//while
}

//�õ�·��
void CAstar::GetPath()
{
	//���ݸ��ڵ�
	m_Path.clear();//���ԭ����·��
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
				//���� ���� ·��
/*				WriteChar(m_Close[nIndex].codParent.Y, m_Close[nIndex].codParent.X, "*", 7, 1);*/
				nIndex = i;
				break;
			}
		}
	}
}

//�õ�·��1
void CAstar::GetPath1()
{
	//���ݸ��ڵ�
	m_Path.clear();//���ԭ����·��
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
				//���� ���� ·��
				//WriteChar(m_Close[nIndex].codParent.Y, m_Close[nIndex].codParent.X, "*", 7, 1);
				nIndex = i;
				break;
			}
		}
	}
}


bool CAstar::AStarSearch(CMap* pMap, const  CTank& tank,const vector<CTank>& vecTank)
{
	//��ʼ������
	InitCoord(tank, vecTank);
	InitMapInfo(pMap, tank);
	FindPath(tank);
	GetPath();
	return 1;
}

bool CAstar::AStarSearch1(CMap* pMap, const  CTank& tank, const vector<CTank>& vecTank)
{
	//��ʼ������
	InitCoord(tank, vecTank);
	InitMapInfo(pMap, tank);
	FindPath1(tank);
	GetPath1();
	return 1;
}



//�жϷ������ܷ���0  �������е���ת�򷵻�1   ����ǰ������ת�򷵻�2
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

//�жϷ����� �ܷ���0
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

//�жϷ����� �ܷ���0
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

//�ж����� 
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