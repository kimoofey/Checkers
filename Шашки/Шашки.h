#pragma once
#define Eat_simple 500						//|������ ����. � ����������� �� ��� ����� ��������� ����� ����.
#define Eat_queen 1000						//|
#define Save_move 10						//|
#define Queen_move 80						//|
#define More_queens 200						//|
#define Under_attack 400					//|
#define Smart 4								//|������� ����
enum color { black, empty, white, quadr };	//���� ��� �����
struct options
{
	int name[2] = { 0 };	//���������� �����
	color shash = empty;	//���� �����
	bool queen = false;		//�������� �� ����� ������
	bool border = false;	//���������� �� ���� ��� �����
	bool chosen = false;	//���������� �� ��������� ����
	bool comp = true;		//����� �� ����� ������ ���� ������
	bool lockcut = false;	//�������� �� ������������ ����
	bool target = false;
};
void drawText(const char *text, int length, int x, int y);	//��������� ���� � ���� �� �����
void handleKeypress(unsigned char key, int x, int y);	//������������ ������� ����������
void reshape(int w, int h);	//��������� ������ ���� (�� ������ ���� ����������)
void display();			//�������� � �������
void board();			//������ �����
void game();			//����� ���������� ���� ����
void coord_fig(color c, int y);
void figures();			//���������� �����
void move(int button, int state, int x, int y);	//����������� �������� �����
void hod();				//��� ������
void coordinates();		//����������� ��������� � ������������ �� ������� desk
void scan(color bro, color enemy, options q[]);			//������������ ����� �� ����������� �����
void hod_comp();		//��� ����������
void finish();			//���� �����
void reshape_finish(int w, int h);
void intelegent(int deep); //���������������� ����
//______________________________________________
bool poshod = false;	//����� �� ������ �����
bool block = false;		//���� �� ����������� ������
int cord[4] = { 0 };	//���������� �������
int click = 2;			//������� �������
int colvo = 0;			//������� �����
options desk[64];		//������ ������
options cop[64];		//����� ^
options intel[64];		//����� ��� ����������������� �����
int point[2] = { 50,50 };					//���������� ���������
int period[8] = { 1,1,-1,1,-1,-1,1,-1 };	//������ ������� ��� ������������ �����
bool was = false;							//�������� ��� ���������� ������
int multi = -1;								//�������, ������� ����� ��������� ���
//_____________________________________________
int value = 0;					//������ ����
long int bufvalue = 0,			//|����������, ������� ������ ������������� ��� ����������
bufx = 0,						//|
bufy = 0,						//|
bufsr = -1,						//|���������� ����� ����� �������
xx = 0,
yy = 0;
int blacks = 0;					//���������� ������ �����
int whites = 0;					//���������� ����� �����

