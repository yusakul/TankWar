#pragma once#pragma once
#include <vector>
using std::vector;
#include <windows.h>
#include "Data.h"
#include "CTank.h"
#include "CGame.h"

class CTank;
class CGame;
class CAstar
{
public:
	CAstar();
	~CAstar();

	/*CGame* pGame;*/
/*	CTank* pTank;*/
	typedef struct _MY_COORD : public COORD
	{
		bool operator==(COORD cod)
		{
			return (X == cod.X) && (Y == cod.Y);
		}
		void operator=(COORD cod)
		{
			X = cod.X;
			Y = cod.Y;
		}
		int dir; //����̹�˵��ƶ�����
	}MY_COORD, *PMY_COORD;


	//�ڵ�Ľṹ
	typedef struct _NODE_INFO
	{
		int g; //�ƶ����
		int h; //���յ���̾���
		int f; //g+h
		MY_COORD codSelf;  //��������
		MY_COORD codParent;//���ڵ����꣨��˭��ɢ�ģ�
		void SetH_F(COORD cod1, COORD cod2)
		{
			h = abs(cod1.X - cod2.X) + abs(cod1.Y - cod2.Y);
			f = g + h;
		}

	}NODE_INFO, *PNODE_INFO;

	COORD m_Start; //�������
	COORD m_End;   //�յ�����

	vector<NODE_INFO> m_Open;  //����ɢ�ĵ�
	vector<NODE_INFO> m_Close; //��ɢ���ĵ�
	vector<MY_COORD>  m_Path;  //���·��

	CMap Astar_Map;
	int* m_pMap;      //��ͼ���׵�ַ*/
	int  m_MapHigh;   //��ͼ�ĳ�
	int  m_MapWidth;  //��ͼ�Ŀ�

	int m_Block;      //�ϰ���
					  /*
					  1 2 3
					  4 5 6
					  7 8 9
					  */
	bool m_bInitMapInfo;    //�Ƿ��ʼ����ͼ��Ϣ
	bool m_bInitCoordInfo;  //�Ƿ��ʼ����ʼ������Ϣ


	void InitMapInfo(CMap* pMap,const CTank& tank);
	void InitCoord(const CTank& tank, const vector<CTank>& vecTank);

	bool FindPath(CTank tank); //���Ұ������·���ĵ㣨�õ�Close��
	bool FindPath1(CTank tank);
	void GetPath();  //��ȡ���·��

	void GetPath1();



	bool AStarSearch(CMap * pMap,const CTank& tank, const vector<CTank>& vecTank);

	bool AStarSearch1(CMap * pMap, const CTank & tank, const vector<CTank>& vecTank);

	int isUP(int x, int y, int dir, CMap MapObj);

	int isDOWN(int x, int y, int dir, CMap MapObj);

	int isLEFT(int x, int y, int dir, CMap MapObj);

	int isRIGHT(int x, int y, int dir, CMap MapObj);

	int isBOSSmove(int x, int y, int dir, CMap MapObj, CTank tank);



					 //=====�Ż�����====
	typedef struct _VIR_INFO
	{
		char isOpen : 1; //���Ƿ���Open����
		char isClose : 1; //��ʾ�Ƿ���CLose����
		char rcieve : 6; //����
	}VIR_INFO, *PVIR_INFO;

	static PVIR_INFO m_pVir; //ָ�������ͼ���׵�ַ

							 //=====test====
// 	void PrintWall();
// 	void PrintPath();
// 	void PrintChar(int x, int y, char* pStr, short color);
};

