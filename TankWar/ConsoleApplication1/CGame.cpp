#include "CGame.h"

//��Ϸѭ��
void CGame::Game()
{

	//���
	m_vecTank.clear();
	CTank* Player_Tank = new CTank[2];
	for (int i = 0; i < 2; i++)
	{
		m_vecTank.push_back(Player_Tank[i]);
	}
	//NPC
	CTank* NPC_Tank = new CTank[100];
	for (int i = 0; i < 100; i++)
	{
		m_vecTank.push_back(NPC_Tank[i]);
	}
	//�ӵ�
	CBullet* pBullet = new CBullet[300];
	for (int i = 0; i < 300; i++)
	{
		m_vecBullet.push_back(pBullet[i]);
	}
	

timing://ʱ�� ����170��
	
	SetBackColor();
	system("cls");
	StartGame();

	g_level = 1;//�ؿ�
	flag_NpcFire = 1;//Npc���𿪹�
	isUserMap = 0;//�Զ����ͼ����
	flag_reGame = 0;//��Ϸ��������Ϸ����ʶ
	flag_nextLeveL = 0;//������һ�ؼǺ�
	flag_NOdead=1;//�޵п��� 
	flag_TimePause = 1;//NPCʱ��ֹͣ����

	int temp_select = Select();
	while (1) {
		

		switch (temp_select) {
		case 1://����
			playerNum = 1; break;
		case 2://˫��
			playerNum = 2; break;
		case 3://��ȡ��Ϸ
			LoadGame(); goto timing; break;
		case 4://��ͼ�༭
			isUserMap = 1; 
			if (MapEdit() == 3) {
				goto timing; break;

			}
				
		}
	timing_nextlevel:
		Sound(5);
		SetBackColor();//���ñ���ɫ
		system("cls");
		isOver = 0;//��Ϸ��������
		killNum = 0;//ɱ��������

		//��ͼ
		DrawAllMap();//����ȫ����ͼ

		//���
		DrawPlayTank(playerNum, Player_Tank);

		//NPC
		DrawNPCTank(NPC_Tank);

		//�ӵ�
		InitBullet();

		InfoMeum(Player_Tank);//�����Ϣ��

		Sleep(1000);

		NPCbornNum = 8;//npcˢ�´��� һ��- -
		
		while (1) 
		{

			if ((m_vecTank[0].isValid==0 && m_vecTank[1].isValid==0)) {
				DeadMeum();
				goto timing;
			}
			if (PlayGame() == 2) {
				int temp = Pause();//��ͣ����ֵ:   1:������Ϸ  2:������Ϸ   3:������Ϸ  4:���ز˵�
				if (temp == 2) { flag_reGame = 1; break; }
				if (temp == 3) { SaveGame(); }
				if (temp == 4) { goto timing; }//����ʱ�� 
			}

			MoveAllBullet();

			if (flag_TimePause == 1)//NPC�ƶ�
			{
				MoveNpcTank_10();
				MoveNpcTank_1();
				MoveNpcTank_2();
				MoveNpcTank_3();
				
			}
		

			if (GetNpcNum()==0)//���npc�����ж��Ƿ������һ��
			{
				Sleep(500);
				g_level++;
				if (g_level > 6)//ͨ��
				{
					Sound(2);
					VictorMeum();
					
					goto timing;
				}
				else//�����¹�
				{
					Sound(4);
					flag_nextLeveL = 1;
					goto timing_nextlevel;
				}
				
			}
			if (isOver == 1) {
				WriteNum(47, 9, Player_Tank[0].hp, 7, 1);
				WriteNum(47, 15, Player_Tank[1].hp, 7, 1);
				DeadMeum();
				goto timing;
			}
		}
	}
}

//����ȫ�����̹��
void CGame::DrawPlayTank(int playerNum, CTank* pTank)
{
	if (flag_nextLeveL == 0)//û�п�����һ�ؼǺ�
	{
		pTank->InitPlayerTank(playerNum, pTank);//��ʼ�����̹������}
		m_vecTank[0] = pTank[0];
		m_vecTank[1] = pTank[1];
	}
	else if (flag_nextLeveL == 1)//������һ�ؼǺ�Ϊ��
	{
		//���긴λ
		m_vecTank[0].dir = UP;
		m_vecTank[0].x = 37;
		m_vecTank[0].y = 23;
		m_vecTank[1].dir = UP;
		m_vecTank[1].x = 37;
		m_vecTank[1].y = 16;
		
	}
	
	m_vecTank[0].DrawTank(m_vecTank[0], pMap);
	m_vecTank[1].DrawTank(m_vecTank[1], pMap);
	
}

//����ȫ��NPC̹��
void CGame::DrawNPCTank(CTank* pTank)
{
	InitNpcTank();
	for (int i = 2; i < 102; i++)
	{
		if (m_vecTank[i].level==10)
		{
			m_vecTank[i].DrawBOSSTank(m_vecTank[i], pMap);
		}
		m_vecTank[i].DrawTank(m_vecTank[i], pMap);
	}
}

//NPC̹�˹���
void CGame::InitNpcTank()
{
	for (int i = 2; i < 102; i++)
	{
		m_vecTank[i].isValid = 0;
	}
	InitNpcTankInfo();
}

//����NPC̹������
void CGame::InitNpcTankInfo()
{

	for (int index = 2; index < 102; index++)
	{
		int flag_loop = 0;
		if (m_vecTank[index].isValid == 0)
		{
			for (int i = 0; i < 40; i++)
			{
				for (int j = 0; j < 40; j++)
				{
					for (int k = 20; k <= 27; k++)
					{
						if (pMap->GameMap[g_level][i][j] == k&&isEmpty(i,j))
						{
							if (k >= 20 && k <= 23)
							{
								m_vecTank[index].level = 1;//̹�˵ȼ�
								m_vecTank[index].hp = 1;
							}
							else if (k == 24 || k == 25)
							{
								m_vecTank[index].level = 2;
								m_vecTank[index].hp = 2;
							}
							else if (k == 26)
							{
								m_vecTank[index].level = 3;
								m_vecTank[index].hp = 3;
							}
							else if (k == 27)
							{
								m_vecTank[index].level = 10;
								m_vecTank[index].hp = 10;
							}
							m_vecTank[index].borntime = 1;
							m_vecTank[index].x_born = j;
							m_vecTank[index].y_born = i;
							m_vecTank[index].x = j;
							m_vecTank[index].y = i;
							m_vecTank[index].dir = DOWN;
							m_vecTank[index].isValid = 1;
							m_vecTank[index].color = BULE;
							m_vecTank[index].tankID = 100 + index;//���̹��IDΪ1��2 Npc̹��idΪ100����
							pMap->GameMap[g_level][i][j] = m_vecTank[index].tankID;//������ֵ������Ϊ̹��id
							flag_loop = 1;
							if (k == 27)m_vecTank[index].color = 4;
							break;
						}	
						else if (pMap->GameMap[g_level][i][j] == k && !isEmpty(i, j))
						{
							pMap->GameMap[g_level][i][j] = 0;//������ֵ������Ϊ0
						}

					}
					if (flag_loop)break;
				}
				if (flag_loop)break;
			}
		}

	}
}
	
//�ӵ�����ֵ����
void CGame::InitBullet()
{
	for (int i = 0; i < 300; i++)
	{
		m_vecBullet[i].isValid = 0;
	}
}

