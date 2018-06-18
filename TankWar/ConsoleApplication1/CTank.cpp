#include "CTank.h"


//初始化玩家坦克属性
void CTank::InitPlayerTank(int num, CTank* Player_Tank)
{
	Player_Tank[0].dir = UP;
	Player_Tank[0].x = 37;
	Player_Tank[0].y = 23;
	Player_Tank[0].hp = 9;
	Player_Tank[0].color = 7;//白色
	Player_Tank[0].isValid = 1;
	Player_Tank[0].tankID = PLAYER_0;
	Player_Tank[0].score = 0;
	Player_Tank[0].level = 5;


	Player_Tank[1].dir = UP;
	Player_Tank[1].x = 37;
	Player_Tank[1].y = 16;
	Player_Tank[1].hp = 9;
	Player_Tank[1].color = 5;//粉红
	Player_Tank[1].isValid = 1;
	Player_Tank[1].tankID = PLAYER_1;
	Player_Tank[1].score = 0;
	Player_Tank[1].level = 5;

	if (num == 1)//一个玩家
	{
		Player_Tank[1].isValid = 0;
	}


}

//纯擦除坦克 没有尾巴 不擦尾巴 
void CTank::OnlyClearTank(CTank tank, CMap* pMap)
{
	switch (tank.dir)
	{
	case UP:

		ClearPointCenter(tank,pMap);//中心点
		ClearPointB(tank, pMap);//B
		ClearPointD(tank, pMap);//D
		ClearPointE(tank, pMap);//E
		ClearPointF(tank, pMap);//F
		ClearPointH(tank, pMap);//H
		break;
	case DOWN:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointG(tank, pMap);//G
		ClearPointD(tank, pMap);//D
		ClearPointE(tank, pMap);//E
		ClearPointC(tank, pMap);//C
		ClearPointA(tank, pMap);//A
		break;
	case LEFT:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointG(tank, pMap);//G
		ClearPointD(tank, pMap);//D
		ClearPointB(tank, pMap);//B
		ClearPointC(tank, pMap);//C
		ClearPointH(tank, pMap);//H
		break;
	case RIGHT:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointG(tank, pMap);//G
		ClearPointA(tank, pMap);//A
		ClearPointB(tank, pMap);//B
		ClearPointE(tank, pMap);//E
		ClearPointF(tank, pMap);//F
		break;
	default:
		break;
	}
}


