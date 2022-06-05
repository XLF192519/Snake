///*************************************************
//	文件名称：main.cpp
//	文件描述：实现最简单的贪吃蛇游戏
//	编译环境：VS2022  &  EasyX
//	作者相关：XLF192519
//**************************************************/
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include <mmsystem.h>        //mci...的头文件    winmm.lib是其lib文件
#include <cstddef>
#pragma comment(lib,"winmm.lib")  
//这条指令和你在工程中添加"winmm.lib"的功能一样，告诉编译器要导入winmm库
//#pragma 是一条编译器指令,是给告诉编译器你要链接一些东西,然后在后面的comment里面指明是什么东西

/*
    lib文件中存放的是函数调用的信息，值得一提的是数据库有静态数据库（.lib文件）和动态数据库（.dll文件）。
    静态编译将导出声明和实现都放在lib中。编译后所有代码都嵌入到宿主程序。
    静态编译的优点是编写出来的程序不需要调用DLL和载入函数，直接可以当成程序的一部分来使用。
    静态编译的缺点也是显而易见的，使用静态编译的程序体积会比动态编译大，原因是函数的实现被嵌入为程序代码的一部分。

    动态lib文件相当于一个C语言中的h文件，是函数导出部分的声明，而不将实现过程嵌入到程序本身中，编译后只是将函数地址存在宿主程序中，
运行到调用函数是调用DLL并载入函数来实现函数的具体操作。
    可以深入学习一下这里的部分。

*/


#define NUM 100   
//蛇的最大长度

/*IMAGE Img; */ //定义背景图变量，以后学会了再添加

//枚举四个方向,初始值就是它的ASCII码，供以后控制方向使用
enum Ch
{
	up=72,
	down=80,
	left=75,
	right=77
};
/*
    枚举类似于结构体，但是二者还是有区别的。
	枚举类型默认为是int类型，并默认为从0,1,2,3…递增排序，也可为属性赋值，也可改变枚举类型的int类型（如将其换成byte来减少内存的消耗）
结构体可以将有限个不同类型的属性变量组合在一起，与枚举类型不同之处是枚举类型内的都是同类型的属性变量，并且结构体可以有结构函数
*/

//定义坐标结构体类型，并未定义确切的变量
struct Coor
{
	int x;
	int y;
};

//结构体定义蛇
struct Snake
{
	int n;  //蛇当前的节数
	Ch ch;   //方向，枚举类型的变量
	Coor szb[NUM];          //蛇每一节的坐标，这是一个结构体数组  
}snake;         

//定义食物结构体及其变量
struct Food
{
	int x;
	int y;           //食物的坐标

	bool isEat;      //bool取值false和true，0为false，非0为true。
}food;

//初始化小蛇和食物的函数，但是还没有画出小蛇与食物。init就是初始化的意思，记住！！！
void InitGame()
{
	srand((unsigned int)time(NULL));   //代入随机数种子

	mciSendString(L"open 甩葱歌.mp3 alias BGM", 0, 0, 0);    //Media Control Interface
	mciSendString(L"play BGM", 0, 0, 0);    //可以设置没有结束的时候播放,暂停是pause，结束是close
	snake.n = 2;
	snake.ch = right;
	snake.szb[0].x = 320;  //蛇头是第0个元素
	snake.szb[0].y = 240;
	snake.szb[1].x = 310;
	snake.szb[1].y = 240;

	food.isEat = true;     //吃到食物判断，初始化为真，下面才会产生新的食物
}

//绘制蛇
void DrawSnake()
{
	for (int i = 0; i < snake.n; i++)
	{
		rectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + 10, snake.szb[i].y + 10);//对角线坐标确定矩形位置
	}
}

//动起来
void SnakeMove()
{
	//通过这种从后往前赋值的方法来表示前面的方块移动后的位置
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
	case up:
		if(snake.ch != down)   //这些条件语句的作用是蛇在向下移动的时候，使得向上失效。
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

	food.isEat = false;  //蛇吃到食物的时候将其改为
}

//绘制食物
void DrawFood()
{
	rectangle(food.x, food.y, food.x + 10, food.y + 10);
}

//吃掉食物
void EatFood()
{
	if (snake.szb[0].x == food.x && snake.szb[0].y == food.y)
			{
				snake.n++;      //吃到了也就是食物与蛇头的坐标重合了，蛇身长度加一
				food.isEat = true;
			}
}

//游戏结束
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
		outtextxy(200, 200, L"Game Over");
		outtextxy(180, 300, L"欢迎下次再来");
		mciSendString(L"close BGM", 0, 0, 0);     
		
		_getch();
		closegraph();
		exit(0);
	}

	//2.撞到自己
	for (int i = snake.n - 1; i > 0; i--)  //将每一个元素遍历一遍判断是否撞到自己
	{
		if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y)
		{
			//结束游戏
			cleardevice();      //撞墙后清除图形屏幕，为下面的结束语句做准备
			setcolor(YELLOW);           //这三个都是<graphics.h>头文件里面的
			settextstyle(50, 0, L"楷体");
			outtextxy(200, 200, L"Game Over");    //设置输出内容
			outtextxy(180, 300, L"欢迎下次再来");
			mciSendString(L"close BGM", 0, 0, 0);        //游戏结束则关掉音乐
			
			_getch();       //得到任意键值就退出图形界面,这里的警告可以忽略
			closegraph();
			exit(0);
			/*
			exit(0) 是退出整个进程，不论在哪里调用，都会退出当前进程。
		    如果main()在一个递归程序中，exit()仍然会终止程序；
		    但return将控制权移交给递归的前一级，直到最初的那一级，此时return才会终止程序。
		    return和exit()的另一个区别在于，即使在除main()之外的函数中调用exit()，它也将终止程序。
			*/

		}
	}


}

//主函数
int main()
{
	initgraph(640, 480);    //初始化图形界面的函数,这个界面是有坐标轴的，左上角是原点的位置
	/*loadimage(&Img, _T("pic.jpg"));
	putimage(0, 0, &Img);*/    //本想在这里插入背景图片的，但是它只是在开始出现一下，等学会了再来完善
	InitGame();    //初始化游戏，包括蛇的初始节数、方向和具体位置
	
	/*
	主循环里面的先后逻辑是有说法的，我们规定小蛇最大长度是100节，而且初始化了最开始的两节，那么第三节坐标就相当于（0,0）
	先画小蛇就会每次都在初始化位置画两个，并且在（0,0）处画一节，所以要设置先给第三节赋值再去画，这样就不会出现左上角出现
	蛇的下一届节的情况了
	*/
	while (1)
	{
		    cleardevice();
		
			if (food.isEat)
			    CreateFood();    //首先先画出一个食物   

			
			//DrawSnake();    //画小蛇 
			//DrawFood();
			//SnakeMove();    //小蛇移动     按照这里的逻辑，画布左上角总会出现一个位于原点的蛇，所以要先赋值
			
			SnakeMove();    //先给蛇新的一节赋值
			DrawSnake();    //画小蛇 
			DrawFood();

			EatFood();
			BreakSnake();      //这里面的exit()负责终止循环和整个程序
			
			//这里的判断语句是根据蛇身长度设置移动速度
			if(snake.n<5)
			  Sleep(100);   //滞留函数，实现移动速度，里面单位是毫秒这里的判断语句是根据蛇身长度设置移动速度
			else
			  Sleep(50);      
		
        if(_kbhit())     //_kbhit()函数是按键检测函数，如果有按键为1，没有按键为0
		    ChangeSnakeCh();
	};
	return 0;
}