//��ʼ��Ϸ
void CGame::StartGame()
{
	SetConsoleTitle(L"̹�˴�ս");//��������
	SetWindowsSize("̹�˴�ս", 100, 40);
	WelcomeUI();
	Sound(8);
}

//��ӭ����
void CGame::WelcomeUI()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (g_StartAnimer[i][j] == 204)
			{
				WriteChar(i, j,
					" \n               \
				    �{��רTһ \n             \
				����������{�{�{�{�{�{�|\n             \
				�������������������� \n                        \
                ���ѡ��ѡ��ѡ��ѡ���", 3, 1);
			}
			else if (g_StartAnimer[i][j] == 5)
			{
				WriteChar(i, j, "��", 2, 1);
			}
		}
	}
}

//�˵�
int CGame::Select()
{
	WriteChar(21, 27, "���¼�ѡ��س�ȷ��", 7, 1);
	WriteChar(23, 29, "������Ϸ", 7, 0);
	WriteChar(23, 31, "˫����Ϸ", 7, 1);
	WriteChar(23, 33, "��ȡ��Ϸ", 7, 1);
	WriteChar(23, 35, "��ͼ�༭", 7, 1);
	WriteChar(23, 37, "�˳���Ϸ", 7, 1);
	ch;//��¼����ֵ*/
	key = 1;//��¼ѡ����,��ʼΪ��һ��
	flag = 0; //��¼�Ƿ����enter��,��ʼΪ��
	while (ch = _getch()) {
		switch (ch) {
		case 224:
			switch (_getch()) {
			case 72://��
				if (key == 1) {
					WriteChar(23, 29, "������Ϸ", 7, 1);
					WriteChar(23, 37, "�˳���Ϸ", 7, 0);
					//
					key = 5;
				}
				else if (key == 2) {
					WriteChar(23, 31, "˫����Ϸ", 7, 1);
					WriteChar(23, 29, "������Ϸ", 7, 0);
					//
					key = 1;
				}
				else if (key == 3) {
					WriteChar(23, 33, "��ȡ��Ϸ", 7, 1);
					WriteChar(23, 31, "˫����Ϸ", 7, 0);
					//
					key = 2;
				}
				else if (key == 4) {
					WriteChar(23, 35, "��ͼ�༭", 7, 1);
					WriteChar(23, 33, "��ȡ��Ϸ", 7, 0);
					//
					key = 3;
				}
				else if (key == 5) {
					WriteChar(23, 37, "�˳���Ϸ", 7, 1);
					WriteChar(23, 35, "��ͼ�༭", 7, 0);
					
					key = 4;
				}
				break;
			case 80://�·����
				if (key == 1) {
					WriteChar(23, 29, "������Ϸ", 7, 1);
					WriteChar(23, 31, "˫����Ϸ", 7, 0);
					
					key = 2;
				}
				else if (key == 2) {
					WriteChar(23, 31, "˫����Ϸ", 7, 1);
					WriteChar(23, 33, "��ȡ��Ϸ", 7, 0);
					
					key = 3;
				}
				else if (key == 3) {
					WriteChar(23, 33, "��ȡ��Ϸ", 7, 1);
					WriteChar(23, 35, "��ͼ�༭", 7, 0);
					
					key = 4;
				}
				else if (key == 4) {
					WriteChar(23, 35, "��ͼ�༭", 7, 1);
					WriteChar(23, 37, "�˳���Ϸ", 7, 0);
					
					key = 5;
				}
				else if (key == 5) {
					WriteChar(23, 37, "�˳���Ϸ", 7, 1);
					WriteChar(23, 29, "������Ϸ", 7, 0);
					
					key = 1;
				}
			}
			break;
		case 13:	//enter�س���		
			
			flag = 1; break;
		default:
			continue;
		}
		if (flag)//�س�ȷ��,�˳�ѭ��
		{
			break;
		}
	}
	switch (key)
	{
	case 1:
		return 1;//����
	case 2:
		return 2;//˫��
	case 3:
		return 3;//��ȡ
	case 4:
		return 4;//�༭��ͼ
	case 5:
		exit(0);//�˳���Ϸ
	}
	return 1;
}

//��ȡ��Ϸ
void CGame::LoadGame()
{
	system("cls");
	WriteChar(18, 18, "����ʩ����...", 7, 1);
	_getch();
}

//������Ϸ
void CGame::SaveGame()
{
	WriteChar(18, 18, "����ʩ����...", 7, 1);
	_getch();
	for (int i = 18; i <= 25; i++) {
		WriteChar(i, 18, "  ", 7, 1);
	}
	for (int i = 29; i <= 35; i += 2) {
		for (int j = 43; j <= 46; j++) {
			WriteChar(j, i, "  ", 7, 1);
		}
	}
}

// ��ͼ�༭
int CGame::MapEdit()
{
	SetBackColor();
	system("cls");
	pMap->InitUserMapformG_Map(pMap);
	pMap->DrawUserMap(g_level);

timing_MessageLoop:

	WriteChar(43, 25, "level ", 7, 1);
	WriteNum(47, 25, g_level, 7, 1);
	WriteChar(43, 29, "ѡ��ѡ��", 7, 1);
	WriteChar(43, 31, "������Ϸ", 7, 1);
	WriteChar(43, 33, "˫����Ϸ", 7, 1);
	WriteChar(43, 35, "���ز˵�", 7, 1);

	WriteChar(42,  2, "���ѡ����", 7, 1);
	WriteChar(42, 4, "��ǽ", 7, 1);				WriteChar(46, 4, "שǽ", 7, 1);
	WriteChar(42, 5, "����", Wall0_color, 1);  WriteChar(46, 5, "����", Wall1_color, 1);
	WriteChar(42, 6, "����", Wall0_color, 1);  WriteChar(46, 6, "����", Wall1_color, 1);
	WriteChar(42, 8, "����", 7, 1);            WriteChar(46, 8, "����", 7, 1);
	WriteChar(42, 9, "����", Wall3_color, 1);  WriteChar(46, 9, "����", Wall2_color, 1);
	WriteChar(42, 10, "����", Wall3_color, 1);  WriteChar(46,10, "����", Wall2_color, 1);
	WriteChar(42, 12, "��ˢ-", 7, 1); WriteChar(46, 12, "��ˢ+", 7, 1);
	WriteChar(42, 13, "����", 7, 1);  WriteChar(46, 13, "����", 7, 1);
	WriteChar(42, 14, "����", 7, 1);  WriteChar(46, 14, "����", 7, 1);
	WriteChar(42, 16, "�ؿ�-", 7, 1); WriteChar(46, 16, "�ؿ�+", 7, 1);
	WriteChar(42, 17, "����", 7, 1);  WriteChar(46, 17, "����", 7, 1);
	WriteChar(42, 18, "����", 7, 1);  WriteChar(46, 18, "����", 7, 1);
	WriteChar(42, 20, "ɾ��", 7, 1);	WriteChar(46, 20, "����", 7, 1);
	WriteChar(42, 21, "����", 7, 1);	WriteChar(46, 21, "���", 7, 1);
	WriteChar(42, 22, "����", 7, 1);	WriteChar(46, 22, "���", 7, 1);


	switch (pMap->MessageLoop())////���أ�1���� 2˫�� 3���ز˵� 
	{
	case 1:
		isUserMap = 1;
		playerNum = 1;
		break;
	case 2:
		isUserMap = 1;
		playerNum = 2;
		break;
	case 3:
		isUserMap = 0;
		return 3;
	case 4://�л���ͼ
		SetBackColor();
		system("cls");
		pMap->DrawUserMap(g_level);
		goto timing_MessageLoop;
	case 5:	//���õ�ǰ�ؿ���ͼ
		SetBackColor();
		system("cls");
		memcpy(g_UserMap[g_level], g_Map[g_level], sizeof(pMap->GameMap[g_level]));//���Ƹ��Զ����ͼ
		pMap->DrawUserMap(g_level);
		goto timing_MessageLoop;
	}
	g_level = 1;
	return 0;
}

