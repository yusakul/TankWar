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

	//��ͼ����������Ϸ����ʹ�øõ�ͼ����
	CMap* pMap = new CMap;

	//̹������������̹�˶�������һ��
	//��һ���͵ڶ����ֱ��ʾ�Լ����Ѿ���
	vector<CTank> m_vecTank;

	//�ӵ������������ӵ���������һ��
	vector<CBullet> m_vecBullet;

	//A��
	CAstar* pAstar;


	int isUserMap;//�Ƿ�ʹ���Զ����ͼ ��1 ��0
	int killNum;//ɱ����
	int key;//�˵���¼ѡ����,��ʼΪ��һ��
	int flag;//��¼�Ƿ����enter��,��ʼΪ��
	int ch;//�˵���¼����ֵ*/
	int speed;//Npc�ж��ٶ�
	int isOver;//��Ϸ�Ƿ����
	int playerNum;//�������
	int flag_NpcFire; //Npc���𿪹�
	int NPCbornNum;		//npcˢ�´��� һ��- -
	int flag_reGame; //������Ϸ��ʶ 1���¹� 0ľ��
	int flag_nextLeveL;//������һ�ؼǺ�
	int flag_NOdead;//�޵п���
	int flag_TimePause;//NPCʱ��ֹͣ����



	//��Ϸѭ��
	void Game();

	//�������̹��
	void DrawPlayTank(int playerNum, CTank* pTank);

	//��ʼ��NPC̹������
	void InitNpcTank();

	//����NPC̹�˲���ʼ������
	void InitNpcTankInfo();

	//����ȫ��NPC̹��
	void DrawNPCTank(CTank * pTank);

	//�ӵ�����ֵ����
	void InitBullet();

	//��ʼ��Ϸ
	void StartGame();

	//��ӭ����
	void WelcomeUI();

	//��ʼ�˵�
	int Select();

	//��ȡ��Ϸ������ʩ��...)
	void LoadGame();

	//������Ϸ������ʩ��...��
	void SaveGame();

	//��ͼ�༭
	int MapEdit();

	//�������е�ͼ
	void DrawAllMap();

	//���Ʋ����Ϣ��
	void InfoMeum(CTank* Player_Tank);

	//�����˵�
	void DeadMeum();

	//ʤ���˵�
	void VictorMeum();

	//��Ҳ���
	int PlayGame();

	//̹�˵����ƶ�
	int Move(CTank * pTank, Dir dir);

	int bossMove(CTank * pTank, Dir dir);

	//̹��ת��
	int ChangeDir(CTank * pTank, Dir dir);


	//��ͣ
	int Pause();

	//�ӵ��ƶ�ѭ��
	int MoveAllBullet();

	//�ӵ������ƶ�
	void MoveBullet(CBullet *Bullet);

	//����ӵ�״̬ 1Ϊ����� 0Ϊ��������������
	int CheckBullet(CBullet bullet);

	//�ӵ�ײǽ
	int hitWall(int x, int y, CBullet bullet);

	//�ӵ�ײ̹��
	int hitTank(int x, int y, CBullet bullet);

	//�ӵ���ײ
	int hitBullet(int x, int y, CBullet bullet);

	//���������Ӧ��̹�˱�� x�� y��
	int SearchTank(int x, int y);

	//Npc level 1̹���ƶ�����ѭ�� 
	int MoveNpcTank_1();

	//Npc level 2̹���ƶ�����ѭ�� 
	int MoveNpcTank_2();

	//Npc level 2̹���ƶ�����ѭ�� 
	int MoveNpcTank_3();

	int MoveNpcTank_10();


	//��ȡNPC̹��ʣ������
	int GetNpcNum();

	//��ȡNPC̹�˱��
	int GetNpcID(int x, int y);


	//���3x3��Χ���ǹ�Ϊ��
	int isEmpty(int posX, int PosY);

	//�����Ƚ�һ��Ĵ��ӵ�Ѱ·AI
	Dir OtherAI(CTank tank);

	//����
	void Fire(CTank * pTank);

	//npc����
	void CGame::RefreshNPC(CTank tank);
};


