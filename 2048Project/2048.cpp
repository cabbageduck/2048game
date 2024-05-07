#include <iostream>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<string>
#include <conio.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include<algorithm>
#include<fstream>//文件流需要的头文件
#include<string>//getline需要的头文件
using namespace std;

string musicFilePath = "冒险岛 - 射手村训练场.mp3";
int musicswitch = 1;//默认

/*
row表示总行数
col表示总列数
map[i][j]表示坐标i，j所对应方块的值
值：0表示方块没有被赋值，非0表示当前方块合成的值
*/
const int row = 4;
const int col = 4;
int map[row][col] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {4, 5, 6, 7}};
int count1 = 0;

/*
用户输入用变量s接收
*/
char s;
void input()
{
	s = _getch();
}

// 表示得分
int score = 0;

// 记录是否使用道具
int flag=0;

// 道具是否使用
bool times;

// 排行榜数组，记录进入排行榜的分数
int rank1[20];
//------------------------------------ -

// 以下界面中无特殊规定则默认提示用户输入's'就返回主界面
/*
	负责人: 空白
	功能: 初始化地图,map[][]全0
	参数: void
	返回值: void
*/
void init();

/*
	负责人: 玉城司
	功能: 绘制主菜单界面
		包含开始游戏，进入设置，退出游戏，排行榜，玩法介绍，温馨提示
		根据用户输入字符判断
		  if(s=='w')开始游戏
		  if(s=='s')进入设置
		  if(s=='x')退出游戏
		  if(s=='e')排行榜
		  if(s=='d')玩法介绍
		  if(s=='c')温馨提示
	参数: void
	返回值: void
*/
void menu_view();

/*
	负责人: MoAlice
	功能: 绘制开始游戏界面，可选择经典模式(w)和无尽模式(s)
	参数: void
	返回值: void
*/
void start_view();

/*
	负责人: MoAlice
	功能: 绘制设置界面
		根据用户输入字符判断
		  if(s=='w')进入音效设置
		  if(s=='s')返回主界面
		  if(s=='x')进入界面设置
	参数: void
	返回值: void
*/
void setting_view();

/*
界面设置
负责人：玉城司
功能：
	1，展示选项：  地图大小   返回主菜单 返回设置

	2，接受输入:if(s=='w')调整界面大小，从小中大依次变化
		  if(s=='x')返回设置

		  地图大小：最小4*4，5*5，最大6*6，三种地图选择

参数：void
返回值：void
*/
void mapSetView();

/*
	负责人:
	功能: 显示 音效大小 返回设置
	if(s=='w')调整音效大小，从小中大依次变化
		  if(s=='x')返回设置界面
	参数: void
	返回值: void
*/
void music_set();

/*
	负责人:
	功能: 绘制排行榜界面
	参数: void
	返回值: void
*/
void rank_view();

/*
	负责人: 函
	功能: 绘制玩法介绍界面
	参数: void
	返回值: void
*/
void game_way();

/*
	负责人:
	功能: 绘制反馈界面
	参数: void
	返回值: void
*/
void feedback_view();

/*
	负责人:
	功能: 绘制温馨提示界面
	参数: void
	返回值: void
*/
void remind_view();

/*
	负责人: 晓看暮色晚看云
	功能: 绘制胜利界面
		  根据用户输入字符判断
		  if(s=='w')重玩
		  if(s=='s')返回主界面
		  if(s=='x')保存积分
	参数: void
	返回值: void
*/
void win_view();

/*
	负责人: 晓看暮色晚看云
	功能: 绘制失败界面
		  根据用户输入字符判断
		  if(s=='w')重玩
		  if(s=='s')返回主界面
		  if(s=='x')保存积分
	参数: void
	返回值: void
*/
void defeat_view();

/*
	负责人: igb
	功能: 绘制暂停界面
		  根据用户输入字符判断
		  if(s=='w')继续
		  if(s=='s')返回主界面
	参数: void
	返回值: void
*/
void pause_view();

/*
	负责人: 玉城司
	功能: 保存积分界面
	是则写入排行榜(调用其他人写的rank函数)
	否则返回主界面
	参数: void
	返回值: void
*/
void save_view();

/*
	负责人: 函
	功能: 绘制经典游戏界面
		 随机在地图上生成一个带值的方块（调用其他人写的creat_block(int map,int row,int col)函数）
		 判断用户的移动输入{
			w上移
			s下移
			a左移
			d右移
			空格暂停
		 }
		 根据移动结果修改数据
		 {//移动方块，加分等操作都是其他人已经编写好的函数
			判断是否可以成功移动
						可以  {移动方块并合并，增加得分，播放音效(非核心)
						判断是否游戏胜利进入游戏界面，
						若没有胜利移动完后随机在空白方块处赋值产生新的带值方块
							  }
						不可以  判断是否游戏结束，是则进入游戏结束界面
			若输入空格 进入暂停界面
		 }

	参数: void
	返回值: void
*/
void game1_view();

