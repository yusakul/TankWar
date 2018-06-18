#pragma once

#define WALL0 10	//铁墙■
#define WALL1 11	//砖墙▓
#define WALL2 12	//河流≈
#define WALL3 13	//树林※
#define BASE  14	//基地★☢
#define WALL5 15	//npc子弹通过树林¤
#define WALL6 16	//玩家子弹通过树林◎
#define WALL7 17	//npc坦克通过树林
#define WALL8 18	//玩家坦克通过树林
#define NPCborn0 20	//NPC出生点
#define NPCborn1 21	//NPC出生点
#define NPCborn2 22	//NPC出生点
#define NPCborn3 23	//NPC出生点
#define NPCborn4 24	//NPC出生点
#define NPCborn5 25	//NPC出生点
#define NPCborn6 26	//NPC出生点

#define PLAYER_0 1    //0号玩家坦克
#define PLAYER_1 2    //1号玩家坦克
#define NPC 100 //NPC坦克
#define Wall0_color 7	//7 = 白色		 铁墙■
#define Wall1_color 6	//6 = 黄色		 砖墙▓
#define Wall2_color 9	//9= 蓝色		河流≈
#define Wall3_color 2	//2 = 绿色		 树林※  子弹通过树林※	 
#define BASE_color  4	//4 = 红色		 基地★☢
#define BULE 3;
enum Dir { UP, DOWN, LEFT, RIGHT, NONE };

//关卡等级level
extern int g_level;
extern int g_Map[7][40][40];		//使用默认地图
extern int g_UserMap[7][40][40];		//使用用户自定义地图


//欢迎界面
extern int g_StartAnimer[40][40];

//坦克数组。。。
extern int tankPoint[3][3];


/*
用 system("color 0A");
其中color后面的0是背景色代号，A是前景色代号。各颜色代码如下：
0 = 黑色
1 = 蓝色
2 = 绿色
3 = 湖蓝色
4 = 红色
5 = 紫色
6 = 黄色
7 = 白色
8 = 灰色
9 = 淡蓝色
A = 淡绿色
B = 淡浅绿色
C = 淡红色
D = 淡紫色
E = 淡黄色
F = 亮白色*/

