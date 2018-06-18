#include "CBullet.h"



//�����ӵ�
void CBullet::ClearBullet(CBullet bullet/*, CMap pMap*/)
{
	int y = bullet.y;
	int x = bullet.x;

	WriteChar(x, y, "  ", 7, 1);
}

//�����ӵ�
void CBullet::DrawBullet(CBullet bullet, CMap* pMap)
{
	if (bullet.isValid == 1) 
	{	
		if ( pMap->GameMap[g_level][x][y]== WALL3 && bullet.tankID == PLAYER_0)		//���0�ӵ���������
		{
			WriteChar(bullet.x, bullet.y, "��", Wall3_color, 1);
		}
		else if (bullet.tankID == PLAYER_0 )	
		{
			WriteChar(bullet.x, bullet.y, "��", 7, 1);
		}
		else if (bullet.tankID == PLAYER_1) {
			WriteChar(bullet.x, bullet.y, "��", 2, 1);
		}
		else {
			WriteChar(bullet.x, bullet.y, "��", 7, 1);
		}
	}
}

// ��ȡ�ӵ���һ����������
// int CBullet::GetBulletNextObj(CBullet bullet, CMap pMap)
// {
// 	if (bullet.isValid == 1)
// 	{
// 		CBullet temp = bullet;
// 		int x = temp.x;	//��
// 		int y = temp.y;	//��
// 		switch (temp.dir)
// 		{
// 		case UP:
// 			y = temp.y--;
// 			break;
// 		case DOWN:
// 			y = temp.y++;
// 			break;
// 		case LEFT:
// 			x = temp.x--;
// 			break;
// 		case RIGHT:
// 			x = temp.x++;
// 			break;
// 		}
// 		return WALL6== pMap.GameMap[x][y];
// 	}
// 	return -1;
// }
// 
// 
// ��ԭ�ӵ���һ���������壬��������
// int CBullet::GetBulletNextObj(CBullet bullet, CMap pMap)
// {
// 	if (bullet.isValid == 1)
// 	{
// 		CBullet temp = bullet;
// 		int x = temp.x;	//��
// 		int y = temp.y;	//��
// 		switch (temp.dir)
// 		{
// 		case UP:
// 			y = temp.y++;
// 			break;
// 		case DOWN:
// 			y = temp.y--;
// 			break;
// 		case LEFT:
// 			x = temp.x++;
// 			break;
// 		case RIGHT:
// 			x = temp.x--;
// 			break;
// 		}
// 		return WALL6 == pMap.GameMap[x][y];
// 	}
// 	return -1;
// }