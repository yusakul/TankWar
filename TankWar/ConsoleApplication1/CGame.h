#pragma once
#include <vector>
using namespace std;
#include "CBullet.h"
#include <windows.h>
#include "Tools.h"
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "CTank.h"
#include "Data.h"
#include "CAstar.h"

class CAstar;
class CTank;
class CBullet;
class CMap;
class CGame
{
public:
	friend class CAstar;

	//地图对象（整个游戏都是使用该地图对象）
	CMap* pMap = new CMap;

	//坦克向量（所有坦克都保存在一起）
	//第一个和第二个分别表示自己和友军）
	vector<CTank> m_vecTank;

	//子弹向量（所有子弹都保存在一起）
	vector<CBullet> m_vecBullet;

	//A星
	CAstar* pAstar;


	int isUserMap;//是否使用自定义地图 是1 否0
	int killNum;//杀敌数
	int key;//菜单记录选中项,初始为第一个
	int flag;//记录是否键入enter键,初始为否
	int ch;//菜单记录键入值*/
	int speed;//Npc行动速度
	int isOver;//游戏是否结束
	int playerNum;//玩家数量
	int flag_NpcFire; //Npc开火开关
	int NPCbornNum;		//npc刷新次数 一次- -
	int flag_reGame; //重新游戏标识 1重新过 0木有
	int flag_nextLeveL;//进入下一关记号
	int flag_NOdead;//无敌开关
	int flag_TimePause;//NPC时间停止开关



	//游戏循环
	void Game();

	//绘制玩家坦克
	void DrawPlayTank(int playerNum, CTank* pTank);

	//初始化NPC坦克属性
	void InitNpcTank();

	//生成NPC坦克并初始化属性
	void InitNpcTankInfo();

	//绘制全部NPC坦克
	void DrawNPCTank(CTank * pTank);

	//子弹存在值清零
	void InitBullet();

	//开始游戏
	void StartGame();

	//欢迎界面
	void WelcomeUI();

	//开始菜单
	int Select();

	//读取游戏（正在施工...)
	void LoadGame();

	//保存游戏（正在施工...）
	void SaveGame();

	//地图编辑
	int MapEdit();

	//绘制所有地图
	void DrawAllMap();

	//绘制侧边信息栏
	void InfoMeum(CTank* Player_Tank);

	//死亡菜单
	void DeadMeum();

	//胜利菜单
	void VictorMeum();

	//玩家操作
	int PlayGame();

	//坦克单步移动
	int Move(CTank * pTank, Dir dir);

	int bossMove(CTank * pTank, Dir dir);

	//坦克转向
	int ChangeDir(CTank * pTank, Dir dir);


	//暂停
	int Pause();

	//子弹移动循环
	int MoveAllBullet();

	//子弹单步移动
	void MoveBullet(CBullet *Bullet);

	//检查子弹状态 1为坐标空 0为坐标有其他物体
	int CheckBullet(CBullet bullet);

	//子弹撞墙
	int hitWall(int x, int y, CBullet bullet);

	//子弹撞坦克
	int hitTank(int x, int y, CBullet bullet);

	//子弹对撞
	int hitBullet(int x, int y, CBullet bullet);

	//检索坐标对应的坦克编号 x列 y行
	int SearchTank(int x, int y);

	//Npc level 1坦克移动开火循环 
	int MoveNpcTank_1();

	//Npc level 2坦克移动开火循环 
	int MoveNpcTank_2();

	//Npc level 2坦克移动开火循环 
	int MoveNpcTank_3();

	int MoveNpcTank_10();


	//获取NPC坦克剩余数量
	int GetNpcNum();

	//获取NPC坦克编号
	int GetNpcID(int x, int y);


	//检测3x3范围内是够为空
	int isEmpty(int posX, int PosY);

	//其他比较一般的粗劣的寻路AI
	Dir OtherAI(CTank tank);

	//开火
	void Fire(CTank * pTank);

	//npc重生
	void CGame::RefreshNPC(CTank tank);
};