//����ȫ����ͼ
void CGame::DrawAllMap()
{
	if (isUserMap) //ʹ���û���ͼ
	{
		pMap->InitGameMapfromUser(pMap);//��Ϸ��ͼ�����Զ����ͼ
	}
	else //ʹ��ԭʼ��ͼ
	{
		pMap->InitGameMapfromG_Map(pMap);//��Ϸ��ͼ����ԭʼ��ͼ	
	}
	pMap->DrawMap(*pMap);//���Ƶ�ͼ
}

//���Ʋ����Ϣ��
void CGame::InfoMeum(CTank* Player_Tank)
{
	WriteChar(43, 1, "Tank War", 7, 1);
	WriteChar(43, 3, "level ", 7, 1);
	WriteNum(47, 3, g_level, 7, 1);
	WriteChar(42, 5, "��ɱ:K", 7, 1);
	WriteChar(46, 5, "��Ĭ:L", 7, 1);
	WriteChar(42, 7, "�޵�:I", 7, 1);
	WriteChar(46, 7, "���:O", 7, 1);

	WriteChar(41, 9, "��� 1", 7, 1);
	WriteChar(43, 11, "����ֵ", 7, 1);
	WriteNum(47, 11, m_vecTank[0].hp, 7, 1);
	WriteChar(43, 13, "��  ��", 7, 1);
	WriteNum(47, 13, m_vecTank[0].score, 7, 1);
	WriteChar(43, 15, "���� ��������", 7, 1);
	WriteChar(43, 17, "���� �س���", 7, 1);
	if (Player_Tank[1].isValid)
	{
		WriteChar(41, 19, "��� 2", 7, 1);
		WriteChar(43, 21, "����ֵ", 7, 1);
		WriteNum(47, 21, m_vecTank[1].hp, 7, 1);
		WriteChar(43, 23, "��  ��", 7, 1);
		WriteNum(47, 23, m_vecTank[1].score, 7, 1);
		WriteChar(43, 25, "���� W S A D", 7, 1);
		WriteChar(43, 27, "���� �ո��", 7, 1);
	}

}

//�����˵�
void CGame::DeadMeum()
{
	WriteChar(18, 18, "DEAFEAT", 7, 0); Sound(6);
	_getch();
	_getch();
}

//ʤ���˵�
void CGame::VictorMeum()
{
	WriteChar(19, 18, "VICTORY", 7, 0);
	_getch();
	_getch();
}

//��Ҳ���
int CGame::PlayGame()
{
	while (_kbhit())
	{
		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 72:
				if (m_vecTank[0].isValid) {
					Move(&m_vecTank[0], UP);
				}	break;
			case 80:
				if (m_vecTank[0].isValid) {
					Move(&m_vecTank[0], DOWN);
				}break;
			case 75:
				if (m_vecTank[0].isValid) {
					Move(&m_vecTank[0], LEFT);
				}break;
			case 77:
				if (m_vecTank[0].isValid) {
					Move(&m_vecTank[0], RIGHT);
				}break;
			default:break;
			}
		default:
			break;
		case 'w':
		case 'W':
			if (m_vecTank[1].isValid) {
				Move(&m_vecTank[1], UP);
			}break;
		case 's':
		case 'S':
			if (m_vecTank[1].isValid) {
				Move(&m_vecTank[1], DOWN);
			}break;
		case 'a':
		case 'A':
			if (m_vecTank[1].isValid) {
				Move(&m_vecTank[1], LEFT);
			}	break;
		case 'd':
		case 'D':
			if (m_vecTank[1].isValid) {
				Move(&m_vecTank[1], RIGHT);
			}break;
		case 32://�ո� �����ӵ�
			if (m_vecTank[1].isValid) {
				Fire(&m_vecTank[1]);
				Sound(6);
			}
			break;
		case 13://�س� �����ӵ�
			if (m_vecTank[0].isValid) {
				Fire(&m_vecTank[0]);
				Sound(6);
			}
			break;
		case 'K'://��յ�ǰ�ؿ�npc ������һ��
		case 'k':
			for (int i = 2; i < 102; i++)
			{
				m_vecTank[i].isValid = 0;
				m_vecTank[i].OnlyClearTank(m_vecTank[i], pMap);
			}
			break;
		case 'L'://NPC���ܷ����ӵ�
		case 'l':
			
			flag_NpcFire *= -1;
			if (flag_NpcFire == -1)
			{
				WriteChar(46, 5, "��Ĭ:L", 4, 1);
			}
			else
			{
				WriteChar(46, 5, "��Ĭ:L", 7, 1);
			}
			break;
		case 'I'://�޵�ģʽ����
		case 'i':
			flag_NOdead *= -1;
			if (flag_NOdead == -1)
			{
				WriteChar(42, 7, "�޵�:I", 4, 1);
			}
			else
			{
				WriteChar(42, 7, "�޵�:I", 7, 1);
			}
			break;
		case 'O'://���NPC����
		case 'o':
			flag_TimePause *= -1;
			if (flag_TimePause == -1)
			{
				WriteChar(46, 7, "���:O", 4, 1);
			}
			else
			{
				WriteChar(46, 7, "���:O", 7, 1);
			}
			break;
		case 27://ESC ��ͣ
			return 2;
		}
		return 1;
	}
	return 1;
}


