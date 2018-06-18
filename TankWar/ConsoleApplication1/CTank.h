#pragma once

#include "Data.h"
#include "Tools.h"
#include <time.h>
#include "CMap.h"
#include "CAstar.h"

class CTank
{
public:


	//画坦克
	void DrawTank(CTank tank, CMap* pMap);

	//初始化玩家坦克属性
	void InitPlayerTank(int num, CTank* Player_Tank);

	//纯擦除坦克 没有尾巴
	void OnlyClearTank(CTank tank, CMap* pMap);

	int GetDirfromAstar(CMap* pMap,  CTank& tank,  vector<CTank>& vecTank);

	int isUP(CTank tank,  CMap Map);

	int isDOWN(CTank tank,  CMap MapObj);

	int isLEFT(CTank tank, CMap MapObj);

	int isRIGHT(CTank tank, CMap MapObj);

	bool inGrass(CTank tank, CMap* pMap);

	/*
	A B C
	D O E
	F G H
	O=(y,x)
	A=(y-1,x-1)
	B=(y, x-1)
	C=(y-2,x-1)
	D=(y-1, x)
	E=(y+1, x)
	F=(y-1, x+1)
	G=(y, x+1)
	H=(y+1, x+1)
	*/

	void DrawPointA(CTank tank, CMap * pMap);
	void DrawPointB(CTank tank, CMap * pMap);
	void DrawPointC(CTank tank, CMap * pMap);
	void DrawPointD(CTank tank, CMap * pMap);
	void DrawPointE(CTank tank, CMap * pMap);
	void DrawPointF(CTank tank, CMap * pMap);
	void DrawPointG(CTank tank, CMap * pMap);
	void DrawPointH(CTank tank, CMap * pMap);
	void DrawPointCenter(CTank tank, CMap* pMap);


	void ClearPointA(CTank tank, CMap * pMap);
	void ClearPointB(CTank tank, CMap * pMap);
	void ClearPointC(CTank tank, CMap * pMap);
	void ClearPointD(CTank tank, CMap * pMap);
	void ClearPointE(CTank tank, CMap * pMap);
	void ClearPointF(CTank tank, CMap * pMap);
	void ClearPointG(CTank tank, CMap * pMap);
	void ClearPointH(CTank tank, CMap * pMap);
	void ClearPointCenter(CTank tank, CMap* pMap);

	bool isValid;//坦克是否存活
	int x;//行
	int y;//列
	Dir dir;
	int hp;
	int score;
	int tankID;
	int color;
	int level;
	int x_born;
	int y_born;
	int borntime;



	//绘制BOSS
	void DrawBOSSTank(CTank tank, CMap * pMap);
	void ClearBOSSTank(CTank tank, CMap * pMap);

	void DrawPointI(CTank tank, CMap *pMap);//I
	void DrawPointJ(CTank tank, CMap *pMap);//J
	void DrawPointK(CTank tank, CMap *pMap);//K
	void DrawPointL(CTank tank, CMap *pMap);//L
	void DrawPointM(CTank tank, CMap *pMap);//M
	void DrawPointN(CTank tank, CMap *pMap);//N
	void DrawPointP(CTank tank, CMap *pMap);
	void DrawPointR(CTank tank, CMap * pMap);
	void DrawPointS(CTank tank, CMap * pMap);
	void DrawPointT(CTank tank, CMap * pMap);
	void DrawPointU(CTank tank, CMap * pMap);
	void DrawPointV(CTank tank, CMap * pMap);
	void DrawPointW(CTank tank, CMap * pMap);
	void DrawPointX(CTank tank, CMap * pMap);
	void DrawPointY(CTank tank, CMap * pMap);

	void ClearPointI(CTank tank, CMap * pMap);
	void ClearPointJ(CTank tank, CMap * pMap);
	void ClearPointK(CTank tank, CMap * pMap);
	void ClearPointL(CTank tank, CMap * pMap);
	void ClearPointM(CTank tank, CMap * pMap);
	void ClearPointN(CTank tank, CMap * pMap);
	void ClearPointP(CTank tank, CMap * pMap);
	void ClearPointR(CTank tank, CMap * pMap);
	void ClearPointS(CTank tank, CMap * pMap);
	void ClearPointT(CTank tank, CMap * pMap);
	void ClearPointU(CTank tank, CMap * pMap);
	void ClearPointV(CTank tank, CMap * pMap);
	void ClearPointW(CTank tank, CMap * pMap);
	void ClearPointX(CTank tank, CMap * pMap);
	void ClearPointY(CTank tank, CMap * pMap);
	//P
};