void CTank::ClearPointCenter(CTank tank, CMap* pMap)
{
	if (pMap->GameMap[g_level][y][x] == WALL8)
	{
		pMap->GameMap[g_level][y][x] = WALL3;//中心点
		pMap->returnMap(y, x, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y][x] = 0;//中心点
		WriteChar(y, x, "  ", tank.color, 1);
	}
}
void CTank::ClearPointA(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x - 1] = WALL3;//a
		pMap->returnMap(y - 1, x - 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x - 1] = 0;//A
		WriteChar(y - 1, x - 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointB(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y][x - 1] = WALL3;//B
		pMap->returnMap(y, x - 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y][x - 1] = 0;//B
		WriteChar(y, x - 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointC(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x - 1] = WALL3;//c
		pMap->returnMap(y + 1, x - 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x - 1] = 0;//C
		WriteChar(y + 1, x - 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointD(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x] = WALL3;//d
		pMap->returnMap(y - 1, x, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x] = 0;//D
		WriteChar(y - 1, x, "  ", tank.color, 1);
	}
}
void CTank::ClearPointE(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x] = WALL3;//e
		pMap->returnMap(y + 1, x, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x] = 0;//E
		WriteChar(y + 1, x, "  ", tank.color, 1);
	}
}
void CTank::ClearPointF(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x + 1] = WALL3;//f
		pMap->returnMap(y - 1, x + 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x + 1] = 0;//F
		WriteChar(y - 1, x + 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointG(CTank tank, CMap * pMap) 
{
	if (pMap->GameMap[g_level][y][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y][x + 1] = WALL3;//g
		pMap->returnMap(y, x + 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y][x + 1] = 0;//G
		WriteChar(y, x + 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointH(CTank tank, CMap * pMap) 
{
	if (pMap->GameMap[g_level][y + 1][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x + 1] = WALL3;//h
		pMap->returnMap(y + 1, x + 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x + 1] = 0;//H
		WriteChar(y + 1, x + 1, "  ", tank.color, 1);
	}
}



/*
A B C
D O E
F G H
O=(y,x)
A=(y-1,x-1)
B=(y, x-1)
C=(y+1,x-1)
D=(y-1, x)
E=(y+1, x)
F=(y-1, x+1)
G=(y, x+1)
H=(y+1, x+1)
*/





//绘制坦克1...1
void CTank::DrawTank(CTank tank, CMap* pMap)
{
	if (!tank.isValid)return;
	switch (tank.dir)
	{
	case UP:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointB(tank, pMap);//B
		DrawPointD(tank, pMap);//D
		DrawPointE(tank, pMap);//E
		DrawPointF(tank, pMap);//F
		DrawPointH(tank, pMap);//H	
		break;
	case DOWN:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointG(tank, pMap);//G
		DrawPointD(tank, pMap);//D
		DrawPointE(tank, pMap);//E
		DrawPointC(tank, pMap);//C
		DrawPointA(tank, pMap);//A
		break;
	case LEFT:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointG(tank, pMap);//G
		DrawPointD(tank, pMap);//D
		DrawPointB(tank, pMap);//B
		DrawPointC(tank, pMap);//C
		DrawPointH(tank, pMap);//H
		break;
	case RIGHT:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointG(tank, pMap);//G
		DrawPointA(tank, pMap);//A
		DrawPointB(tank, pMap);//B
		DrawPointE(tank, pMap);//E
		DrawPointF(tank, pMap);//F
		break;
	default:
		break;
	}

}

//中心点以及其他点
void CTank::DrawPointCenter(CTank tank, CMap* pMap)
{
	if (pMap->GameMap[g_level][y][x] == WALL3 || pMap->GameMap[g_level][y][x] == WALL8)
	{
		pMap->GameMap[g_level][y][x] = WALL8;		//中心点
		if (tank.level == 1)
		{
			WriteChar(y, x, "●", Wall3_color, 1);
		}
		else if (tank.level == 2)
		{
			WriteChar(y, x, "◆", Wall3_color, 1);
		}
		else if (tank.level == 3)
		{
			WriteChar(y, x, "★", Wall3_color, 1);
		}
		else if (tank.level = 5)
		{
			WriteChar(y, x, "■", Wall3_color, 1);
		}	
	}
	else
	{
		pMap->GameMap[g_level][y][x] = tank.tankID;//中心点
		if (tank.level == 1)
		{
			WriteChar(y, x, "●", tank.color, 1);
		}
		else if (tank.level == 2)
		{
			WriteChar(y, x, "◆", tank.color, 1);
		}
		else if (tank.level == 3)
		{
			WriteChar(y, x, "★", tank.color, 1);
		}
		else if (tank.level = 5)
		{
			WriteChar(y, x, "■", tank.color, 1);
		}
	}
}
void CTank::DrawPointA(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x - 1] == WALL3 || pMap->GameMap[g_level][y - 1][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x - 1] = WALL8;
		WriteChar(y - 1, x - 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x - 1] = tank.tankID;//A
		WriteChar(y - 1, x - 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointB(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y][x - 1] == WALL3 || pMap->GameMap[g_level][y][x - 1] == WALL8)
	{

		pMap->GameMap[g_level][y][x - 1] = WALL8;	//B
		WriteChar(y, x - 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y][x - 1] = tank.tankID;//B                                                                                                                                                                               
		WriteChar(y, x - 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointC(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x - 1] == WALL3 || pMap->GameMap[g_level][y + 1][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x - 1] = WALL8;
		WriteChar(y + 1, x - 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x - 1] = tank.tankID;//C
		WriteChar(y + 1, x - 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointD(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x] == WALL3 || pMap->GameMap[g_level][y - 1][x] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x] = WALL8;		//d
		WriteChar(y - 1, x, "■", Wall3_color, 1);

	}
	else
	{
		pMap->GameMap[g_level][y - 1][x] = tank.tankID;//D
		WriteChar(y - 1, x, "■", tank.color, 1);
	}
}
void CTank::DrawPointE(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x] == WALL3 || pMap->GameMap[g_level][y + 1][x] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x] = WALL8;//E
		WriteChar(y + 1, x, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x] = tank.tankID;//E
		WriteChar(y + 1, x, "■", tank.color, 1);
	}
}
void CTank::DrawPointF(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x + 1] == WALL3 || pMap->GameMap[g_level][y - 1][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x + 1] = WALL8;
		WriteChar(y - 1, x + 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x + 1] = tank.tankID;//F
		WriteChar(y - 1, x + 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointG(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y][x + 1] == WALL3 || pMap->GameMap[g_level][y][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y][x + 1] = WALL8;
		WriteChar(y, x + 1, "■", Wall3_color, 1);

	}
	else
	{
		pMap->GameMap[g_level][y][x + 1] = tank.tankID;//G
		WriteChar(y, x + 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointH(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x + 1] == WALL3 || pMap->GameMap[g_level][y + 1][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x + 1] = WALL8;
		WriteChar(y + 1, x + 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x + 1] = tank.tankID;//H
		WriteChar(y + 1, x + 1, "■", tank.color, 1);
	}
}





int CTank::GetDirfromAstar(CMap* pMap,  CTank& tank,  vector<CTank>& vecTank)
{
	CAstar* aStar = new CAstar;
	if (tank.level == 10)
	{
		aStar->AStarSearch1(pMap, tank, vecTank);
	}
	else
		aStar->AStarSearch(pMap, tank, vecTank);
	//int temp= aStar->m_Path[sizeof(aStar->m_Path)-2].dir;
 	int num = aStar->m_Path.size();
// 	int  temp=aStar->m_Path[num].dir;
	bool  flag_inGrass = vecTank[0].inGrass(vecTank[0], pMap);
	if (num > 0 && !flag_inGrass)
	{
		int dir = aStar->m_Path[aStar->m_Path.size() - 1].dir;
		return dir;
	}
	int num_rand = rand() % 7;
	switch (num_rand) {
	case 0:return 0;
	case 1:return 1;
	case 2:return 2;
	case 3:return 3;
	case 4:
	case 5:
	case 6:return tank.dir;
	}
	return tank.dir;
}


//判断否上行能返回0  不能上行但能转向返回1   不能前进不能转向返回2
int CTank::isUP(CTank tank, CMap MapObj)
{
	if (tank.dir == UP)//当前方向
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == 0);
		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == WALL3);
		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		return 2;
	}
	else if (tank.dir == DOWN)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y][tank.x - 1] == 0);
		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y][tank.x - 1] == WALL3);
		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;

		if (flag111&&flag222)
		{
			return 0;
		}
		else if (!flag111 && flag222)
		{
			return 1;
		}
		return 2;
	}
	else if (tank.dir == LEFT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y + 1][tank.x] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y + 1][tank.x] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333&& flag444)//能转
		{
			return 1;
		}
		return 2;
	}
	else if (tank.dir == RIGHT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y - 1][tank.x] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x - 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y - 1][tank.x] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;
	}
	return 2;
}

