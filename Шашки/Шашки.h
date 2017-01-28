#pragma once
#define Eat_simple 500						//|Оценки хода. В зависимости от них будет определен стиль игры.
#define Eat_queen 1000						//|
#define Save_move 10						//|
#define Queen_move 80						//|
#define More_queens 200						//|
#define Under_attack 400					//|
#define Smart 4								//|Глубина хода
enum color { black, empty, white, quadr };	//Цвет для шашек
struct options
{
	int name[2] = { 0 };	//Координаты шашки
	color shash = empty;	//Цвет шашки
	bool queen = false;		//Является ли шашка дамкой
	bool border = false;	//Подсвечено ли поле для сруба
	bool chosen = false;	//Подсвечено ли выбранное поле
	bool comp = true;		//Может ли игрок ходить этой шашкой
	bool lockcut = false;	//Отвечает за обязательный сруб
	bool target = false;
};
void drawText(const char *text, int length, int x, int y);	//Отрисовка цифр и букв на рамке
void handleKeypress(unsigned char key, int x, int y);	//Отслеживание нажатий клавиатуры
void reshape(int w, int h);	//Обновляем размер окна (он должен быть постоянным)
void display();			//Работает с экраном
void board();			//Рисуем доску
void game();			//Здесь происходит сама игра
void coord_fig(color c, int y);
void figures();			//Прорисовка фигур
void move(int button, int state, int x, int y);	//Отслеживаем движения мышки
void hod();				//Ход игрока
void coordinates();		//Расстановка координат и присваивание их массиву desk
void scan(color bro, color enemy, options q[]);			//Сканирование доски на возможность сруба
void hod_comp();		//Ход компьютера
void finish();			//Окно конца
void reshape_finish(int w, int h);
void intelegent(int deep); //Предположиельные ходы
//______________________________________________
bool poshod = false;	//Может ли ходить игрок
bool block = false;		//Есть ли возможность рубить
int cord[4] = { 0 };	//Координаты нажитий
int click = 2;			//Счетчик нажатий
int colvo = 0;			//Счетчик ходов
options desk[64];		//Массив клеток
options cop[64];		//Копия ^
options intel[64];		//Копия для предположительных ходов
int point[2] = { 50,50 };					//Координаты указателя
int period[8] = { 1,1,-1,1,-1,-1,1,-1 };	//Массив периода для сканирования доски
bool was = false;							//Проверка для нескольких срубов
int multi = -1;								//Элемент, который рубит несколько раз
//_____________________________________________
int value = 0;					//Оценка хода
long int bufvalue = 0,			//|Переменные, которые хранят потенциальный ход компьютера
bufx = 0,						//|
bufy = 0,						//|
bufsr = -1,						//|Запоминаем какую шашку срубили
xx = 0,
yy = 0;
int blacks = 0;					//Количество черных шашек
int whites = 0;					//Количество белых шашек