//̹�˵����ƶ�
int CGame::Move(CTank* pTank, Dir dir)
{
	int temp;
	CTank tank = *pTank;

	switch (dir)
	{
	case UP:
	{
		temp = pTank->isUP(*pTank,*pMap);
		if (temp==1)//ֻ��ת��
		{
			pTank->OnlyClearTank(*pTank, pMap);
			pTank->dir = UP;
			pTank->DrawTank(*pTank, pMap);
			return 0;
		}
		else if (temp == 2)//������
		{
			return 0;
		}
		//���ƶ�
		if (temp == 0)
		{
			pTank->OnlyClearTank(*pTank, pMap);//
			if (pTank->x > 2) { pTank->x--; }
			pTank->dir = UP;
			break;
		}
	}
	case DOWN:
	{
		temp = pTank->isDOWN(*pTank, *pMap);//����0��ʾ��������
		if (temp==1)//ֻ��ת
		{
			pTank->OnlyClearTank(*pTank, pMap);
			pTank->dir = DOWN;
			pTank->DrawTank(*pTank, pMap);
		
			return 0;
		}
		if (temp == 2)
		{
			return 0;
		}
		if (temp == 0)
		{
			pTank->OnlyClearTank(*pTank, pMap);//
			if (pTank->x < 37) { pTank->x++; }
			pTank->dir = DOWN;
			break;
		}

	}
	case LEFT:
	{
		temp = pTank->isLEFT(*pTank, *pMap);//�����߷���0
		if (temp==1)
		{
			pTank->OnlyClearTank(*pTank, pMap);
			pTank->dir = LEFT;
			pTank->DrawTank(*pTank, pMap);
			return 0;
		}
		if (temp == 2)
		{
			return 0;
		}
		if (temp == 0)
		{
			pTank->OnlyClearTank(*pTank, pMap);//
			if (pTank->y > 2) { pTank->y--; }
			pTank->dir = LEFT;
			break;
		}
	}
	case RIGHT:
	{
		temp = pTank->isRIGHT(*pTank, *pMap);
		if (temp==1)
		{
			pTank->OnlyClearTank(*pTank, pMap);
			pTank->dir = RIGHT;
			pTank->DrawTank(*pTank, pMap);
			return 0;
		}
		if (temp == 2)
		{
			return 0;
		}
		if (temp == 0)
		{
			pTank->OnlyClearTank(*pTank, pMap);//
			if (pTank->y < 37) { pTank->y++; }
			pTank->dir = RIGHT;
			break;
		}
	}
	default:
		break;
	}
	pTank->DrawTank(*pTank, pMap);

	return 0;
}

//boss̹�˵����ƶ�
int CGame::bossMove(CTank* pTank, Dir dir)
{
	CTank tank = *pTank;

	switch (dir)
	{
	case UP:
	{	
		pTank->ClearBOSSTank(*pTank, pMap);//
		if (pTank->x > 4) { pTank->x--; }
		pTank->dir = UP;
		break;
	}
	case DOWN:
	{
		
		pTank->ClearBOSSTank(*pTank, pMap);//
		if (pTank->x < 35) { pTank->x++; }
		pTank->dir = DOWN;
		break;
	}
	case LEFT:
	{
		pTank->ClearBOSSTank(*pTank, pMap);//
		if (pTank->y > 4) { pTank->y--; }
		pTank->dir = LEFT;
		break;
	}
	case RIGHT:
	{
		pTank->ClearBOSSTank(*pTank, pMap);//
		if (pTank->y < 35) { pTank->y++; }
		pTank->dir = RIGHT;
		break;
	}
	default:
		break;
	}
	pTank->DrawBOSSTank(*pTank, pMap);

	return 0;
}

//̹��ת��
int CGame::ChangeDir(CTank* pTank, Dir dir)
{
	switch (dir)
	{
	case UP:
	{

		pTank->OnlyClearTank(*pTank, pMap);
		pTank->dir = UP;
		pTank->DrawTank(*pTank, pMap);
		return 0;
		

	}
	case DOWN:
	{

		pTank->OnlyClearTank(*pTank, pMap);
		pTank->dir = DOWN;
		pTank->DrawTank(*pTank, pMap);
		return 0;

	}
	case LEFT:
	{

		pTank->OnlyClearTank(*pTank, pMap);
		pTank->dir = LEFT;
		pTank->DrawTank(*pTank, pMap);
		return 0;
		
	}
	case RIGHT:
	{

		pTank->OnlyClearTank(*pTank, pMap);
		pTank->dir = RIGHT;
		pTank->DrawTank(*pTank, pMap);
		return 0;
	
	}
	default:
		break;
	}
	return 0;
}

//����
void CGame::Fire(CTank* pTank)
{
	for (int i = 0; i < 300; i++) {
		if (m_vecBullet[i].isValid == 0) 
		{
			m_vecBullet[i].dir = pTank->dir;
			m_vecBullet[i].isValid = 1;
			m_vecBullet[i].tankID = pTank->tankID;
			switch (m_vecBullet[i].dir)
			{
			case UP:
				m_vecBullet[i].x = pTank->y;			//��̹�˵���yת��Ϊ�ӵ�����x 
				m_vecBullet[i].y = pTank->x - 2;		//��̹�˵���xת��Ϊ�ӵ�����y
				break;
			case DOWN:
				m_vecBullet[i].x = pTank->y;
				m_vecBullet[i].y = pTank->x + 2;
				break;
			case LEFT:
				m_vecBullet[i].x = pTank->y - 2;
				m_vecBullet[i].y = pTank->x;
				break;
			case RIGHT:
				m_vecBullet[i].x = pTank->y + 2;
				m_vecBullet[i].y = pTank->x;
				break;
			default:
				break;
			}
			WriteChar(m_vecBullet[i].x, m_vecBullet[i].y, "��", 7, 1); 
			break;
		}
	}
}

//��ͣ�˵�
int CGame::Pause()
{
	WriteChar(43, 29, "������Ϸ", 7, 0);
	WriteChar(43, 31, "������Ϸ", 7, 1);
	WriteChar(43, 33, "������Ϸ", 7, 1);
	WriteChar(43, 35, "���ز˵�", 7, 1);
	ch;//��¼����ֵ*/
	key = 1;//��¼ѡ����,��ʼΪ��һ��
	flag = 0; //��¼�Ƿ����enter��,��ʼΪ��
	while (ch = _getch())
	{
		switch (ch)
		{
		case 224:
			switch (_getch())
			{
			case 72://��
				if (key == 1)
				{
					WriteChar(43, 29, "������Ϸ", 7, 1);
					WriteChar(43, 35, "���ز˵�", 7, 0);
					
					key = 4;
				}
				else if (key == 2)
				{
					WriteChar(43, 31, "������Ϸ", 7, 1);
					WriteChar(43, 29, "������Ϸ", 7, 0);
					
					key = 1;
				}
				else if (key == 3)
				{
					WriteChar(43, 33, "������Ϸ", 7, 1);
					WriteChar(43, 31, "������Ϸ", 7, 0);
					
					key = 2;
				}
				else if (key == 4)
				{
					WriteChar(43, 35, "���ز˵�", 7, 1);
					WriteChar(43, 33, "������Ϸ", 7, 0);
					
					key = 3;
				}
				break;
			case 80://�·����
				if (key == 1)//����
				{
					WriteChar(43, 29, "������Ϸ", 7, 1);
					WriteChar(43, 31, "������Ϸ", 7, 0);
					
					key = 2;
				}
				else if (key == 2)//˫��
				{
					WriteChar(43, 31, "������Ϸ", 7, 1);
					WriteChar(43, 33, "������Ϸ", 7, 0);
					
					key = 3;
				}
				else if (key == 3)//����
				{
					WriteChar(43, 33, "������Ϸ", 7, 1);
					WriteChar(43, 35, "���ز˵�", 7, 0);
					
					key = 4;
				}
				else if (key == 4)//���ز˵�
				{
					WriteChar(43, 35, "���ز˵�", 7, 1);
					WriteChar(43, 29, "������Ϸ", 7, 0);
					
					key = 1;
				}
				break;
			}
			break;
		case 13:	//enter�س���		
			
			flag = 1;
			break;
		default:
			continue;
		}
		if (flag)//�س�ȷ��,�˳�ѭ��
		{
			break;
		}
	}
	switch (key)
	{
	case 1://������Ϸ
		for (int i = 29; i <= 35; i += 2)
		{
			for (int j = 43; j <= 46; j++)
			{
				WriteChar(j, i, "  ", 7, 1);
			}
		}
		break;
	case 2://������Ϸ
		return 2;
		break;
	case 3://������Ϸ
		return 3;
		break;
	case 4://���ز˵�
		return 4;
		break;
	default:
		break;
	}
	return 0;
}

