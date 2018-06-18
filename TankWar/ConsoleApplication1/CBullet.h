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

	//�����ӵ�
	void ClearBullet(CBullet bullet/*, CMap pMap*/);

	//�����ӵ�
	void DrawBullet(CBullet bullet, CMap* pMap);



	bool isValid;//�Ƿ���
	int x;//��
	int y;//��
	Dir dir;
	int hp;
	int tankID;
	int color;
};