//判断否下行 能返回0
int CTank::isDOWN(CTank tank, CMap MapObj)
{
	if (tank.dir == UP)//当前方向
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y][tank.x + 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y][tank.x + 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;

		if (flag111&&flag222)
		{
			return 0;
		}
		else if (!flag111 && flag222)
		{
			return 1;
		}
		return 2;


	}
	else if (tank.dir == DOWN)
	{

		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == 0);
		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == WALL3);
		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		return 2;
	}
	else if (tank.dir == LEFT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y + 1][tank.x] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y + 1][tank.x] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;
	}
	else if (tank.dir == RIGHT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y - 1][tank.x] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y][tank.x + 2] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y - 1][tank.x] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;
	}
	return 2;
}

//判断否左行 能返回0
int CTank::isLEFT(CTank tank, CMap MapObj)
{
	if (tank.dir == UP)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y][tank.x + 1] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y][tank.x + 1] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;


	}
	else if (tank.dir == DOWN)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y][tank.x - 1] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y][tank.x - 1] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;


	}
	else if (tank.dir == LEFT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == 0);


		int flag11 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == WALL3);


		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;


		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		return 2;
	}
	else if (tank.dir == RIGHT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y - 1][tank.x] == 0);


		int flag11 = (MapObj.GameMap[g_level][tank.y - 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y - 1][tank.x] == WALL3);


		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;


		if (flag111&&flag222)
		{
			return 0;
		}
		else if ((!flag111 || flag222))//能转
		{
			return 1;
		}
		return 2;
	}
	return 2;
}

