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
#include<fstream>//�ļ�����Ҫ��ͷ�ļ�
#include<string>//getline��Ҫ��ͷ�ļ�
using namespace std;

string musicFilePath = "ð�յ� - ���ִ�ѵ����.mp3";
int musicswitch = 1;//Ĭ��

/*
row��ʾ������
col��ʾ������
map[i][j]��ʾ����i��j����Ӧ�����ֵ
ֵ��0��ʾ����û�б���ֵ����0��ʾ��ǰ����ϳɵ�ֵ
*/
const int row = 4;
const int col = 4;
int map[row][col] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {4, 5, 6, 7}};
int count1 = 0;

/*
�û������ñ���s����
*/
char s;
void input()
{
	s = _getch();
}

// ��ʾ�÷�
int score = 0;

// ��¼�Ƿ�ʹ�õ���
int flag=0;

// �����Ƿ�ʹ��
bool times;

// ���а����飬��¼�������а�ķ���
int rank1[20];
//------------------------------------ -

// ���½�����������涨��Ĭ����ʾ�û�����'s'�ͷ���������
/*
	������: �հ�
	����: ��ʼ����ͼ,map[][]ȫ0
	����: void
	����ֵ: void
*/
void init();

/*
	������: ���˾
	����: �������˵�����
		������ʼ��Ϸ���������ã��˳���Ϸ�����а��淨���ܣ���ܰ��ʾ
		�����û������ַ��ж�
		  if(s=='w')��ʼ��Ϸ
		  if(s=='s')��������
		  if(s=='x')�˳���Ϸ
		  if(s=='e')���а�
		  if(s=='d')�淨����
		  if(s=='c')��ܰ��ʾ
	����: void
	����ֵ: void
*/
void menu_view();

/*
	������: MoAlice
	����: ���ƿ�ʼ��Ϸ���棬��ѡ�񾭵�ģʽ(w)���޾�ģʽ(s)
	����: void
	����ֵ: void
*/
void start_view();

/*
	������: MoAlice
	����: �������ý���
		�����û������ַ��ж�
		  if(s=='w')������Ч����
		  if(s=='s')����������
		  if(s=='x')�����������
	����: void
	����ֵ: void
*/
void setting_view();

/*
��������
�����ˣ����˾
���ܣ�
	1��չʾѡ�  ��ͼ��С   �������˵� ��������

	2����������:if(s=='w')���������С����С�д����α仯
		  if(s=='x')��������

		  ��ͼ��С����С4*4��5*5�����6*6�����ֵ�ͼѡ��

������void
����ֵ��void
*/
void mapSetView();

/*
	������:
	����: ��ʾ ��Ч��С ��������
	if(s=='w')������Ч��С����С�д����α仯
		  if(s=='x')�������ý���
	����: void
	����ֵ: void
*/
void music_set();

/*
	������:
	����: �������а����
	����: void
	����ֵ: void
*/
void rank_view();

/*
	������: ��
	����: �����淨���ܽ���
	����: void
	����ֵ: void
*/
void game_way();

/*
	������:
	����: ���Ʒ�������
	����: void
	����ֵ: void
*/
void feedback_view();

/*
	������:
	����: ������ܰ��ʾ����
	����: void
	����ֵ: void
*/
void remind_view();

/*
	������: ����ĺɫ����
	����: ����ʤ������
		  �����û������ַ��ж�
		  if(s=='w')����
		  if(s=='s')����������
		  if(s=='x')�������
	����: void
	����ֵ: void
*/
void win_view();

/*
	������: ����ĺɫ����
	����: ����ʧ�ܽ���
		  �����û������ַ��ж�
		  if(s=='w')����
		  if(s=='s')����������
		  if(s=='x')�������
	����: void
	����ֵ: void
*/
void defeat_view();

/*
	������: igb
	����: ������ͣ����
		  �����û������ַ��ж�
		  if(s=='w')����
		  if(s=='s')����������
	����: void
	����ֵ: void
*/
void pause_view();

/*
	������: ���˾
	����: ������ֽ���
	����д�����а�(����������д��rank����)
	���򷵻�������
	����: void
	����ֵ: void
*/
void save_view();

