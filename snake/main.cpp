/*************************************************
	文件名称：main.cpp
	文件描述：实现贪吃蛇游戏
	编译环境：VS2022  &  EasyX
	作者相关：XLF192519
**************************************************/
#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")


//最简单的贪吃蛇


#define NUM 100  //蛇的最大长度

//枚举4个方向 72  80  75  77  ↑↓←→
enum Ch { up = 72, down = 80, left = 75, right = 77 };

//坐标
struct Coor
{
	int x;
	int y;
};

//蛇的结构体
struct Snake
{
	int n;			//蛇当前的节数
	Ch  ch;         //方向
	Coor szb[NUM];				//蛇每一节的坐标
}snake;   //snake

//食物
struct Food
{
	int x;
	int y;

	bool isEat;
}food;

//游戏的初始化函数
void InitGame()
{
	srand((unsigned int)time(NULL));

	mciSendString(L"open 甩葱歌.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM", 0, 0, 0);

	//先得到一条蛇 1节  right 320 240
	snake.n = 4;
	snake.ch = right;
	snake.szb[0].x = 320;
	snake.szb[0].y = 240;
	snake.szb[1].x = 310;
	snake.szb[1].y = 240;
	snake.szb[2].x = 310;
	snake.szb[2].y = 250;
	snake.szb[3].x = 310;
	snake.szb[3].y = 260;

	//isEat  只有当食物被吃掉  才产生新的食物。 
	food.isEat = true;
}

//绘制蛇.
void DrawSnake()
{
	for (int i = 0; i < snake.n; i++)
	{
		rectangle(snake.szb[i].x, snake.szb[i].y,
			snake.szb[i].x + 10, snake.szb[i].y + 10);
	}
}

//动起来
void SnakeMove()
{
	//n-1下标从0开始  i>0 蛇头是不需要传递
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}

	switch (snake.ch)
	{
	case up:
		snake.szb[0].y -= 10;
		break;
	case down:
		snake.szb[0].y += 10;
		break;
	case left:
		snake.szb[0].x -= 10;
		break;
	case right:
		snake.szb[0].x += 10;
		break;
	}

}

//控制蛇的方向
void ChangeSnakeCh()
{
	char key;
	key = _getch();

	switch (key)
	{
	case up:  //上键  down
		if (snake.ch != down)
			snake.ch = up;
		break;
	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case left:
		if (snake.ch != right)
			snake.ch = left;
		break;
	case right:
		if (snake.ch != left)
			snake.ch = right;
		break;
	}
}

//产生食物
void CreateFood()
{
	food.x = rand() % 64 * 10;
	food.y = rand() % 48 * 10;

	food.isEat = false;  //蛇迟到食物的时候  isEat ture
}

void DrawFood()
{
	rectangle(food.x, food.y, food.x + 10, food.y + 10);
}

void SnakeEatFood()
{
	if (snake.szb[0].x == food.x && snake.szb[0].y == food.y)
	{
		snake.n++;
		food.isEat = true;
	}

}

//
void BreakSnake()
{
	//1.撞墙
	if (snake.szb[0].x < 0 || snake.szb[0].x>630 ||
		snake.szb[0].y < 0 || snake.szb[0].y>470)
	{
		//结束游戏
		cleardevice();
		setcolor(YELLOW);
		settextstyle(50, 0, L"楷体");
		outtextxy(100, 100, L"Game Over");
		
		_getch();
		closegraph();
		exit(0);
	}

	//2.吃到自己
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y)
		{
			//结束游戏
			cleardevice();
			setcolor(YELLOW);
			settextstyle(50, 0, L"楷体");
			outtextxy(100, 100, L"Game Over");
			
			_getch();
			closegraph();
			exit(0);
		}
	}


}

int main()
{
	initgraph(640, 480);  //打开一个窗口。多大？
	InitGame();

	while (1)  //kbhit() 检测按键  如果有按键返回1 没有返回0
	{
		if (food.isEat)
			CreateFood();
		cleardevice();
		SnakeMove();     //蛇新的一节赋值    ！0 0
		DrawSnake();     //根据蛇的坐标绘制蛇  0 0
		DrawFood();
		SnakeEatFood();
		BreakSnake();
		Sleep(50);
		if (_kbhit())
		{
			ChangeSnakeCh();
		}
	}
	return 0;
}



//#include<opencv2/opencv.hpp>
//using namespace cv;
//int main()
//{
//    Mat test = imread("test.jpg"); //载入图像到test
//    imshow("test", test);
//    waitKey(0);
//    return 0;
//}
