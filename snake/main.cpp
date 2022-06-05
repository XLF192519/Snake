///*************************************************
//	�ļ����ƣ�main.cpp
//	�ļ�������ʵ����򵥵�̰������Ϸ
//	���뻷����VS2022  &  EasyX
//	������أ�XLF192519
//**************************************************/
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include <mmsystem.h>        //mci...��ͷ�ļ�    winmm.lib����lib�ļ�
#include <cstddef>
#pragma comment(lib,"winmm.lib")  
//����ָ������ڹ��������"winmm.lib"�Ĺ���һ�������߱�����Ҫ����winmm��
//#pragma ��һ��������ָ��,�Ǹ����߱�������Ҫ����һЩ����,Ȼ���ں����comment����ָ����ʲô����

/*
    lib�ļ��д�ŵ��Ǻ������õ���Ϣ��ֵ��һ��������ݿ��о�̬���ݿ⣨.lib�ļ����Ͷ�̬���ݿ⣨.dll�ļ�����
    ��̬���뽫����������ʵ�ֶ�����lib�С���������д��붼Ƕ�뵽��������
    ��̬������ŵ��Ǳ�д�����ĳ�����Ҫ����DLL�����뺯����ֱ�ӿ��Ե��ɳ����һ������ʹ�á�
    ��̬�����ȱ��Ҳ���Զ��׼��ģ�ʹ�þ�̬����ĳ��������ȶ�̬�����ԭ���Ǻ�����ʵ�ֱ�Ƕ��Ϊ��������һ���֡�

    ��̬lib�ļ��൱��һ��C�����е�h�ļ����Ǻ����������ֵ�������������ʵ�ֹ���Ƕ�뵽�������У������ֻ�ǽ�������ַ�������������У�
���е����ú����ǵ���DLL�����뺯����ʵ�ֺ����ľ��������
    ��������ѧϰһ������Ĳ��֡�

*/


#define NUM 100   
//�ߵ���󳤶�

/*IMAGE Img; */ //���屳��ͼ�������Ժ�ѧ���������

//ö���ĸ�����,��ʼֵ��������ASCII�룬���Ժ���Ʒ���ʹ��
enum Ch
{
	up=72,
	down=80,
	left=75,
	right=77
};
/*
    ö�������ڽṹ�壬���Ƕ��߻���������ġ�
	ö������Ĭ��Ϊ��int���ͣ���Ĭ��Ϊ��0,1,2,3����������Ҳ��Ϊ���Ը�ֵ��Ҳ�ɸı�ö�����͵�int���ͣ��罫�任��byte�������ڴ�����ģ�
�ṹ����Խ����޸���ͬ���͵����Ա��������һ����ö�����Ͳ�֮ͬ����ö�������ڵĶ���ͬ���͵����Ա��������ҽṹ������нṹ����
*/

//��������ṹ�����ͣ���δ����ȷ�еı���
struct Coor
{
	int x;
	int y;
};

//�ṹ�嶨����
struct Snake
{
	int n;  //�ߵ�ǰ�Ľ���
	Ch ch;   //����ö�����͵ı���
	Coor szb[NUM];          //��ÿһ�ڵ����꣬����һ���ṹ������  
}snake;         

//����ʳ��ṹ�弰�����
struct Food
{
	int x;
	int y;           //ʳ�������

	bool isEat;      //boolȡֵfalse��true��0Ϊfalse����0Ϊtrue��
}food;

//��ʼ��С�ߺ�ʳ��ĺ��������ǻ�û�л���С����ʳ�init���ǳ�ʼ������˼����ס������
void InitGame()
{
	srand((unsigned int)time(NULL));   //�������������

	mciSendString(L"open ˦�и�.mp3 alias BGM", 0, 0, 0);    //Media Control Interface
	mciSendString(L"play BGM", 0, 0, 0);    //��������û�н�����ʱ�򲥷�,��ͣ��pause��������close
	snake.n = 2;
	snake.ch = right;
	snake.szb[0].x = 320;  //��ͷ�ǵ�0��Ԫ��
	snake.szb[0].y = 240;
	snake.szb[1].x = 310;
	snake.szb[1].y = 240;

	food.isEat = true;     //�Ե�ʳ���жϣ���ʼ��Ϊ�棬����Ż�����µ�ʳ��
}

//������
void DrawSnake()
{
	for (int i = 0; i < snake.n; i++)
	{
		rectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + 10, snake.szb[i].y + 10);//�Խ�������ȷ������λ��
	}
}