/*
	������: ��
	����: ���ƾ�����Ϸ����
		 ����ڵ�ͼ������һ����ֵ�ķ��飨����������д��creat_block(int map,int row,int col)������
		 �ж��û����ƶ�����{
			w����
			s����
			a����
			d����
			�ո���ͣ
		 }
		 �����ƶ�����޸�����
		 {//�ƶ����飬�ӷֵȲ��������������Ѿ���д�õĺ���
			�ж��Ƿ���Գɹ��ƶ�
						����  {�ƶ����鲢�ϲ������ӵ÷֣�������Ч(�Ǻ���)
						�ж��Ƿ���Ϸʤ��������Ϸ���棬
						��û��ʤ���ƶ��������ڿհ׷��鴦��ֵ�����µĴ�ֵ����
							  }
						������  �ж��Ƿ���Ϸ���������������Ϸ��������
			������ո� ������ͣ����
		 }

	����: void
	����ֵ: void
*/
void game1_view();

/*
	������: ��
	����: �����޾�ģʽ��Ϸ����
		 ����ڵ�ͼ������һ����ֵ�ķ���
		 �ж��û����ƶ�����{
			w����
			s����
			a����
			d����
			�ո���ͣ
			pʹ�õ���
		 }
		 �����ƶ�����޸�����
		 {
			�ж��Ƿ���Գɹ��ƶ�
						����  {�ƶ����鲢�ϲ������ӵ÷֣�������Ч(�Ǻ���)
					   �ƶ��������ڿհ׷��鴦��ֵ�����µĴ�ֵ����
							  }
						������  �ж��Ƿ���Ϸ���������������Ϸ��������
			������ո� ������ͣ����
			������p����ʹ�ô���times==0 ����ʹ�õ��ߺ���
		 }

	����: void
	����ֵ: void
*/
void game2_view();

//---------------------------------------------------- -
/*
	������: �հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
int move_w(int map, int row, int col);

/*
	������: �հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
int move_s(int map, int row, int col);

/*
	������:�հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
int move_a(int map, int row, int col);

/*
	������: �հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
int move_d(int map, int row, int col);

/*
	������: igb
	����: �����·���
	��map[][]Ϊ0�������һ�����꽫�丳ֵ����������д�õ�select����������
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
int creat_block();

/*
	������: MoAlice
	����: ���²����ķ��������ֵ2����4
		����2�ĸ���Ϊ2/3��4�ĸ���Ϊ1/3
	����: void
	����ֵ:����2����4
*/
int select();

/*
	������: admin
	����: �ж��Ƿ�ʤ��
	����: x��ʾ�ϲ������������
	����ֵ: �ɹ�1����0
*/
int is_win(int x);

/*
	������: admin
	����: �ж��Ƿ���Ϸ����
	Ҫ��д���ĸ������ж��������Ҷ��������ƶ�Ȼ��ϲ��ж���Ϸ����
	��bool no_w(int map[][],int row,int col)��ʾw���򲻿����ƶ�
	����: void
	����ֵ: �ɹ�1����0
*/
int is_end();

/*
	������:����ĺɫ����
	����: ͨ���ƶ��ͺϲ����ӵ÷�
	����: score��ʾ����
	����ֵ: �ɹ�1����0
*/
int add_score(int score);

/*
	������:
	����: ʹ�õ���
	��Ŀǰ��ͼȫ��ֵ�ۼӲ��Ҹ�ֵ�����½ǵķ��飬���෽������
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
int use_item();

/*
	������:
	����: �жϻ����Ƿ���Խ���ǰ10�������򽫻���д�����а�
	����: score�÷� rank[]���а�����
	����ֵ: �ɹ�1����0
*/
bool write_rank(int score);

/*
	������:
	����: �ҳ����а���߷�
	����: rank[]���а�����
	����ֵ: �ɹ�1����0
*/
int find_rank(int rank[]);