//�ӵ��ƶ�ѭ��
int CGame::MoveAllBullet()
{
	static clock_t BulletClockA;//ʱ��A
	clock_t BulleClockB = clock();//ʱ��B
	if (BulleClockB - BulletClockA < 50)
		return 0;
	BulletClockA = BulleClockB;
	for (int i = 0; i < 300; i++) {
		if (m_vecBullet[i].isValid == 1) {
			MoveBullet(&m_vecBullet[i]);
		}
	}
	return 0;
}

//�ӵ������ƶ�
void CGame::MoveBullet(CBullet* pBullet)
{
	CBullet temp = *pBullet;
	int x = temp.x;	//��
	int y = temp.y;	//��
	switch (temp.dir)
	{
	case UP:
		temp.y--;	
		break;
	case DOWN:
		temp.y++;
		break;
	case LEFT:
		temp.x--;
		break;
	case RIGHT:
		temp.x++;
		break;
	}
	int chect_temp = CheckBullet(*pBullet);
	if (chect_temp == 1)		//�ӵ�û��ײ������
	{
		pBullet->ClearBullet(*pBullet);	//�����ӵ�
		*pBullet = temp;
		pBullet->DrawBullet(*pBullet,pMap);	//�����ӵ�
	}
	else if (chect_temp == 2)/*�ӵ���������*/
	{
		pBullet->ClearBullet(*pBullet);	//�����ӵ�
		pMap->returnMap(x, y, pMap->GameMap[g_level][x][y]);//���λ�ԭ
		*pBullet = temp;
		pBullet->DrawBullet(*pBullet,pMap);	//�����ӵ�
	}
	else if (chect_temp == 3)	/*�ӵ���������*/
	{
		pBullet->ClearBullet(*pBullet);		//�����ӵ�
		pMap->returnMap(x, y, pMap->GameMap[g_level][x][y]);//���λ�ԭ
		*pBullet = temp;
		pBullet->DrawBullet(*pBullet,pMap);		//�����ӵ�
	}
	else
		pBullet->isValid = 0;
}

//����ӵ�״̬ 1Ϊ����� 0Ϊ��������������
int CGame::CheckBullet(CBullet bullet)
{
	int y = bullet.y;
	int x = bullet.x;
	if (pMap->GameMap[g_level][x][y] == PLAYER_0 || pMap->GameMap[g_level][x][y] == PLAYER_1 || pMap->GameMap[g_level][x][y] >= NPC && pMap->GameMap[g_level][x][y] <= NPC + 99|| pMap->GameMap[g_level][x][y] == WALL8|| pMap->GameMap[g_level][x][y] == WALL7)
	{
		hitTank(x, y, bullet);
		return 0;
	}
	else if (pMap->GameMap[g_level][x][y] == WALL0 || pMap->GameMap[g_level][x][y] == WALL1 || pMap->GameMap[g_level][x][y] == BASE || pMap->GameMap[g_level][x][y] == WALL2 || pMap->GameMap[g_level][x][y] == WALL3) {
		return hitWall(x, y, bullet);//0�ӵ�ʧЧ��2�ӵ�����������3�ӵ���������	 
	}
	return hitBullet(x, y, bullet);

	return 1;//�ӵ�û��ײ������
}

//�ӵ�ײǽ
int CGame:: hitWall(int x, int y, CBullet bullet)
{
	switch (pMap->GameMap[g_level][x][y])
	{
	case WALL0://��ǽ
		pMap->returnMap(x, y, pMap->GameMap[g_level][x][y]);//���λ�ԭ
		return 0;//�ӵ�ʧЧ

	case WALL1://שǽ
		pMap->GameMap[g_level][x][y] = 0;//�ƻ���Ϊ��
		WriteChar(x, y, "  ", 7, 1);
		return 0;//�ӵ�ʧЧ

	case WALL2://����
		pMap->returnMap(x, y, pMap->GameMap[g_level][x][y]);//���λ�ԭ..
		return 2;//�ӵ���Ч

	case WALL3://����
		pMap->returnMap(x, y, pMap->GameMap[g_level][x][y]);//���λ�ԭ..
		return 3;//�ӵ���Ч

	case BASE:
		pMap->GameMap[g_level][x][y] = 0;	//�ƻ���Ϊ��											
		WriteChar(x, y, "��", 7, 1);
		isOver = 1;//��Ϸ��������																
		break;
	}
	return 0;
}

//�ӵ�ײ̹��
int CGame::hitTank(int x, int y, CBullet bullet)//�����е�̹��
{
	//���������Ӧ��̹�˱�� x�� y�� m_vecTank[temp]
	int temp = SearchTank(x, y);
	bullet.isValid = 0;
	//�ӵ���̹��
	if (temp == 0)//0���������ֵΪ1 
	{
		
		if (bullet.tankID != PLAYER_1&&bullet.tankID != PLAYER_0)//���ӵ�Ϊ�з����
		{
			if (m_vecTank[0].hp >= 2)//���0����ֵ����2
			{
				int temp_color = m_vecTank[0].color;
				m_vecTank[0].color = 4;//��ɫ���һ��
				m_vecTank[0].DrawTank(m_vecTank[0], pMap);
				Sleep(50);
 				m_vecTank[0].color = temp_color;//��ɫ���
 				m_vecTank[0].DrawTank(m_vecTank[0], pMap);
				if (flag_NOdead == 1)//�Ƿ����޵�
				{
					m_vecTank[0].hp--;
				}
				WriteNum(47, 11, m_vecTank[0].hp, 7, 1);
				Sound(3);
			}
			else
			{
				m_vecTank[0].isValid = 0;
				m_vecTank[0].OnlyClearTank(m_vecTank[0], pMap);
				WriteNum(47, 9, 0, 7, 1);
			}
			return 0;
		}
		else//�����ӵ�����
			m_vecTank[0].DrawTank(m_vecTank[0], pMap);
			return 0;
	}
	else if (temp==1)//1���������ֵΪ2 
	{
		if (bullet.tankID != PLAYER_0&&bullet.tankID != PLAYER_1)//���ӵ�Ϊ�з����
		{
			if (m_vecTank[1].hp >= 2)//���1����ֵ
			{
				int temp_color = m_vecTank[1].color;
				m_vecTank[1].color = 4;//��ɫ���һ��
				m_vecTank[1].DrawTank(m_vecTank[1], pMap);
				Sleep(50);
	
				m_vecTank[1].color = temp_color;//��ɫ���
				m_vecTank[1].DrawTank(m_vecTank[1], pMap);
				if (flag_NOdead == 1)//�Ƿ����޵� Ĭ��Ϊ1 ������
				{
					m_vecTank[1].hp--;
				}
				WriteNum(47, 21, m_vecTank[1].hp, 7, 1);
				Sound(3);


			}
			else
			{
				m_vecTank[1].isValid = 0;
				m_vecTank[1].OnlyClearTank(m_vecTank[1], pMap);
				WriteNum(47, 19, 0, 7, 1);
			}
			return 0;
		}
		else//�����ӵ�����
			m_vecTank[1].DrawTank(m_vecTank[1], pMap);
			return 0;
	}

	else if (temp >= 2 && temp < 102)//NPC̹�� m_vecTank[temp]
	{
		int i = temp;
		if (bullet.tankID == PLAYER_0 || bullet.tankID == PLAYER_1)//���ӵ�Ϊ�з����
		{
			if (m_vecTank[i].hp >= 2)//����ֵ����2
			{
				int temp_color = m_vecTank[i].color;
				m_vecTank[i].color = 4;//��ɫ���һ��
				m_vecTank[i].DrawTank(m_vecTank[i], pMap);
				Sleep(50);
				m_vecTank[i].color = temp_color;//��ɫ���
				m_vecTank[i].DrawTank(m_vecTank[i], pMap);
				m_vecTank[i].hp--;
			}
			else if(m_vecTank[i].hp <= 1)
			{
				if (m_vecTank[i].borntime > 0)
				{
					RefreshNPC(m_vecTank[i]);
				}
				m_vecTank[i].isValid = 0;
				m_vecTank[i].tankID = 0;
				killNum++;
				m_vecTank[i].OnlyClearTank(m_vecTank[i], pMap);
			

			}
			if (bullet.tankID == PLAYER_0)
			{
				m_vecTank[0].score+=m_vecTank[i].level;
				WriteNum(47, 13, m_vecTank[0].score, 7, 1);
			}
			else if (bullet.tankID == PLAYER_1)
			{
				m_vecTank[1].score += m_vecTank[i].level;
				WriteNum(47, 23, m_vecTank[1].score, 7, 1);
			}
			return 0;
		}
		else//�����ӵ�����
		{
			m_vecTank[i].DrawTank(m_vecTank[i], pMap);
			return 0;
		}
	}
	return 0;
}
	