//判断右行 
int CTank::isRIGHT(CTank tank, CMap MapObj)
{
	if (tank.dir == UP)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y][tank.x + 1] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y][tank.x + 1] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y - 1][tank.x - 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;
	}
	else if (tank.dir == DOWN)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y][tank.x - 1] == 0);
		int flag4 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == 0);

		int flag11 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y][tank.x - 1] == WALL3);
		int flag44 = (MapObj.GameMap[g_level][tank.y - 1][tank.x + 1] == WALL3);

		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;
		int flag444 = flag4 || flag44;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		else if ((!flag111 || !flag222) && flag333 && flag444)//能转
		{
			return 1;
		}
		return 2;
	}
	else if (tank.dir == LEFT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y + 1][tank.x] == 0);


		int flag11 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y + 1][tank.x] == WALL3);


		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;


		if (flag111&&flag222)
		{
			return 0;
		}
		else if (!flag111 || flag222)//能转
		{
			return 1;
		}
		return 2;
	}
	else if (tank.dir == RIGHT)
	{
		int flag1 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == 0);
		int flag2 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == 0);
		int flag3 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == 0);


		int flag11 = (MapObj.GameMap[g_level][tank.y + 2][tank.x] == WALL3);
		int flag22 = (MapObj.GameMap[g_level][tank.y + 1][tank.x - 1] == WALL3);
		int flag33 = (MapObj.GameMap[g_level][tank.y + 1][tank.x + 1] == WALL3);


		int flag111 = flag1 || flag11;
		int flag222 = flag2 || flag22;
		int flag333 = flag3 || flag33;

		if (flag111&&flag222&&flag333)
		{
			return 0;
		}
		return 2;
	}
	return 2;
}

//判断玩家是否在草里
bool CTank::inGrass(CTank tank, CMap* pMap)
{
	if (!tank.isValid) return 0;

	/*
	A B C
	D O E
	F G H
	O=(y,x)
	A=(y-1,x-1)
	B=(y, x-1)
	C=(y+1,x-1)
	D=(y-1, x)
	E=(y+1, x)
	F=(y-1, x+1)
	G=(y, x+1)
	H=(y+1, x+1)
	...
	*/

	int x = tank.x;
	int y = tank.y;

	//O 中心center	
	bool flagO = pMap->GameMap[g_level][y][x] == WALL8;
	//A
	bool flagA = pMap->GameMap[g_level][y - 1][x - 1] == WALL8;
	//B
	bool flagB = pMap->GameMap[g_level][y][x - 1] == WALL8;
	//C
	bool flagC = pMap->GameMap[g_level][y + 1][x - 1] == WALL8;
	//D
	bool flagD = pMap->GameMap[g_level][y - 1][x] == WALL8;
	//E
	bool flagE = pMap->GameMap[g_level][y + 1][x] == WALL8;
	//F
	bool flagF = pMap->GameMap[g_level][y-1][x + 1] == WALL8;
	//G
	bool flagG = pMap->GameMap[g_level][y + 1][x + 1] == WALL8;
	//H
	bool flagH = pMap->GameMap[g_level][y - 1][x] == WALL8;

	switch (tank.dir)
	{
	case UP:
		//O B D E F H	
		return flagO&&flagB&&flagD&&flagE&&flagF&&flagH;
	case DOWN:
		//O G D E C A
		return flagO&&flagG&&flagD&&flagE&&flagC&&flagA;
	case LEFT:
		//O G D B C H
		return flagO&&flagG&&flagD&&flagE&&flagC&&flagH;
	case RIGHT:
		//O G A B E F
		return flagO&&flagG&&flagA&&flagB&&flagE&&flagF;
	default:
		break;
	}
	return 0;
}