/*
	负责人: 函
	功能: 绘制无尽模式游戏界面
		 随机在地图上生成一个带值的方块
		 判断用户的移动输入{
			w上移
			s下移
			a左移
			d右移
			空格暂停
			p使用道具
		 }
		 根据移动结果修改数据
		 {
			判断是否可以成功移动
						可以  {移动方块并合并，增加得分，播放音效(非核心)
					   移动完后随机在空白方块处赋值产生新的带值方块
							  }
						不可以  判断是否游戏结束，是则进入游戏结束界面
			若输入空格 进入暂停界面
			若输入p并且使用次数times==0 调用使用道具函数
		 }

	参数: void
	返回值: void
*/
void game2_view();

//---------------------------------------------------- -
/*
	负责人: 空白
	功能: 上移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
int move_w(int map, int row, int col);

/*
	负责人: 空白
	功能: 下移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
int move_s(int map, int row, int col);

/*
	负责人:空白
	功能: 左移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
int move_a(int map, int row, int col);

/*
	负责人: 空白
	功能: 右移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
int move_d(int map, int row, int col);

/*
	负责人: igb
	功能: 产生新方块
	在map[][]为0处随机找一个坐标将其赋值（用其他人写好的select（）函数）
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
int creat_block();

/*
	负责人: MoAlice
	功能: 对新产生的方块随机赋值2或者4
		返回2的概率为2/3，4的概率为1/3
	参数: void
	返回值:返回2或者4
*/
int select();

/*
	负责人: admin
	功能: 判断是否胜利
	参数: x表示合并后产生的数字
	返回值: 成功1否则0
*/
int is_win(int x);

/*
	负责人: admin
	功能: 判断是否游戏结束
	要求写出四个函数判断上下左右都不可以移动然后合并判断游戏结束
	如bool no_w(int map[][],int row,int col)表示w方向不可以移动
	参数: void
	返回值: 成功1否则0
*/
int is_end();

/*
	负责人:晓看暮色晚看云
	功能: 通过移动和合并增加得分
	参数: score表示分数
	返回值: 成功1否则0
*/
int add_score(int score);

/*
	负责人:
	功能: 使用道具
	将目前地图全部值累加并且赋值给左下角的方块，其余方块清零
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
int use_item();

/*
	负责人:
	功能: 判断积分是否可以进入前10，可以则将积分写入排行榜
	参数: score得分 rank[]排行榜数组
	返回值: 成功1否则0
*/
bool write_rank(int score);

/*
	负责人:
	功能: 找出排行榜最高分
	参数: rank[]排行榜数组
	返回值: 成功1否则0
*/
int find_rank(int rank[]);

/*
	负责人:
	功能: 放出合成音效(非核心)
	参数: *pf文件地址
	返回值:void
*/
void music(FILE *pf);

//////////////////////

bool no_col()
{
	bool mark = false;
	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row - 1; ++j)
		{
			if (map[j][i] == map[j + 1][i]|| map[j][i] ==0|| map[j + 1][i]==0)
			{
				mark = true;
			}
		}
	}
	if (!mark)
		return true;
	else
		return false;
}
bool no_row()
{
	bool mark = false;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col - 1; ++j)
		{
			if (map[i][j] == map[i][j + 1]||map[i][j]==0||map[i][j + 1]==0)
			{
				mark = true;
			}
		}
	}
	if (!mark)
		return true;
	else
		return false;
}
int is_end()
{
	if (no_row() && no_col())
		return 1;
	else
		return 0;
}

int is_win()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (map[i][j] == 2048)
			{
				return 1;
			}

		}
	}
	return 0;
}