//������
void SnakeMove()
{
	//ͨ�����ִӺ���ǰ��ֵ�ķ�������ʾǰ��ķ����ƶ����λ��
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
	case up:
		if(snake.ch != down)   //��Щ�����������������������ƶ���ʱ��ʹ������ʧЧ��
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

	food.isEat = false;  //�߳Ե�ʳ���ʱ�����Ϊ
}

//����ʳ��
void DrawFood()
{
	rectangle(food.x, food.y, food.x + 10, food.y + 10);
}

//�Ե�ʳ��
void EatFood()
{
	if (snake.szb[0].x == food.x && snake.szb[0].y == food.y)
			{
				snake.n++;      //�Ե���Ҳ����ʳ������ͷ�������غ��ˣ������ȼ�һ
				food.isEat = true;
			}
}

//��Ϸ����
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
		outtextxy(200, 200, L"Game Over");
		outtextxy(180, 300, L"��ӭ�´�����");
		mciSendString(L"close BGM", 0, 0, 0);     
		
		_getch();
		closegraph();
		exit(0);
	}

	//2.ײ���Լ�
	for (int i = snake.n - 1; i > 0; i--)  //��ÿһ��Ԫ�ر���һ���ж��Ƿ�ײ���Լ�
	{
		if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y)
		{
			//������Ϸ
			cleardevice();      //ײǽ�����ͼ����Ļ��Ϊ����Ľ��������׼��
			setcolor(YELLOW);           //����������<graphics.h>ͷ�ļ������
			settextstyle(50, 0, L"����");
			outtextxy(200, 200, L"Game Over");    //�����������
			outtextxy(180, 300, L"��ӭ�´�����");
			mciSendString(L"close BGM", 0, 0, 0);        //��Ϸ������ص�����
			
			_getch();       //�õ������ֵ���˳�ͼ�ν���,����ľ�����Ժ���
			closegraph();
			exit(0);
			/*
			exit(0) ���˳��������̣�������������ã������˳���ǰ���̡�
		    ���main()��һ���ݹ�����У�exit()��Ȼ����ֹ����
		    ��return������Ȩ�ƽ����ݹ��ǰһ����ֱ���������һ������ʱreturn�Ż���ֹ����
		    return��exit()����һ���������ڣ���ʹ�ڳ�main()֮��ĺ����е���exit()����Ҳ����ֹ����
			*/

		}
	}


}

//������
int main()
{
	initgraph(640, 480);    //��ʼ��ͼ�ν���ĺ���,�����������������ģ����Ͻ���ԭ���λ��
	/*loadimage(&Img, _T("pic.jpg"));
	putimage(0, 0, &Img);*/    //������������뱳��ͼƬ�ģ�������ֻ���ڿ�ʼ����һ�£���ѧ������������
	InitGame();    //��ʼ����Ϸ�������ߵĳ�ʼ����������;���λ��
	
	/*
	��ѭ��������Ⱥ��߼�����˵���ģ����ǹ涨С����󳤶���100�ڣ����ҳ�ʼ�����ʼ�����ڣ���ô������������൱�ڣ�0,0��
	�Ȼ�С�߾ͻ�ÿ�ζ��ڳ�ʼ��λ�û������������ڣ�0,0������һ�ڣ�����Ҫ�����ȸ������ڸ�ֵ��ȥ���������Ͳ���������Ͻǳ���
	�ߵ���һ��ڵ������
	*/
	while (1)
	{
		    cleardevice();
		
			if (food.isEat)
			    CreateFood();    //�����Ȼ���һ��ʳ��   

			
			//DrawSnake();    //��С�� 
			//DrawFood();
			//SnakeMove();    //С���ƶ�     ����������߼����������Ͻ��ܻ����һ��λ��ԭ����ߣ�����Ҫ�ȸ�ֵ
			
			SnakeMove();    //�ȸ����µ�һ�ڸ�ֵ
			DrawSnake();    //��С�� 
			DrawFood();

			EatFood();
			BreakSnake();      //�������exit()������ֹѭ������������
			
			//������ж�����Ǹ��������������ƶ��ٶ�
			if(snake.n<5)
			  Sleep(100);   //����������ʵ���ƶ��ٶȣ����浥λ�Ǻ���������ж�����Ǹ��������������ƶ��ٶ�
			else
			  Sleep(50);      
		
        if(_kbhit())     //_kbhit()�����ǰ�����⺯��������а���Ϊ1��û�а���Ϊ0
		    ChangeSnakeCh();
	};
	return 0;
}