//�ӵ���ײ
int CGame::hitBullet(int x, int y, CBullet bullet)
{
	int i = 0, flag = 0;
	for (; i < 300; i++)
	{
		if (m_vecBullet[i].isValid)
		{
			if (m_vecBullet[i].x == x&&m_vecBullet[i].y == y)
			{
				if (bullet.tankID != m_vecBullet[i].tankID)
				{
					m_vecBullet[i].isValid = 0;
					bullet.isValid = 0;
					WriteChar(x, y, " ", 1, 1);
					return 0;
				}
			}

		}

	}
	return 1;
}

//���������Ӧ��̹�˱�� x�� y��
int CGame::SearchTank(int x, int y)
{
	int i = 0, flag = 0;
	for (; i < 102; i++)
	{
		if (m_vecTank[i].isValid)
		{
			for (int row = -1; row <= 1; row++)
			{
				for (int col = -1; col <= 1; col++)
				{
					int PosX = m_vecTank[i].x + col; //��
					int PoxY = m_vecTank[i].y + row; //��
					if (PosX == y && PoxY == x)
					{
						flag = 1;
						break;
					}
				}
			}
		}
		if (flag)break;
	}
	return i;
}

//Npc level 1̹���ƶ�����ѭ�� 
int CGame::MoveNpcTank_1()
{
	static clock_t NpcClockA;
	clock_t NpcClockB = clock();
	if (NpcClockB - NpcClockA < 250)
	{
		return 0;
	}
	NpcClockA = NpcClockB;
	for (int i = 2; i < 102; i++) {
		if (m_vecTank[i].isValid == 1&&m_vecTank[i].level==1) {
			int randomNum = rand() % 15;
			switch (randomNum) {
			case 0:
			case 1:Move(&m_vecTank[i], UP); break;
			case 2:
			case 3:Move(&m_vecTank[i], DOWN); break;
			case 4:
			case 5:Move(&m_vecTank[i], LEFT); break;
			case 6:
			case 7:Move(&m_vecTank[i], RIGHT); break;
			case 8:
			case 9:if (flag_NpcFire==1) { Fire(&m_vecTank[i]); }; break;
			case 10://Ѱ·
			case 11:
			case 12:
			case 13:Move(&m_vecTank[i], OtherAI(m_vecTank[i])); break;


			default:
				Move(&m_vecTank[i], m_vecTank[i].dir);
			}

			
		}
	}
	return 1;
}

//Npc level 2̹���ƶ�����ѭ�� 
int CGame::MoveNpcTank_2()
{
	static clock_t NpcClockA;
	clock_t NpcClockB = clock();
	if (NpcClockB - NpcClockA < 200)
	{
		return 0;
	}
	NpcClockA = NpcClockB;


	for (int i = 2; i < 102; i++) {
		if (m_vecTank[i].isValid == 1 && m_vecTank[i].level == 2) {
			int randomNum = rand() % 15;

			if (abs(m_vecTank[i].x - m_vecTank[0].x < 7) && abs(m_vecTank[i].y - m_vecTank[0].y < 7))//npc������ұȽϽ���ʱ��ʹ��A��Ѱ·
			{
				switch (randomNum) {
				case 0:Move(&m_vecTank[i], UP); break;
				case 1:Move(&m_vecTank[i], DOWN); break;
				case 2:Move(&m_vecTank[i], LEFT); break;
				case 3:Move(&m_vecTank[i], RIGHT); break;
				case 4:
				case 5:
				case 6:
				case 7:if (flag_NpcFire == 1) { Fire(&m_vecTank[i]); }; break;
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:Move(&m_vecTank[i], OtherAI(m_vecTank[i])); break;//Ѱ·

				default:
					Move(&m_vecTank[i], m_vecTank[i].dir);
				}
				continue;
			}
			else
			{
				Dir dir_temp = m_vecTank[i].dir;
				switch (m_vecTank[i].GetDirfromAstar(pMap, m_vecTank[i], m_vecTank))
				{
				case 0:dir_temp = UP; break;
				case 1:dir_temp = DOWN; break;
				case 2:dir_temp = LEFT; break;
				case 3:dir_temp = RIGHT; break;
				}
				Move(&m_vecTank[i], dir_temp);
			}
		}
	}
	return 1;
}