/*
	������:
	����: �ų��ϳ���Ч(�Ǻ���)
	����: *pf�ļ���ַ
	����ֵ:void
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
	cout << "w.��ʼ��Ϸ" << endl;
	cout << "s.��������" << endl;
	cout << "x.�˳���Ϸ" << endl;
	cout << " e.���а�" << endl;
	cout << "d.�淨����" << endl;
	cout << "c.��ܰ��ʾ" << endl;
	//cout << "q.��ϵ����" << endl;
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
	cout << "VFUNС������" << endl;
	cout << "�鳤��iGB" << endl;
	cout << "�����٣����˾" << endl;
	cout << "�����٣�admin" << endl;
	cout << "��Ϣ�٣�MoAlice" << endl;
	cout << "�ල�٣�����ĺɫ����" << endl;
	cout << "��Ʒ������" << endl;
	cout << "��Ʒ����   " << endl;
	cout << "x.����������" << endl;
	input();
	while (s != 'x') {
		input();
	}
	menu_view();
}



void start_view()
{
	system("cls");
	cout << "����ģʽ��w)" << endl;
	cout << "�޾�ģʽ��s��" << endl;
	cout << "���������ѡ��" << endl;
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
	cout << "�����ڴ�" << endl;
	cout << "����������(s)" << endl;
	cout << "���������ѡ��" << endl;
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
	cout << "������(w)" << endl;
	cout << "�ر�����(a)" << endl;
	cout << "����������(s)" << endl;
	cout << "���������ѡ��" << endl;
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

	cout << "\n   ��ͣ��...\n   w ����\n   s ����������\n";
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
	system("cls");//�������̨����
	cout << "��ϲ��������Ϸ ��ȥ��ս���޾�ģʽ��" << endl;
	cout << "s:����������" << endl;
	cout << "x:�������" << endl;
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
	system("cls");//�������̨����
	cout << "�ٽ�������ʧ���ǳɹ�֮ĸ���´���һ����" << endl;
	cout << "s:����������" << endl;
	cout << "x:���뱣����ֽ���" << endl;
	cout << "Ŀǰ�÷�" << score << endl;
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
	cout << "��ӭ����2048��" << endl;
	cout << "�淨˵�����ܣ�" << endl;

	cout << "����ģʽ���ϳ�2048��Ϊʤ��" << endl;
	cout << "�޾�ģʽ������������ۼӣ���¼��߷�" << endl;
	cout << "����������" << endl;
	cout << "	W��������һ��" << endl;
	cout << "	A��������һ��" << endl;
	cout << "	S��������һ��" << endl;
	cout << "	D��������һ��" << endl;
	cout << "	G����ͣ" << endl;
	cout << "	P��ʹ�õ��ߣ�����һ�Σ�" << endl;
	cout <<  "�������˵��밴x��" << endl;
	
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
	������: �հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
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
	������: �հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
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
	������:�հ�
	����: ����
	����: ��ͼ����map����row����col
	����ֵ: �ɹ�1����0
*/
void move_a() {

	//����ת�ã������ƶ�ʵ�����ƶ�
	int t;
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {//���Խ����ϵ�����ת֮��Ϊ����,���Խ��н���
				t = map[i][j];
				map[i][j] = map[j][i];
				map[j][i] = t;
			}
		}
	}
	//�������ƶ�
	move_w();

	//���鸴ԭ
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

	//����ת�ã������ƶ�ʵ�����ƶ�
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
	//�������ƶ�
	move_s();

	//���鸴ԭ
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
	cout << "���ĵ÷���" << score << endl;
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
	cout << "w.�������" << endl;
	cout << "s.����������" << endl;
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
				cout << "���ļ�" << filename << "ʧ�ܡ�\n";
			}
			for (int i = 0; i < 1; i++) {
				fout << rank1[i] << endl;

			}

			fout.close();
			cout << "����������\n";
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
		cout << "���ļ�" << filename << "ʧ�ܡ�\n";
	}
	while (getline(fin, line)) { // ���ж�ȡ�ļ�  
		int number;
		stringstream ss(line);
		if (!(ss >> number)) { // ���Խ��ַ���ת��Ϊ����  
			cout << "Failed to convert line to integer: " << line << endl;
			continue; // ���ת��ʧ�ܣ�������ǰ�в�������һ��  
		}
		rank1[count1++] = number; // ��������ӵ�������  
	}

	//while (getline(fin, buffer)) {
	//	cout << buffer << endl;
	//}
	
	fin.close();
	*/
	if (count1 > 10)count1 = 10;
	//sort(rank1, rank1 + count1);
	for (int i = 0,j=count1-1; j>=0; ++i,--j)
		cout << "��"<<i+1<<"���÷֣�"<<rank1[j] <<endl;
	int syc = 1;
	cout << "x����������" << endl; 

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
	cout << "������Ϸʱ���������ʱ�䣬������ȳ�����Ϸ��Ӱ��ѧϰ�����" << endl << "ͬʱ��Ҳ��ע�Ᵽ���۾������彡�����ʵ���Ϣ���˶���" << endl;
	cout << "x����������";
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
		cout << "���ļ�" << filename << "ʧ�ܡ�\n";
	}
	while (getline(fin, line)) { // ���ж�ȡ�ļ�  
		int number;
		stringstream ss(line);
		if (!(ss >> number)) { // ���Խ��ַ���ת��Ϊ����  
			cout << "Failed to convert line to integer: " << line << endl;
			continue; // ���ת��ʧ�ܣ�������ǰ�в�������һ��  
		}
		rank1[count1++] = number; // ��������ӵ�������  
	}

	//while (getline(fin, buffer)) {
	//	cout << buffer << endl;
	//}

	fin.close();
	sort(rank1, rank1 + count1);
	menu_view();
	return 0;
}