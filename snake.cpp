#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
/*
贪吃蛇
知识点；结构体，循环，函数，easyx，数组
*/
//做界面，创建一个窗口，图形窗口
#define SNAKE_NUM 500  //蛇的最大节数 
enum DIR //表示蛇得方向
{
	UP,
    DOWN,
    LEFT,
    RIGHT,
};
//蛇的结构
struct Snake
{
	int size;//蛇的节数
	int dir;//蛇的方向
	int speed;//移动速度
	POINT coor[SNAKE_NUM];//坐标
}snake;
//食物结构
struct Food
{
	int x;
	int y;
	int r; //食物大小
	bool flag; //食物是否被吃
	DWORD color; //食物颜色
}food;
//数据的初始化
void GameInit()
{
	//播放bgm
	mciSendString("open ./MayPiano-Summer-_钢琴版_.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	//init 初始化 graph 图形窗口
	initgraph(640, 480);
	//设置随机数种子  GetTickCount();获取系统开机，到现在所经历的1毫秒数
	srand(GetTickCount());
	//初始化蛇 一开始有三节
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for(int i=0;i< snake.size;i++)
	{ 
		snake.coor[i].x = 40-10*i;
	    snake.coor[i].y = 10;
	}	
	//初始化食物  rand()随机产生整数，若没有设置随机数种子，每次产生的都是固定整数
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(255, 228, 225));
	cleardevice();
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
       solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
//移动蛇
void snakemove() 
{
	//身体跟着头移动
	for (int i = snake.size-1; i >0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//移动是坐标发生改变
	switch (snake.dir)
		{
		case UP:
			snake.coor[0].y-=snake.speed;
			if (snake.coor[0].y + 10 <= 0) //超出上面的边界
			{
				snake.coor[0].y = 480;
			}
			break;
		case DOWN:
			snake.coor[0].y+=snake.speed;
			if (snake.coor[0].y - 10 >= 480) //超出上面的边界
			{
				snake.coor[0].y = 0;
			}
			break;
		case LEFT:
			snake.coor[0].x-=snake.speed;
			if (snake.coor[0].x + 10 <= 0) //超出上面的边界
			{
				snake.coor[0].x = 640;
			}
			break;
		case RIGHT:
			snake.coor[0].x+=snake.speed;
			if (snake.coor[0].x - 10 >= 640) //超出上面的边界
			{
				snake.coor[0].x = 0;
			}
			break;
		}
}
//通过按键改变蛇的移动方向 
void keyControl()
{
	//判断有没有按键,如果有按键，就返回真
	if (_kbhit())
	{
       //72 80 75 77 上下左右键值
	switch (_getch())
	{
	case'w':
	case'W':
	case 72:
		//改变方向 
		if (snake.dir != DOWN)
		{
           snake.dir = UP;
		}		
		break;
	case's':
	case'S':
	case 80:
		//改变方向
		if (snake.dir != UP)
		{
	       snake.dir = DOWN;
		}	
		break; 
	case'a':
	case'A':
	case 75:
		//改变方向
		if (snake.dir != RIGHT)
		{
			snake.dir = LEFT;
		}		
		break;
	case'd':
	case'D':
	case 77:
		//改变方向
		if (snake.dir != LEFT)
		{	
			snake.dir = RIGHT;
		}	
		break;
	case' ':  //游戏暂停  空格
		while (1)
		{
			if (_getch() == ' ')
				return;
		}
		break;
	}
  }
	
}
//通过按键改变蛇方向
void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y+food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}

int main()
{
	GameInit();	

	while (1)
	{
		snakemove();
		GameDraw();
		keyControl();
		EatFood();
		Sleep(250);
	}
	return 0;
}