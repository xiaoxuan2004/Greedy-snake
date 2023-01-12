#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <graphics.h>	// ����ͼ�ο�ͷ�ļ�
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define SNAKE_NUM 500//�ߵ�������
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
	POINT coor[SNAKE_NUM];//����

}snake;
struct Food
{
	int x;
	int y;
	int r;//ʳ���С
	bool flag;//ʳ���Ƿ񱻳�
	DWORD color;//ʳ����ɫ
}food;

//void Menu()
//{//�˵�
//	int num;
//	printf("��ӭ����̰���ߴ���ս��Ϸ\n");
//	printf("��Ϸ�������£�\n");
//	printf("�����̵��������ҿ����ߵķ���Ѱ�ҳԵĶ�����");
//	printf("ÿ��һ���߱䳤����Ϸ��������");
//	printf("ע���߿��Դ�ǽ����,���ҵ���ͷ�����ߵ����弴��Ϊ��ɱ��\n");
//	printf("ȷ�Ͻ�����Ϸ������1,�˳���Ϸ����0\n");
//	while (1)
//	{
//		printf("���룺");
//		scanf_s("%d", &num);
//		if (num== 1)
//		{
//			cleardevice();
//			break;
//		}
//		else if (num== 0)
//		{
//			printf("���˳���Ϸ");
//			break;
//		}
//		if (num != 1 && num != 0)
//		{
//			printf("�����������������");
//		}
//
//	}
//}

void GameInit()
{
	initgraph(640, 480);//��������
	mciSendString("open./111.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);//��������
	
	//��ʼ����
	snake.size = 3;
	snake.speed = 10;
	snake.dir=RIGHT;
	srand(unsigned int(time(0)));//srand(GetTickCount());��ȡ���������ڵĺ�����
	for (int i = 0;i < snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//��ʼ��ʳ��
	food.r = rand() % 10+5;
	food.x = rand() % 610+15;
	food.y = rand() % 450+15;
	food.flag = true;
	//�˵�
	settextcolor(YELLOW);
	outtextxy(160, 160, "��ӭ����̰���ߴ���ս��Ϸ!");
	outtextxy(190, 180, "��Ϸ�������£�");
	outtextxy(60, 200, "�����̵��������ҿ����ߵķ���Ѱ�ҳԵĶ���,ÿ��һ���߱䳤");
	outtextxy(80, 220, "ע��:�߿��Դ�ǽ����,����ͷ�����ߵ����弴��Ϊ��ɱ��");
	Sleep(3000);
	cleardevice();
	outtextxy(180, 200, "������Ϸ�밴Y���˳���Ϸ�밴N");
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
				outtextxy(270, 200, "��ʼ��Ϸ");
				Sleep(1000);
				t = 1;
				break;
			}
			case'n':
			case'N':
			{
				cleardevice();
				outtextxy(270, 200, "�˳���Ϸ");
				t = 0;
				break;
			}

			}
		}
	}
}

void GameDraw()
{
	BeginBatchDraw();//˫����
    setbkcolor(RGB(205,155,155));//���ñ���ɫ
	cleardevice();//����

	
	for (int i = 0;i < snake.size;i++)
	{
	   setfillcolor(GREEN);//�����ɫ
       solidcircle(snake.coor[i].x, snake.coor[i].y, 5);//��������
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
	}//�ߵ���һ�ڸ�����һ���ƶ�
	switch(snake.dir)
    {	
	   case UP:
			snake.coor[0].y-= snake.speed;
			//���߿��Դ�ǽ����
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
	//�ж���û�а�������������Ϊ��
	if(_kbhit())
	{
		switch (_getch())
		{
		case 72:
		case'w':
			if (snake.dir != DOWN)//��ֹ�ߵ�ͷ
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
			//��Ϸ��ͣ
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
	if (!food.flag)//���ʳ�ﱻ�Ե��������������µ�ʳ�
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
			outtextxy(270, 200, "����ɱ����");
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