//绘制BOSS
void CTank::DrawBOSSTank(CTank tank, CMap* pMap)
{
	if (!tank.isValid)return;
	switch (tank.dir)
	{
	case UP:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointA(tank, pMap);//A
		DrawPointB(tank, pMap);//B
		DrawPointC(tank, pMap);//C
		DrawPointD(tank, pMap);//D
		DrawPointE(tank, pMap);//E
		DrawPointF(tank, pMap);//F
		DrawPointG(tank, pMap);//G
		DrawPointH(tank, pMap);//H	

		DrawPointI(tank, pMap);//I	
		DrawPointJ(tank, pMap);//J	
		DrawPointK(tank, pMap);//K	
		DrawPointL(tank, pMap);//L	
		DrawPointM(tank, pMap);//M	
		DrawPointN(tank, pMap);//N	
		DrawPointP(tank, pMap);//P	
		break;
	case DOWN:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointA(tank, pMap);//A
		DrawPointB(tank, pMap);//B
		DrawPointC(tank, pMap);//C
		DrawPointD(tank, pMap);//D
		DrawPointE(tank, pMap);//E
		DrawPointF(tank, pMap);//F
		DrawPointG(tank, pMap);//G
		DrawPointH(tank, pMap);//H	

		DrawPointT(tank, pMap);//T	

		DrawPointU(tank, pMap);//U
		DrawPointV(tank, pMap);//V
		DrawPointW(tank, pMap);//W	
		DrawPointR(tank, pMap);//R
		DrawPointS(tank, pMap);//S	
		DrawPointJ(tank, pMap);//J	

		break;
	case LEFT:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointA(tank, pMap);//A
		DrawPointB(tank, pMap);//B
		DrawPointC(tank, pMap);//C
		DrawPointD(tank, pMap);//D
		DrawPointE(tank, pMap);//E
		DrawPointF(tank, pMap);//F
		DrawPointG(tank, pMap);//G
		DrawPointH(tank, pMap);//H	

		DrawPointI(tank, pMap);//I	
		DrawPointJ(tank, pMap);//J	
		DrawPointM(tank, pMap);//M	
		DrawPointP(tank, pMap);//P	

		DrawPointR(tank, pMap);//R
		DrawPointS(tank, pMap);//S	
		DrawPointT(tank, pMap);//T	
		break;
	case RIGHT:
		DrawPointCenter(tank, pMap);//O 中心center	
		DrawPointA(tank, pMap);//A
		DrawPointB(tank, pMap);//B
		DrawPointC(tank, pMap);//C
		DrawPointD(tank, pMap);//D
		DrawPointE(tank, pMap);//E
		DrawPointF(tank, pMap);//F
		DrawPointG(tank, pMap);//G
		DrawPointH(tank, pMap);//H	
		DrawPointI(tank, pMap);//I	
		DrawPointT(tank, pMap);//T	

		DrawPointU(tank, pMap);//U
		DrawPointV(tank, pMap);//V
		DrawPointW(tank, pMap);//W	
		DrawPointX(tank, pMap);//X	
		DrawPointY(tank, pMap);//Y	


		break;
	default:
		break;
	}

}
//绘制BOSS
void CTank::ClearBOSSTank(CTank tank, CMap* pMap)
{
	if (!tank.isValid)return;
	switch (tank.dir)
	{
	case UP:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointA(tank, pMap);//A
		ClearPointB(tank, pMap);//B
		ClearPointC(tank, pMap);//C
		ClearPointD(tank, pMap);//D
		ClearPointE(tank, pMap);//E
		ClearPointF(tank, pMap);//F
		ClearPointG(tank, pMap);//G
		ClearPointH(tank, pMap);//H	
		ClearPointI(tank, pMap);//I	
		ClearPointJ(tank, pMap);//J	
		ClearPointK(tank, pMap);//K	
		ClearPointL(tank, pMap);//L	
		ClearPointM(tank, pMap);//M	
		ClearPointN(tank, pMap);//N	
		ClearPointP(tank, pMap);//P	
		break;
	case DOWN:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointA(tank, pMap);//A
		ClearPointB(tank, pMap);//B
		ClearPointC(tank, pMap);//C
		ClearPointD(tank, pMap);//D
		ClearPointE(tank, pMap);//E
		ClearPointF(tank, pMap);//F
		ClearPointG(tank, pMap);//G
		ClearPointH(tank, pMap);//H	
		ClearPointT(tank, pMap);//T	
		ClearPointU(tank, pMap);//U
		ClearPointV(tank, pMap);//V
		ClearPointW(tank, pMap);//W	
		ClearPointR(tank, pMap);//R
		ClearPointS(tank, pMap);//S	
		ClearPointJ(tank, pMap);//J	

		break;
	case LEFT:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointA(tank, pMap);//A
		ClearPointB(tank, pMap);//B
		ClearPointC(tank, pMap);//C
		ClearPointD(tank, pMap);//D
		ClearPointE(tank, pMap);//E
		ClearPointF(tank, pMap);//F
		ClearPointG(tank, pMap);//G
		ClearPointH(tank, pMap);//H	
		ClearPointI(tank, pMap);//I	
		ClearPointJ(tank, pMap);//J	
		ClearPointM(tank, pMap);//M	
		ClearPointP(tank, pMap);//P	

		ClearPointR(tank, pMap);//R
		ClearPointS(tank, pMap);//S	
		ClearPointT(tank, pMap);//T	
	case RIGHT:
		ClearPointCenter(tank, pMap);//O 中心center	
		ClearPointA(tank, pMap);//A
		ClearPointB(tank, pMap);//B
		ClearPointC(tank, pMap);//C
		ClearPointD(tank, pMap);//D
		ClearPointE(tank, pMap);//E
		ClearPointF(tank, pMap);//F
		ClearPointG(tank, pMap);//G
		ClearPointH(tank, pMap);//H	
		ClearPointI(tank, pMap);//I	
		ClearPointT(tank, pMap);//T	
		ClearPointU(tank, pMap);//U
		ClearPointV(tank, pMap);//V
		ClearPointW(tank, pMap);//W	
		ClearPointX(tank, pMap);//X	
		ClearPointY(tank, pMap);//Y	


		break;
	default:
		break;
	}

}