void menu_view()
{
	system("cls");
	cout << "    2048  " << endl;
	cout << "w.开始游戏" << endl;
	cout << "s.进入设置" << endl;
	cout << "x.退出游戏" << endl;
	cout << " e.排行榜" << endl;
	cout << "d.玩法介绍" << endl;
	cout << "c.温馨提示" << endl;
	//cout << "q.联系我们" << endl;
	score = 0;
	
	do
	{
		if (musicswitch == 1) {
			mciSendString(("open \"" + musicFilePath + "\" type MPEGVideo alias mp3").c_str(), 0, 0, 0);
			mciSendString("play mp3 repeat", 0, 0, 0);
		}
		if (musicswitch == 0) {
			mciSendString(("open \"" + musicFilePath + "\" type MPEGVideo alias mp3").c_str(), 0, 0, 0);
			mciSendString("close mp3 ", 0, 0, 0);
		}
		
		input();
		if (s == 'w')
		{
			start_view();
			break;
		}
		if (s == 's')
			setting_view();
		if (s == 'x')
			exit(0);
		if (s == 'e')
			rank_view();
			cout << '2';
		if (s == 'd')
			game_way();
		if (s == 'c')
		remind_view();
		if (s == 'q')
			feedback_view();
			
	} while (s != 'w' && s != 's' && s != 'x' && s != 'e' && s != 'd' && s != 'c' && s != 'q');
}

void feedback_view() {
	system("cls");
	cout << "VFUN小组制作" << endl;
	cout << "组长：iGB" << endl;
	cout << "技术官：玉城司" << endl;
	cout << "技术官：admin" << endl;
	cout << "信息官：MoAlice" << endl;
	cout << "监督官：晓看暮色晚看云" << endl;
	cout << "产品经理：函" << endl;
	cout << "产品经理：   " << endl;
	cout << "x.返回主界面" << endl;
	input();
	while (s != 'x') {
		input();
	}
	menu_view();
}



void start_view()
{
	system("cls");
	cout << "经典模式（w)" << endl;
	cout << "无尽模式（s）" << endl;
	cout << "请输入你的选择" << endl;
	while (1)
	{
		input();
		if (s == 'w')
		{
			game1_view();
			break;
		}
		else if (s == 's')
		{
		game2_view();
			break;
		}
	}
}
/*
void setting_view()
{
	system("cls");
	int set = 1;
	cout << "敬请期待" << endl;
	cout << "返回主界面(s)" << endl;
	cout << "请输入你的选择" << endl;
	do
	{
		input();
		switch (s)
		{

		case 's':
			 menu_view();
			break;

		default:
			set = 0;
		}
	} while (set == 0);
}
*/
void setting_view()
{
	system("cls");
	int set = 1;
	cout << "打开音乐(w)" << endl;
	cout << "关闭音乐(a)" << endl;
	cout << "返回主界面(s)" << endl;
	cout << "请输入你的选择" << endl;
	do
	{
		input();
		switch (s)
		{

		case 's':
			menu_view();
			break;
		case'w':
			musicswitch = 1;
			menu_view();
			break;
		case'a':
			musicswitch = 0;
			menu_view();
			break;
		default:
			set = 0;
		}
	} while (set == 0);
}

int select()
{
	srand((unsigned)time(NULL));
	double cent = rand() % 11;
	if (cent < 7) {
		cent = 2;
	}
	else {
		cent = 4;
	}
	return cent;
}

void pause_view()
{

	cout << "\n   暂停中...\n   w 继续\n   s 返回主界面\n";
	while (1)
	{
		input();
		if (s == 'w')
		{
			break;
		}
		else if (s == 's')
		{
			menu_view();
			break;
		}
	}

}

int creat_block()
{
	srand((unsigned int)time(NULL));
	while (1) 
	{
		int creat_row = rand() % 4;
		int creat_col = rand() % 4;
		if (map[creat_row][creat_col] == 0) 
		{
			map[creat_row][creat_col] = select();
			return 1;
			break;
		}
		int cnt = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (map[i][j] == 0)
				{
					cnt = 1;
				}
			}
		}
		if (cnt == 0)break;
	}
}

void win_view() {
	system("cls");//清除控制台内容
	cout << "恭喜玩家完成游戏 快去挑战下无尽模式吧" << endl;
	cout << "s:返回主界面" << endl;
	cout << "x:保存积分" << endl;
	input();
	while (s != 'w' && s != 's' && s != 'x') {
		input();
	}
	if (s == 'w') {
		game1_view();
	}
	else if (s == 's') {
		menu_view();
	}
	else {
		save_view();
	}
}

void defeat_view() {
	system("cls");//清除控制台内容
	cout << "再接再厉，失败是成功之母，下次你一定行" << endl;
	cout << "s:返回主界面" << endl;
	cout << "x:进入保存积分界面" << endl;
	cout << "目前得分" << score << endl;
	input();
	while (s != 's' && s != 'x') {
		input();
	}
	if (s == 's') {
		menu_view();
	}
	else {
		save_view();
	}
}