//Npc level 3̹���ƶ�����ѭ�� 
int CGame::MoveNpcTank_3()
{
	static clock_t NpcClockA;
	clock_t NpcClockB = clock();
	if (NpcClockB - NpcClockA < 150)
	{
		return 0;
	}
	NpcClockA = NpcClockB;


	for (int i = 2; i < 102; i++) {
		if (m_vecTank[i].isValid == 1 && m_vecTank[i].level == 3) {
 			int randomNum = rand() % 3;
 			switch (randomNum) {
 			case 0:if (flag_NpcFire == 1) { Fire(&m_vecTank[i]); }; break;
 			default:
				break;		
 			}

			Dir dir_temp = m_vecTank[i].dir;
 			bool flag1 = m_vecTank[i].y == m_vecTank[0].y && m_vecTank[i].x == m_vecTank[0].x - 2;	//��;
 			bool flag11 = m_vecTank[i].y == m_vecTank[0].y + 1 && m_vecTank[i].x == m_vecTank[0].x - 2;	//��;
 			bool flag2 = m_vecTank[i].y == m_vecTank[0].y && m_vecTank[i].x == m_vecTank[0].x + 2;	//��;
 			bool flag22 = m_vecTank[i].y == m_vecTank[0].y + 1 && m_vecTank[i].x == m_vecTank[0].x + 2;	//��;*/
 			bool flag3 = m_vecTank[i].x == m_vecTank[0].x && m_vecTank[i].y == m_vecTank[0].y - 3;	//��;
 			bool flag33 = m_vecTank[i].x == m_vecTank[0].x - 1 && m_vecTank[i].y == m_vecTank[0].y - 2;	//��;*/
 			bool flag4 = m_vecTank[i].x == m_vecTank[0].x && m_vecTank[i].y == m_vecTank[0].y + 3;	//��;
 			bool flag44 = m_vecTank[i].x == m_vecTank[0].x - 1 && m_vecTank[i].y == m_vecTank[0].y + 2;	//��;*/
 
 			bool flag5 = m_vecTank[i].x == m_vecTank[0].x - 2 && m_vecTank[i].y == m_vecTank[0].y + 1;
 			bool flag55 = m_vecTank[i].x == m_vecTank[0].x - 2 && m_vecTank[i].y == m_vecTank[0].y - 1;
 
 			bool flag6 = m_vecTank[i].x == m_vecTank[0].x + 1 && m_vecTank[i].y == m_vecTank[0].y + 2;
 			bool flag66 = m_vecTank[i].x == m_vecTank[0].x + 1 && m_vecTank[i].y == m_vecTank[0].y - 2;
 
 			if ((flag1 || flag2 || flag3 || flag4 || flag11 || flag22 || flag33 || flag44 || flag5 || flag55 || flag6 || flag66))//���npc�������������ƶ� ֻת��
 			{
 				if (flag1)dir_temp = DOWN;
 				else if (flag2)dir_temp = UP;
 				else if (flag3)dir_temp = RIGHT;
 				else if (flag4)dir_temp = LEFT;
 				ChangeDir(&m_vecTank[i], dir_temp);
 				continue;
 			}
			




			switch (m_vecTank[i].GetDirfromAstar(pMap, m_vecTank[i], m_vecTank))
			{
			case 0:dir_temp = UP; break;
			case 1:dir_temp = DOWN; break;
			case 2:dir_temp = LEFT; break;
			case 3:dir_temp = RIGHT; break;

			}
			Move(&m_vecTank[i], dir_temp);
			
		}
	}
	return 1;
}

//Npc level 10̹���ƶ�����ѭ�� 
int CGame::MoveNpcTank_10()
{
	static clock_t NpcClockA;
	clock_t NpcClockB = clock();
	if (NpcClockB - NpcClockA < 150)
	{
		return 0;
	}
	NpcClockA = NpcClockB;


	for (int i = 2; i < 102; i++) {
		if (m_vecTank[i].isValid == 1 && m_vecTank[i].level == 10) {
			int randomNum = rand() % 3;
			switch (randomNum) {
			case 0:if (flag_NpcFire == 1) { Fire(&m_vecTank[i]); }; break;
			default:
				break;
			}

			Dir dir_temp = m_vecTank[i].dir;
			bool flag1 = m_vecTank[i].y == m_vecTank[0].y && m_vecTank[i].x == m_vecTank[0].x - 2;	//��;
			bool flag11 = m_vecTank[i].y == m_vecTank[0].y + 1 && m_vecTank[i].x == m_vecTank[0].x - 2;	//��;
			bool flag2 = m_vecTank[i].y == m_vecTank[0].y && m_vecTank[i].x == m_vecTank[0].x + 2;	//��;
			bool flag22 = m_vecTank[i].y == m_vecTank[0].y + 1 && m_vecTank[i].x == m_vecTank[0].x + 2;	//��;*/
			bool flag3 = m_vecTank[i].x == m_vecTank[0].x && m_vecTank[i].y == m_vecTank[0].y - 3;	//��;
			bool flag33 = m_vecTank[i].x == m_vecTank[0].x - 1 && m_vecTank[i].y == m_vecTank[0].y - 2;	//��;*/
			bool flag4 = m_vecTank[i].x == m_vecTank[0].x && m_vecTank[i].y == m_vecTank[0].y + 3;	//��;
			bool flag44 = m_vecTank[i].x == m_vecTank[0].x - 1 && m_vecTank[i].y == m_vecTank[0].y + 2;	//��;*/

			bool flag5 = m_vecTank[i].x == m_vecTank[0].x - 2 && m_vecTank[i].y == m_vecTank[0].y + 1;
			bool flag55 = m_vecTank[i].x == m_vecTank[0].x - 2 && m_vecTank[i].y == m_vecTank[0].y - 1;

			bool flag6 = m_vecTank[i].x == m_vecTank[0].x + 1 && m_vecTank[i].y == m_vecTank[0].y + 2;
			bool flag66 = m_vecTank[i].x == m_vecTank[0].x + 1 && m_vecTank[i].y == m_vecTank[0].y - 2;

			if ((flag1 || flag2 || flag3 || flag4 || flag11 || flag22 || flag33 || flag44 || flag5 || flag55 || flag6 || flag66))//���npc�������������ƶ� ֻת��
			{
				if (flag1)dir_temp = DOWN;
				else if (flag2)dir_temp = UP;
				else if (flag3)dir_temp = RIGHT;
				else if (flag4)dir_temp = LEFT;
				ChangeDir(&m_vecTank[i], dir_temp);
				continue;
			}





			switch (m_vecTank[i].GetDirfromAstar(pMap, m_vecTank[i], m_vecTank))
			{
			case 0:dir_temp = UP; break;
			case 1:dir_temp = DOWN; break;
			case 2:dir_temp = LEFT; break;
			case 3:dir_temp = RIGHT; break;

			}
			bossMove(&m_vecTank[i], dir_temp);

		}
	}
	return 1;
}


//��ȡNPC̹��ʣ������
int CGame::GetNpcNum()
{
	int num = 0;
	for (int i = 2; i < 102; i++)
	{
		if (m_vecTank[i].isValid)
		{
			num++;
		}
	}
	return num;
}

int CGame::GetNpcID(int x, int y)
{
	for (int i = 2; i < 102; i++)
	{
		if (m_vecTank[i].isValid)
		{
			if (pMap->GameMap[g_level][x][y] == m_vecTank[i].tankID)
			{
				return i;
			}
		}
	}
	return -1;
}
	

