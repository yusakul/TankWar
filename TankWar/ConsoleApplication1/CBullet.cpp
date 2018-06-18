#include "CBullet.h"



//擦除子弹
void CBullet::ClearBullet(CBullet bullet/*, CMap pMap*/)
{
	int y = bullet.y;
	int x = bullet.x;

	WriteChar(x, y, "  ", 7, 1);
}

//绘制子弹
void CBullet::DrawBullet(CBullet bullet, CMap* pMap)
{
	if (bullet.isValid == 1) 
	{	
		if ( pMap->GameMap[g_level][x][y]== WALL3 && bullet.tankID == PLAYER_0)		//玩家0子弹遇到树林
		{
			WriteChar(bullet.x, bullet.y, "◎", Wall3_color, 1);
		}
		else if (bullet.tankID == PLAYER_0 )	
		{
			WriteChar(bullet.x, bullet.y, "◎", 7, 1);
		}
		else if (bullet.tankID == PLAYER_1) {
			WriteChar(bullet.x, bullet.y, "◎", 2, 1);
		}
		else {
			WriteChar(bullet.x, bullet.y, "¤", 7, 1);
		}
	}
}

// 获取子弹下一步坐标物体
// int CBullet::GetBulletNextObj(CBullet bullet, CMap pMap)
// {
// 	if (bullet.isValid == 1)
// 	{
// 		CBullet temp = bullet;
// 		int x = temp.x;	//列
// 		int y = temp.y;	//行
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
// 还原子弹上一步坐标物体，用于树林
// int CBullet::GetBulletNextObj(CBullet bullet, CMap pMap)
// {
// 	if (bullet.isValid == 1)
// 	{
// 		CBullet temp = bullet;
// 		int x = temp.x;	//列
// 		int y = temp.y;	//行
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