void game_way()
{
	system("cls");
	cout << "欢迎来到2048！" << endl;
	cout << "玩法说明介绍：" << endl;

	cout << "经典模式：合成2048即为胜利" << endl;
	cout << "无尽模式：分数会进行累加，记录最高分" << endl;
	cout << "操作按键：" << endl;
	cout << "	W：向上走一格" << endl;
	cout << "	A：向左走一格" << endl;
	cout << "	S：向下走一格" << endl;
	cout << "	D：向右走一格" << endl;
	cout << "	G：暂停" << endl;
	cout << "	P：使用道具（仅限一次）" << endl;
	cout <<  "返回主菜单请按x键" << endl;
	
	while (1)
	{input();
		if (s == 'x')
		{
			menu_view();
			break;
		}
	}
}

bool write_rank(int score)
{
	sort(rank1, rank1 + count1);
	if (count1 <= 9)
	{
		rank1[count1] = score;
		count1++;
		sort(rank1, rank1 + count1);
	}
	else if (rank1[0] <= score)
	{
		rank1[0] = score;
		sort(rank1, rank1 + 10);
	}
	return 1;
}

int find_rank()
{
	if (count1 <= 9)
		return (rank1[count1 - 1]);
	else
		return (rank1[9]);
}

void init()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j] = 0;
		}
	}
}

//---------------------------------------------------- -
/*
	负责人: 空白
	功能: 上移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
void move_w() {
	for (int i = 3; i > 0; --i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i - 1][j] == 0 && i > 0) {
				map[i - 1][j] = map[i][j];
				map[i][j] = 0;
			}
			else if (map[i - 1][j] == map[i][j]) {
				if (map[i - 1][j] == map[i][j] && map[i - 2][j] == map[i][j] && i > 1 && map[i - 3][j] != map[i][j]) {
					map[i - 2][j] = map[i - 2][j] + map[i - 1][j];
					map[i - 1][j] = 0;
					score = score + map[i - 2][j];
				}
				else {
					map[i - 1][j] = map[i - 1][j] + map[i][j];
					map[i][j] = 0;
					score = score + map[i - 1][j];
				}
			}
		}
	}
	for (int i = 3; i > 0; --i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i - 1][j] == 0 && i > 0) {
				map[i - 1][j] = map[i][j];
				map[i][j] = 0;
			}
		}
	}
	for (int i = 3; i > 0; --i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i - 1][j] == 0 && i > 0) {
				map[i - 1][j] = map[i][j];
				map[i][j] = 0;
			}
		}
	}

}

/*
	负责人: 空白
	功能: 下移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
void move_s() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i + 1][j] == 0 && i < 3) {
				map[i + 1][j] = map[i][j];
				map[i][j] = 0;
			}
			else if (map[i + 1][j] == map[i][j]) {
				if (map[i + 1][j] == map[i][j] && map[i + 2][j] == map[i][j] && i < 2 && map[i + 3][j] != map[i][j]) {
					map[i + 2][j] = map[i + 2][j] + map[i + 1][j];
					map[i + 1][j] = 0;
					score = score + map[i + 2][j];
				}
				else {
					map[i + 1][j] = map[i + 1][j] + map[i][j];
					map[i][j] = 0;
					score = score + map[i + 1][j];
				}
			}
		}
	}


	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i + 1][j] == 0 && i < 3) {
				map[i + 1][j] = map[i][j];
				map[i][j] = 0;
			}
		}
	}


	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i + 1][j] == 0 && i < 3) {
				map[i + 1][j] = map[i][j];
				map[i][j] = 0;
			}
		}
	}

}

/*
	负责人:空白
	功能: 左移
	参数: 地图数组map，行row，列col
	返回值: 成功1否则0
*/
void move_a() {

	//数组转置，由上移动实现左移动
	int t;
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {//主对角线上的数组转之后为本身,所以进行交换
				t = map[i][j];
				map[i][j] = map[j][i];
				map[j][i] = t;
			}
		}
	}
	//调用上移动
	move_w();

	//数组复原
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {
				t = map[i][j];
				map[i][j] = map[j][i];
				map[j][i] = t;
			}
		}
	}

}

void move_d() {

	//数组转置，由下移动实现右移动
	int t;
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {
				t = map[i][j];
				map[i][j] = map[j][i];
				map[j][i] = t;
			}
		}
	}
	//调用下移动
	move_s();

	//数组复原
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {
				t = map[i][j];
				map[i][j] = map[j][i];
				map[j][i] = t;
			}
		}
	}

}

void pri()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (map[i][j] == 0)
			{
				printf("    ");
			}
			else
				printf("%4d", map[i][j]);
		}
		cout << endl;
	}
	cout << "您的得分是" << score << endl;
}
int use_item()
{
	int sum = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			sum += map[i][j];
		}
	}
	init();
	map[3][0] = sum;
	return 1;
}


