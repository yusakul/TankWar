#pragma once
#include "Data.h"
#include "Tools.h"

class CMap
{
public:

	//��Ϸ��ͼ����ԭʼ��ͼ
	void InitGameMapfromG_Map(CMap* pMap);

	//��ʼ���Զ����ͼ
	void InitUserMapformG_Map(CMap* pMap);

	//��Ϸ��ͼ�����Զ����ͼ
	void InitGameMapfromUser(CMap* pMap);

	//�����Զ����ͼ
	void DrawUserMap(int level);

	//���Ƶ�ͼ
	void DrawMap(CMap Map);

	//���λ�ԭ
	void returnMap(int y, int x, int WAll);

	//��Ϸ��ʹ�õĵ�ͼ
	int GameMap[7][40][40];

	//����̨������Ƶ�ͼ����;
	void OutPutPos(int nPosX, int nPoxY);

	// ��괦���¼�
	int MouseEventProc(MOUSE_EVENT_RECORD StcMouse);

	//����϶��¼�
	bool MouseMove(MOUSE_EVENT_RECORD &StcMouse);
	
	// ������¼�
	int MouseClick(MOUSE_EVENT_RECORD &StcMouse);
 
 	// ���̴����¼�
 	int KeyEventProc(KEY_EVENT_RECORD &StcKeyEvent);

	// ��ˢ������չ��;
	void BrushDraw(MOUSE_EVENT_RECORD &StcMouse, char *Pstr, WORD color, int isback/*����ɫ 0�� 1��*/);


	//��Ϣ������
	int MessageLoop();

	
private:
	int m_nMapVlue;	//�Զ���д���ͼֵ;
	int flag_switch;	//����¼�ѡ���

	//����

	int key;//��¼ѡ����,��ʼΪ��һ��
	int flag_kb;//�����¼��س��ж�
	int ch;//���밴��
	int flag_enter;//ѡ��˵�ѭ���ڻس��ж�
	int m_nBrush;	//��ˢ�Ĵ�С
	
};