void CTank::ClearPointI(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y][x - 2] == WALL8)
	{
		pMap->GameMap[g_level][y][x - 2] = WALL3;//
		pMap->returnMap(y, x - 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y][x - 2] = 0;//
		WriteChar(y, x - 2, "  ", tank.color, 1);
	}
}
void CTank::ClearPointJ(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 2][x] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x] = WALL3;//j
		pMap->returnMap(y - 2, x, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x] = 0;//C
		WriteChar(y - 2, x, "  ", tank.color, 1);
	}
}
void CTank::ClearPointK(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 2][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x + 1] = WALL3;//d
		pMap->returnMap(y - 2, x + 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x + 1] = 0;//D
		WriteChar(y - 2, x + 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointL(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 2][x] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x] = WALL3;//e
		pMap->returnMap(y + 2, x, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x] = 0;//E
		WriteChar(y + 2, x, "  ", tank.color, 1);
	}
}
void CTank::ClearPointM(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 2][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x + 1] = WALL3;//f
		pMap->returnMap(y + 2, x + 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x + 1] = 0;//F
		WriteChar(y + 2, x + 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointN(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x + 2] = WALL3;//g
		pMap->returnMap(y - 1, x + 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x + 2] = 0;//G
		WriteChar(y - 1, x + 2, "  ", tank.color, 1);
	}
}
void CTank::ClearPointP(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x + 2] = WALL3;//h
		pMap->returnMap(y + 1, x + 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x + 2] = 0;//H
		WriteChar(y + 1, x + 2, "  ", tank.color, 1);
	}
}
void CTank::ClearPointR(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 1][x - 2] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x - 2] = WALL3;//c
		pMap->returnMap(y + 1, x - 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x - 2] = 0;//C
		WriteChar(y + 1, x - 2, "  ", tank.color, 1);
	}
}
void CTank::ClearPointS(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 2][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x - 1] = WALL3;//d
		pMap->returnMap(y + 2, x - 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x - 1] = 0;//D
		WriteChar(y + 2, x - 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointT(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y][x + 2] = WALL3;//e
		pMap->returnMap(y, x + 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y][x + 2] = 0;//E
		WriteChar(y, x + 2, "  ", tank.color, 1);
	}
}
void CTank::ClearPointU(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x - 2] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x - 2] = WALL3;//f
		pMap->returnMap(y - 1, x - 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x - 2] = 0;//F
		WriteChar(y - 1, x - 2, "  ", tank.color, 1);
	}
}
void CTank::ClearPointV(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 2][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x - 1] = WALL3;//g
		pMap->returnMap(y - 2, x - 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x - 1] = 0;//G
		WriteChar(y - 2, x - 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointW(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y + 2][x] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x] = WALL3;//h
		pMap->returnMap(y + 2, x, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x] = 0;//H
		WriteChar(y + 2, x, "  ", tank.color, 1);
	}
}
void CTank::ClearPointX(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 2][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x + 1] = WALL3;//B
		pMap->returnMap(y - 2, x + 1, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x + 1] = 0;//B
		WriteChar(y - 2, x + 1, "  ", tank.color, 1);
	}
}
void CTank::ClearPointY(CTank tank, CMap * pMap)
{
	if (pMap->GameMap[g_level][y - 1][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x + 2] = WALL3;//c
		pMap->returnMap(y - 1, x + 2, WALL3);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x + 2] = 0;//C
		WriteChar(y - 1, x + 2, "  ", tank.color, 1);
	}
}