void game1_view()
{
	init();
	creat_block();

	pri();
	while (1)
	{
		system("cls");
		pri();

		do {
			input();
			if (s == 'w')
			{
				move_w();
				creat_block();

			}
			if (s == 's')
			{
				move_s();
				creat_block();

			}
			if (s == 'a')
			{
				move_a();
				creat_block();
			}
			if (s == 'd')
			{
				move_d();
				creat_block();
			}
			if (s == 'g')
			{
				pause_view();
			}
			if (is_win())
				win_view();
				if (is_end())
					defeat_view();
		} while (s != 'w' && s != 's' && s != 'a' && s != 'd' && s != 'g');
	}
}

void game2_view()
{
	init();
	creat_block();

	pri();
	while (1)
	{
		system("cls");
		pri();

		do {
			input();
			if (s == 'w')
			{
				move_w();
				creat_block();

			}
			if (s == 's')
			{
				move_s();
				creat_block();

			}
			if (s == 'a')
			{
				move_a();
				creat_block();
			}
			if (s == 'd')
			{
				move_d();
				creat_block();
			}
			if (s == 'g')
			{
				pause_view();
			}
			if (s == 'p'&&flag==0)
			{
				use_item();
				flag = 1;
			}
			if (is_end())
				defeat_view();
		} while (s != 'w' && s != 's' && s != 'a' && s != 'd' && s != 'g' && s != 'p');
	}
}


void save_view()
{
	system("cls");
	cout << "w.保存积分" << endl;
	cout << "s.返回主界面" << endl;
	while (1)
	{
		input();
		if (s == 'w')
		{
			write_rank(score);
			string filename = "test.txt";
			ofstream fout;
			fout.open(filename, ios::app);
			if (fout.is_open() == false) {
				cout << "打开文件" << filename << "失败。\n";
			}
			for (int i = 0; i < 1; i++) {
				fout << rank1[i] << endl;

			}

			fout.close();
			cout << "保存操作完毕\n";
			system("pause");
			menu_view();
			break;
		}

		else if (s == 's')
		{
			menu_view();
			break;
		}
	}
}

void rank_view() {
	system("cls");
	/*
	string filename = "test.txt";
	string buffer;
	string line;
	ifstream fin;
	fin.open(filename, ios::in);
	if (fin.is_open() == false) {
		cout << "打开文件" << filename << "失败。\n";
	}
	while (getline(fin, line)) { // 逐行读取文件  
		int number;
		stringstream ss(line);
		if (!(ss >> number)) { // 尝试将字符串转换为整数  
			cout << "Failed to convert line to integer: " << line << endl;
			continue; // 如果转换失败，跳过当前行并继续下一行  
		}
		rank1[count1++] = number; // 将整数添加到数组中  
	}

	//while (getline(fin, buffer)) {
	//	cout << buffer << endl;
	//}
	
	fin.close();
	*/
	if (count1 > 10)count1 = 10;
	//sort(rank1, rank1 + count1);
	for (int i = 0,j=count1-1; j>=0; ++i,--j)
		cout << "第"<<i+1<<"名得分："<<rank1[j] <<endl;
	int syc = 1;
	cout << "x返回主界面" << endl; 

	while (syc)
	{
		input();
		if (s == 'x')
		{
			menu_view();
			syc = 0;
		}
	}

}

void remind_view()
{
	system("cls");
	cout << "在玩游戏时，请合理安排时间，避免过度沉迷游戏，影响学习和生活。" << endl << "同时，也请注意保护眼睛和身体健康，适当休息和运动。" << endl;
	cout << "x返回主界面";
		while(1)
   {
			input();
			if (s == 'x')
			{
				menu_view();
			    break;
		    }
	}
}

int main()
{
	string filename = "test.txt";
	string buffer;
	string line;
	ifstream fin;
	fin.open(filename, ios::in);
	if (fin.is_open() == false) {
		cout << "打开文件" << filename << "失败。\n";
	}
	while (getline(fin, line)) { // 逐行读取文件  
		int number;
		stringstream ss(line);
		if (!(ss >> number)) { // 尝试将字符串转换为整数  
			cout << "Failed to convert line to integer: " << line << endl;
			continue; // 如果转换失败，跳过当前行并继续下一行  
		}
		rank1[count1++] = number; // 将整数添加到数组中  
	}

	//while (getline(fin, buffer)) {
	//	cout << buffer << endl;
	//}

	fin.close();
	sort(rank1, rank1 + count1);
	menu_view();
	return 0;
}