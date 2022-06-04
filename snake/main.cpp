/*************************************************
	�ļ����ƣ�main.cpp
	�ļ�������ʵ��̰������Ϸ
	���뻷����VS2022  &  EasyX
	������أ�XLF192519
**************************************************/
#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")


//��򵥵�̰����


#define NUM 100  //�ߵ���󳤶�

//ö��4������ 72  80  75  77  ��������
enum Ch { up = 72, down = 80, left = 75, right = 77 };

//����
struct Coor
{
	int x;
	int y;
};

//�ߵĽṹ��
struct Snake
{
	int n;			//�ߵ�ǰ�Ľ���
	Ch  ch;         //����
	Coor szb[NUM];				//��ÿһ�ڵ�����
}snake;   //snake

//ʳ��
struct Food
{
	int x;
	int y;

	bool isEat;
}food;

//��Ϸ�ĳ�ʼ������
void InitGame()
{
	srand((unsigned int)time(NULL));

	mciSendString(L"open ˦�и�.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM", 0, 0, 0);

	//�ȵõ�һ���� 1��  right 320 240
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

	//isEat  ֻ�е�ʳ�ﱻ�Ե�  �Ų����µ�ʳ� 
	food.isEat = true;
}

//������.
void DrawSnake()
{
	for (int i = 0; i < snake.n; i++)
	{
		rectangle(snake.szb[i].x, snake.szb[i].y,
			snake.szb[i].x + 10, snake.szb[i].y + 10);
	}
}

//������
void SnakeMove()
{
	//n-1�±��0��ʼ  i>0 ��ͷ�ǲ���Ҫ����
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

//�����ߵķ���
void ChangeSnakeCh()
{
	char key;
	key = _getch();

	switch (key)
	{
	case up:  //�ϼ�  down
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

//����ʳ��
void CreateFood()
{
	food.x = rand() % 64 * 10;
	food.y = rand() % 48 * 10;

	food.isEat = false;  //�߳ٵ�ʳ���ʱ��  isEat ture
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
	//1.ײǽ
	if (snake.szb[0].x < 0 || snake.szb[0].x>630 ||
		snake.szb[0].y < 0 || snake.szb[0].y>470)
	{
		//������Ϸ
		cleardevice();
		setcolor(YELLOW);
		settextstyle(50, 0, L"����");
		outtextxy(100, 100, L"Game Over");
		
		_getch();
		closegraph();
		exit(0);
	}

	//2.�Ե��Լ�
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y)
		{
			//������Ϸ
			cleardevice();
			setcolor(YELLOW);
			settextstyle(50, 0, L"����");
			outtextxy(100, 100, L"Game Over");
			
			_getch();
			closegraph();
			exit(0);
		}
	}


}

int main()
{
	initgraph(640, 480);  //��һ�����ڡ����
	InitGame();

	while (1)  //kbhit() ��ⰴ��  ����а�������1 û�з���0
	{
		if (food.isEat)
			CreateFood();
		cleardevice();
		SnakeMove();     //���µ�һ�ڸ�ֵ    ��0 0
		DrawSnake();     //�����ߵ����������  0 0
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
//    Mat test = imread("test.jpg"); //����ͼ��test
//    imshow("test", test);
//    waitKey(0);
//    return 0;
//}
