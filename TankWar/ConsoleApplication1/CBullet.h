#pragma once
#include <vector>
using namespace std;

#include "CMap.h"
#include "CTank.h"
#include "CGame.h"
#include "Data.h"

class CBullet
{
public :

	//擦除子弹
	void ClearBullet(CBullet bullet/*, CMap pMap*/);

	//绘制子弹
	void DrawBullet(CBullet bullet, CMap* pMap);



	bool isValid;//是否存活
	int x;//列
	int y;//行
	Dir dir;
	int hp;
	int tankID;
	int color;
};