void CTank::DrawPointI(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y][x - 2] == WALL3 || pMap->GameMap[g_level][y][x - 2] == WALL8)
	{
		pMap->GameMap[g_level][y][x - 2] = WALL8;
		WriteChar(y, x - 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y][x - 2] = tank.tankID;//I
		WriteChar(y, x - 2, "■", tank.color, 1);
	}
}
void CTank::DrawPointJ(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 2][x] == WALL3 || pMap->GameMap[g_level][y - 2][x] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x] = WALL8;
		WriteChar(y - 2, x, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x] = tank.tankID;//I
		WriteChar(y - 2, x, "■", tank.color, 1);
	}
}
void CTank::DrawPointK(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 2][x + 1] == WALL3 || pMap->GameMap[g_level][y - 2][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x + 1] = WALL8;
		WriteChar(y - 2, x + 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x + 1] = tank.tankID;//K
		WriteChar(y - 2, x + 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointL(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y + 2][x] == WALL3 || pMap->GameMap[g_level][y + 2][x] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x] = WALL8;
		WriteChar(y + 2, x, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x] = tank.tankID;//L
		WriteChar(y + 2, x, "■", tank.color, 1);
	}
}
void CTank::DrawPointM(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y + 2][x + 1] == WALL3 || pMap->GameMap[g_level][y + 2][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x + 1] = WALL8;
		WriteChar(y + 2, x + 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x + 1] = tank.tankID;//M
		WriteChar(y + 2, x + 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointN(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 1][x + 2] == WALL3 || pMap->GameMap[g_level][y - 1][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x + 2] = WALL8;
		WriteChar(y - 1, x + 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x + 2] = tank.tankID;//N
		WriteChar(y - 1, x + 2, "■", tank.color, 1);
	}
}
void CTank::DrawPointP(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y + 1][x + 2] == WALL3 || pMap->GameMap[g_level][y + 1][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x + 2] = WALL8;
		WriteChar(y + 1, x + 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x + 2] = tank.tankID;//P
		WriteChar(y + 1, x + 2, "■", tank.color, 1);
	}
}
void CTank::DrawPointR(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y + 1][x - 2] == WALL3 || pMap->GameMap[g_level][y + 1][x - 2] == WALL8)
	{
		pMap->GameMap[g_level][y + 1][x - 2] = WALL8;
		WriteChar(y + 1, x - 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 1][x - 2] = tank.tankID;//R
		WriteChar(y + 1, x - 2, "■", tank.color, 1);
	}
}
void CTank::DrawPointS(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y + 2][x - 1] == WALL3 || pMap->GameMap[g_level][y + 2][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x - 1] = WALL8;
		WriteChar(y + 2, x - 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x - 1] = tank.tankID;//S
		WriteChar(y + 2, x - 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointT(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y][x + 2] == WALL3 || pMap->GameMap[g_level][y][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y][x + 2] = WALL8;
		WriteChar(y, x + 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y][x + 2] = tank.tankID;//T
		WriteChar(y, x + 2, "■", tank.color, 1);
	}
}
void CTank::DrawPointU(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 1][x - 2] == WALL3 || pMap->GameMap[g_level][y - 1][x - 2] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x - 2] = WALL8;
		WriteChar(y - 1, x - 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x - 2] = tank.tankID;//U
		WriteChar(y - 1, x - 2, "■", tank.color, 1);
	}
}
void CTank::DrawPointV(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 2][x - 1] == WALL3 || pMap->GameMap[g_level][y - 2][x - 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x - 1] = WALL8;
		WriteChar(y - 2, x - 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x - 1] = tank.tankID;//V
		WriteChar(y - 2, x - 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointW(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y + 2][x] == WALL3 || pMap->GameMap[g_level][y + 2][x] == WALL8)
	{
		pMap->GameMap[g_level][y + 2][x] = WALL8;
		WriteChar(y + 2, x, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y + 2][x] = tank.tankID;//T
		WriteChar(y + 2, x, "■", tank.color, 1);
	}
}
void CTank::DrawPointX(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 2][x + 1] == WALL3 || pMap->GameMap[g_level][y - 2][x + 1] == WALL8)
	{
		pMap->GameMap[g_level][y - 2][x + 1] = WALL8;
		WriteChar(y - 2, x + 1, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 2][x + 1] = tank.tankID;//X
		WriteChar(y - 2, x + 1, "■", tank.color, 1);
	}
}
void CTank::DrawPointY(CTank tank, CMap *pMap)
{
	if (pMap->GameMap[g_level][y - 1][x + 2] == WALL3 || pMap->GameMap[g_level][y - 1][x + 2] == WALL8)
	{
		pMap->GameMap[g_level][y - 1][x + 2] = WALL8;
		WriteChar(y - 1, x + 2, "■", Wall3_color, 1);
	}
	else
	{
		pMap->GameMap[g_level][y - 1][x + 2] = tank.tankID;//Y
		WriteChar(y - 1, x + 2, "■", tank.color, 1);
	}
}
