#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <graphics.h>	// 引用图形库头文件
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define SNAKE_NUM 500//蛇的最大节数
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coor[SNAKE_NUM];//坐标

}snake;
struct Food
{
	int x;
	int y;
	int r;//食物大小
	bool flag;//食物是否被吃
	DWORD color;//食物颜色
}food;

//void Menu()
//{//菜单
//	int num;
//	printf("欢迎来到贪吃蛇大作战游戏\n");
//	printf("游戏规则如下：\n");
//	printf("按键盘的上下左右控制蛇的方向寻找吃的东西，");
//	printf("每吃一口蛇变长且游戏积分增加");
//	printf("注意蛇可以穿墙而过,并且当蛇头碰到蛇的身体即视为自杀。\n");
//	printf("确认进入游戏请输入1,退出游戏输入0\n");
//	while (1)
//	{
//		printf("输入：");
//		scanf_s("%d", &num);
//		if (num== 1)
//		{
//			cleardevice();
//			break;
//		}
//		else if (num== 0)
//		{
//			printf("已退出游戏");
//			break;
//		}
//		if (num != 1 && num != 0)
//		{
//			printf("输入错误，请重新输入");
//		}
//
//	}
//}

void GameInit()
{
	initgraph(640, 480);//创建窗口
	mciSendString("open./111.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);//播放音乐
	
	//初始化蛇
	snake.size = 3;
	snake.speed = 10;
	snake.dir=RIGHT;
	srand(unsigned int(time(0)));//srand(GetTickCount());获取开机到现在的毫秒数
	for (int i = 0;i < snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//初始化食物
	food.r = rand() % 10+5;
	food.x = rand() % 610+15;
	food.y = rand() % 450+15;
	food.flag = true;
	//菜单
	settextcolor(YELLOW);
	outtextxy(160, 160, "欢迎来到贪吃蛇大作战游戏!");
	outtextxy(190, 180, "游戏规则如下：");
	outtextxy(60, 200, "按键盘的上下左右控制蛇的方向寻找吃的东西,每吃一口蛇变长");
	outtextxy(80, 220, "注意:蛇可以穿墙而过,当蛇头碰到蛇的身体即视为自杀。");
	Sleep(3000);
	cleardevice();
	outtextxy(180, 200, "进入游戏请按Y，退出游戏请按N");
	int t=0;
	while(t==0)
	{
		if (_kbhit())
		{
			char key = _getch();
			switch (key)
			{
			case'y':
			case'Y':
			{
				cleardevice();
				outtextxy(270, 200, "开始游戏");
				Sleep(1000);
				t = 1;
				break;
			}
			case'n':
			case'N':
			{
				cleardevice();
				outtextxy(270, 200, "退出游戏");
				t = 0;
				break;
			}

			}
		}
	}
}

void GameDraw()
{
	BeginBatchDraw();//双缓冲
    setbkcolor(RGB(205,155,155));//设置背景色
	cleardevice();//清屏

	
	for (int i = 0;i < snake.size;i++)
	{
	   setfillcolor(GREEN);//填充颜色
       solidcircle(snake.coor[i].x, snake.coor[i].y, 5);//绘制蛇形
	}
	if (food.flag)
	{
		setfillcolor(BLUE);
		solidcircle(food.x, food.y, food.r);
	}
	
	EndBatchDraw();
}
void SnakeMove()
{
	for (int i = snake.size - 1;i > 0;i--)
	{
		snake.coor[i]= snake.coor[i - 1];
	}//蛇的下一节跟着上一节移动
	switch(snake.dir)
    {	
	   case UP:
			snake.coor[0].y-= snake.speed;
			//让蛇可以穿墙回来
			if (snake.coor[0].y + 10 <= 0)
			{
				snake.coor[0].y = 480;
			}
			break;
		case DOWN:
			snake.coor[0].y+= snake.speed;
			if (snake.coor[0].y - 10 >= 480)
			{
				snake.coor[0].y = 0;
			}
			break;
		case LEFT:
			snake.coor[0].x-= snake.speed;
			if (snake.coor[0].x + 10 <= 0)
			{
				snake.coor[0].x = 640;
			}
			break;
		case RIGHT:
			snake.coor[0].x += snake.speed;
			if (snake.coor[0].x - 10 >= 640)
			{
				snake.coor[0].x = 0;
			}
				break;
			
	}
	
   
}
void KeyControl()
{
	//判断有没有按键，若按键则为真
	if(_kbhit())
	{
		switch (_getch())
		{
		case 72:
		case'w':
			if (snake.dir != DOWN)//防止蛇掉头
			{
				snake.dir = UP;
			}
				break;
		case 80:
		case's':
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
				break;
		case 75:
		case'a':
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 77:
		case'd':
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
			//游戏暂停
		case' ':
			while (1)
			{
				if (_getch() == ' ')
					return;
			}
			break;
		}
	}
	
}
void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)//如果食物被吃掉，则重新生成新的食物。
	{
		food.x = rand() % 610+15;
		food.y = rand() % 450+15;
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}
int Suicide()
{
	int i;
	for(i=1;i<snake.size;i++)
		if (snake.coor[0].x == snake.coor[i].x&& snake.coor[0].y== snake.coor[i].y)
		{
			settextcolor(RED);
			outtextxy(270, 200, "你自杀啦！");
			outtextxy(270, 220, "Game Over");
			Sleep(3000);
			return 1;
		}
	return 0;
}

int main()
{
	GameInit();
	while (1)
	{ 
	  GameDraw();
	  if (Suicide())
	  {
		  break;
	  }
      SnakeMove();
	  KeyControl();
	  EatFood();
	  Sleep(80);
	}
	return 0;
}