//���3x3��Χ���ǹ�Ϊ�� //���Լ�����
int CGame::isEmpty(int posX, int PosY)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) { continue; }
			int x = posX + i;
			int y = PosY + j;
			if (pMap->GameMap[g_level][x][y] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

//�����Ƚ�һ��Ĵ��ӵ�Ѱ·AI
Dir CGame::OtherAI(CTank tank)
{
	Dir temp_0_y = NONE, temp_1_y = NONE;
	int temp_0_sub_y = 100, temp_1_sub_y = 100;
	int min_y = 1000;
	int max_y = 0;

	//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
	if (tank.y < m_vecTank[0].y)
	{
		temp_0_y = DOWN;
		temp_0_sub_y = abs(tank.y - m_vecTank[0].y);
	}
	else if (tank.y > m_vecTank[0].y)
	{
		temp_0_y = UP;
		temp_0_sub_y = abs(tank.y - m_vecTank[0].y);
	}


	if (tank.y < m_vecTank[1].y)
	{
		temp_1_y = RIGHT;
		temp_1_sub_y = abs(tank.y - m_vecTank[1].y);
	}

	else if (tank.y > m_vecTank[1].y)
	{
		temp_1_y = LEFT;
		temp_1_sub_y = abs(tank.y - m_vecTank[1].y);
	}

	min_y = temp_0_sub_y < temp_1_sub_y ? temp_0_sub_y : temp_1_sub_y;
	max_y = temp_0_sub_y > temp_1_sub_y ? temp_0_sub_y : temp_1_sub_y;


	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	Dir temp_0_x = NONE, temp_1_x = NONE;
	int temp_0_sub_x = 100, temp_1_sub_x = 100;
	int min_x = 1000;
	int max_x = 0;

	if (tank.x < m_vecTank[0].x)
	{
		temp_0_x = DOWN;
		temp_0_sub_x = abs(tank.x - m_vecTank[0].x);
	}
	else if (tank.x > m_vecTank[0].x)
	{
		temp_0_x = UP;
		temp_0_sub_x = abs(tank.x - m_vecTank[0].x);
	}


	if (tank.x < m_vecTank[1].x)
	{
		temp_1_x = RIGHT;
		temp_1_sub_x = abs(tank.x - m_vecTank[1].x);
	}

	else if (tank.x > m_vecTank[1].x)
	{
		temp_1_x = LEFT;
		temp_1_sub_x = abs(tank.x - m_vecTank[1].x);
	}

	min_x = temp_0_sub_x < temp_1_sub_x ? temp_0_sub_x : temp_1_sub_x;
	max_x = temp_0_sub_x > temp_1_sub_x ? temp_0_sub_x : temp_1_sub_x;

// 	int Min = min_x < min_y ? min_x : min_y;
// 	if (Min == temp_0_sub_x)return temp_0_x;
// 	else if (Min == temp_1_sub_x)return temp_1_x;
// 	else if (Min == temp_0_sub_y)return temp_0_y;
// 	else if (Min == temp_1_sub_y)return temp_1_y;

	int Max = min_x > min_y ? min_x : min_y;
	if (Max == temp_0_sub_x)return temp_0_x;
	else if (Max == temp_1_sub_x)return temp_1_x;
	else if (Max == temp_0_sub_y)return temp_0_y;
	else if (Max == temp_1_sub_y)return temp_1_y;

	return NONE;
}

//npc����
void CGame::RefreshNPC(CTank tank)
{
	int index = 2;
	int flag = 1;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int x = m_vecTank[index].x_born + i;
			int y = m_vecTank[index].y_born + j;
			if (pMap->GameMap[g_level][x][y] != 0)
			{
				flag = 0;
				break;
			}
		}
	}

	for ( ; index < 102; index++)
	{
		if (m_vecTank[index].isValid == 0 && flag == 1)
		{
			m_vecTank[index].level = tank.level;
			m_vecTank[index].hp = tank.level;
			m_vecTank[index].borntime = 0;
			m_vecTank[index].x = tank.x_born;
			m_vecTank[index].y = tank.y_born;
			m_vecTank[index].x_born = tank.x_born;
			m_vecTank[index].y_born = tank.y_born;
			m_vecTank[index].dir = DOWN;
			m_vecTank[index].isValid = 1;
			m_vecTank[index].color = BULE;
			m_vecTank[index].tankID = tank.tankID;
	/*		pMap->GameMap[g_level][tank.x_born][tank.y_born] = tank.tankID;*/
			m_vecTank[index].DrawTank(m_vecTank[index], pMap);
			break;
		}
	}
}



/*


// 			Dir dir_temp = m_vecTank[i].dir;
// 			bool flag1 =  0;
// 			bool flag2 =  0;
// 			bool flag3 =  0;
// 			bool flag4 =  0;
// 			if (m_vecTank[0].dir == UP)//�������̹��״̬�����ط���
// 			{
// 				if (flag1 = m_vecTank[i].x == m_vecTank[0].x - 2 && m_vecTank[i].y == m_vecTank[0].y) {
//
// 					ChangeDir(&m_vecTank[i], UP);//������;
// 					continue;
// 				}
// 				else if (flag2 = m_vecTank[i].x == m_vecTank[0].x + 3 && m_vecTank[i].y == m_vecTank[0].y) {
// 					ChangeDir(&m_vecTank[i], DOWN);//��;
// 					continue;
// 				}
// 				else if (flag3 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y + 3) {
// 					ChangeDir(&m_vecTank[i], LEFT);//��;
// 					continue;
// 				}
// 				else if (flag4 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y - 3) {
// 					ChangeDir(&m_vecTank[i], RIGHT);//��;*/
// 					continue;
// 				}	
// 			}
// 			else if (m_vecTank[0].dir == DOWN)
// 			{
// 				if (flag1 = m_vecTank[i].x == m_vecTank[0].x + 3 && m_vecTank[i].y == m_vecTank[0].y) {
// 
// 					ChangeDir(&m_vecTank[i], UP);//������;
// 					continue;
// 				}
// 				else if (flag2 = m_vecTank[i].x == m_vecTank[0].x - 2 && m_vecTank[i].y == m_vecTank[0].y) {
// 					ChangeDir(&m_vecTank[i], DOWN);//��;
// 					continue;
// 				}
// 				else if (flag3 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y + 3) {
// 					ChangeDir(&m_vecTank[i], LEFT);//��;
// 					continue;
// 				}
// 				else if (flag4 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y - 3) {
// 					ChangeDir(&m_vecTank[i], RIGHT);//��;*/
// 					continue;
// 				}
// 			}
// 
// 			else if (m_vecTank[0].dir == LEFT)
// 			{
// 				if (flag1 = m_vecTank[i].x == m_vecTank[0].x + 3 && m_vecTank[i].y == m_vecTank[0].y) {
// 
// 					ChangeDir(&m_vecTank[i], UP);//������;
// 					continue;
// 				}
// 				else if (flag2 = m_vecTank[i].x == m_vecTank[0].x - 3 && m_vecTank[i].y == m_vecTank[0].y) {
// 					ChangeDir(&m_vecTank[i], DOWN);//��;
// 					continue;
// 				}
// 				else if (flag3 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y + 2) {
// 					ChangeDir(&m_vecTank[i], LEFT);//��;
// 					continue;
// 				}
// 				else if (flag4 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y - 3) {
// 					ChangeDir(&m_vecTank[i], RIGHT);//��;*/
// 					continue;
// 				}
// 			}
// 			else if (m_vecTank[0].dir == RIGHT)
// 			{
// 				if (flag1 = m_vecTank[i].x == m_vecTank[0].x + 3 && m_vecTank[i].y == m_vecTank[0].y) {
// 
// 					ChangeDir(&m_vecTank[i], UP);//������;
// 					continue;
// 				}
// 				else if (flag2 = m_vecTank[i].x == m_vecTank[0].x - 3 && m_vecTank[i].y == m_vecTank[0].y) {
// 					ChangeDir(&m_vecTank[i], DOWN);//��;
// 					continue;
// 				}
// 				else if (flag3 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y + 3) {
// 					ChangeDir(&m_vecTank[i], LEFT);//��;
// 					continue;
// 				}
// 				else if (flag4 = m_vecTank[i].x == m_vecTank[0].x  && m_vecTank[i].y == m_vecTank[0].y - 2) {
// 					ChangeDir(&m_vecTank[i], RIGHT);//��;*/
// 					continue;
// 				}
// 			}
// 			
