#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <clocale>
#include <windows.h>
#include "Шашки.h"

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); /*Включаем двойную буферизацию и четырехкомпонентный цвет*/
	glutInitWindowSize(450, 450);
	glutCreateWindow("Шашки");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(move);				//Отслеживаем нажатия
	glutKeyboardFunc(handleKeypress);	//Выход на Esc
	glutMainLoop();
	return 0;
}
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 97:
		if (point[0] == 50)
			break;
		else
			point[0] -= 50;
		break;
	case 100:
		if (point[0] == 400)
			break;
		else
			point[0] += 50;
		break;
	case 119:
		if (point[1] == 400)
			break;
		else
			point[1] += 50;
		break;
	case 115:
		if (point[1] == 50)
			break;
		else
			point[1] -= 50;
		break;
	case 246:
		if (point[1] == 400)
			break;
		else
			point[1] += 50;
		break;
	case 244:
		if (point[0] == 50)
			break;
		else
			point[0] -= 50;
		break;
	case 251:
		if (point[1] == 50)
			break;
		else
			point[1] -= 50;
		break;
	case 226:
		if (point[0] == 400)
			break;
		else
			point[0] += 50;
		break;
	case 13:
		if (click == 2)
		{
			cord[0] = point[0];
			cord[1] = point[1];
			click = 1;
			for (int i = 0; i < 64; i++)
			{
				if (desk[i].name[0] == point[0] && desk[i].name[1] == point[1])
				{
					desk[i].chosen = true;
					break;
				}
			}
		}
		else
		{
			cord[2] = point[0];
			cord[3] = point[1];
			click = 2;
			poshod = true;
		}
		break;
	default:
		break;
	}
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutReshapeWindow(450, 450);
}
void display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	board();
	game();
	glFlush();
	glutSwapBuffers();
	whites = blacks = 0;
	for (i = 0; i < 64; i++)
	{
		if (desk[i].shash == white)
			whites++;
		if (desk[i].shash == black)
			blacks++;
	}
	if (blacks < 1 || whites < 1)
	{
		glutInitWindowSize(200, 100);
		glutInitWindowPosition(125, 200);
		glutCreateWindow("");
		glutDisplayFunc(finish);
		glutReshapeFunc(reshape_finish);
		glutKeyboardFunc(handleKeypress);
		glutMainLoop();
	}
}
void board()	//Создаем доску
{
	int i = 0, j = 0,
		d = 100; //Шаг отступа
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	for (j = 0; j < 8; j++)
	{
		if (j % 2 == 1)
			for (d = 0;d <= 300; d += 100)
			{
				glColor3f(1, 1, 0.5);
				glVertex2i(d + 25, j * 50 + 25);
				glVertex2i(50 + d + 25, j * 50 + 25);
				glVertex2i(50 + d + 25, j * 50 + 50 + 25);
				glVertex2i(d + 25, j * 50 + 50 + 25);

				glColor3f(0.5, 0.2, 0.1);
				glVertex2i(d + 50 + 25, j * 50 + 25);
				glVertex2i(100 + d + 25, j * 50 + 25);
				glVertex2i(100 + d + 25, j * 50 + 50 + 25);
				glVertex2i(d + 50 + 25, j * 50 + 50 + 25);
			}
		else
			for (d = 0;d <= 300; d += 100)
			{
				glColor3f(0.5, 0.2, 0.1);
				glVertex2i(d + 25, j * 50 + 25);
				glVertex2i(50 + d + 25, j * 50 + 25);
				glVertex2i(50 + d + 25, j * 50 + 50 + 25);
				glVertex2i(d + 25, j * 50 + 50 + 25);

				glColor3f(1, 1, 0.5);
				glVertex2i(d + 50 + 25, j * 50 + 25);
				glVertex2i(100 + d + 25, j * 50 + 25);
				glVertex2i(100 + d + 25, j * 50 + 50 + 25);
				glVertex2i(d + 50 + 25, j * 50 + 50 + 25);
			}
	}
	glColor3f(0.8, 0.3, 0.05);		//Рисуем рамку
	glVertex2i(0, 0);
	glVertex2i(0, 25);
	glVertex2i(450, 25);
	glVertex2i(450, 0);
	glVertex2i(0, 0);
	glVertex2i(0, 450);
	glVertex2i(25, 450);
	glVertex2i(25, 0);
	glVertex2i(0, 450);
	glVertex2i(0, 425);
	glVertex2i(450, 425);
	glVertex2i(450, 450);
	glVertex2i(450, 0);
	glVertex2i(450, 450);
	glVertex2i(425, 450);
	glVertex2i(425, 0);
	glEnd();
	char abc[16] = { 'A','B','C','D','E','F','G','H','1','2','3','4','5','6','7','8' };
	glColor3f(1, 1, 0.5);
	for (i = 0; i < 8; i++)			//Пишем координаты
	{
		std::string text;
		text = abc[i];
		drawText(text.data(), text.size(), 43 + 50 * i, 8);
		text = abc[i + 8];
		drawText(text.data(), text.size(), 8, 45 + 50 * i);
	}
}
void game()
{
	int i = 0;
	multi = -1;
	coordinates();
	coord_fig(white, 50);
	coord_fig(black, 300);
	figures();
	if (poshod)
	{
		hod();
		scan(white, black, desk);
		for (i = 0; i < 64; i++)
		{
			cop[i].name[0] = desk[i].name[0];
			cop[i].name[1] = desk[i].name[1];
			cop[i].shash = desk[i].shash;
			cop[i].queen = desk[i].queen;
			cop[i].border = desk[i].border;
			cop[i].chosen = desk[i].chosen;
			cop[i].comp = desk[i].comp;
			cop[i].lockcut = desk[i].lockcut;
		}
		if (desk[multi].lockcut  && was)
			colvo--;
	}
	if (colvo % 2 == 1)
	{
		multi = -1;
		was = false;
		hod_comp();
		colvo++;
		scan(black, white, desk);
		while (desk[multi].lockcut && was)
			hod_comp();
		for (i = 0; i < 64; i++)
		{
			cop[i].name[0] = desk[i].name[0];
			cop[i].name[1] = desk[i].name[1];
			cop[i].shash = desk[i].shash;
			cop[i].queen = desk[i].queen;
			cop[i].border = desk[i].border;
			cop[i].chosen = desk[i].chosen;
			cop[i].comp = desk[i].comp;
			cop[i].lockcut = desk[i].lockcut;
		}
		for (i = 0; i < 64; i++)
		{
			if (cop[i].shash == white)
				whites++;
			if (cop[i].shash = black)
				blacks++;
		}
		scan(white, black, desk);
	}
	glutPostRedisplay();
}
void coord_fig(color c, int y)
{
	int x, j = 0, col = 3, b = 0;
	if (colvo == 0)
	{
		if (c == black)
		{
			glColor3f(0, 0, 0);
			j++;
			col++;
		}
		else
			glColor3f(1, 1, 1);
		for (j; j < col; j++)
		{
			if (j % 2 == 1)
				for (x = 100; x < 425; x += 100)
				{

					for (b = 0; b < 64; b++)
					{
						if (desk[b].name[0] == x && desk[b].name[1] == y)
						{
							desk[b].shash = c;
							break;
						}
					}
				}
			else
				for (x = 50; x < 425; x += 100)
				{

					for (b = 0; b < 64; b++)
					{
						if (desk[b].name[0] == x && desk[b].name[1] == y)
						{
							desk[b].shash = c;
							break;
						}
					}
				}
			y += 50;
		}
	}
	else
	{
		return;
	}
}
void figures()
{
	for (int i = 0; i < 64; i++)
	{
		switch (desk[i].shash)
		{
		case (black):
			glColor3f(0, 0, 0);
			break;
		case (white):
			glColor3f(1, 1, 1);
			break;
		case (quadr):
			glColor3f(0.5, 0.2, 0.1);
			break;
		}
		if (desk[i].shash != empty)
		{
			glBegin(GL_TRIANGLE_FAN);
			glVertex2i(desk[i].name[0], desk[i].name[1]);
			for (int b = 0; b <= 100; b++)
			{
				float a = (float)b / (float)100 * M_PI * 2.0f;
				glVertex2i(desk[i].name[0] - cos(a) * 24, desk[i].name[1] - sin(a) * 24);
			}
			glEnd();
		}
		if (desk[i].shash == white)
			desk[i].comp = false;
		if (desk[i].border == true)
		{
			glLineWidth(5);
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] + 25);
			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] - 25);

			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] - 25);
			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] - 25);

			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] - 25);
			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] + 25);

			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] + 25);
			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] + 25);
			glEnd();
			glLineWidth(1);
		}
		if (desk[i].queen == true)
		{
			glColor3f(0, 1, 0);
			glBegin(GL_QUADS);
			glVertex2i(desk[i].name[0], desk[i].name[1] + 10);
			glVertex2i(desk[i].name[0] + 10, desk[i].name[1]);
			glVertex2i(desk[i].name[0], desk[i].name[1] - 10);
			glVertex2i(desk[i].name[0] - 10, desk[i].name[1]);
			glEnd();
		}
		if ((desk[i].chosen == true || desk[i].lockcut == true) && desk[i].shash == white)
		{
			glLineWidth(5);
			glBegin(GL_LINES);
			glColor3f(0, 0, 1);
			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] + 25);
			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] - 25);

			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] - 25);
			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] - 25);

			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] - 25);
			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] + 25);

			glVertex2i(desk[i].name[0] - 25, desk[i].name[1] + 25);
			glVertex2i(desk[i].name[0] + 25, desk[i].name[1] + 25);
			glEnd();
			glLineWidth(1);
		}
	}
	glBegin(GL_TRIANGLES);		// Рисуем курсор
	glColor3f(0.8, 0.3, 0.1);
	glVertex2i(point[0], point[1] - 20);
	glVertex2i(point[0] + 15, point[1] - 10);
	glVertex2i(point[0], point[1]);
	glEnd();
}
void drawText(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double matrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 450, 0, 450, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
void move(int button, int state, int x, int y)
{
	int i = 0;
	if (button == 0 && state == 0 && (click == 0 || click == 2))
	{
		cord[0] = x;
		cord[1] = abs(y - 450);

		if (x <= 25 || x >= 425 || y >= 425 || y <= 25)
		{
			poshod = false;
			return;
		}
		else
		{
			click = 1;
			for (i = 0; i < 64; i++)
			{
				if ((desk[i].name[0] - 25 < cord[0]) && (cord[0] < desk[i].name[0] + 25) && (desk[i].name[1] - 25 < cord[1]) && (cord[1] < desk[i].name[1] + 25))
				{

					desk[i].chosen = true;
					break;
				}
			}
		}
	}
	if (button == 2 && state == 0 && click == 1)
	{
		cord[2] = x;
		cord[3] = abs(y - 450);

		click = 0;
		if (x <= 25 || x >= 425 || y >= 425 || y <= 25)
		{
			for (i = 0; i < 64; i++)
			{
				if ((desk[i].name[0] - 25 < cord[0]) && (cord[0] < desk[i].name[0] + 25) && (desk[i].name[1] - 25 < cord[1]) && (cord[1] < desk[i].name[1] + 25))
				{
					desk[i].chosen = false;
					break;
				}
			}
			poshod = false;
		}
		else
			poshod = true;
	}
}
void coordinates()
{
	if (colvo == 0)
	{
		int i, j = 0, d = 50, count = 0;
		for (j = 0; j < 8; j++)
		{
			for (i = 0; i < 8; i++)
			{
				desk[count].name[0] = d*(i + 1);
				desk[count].name[1] = d*(j + 1);
				count++;
			}
		}
	}
	else
		return;
}
void hod()
{
	int b = 0, i = 0;
	if ((cord[0] <= 25 || cord[0] >= 425 || cord[1] >= 425 || cord[1] <= 25) && (cord[2] <= 25 || cord[2] >= 425 || cord[3] >= 425 || cord[3] <= 25))
	{
		for (i = 0; i < 64; i++)
		{
			if ((desk[i].name[0] - 25 < cord[0]) && (cord[0] < desk[i].name[0] + 25) && (desk[i].name[1] - 25 < cord[1]) && (cord[1] < desk[i].name[1] + 25))
			{
				desk[i].chosen = false;
				poshod = false;
				break;
			}
		}
		poshod = false;
		return;
	}

	for (i = 0; i < 64; i++)
	{
		if (desk[multi].lockcut)
		{
			if (multi == i)
			{
				b = i; // Переменную b не использовать
				cord[0] = desk[i].name[0];
				cord[1] = desk[i].name[1];
				if (block)
				{
					if (desk[b].lockcut == false)
					{
						desk[b].chosen = false;
						poshod = false;
						return;
					}
				}
				break;
			}
		}
		if ((desk[i].name[0] - 25 < cord[0]) && (cord[0] < desk[i].name[0] + 25) && (desk[i].name[1] - 25 < cord[1]) && (cord[1] < desk[i].name[1] + 25))
		{
			b = i; // Переменную b не использовать
			cord[0] = desk[i].name[0];
			cord[1] = desk[i].name[1];
			if (block)
			{
				if (desk[b].lockcut == false)
				{
					desk[b].chosen = false;
					poshod = false;
					return;
				}
			}
			break;
		}
	}
	for (i = 0; i < 64; i++)
	{
		if (((desk[i].name[0] - 25 < cord[2]) && (cord[2] < desk[i].name[0] + 25) && (desk[i].name[1] - 25 < cord[3]) && (cord[3] < desk[i].name[1] + 25)))
		{
			cord[2] = desk[i].name[0];
			cord[3] = desk[i].name[1]; // Переменную i не использовать
			if (block)
			{
				if (desk[i].border == false)
				{
					desk[b].chosen = false;
					poshod = false;
					return;
				}
			}
			break;
		}
	}

	if ((abs(cord[2] - cord[0]) == 50 && (cord[3] - cord[1]) == 50 && desk[b].comp != true) || (desk[i].border == true && abs(cord[2] - cord[0]) == 100 && abs(cord[3] - cord[1]) == 100) || desk[b].queen == true)
	{
		if ((desk[i].shash == quadr || desk[i].shash == empty) && (desk[b].shash == white))
		{
			if (desk[i].border == true && desk[b].queen != true)
			{
				for (int k = 0; k < 64; k++)
				{
					if (desk[k].name[0] == (cord[0] + (cord[2] - cord[0]) / 2))
					{
						if (desk[k].name[1] == (cord[1] + (cord[3] - cord[1]) / 2))
						{
							if (desk[k].shash == black)
							{
								desk[k].shash = quadr;
								desk[k].queen = false;
								break;
							}
						}
					}
				}
			}
			if (desk[b].queen == true)
			{
				if (abs(desk[i].name[0] - desk[b].name[0]) != abs(desk[i].name[1] - desk[b].name[1]))
				{
					desk[b].chosen = false;
					poshod = false;
					return;
				}
				int dx = 0,	// Расстояние между координатами для вычисления направлния пути и наличия срубленной шашки
					dy = 0,
					mx = 0,	// Координаты по х
					my = 0,	// Координаты по у
					nx = 0,
					ny = 0,
					j = 0,	// Счетчик
					k = 0;
				dx = desk[b].name[0] - desk[i].name[0];
				dy = desk[b].name[1] - desk[i].name[1];

				if (dx < 0)
					dx = 50;
				else
					dx = -50;
				if (dy < 0)
					dy = 50;
				else
					dy = -50;
				mx = desk[b].name[0] + dx;
				my = desk[b].name[1] + dy;
				while (mx != desk[i].name[0] && my != desk[i].name[1])
				{
					if (dx > 0)
						nx = mx + 50;
					else
						nx = mx - 50;

					if (dy > 0)
						ny = my + 50;
					else
						ny = my - 50;

					// проверка хода дамкой через белые шашки
					for (j = 0; j < 64; j++)
					{
						if (desk[j].name[0] == mx && desk[j].name[1] == my && desk[j].shash == white)
						{
							poshod = false;
							return;
						}
					}
					// если после черной шашки стоит еще одна шашка, то не можем кушать
					for (j = 0; j < 64; j++)
					{
						//
						if (desk[j].name[0] == mx && desk[j].name[1] == my && desk[j].shash == black)
						{
							for (k = 0; k < 64; k++)
							{
								if (desk[k].name[0] == nx && desk[k].name[1] == ny && (desk[k].shash == black || desk[k].shash == white))
								{
									poshod = false;
									return;
								}
							}
							if (desk[j].target == true)
							{
								desk[j].shash = quadr;
								desk[j].queen = false;
								j = 64;
								mx = desk[i].name[0];
							}
						}
					}
					if (mx == desk[i].name[0])
						break;
					if (dx < 0)
						dx -= 50;
					else
						dx += 50;
					if (dy < 0)
						dy -= 50;
					else
						dy += 50;
					mx = desk[b].name[0] + dx;
					my = desk[b].name[1] + dy;
				}
			}
			if (desk[b].lockcut)
				was = true;
			else
				was = false;
			desk[b].chosen = false;
			desk[i].shash = desk[b].shash;
			desk[i].queen = desk[b].queen;
			desk[b].queen = false;
			desk[i].comp = false;
			desk[b].shash = quadr;
			desk[b].comp = true;
			multi = i;
			if (desk[i].name[1] == 400 && desk[i].shash == white)
			{
				desk[i].queen = true;
			}
			colvo++;
		}
	}
	desk[b].chosen = false;
	poshod = false;
}
void scan(color bro, color enemy, options q[])
{
	int x, y, i, j, jj, k, kk, x1, y1; //Переменные для обычных шашек
	int d = 50, nx, ny, count, c, my, mx, d2 = 50;//Переменные для дамок
	block = false;
	for (i = 0; i < 64; i++)
	{
		q[i].border = false;
		q[i].lockcut = false;
		q[i].chosen = false;
		q[i].target = false;
	}
	for (i = 0; i < 64; i++)
	{
		if (q[i].shash == bro && q[i].queen == false)
		{
			for (j = 0; j < 4; j++)
			{
				switch (j)
				{
				case 0:
					x = q[i].name[0] + 50;
					y = q[i].name[1] + 50;
					break;
				case 1:
					x = q[i].name[0] + 50;
					y = q[i].name[1] - 50;
					break;
				case 2:
					x = q[i].name[0] - 50;
					y = q[i].name[1] - 50;
					break;
				case 3:
					x = q[i].name[0] - 50;
					y = q[i].name[1] + 50;
					break;
				}
				if (x > 25 && x < 425 && y < 425 && y > 25)
				{
					for (k = 0; k < 64; k++)
					{
						if (q[k].name[0] == x && q[k].name[1] == y && q[k].shash == enemy)
						{
							for (jj = 0; jj < 4; jj++)
							{
								switch (jj)
								{
								case 0:
									x1 = q[k].name[0] + 50;
									y1 = q[k].name[1] + 50;
									break;
								case 1:
									x1 = q[k].name[0] + 50;
									y1 = q[k].name[1] - 50;
									break;
								case 2:
									x1 = q[k].name[0] - 50;
									y1 = q[k].name[1] - 50;
									break;
								case 3:
									x1 = q[k].name[0] - 50;
									y1 = q[k].name[1] + 50;
									break;
								}
								if (x1 > 25 && x1 < 425 && y1 < 425 && y1 > 25)
								{
									for (kk = 0; kk < 64; kk++)
									{
										if (q[kk].name[0] == x1 && q[kk].name[0] != q[i].name[0] && q[kk].name[1] == y1 && q[kk].name[1] != q[i].name[1] && q[kk].shash != bro && q[kk].shash != enemy && kk != k)
										{
											q[kk].border = true;
											q[i].lockcut = true;
											q[k].target = true;
											block = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (q[i].queen == true && q[i].shash == bro)
		{
			for (count = 0; count < 8; count += 2)
			{
				mx = nx = q[i].name[0];
				my = ny = q[i].name[1];
				d2 = d = 50;
				while (ny < 450 && nx < 450 && ny > 25 && nx > 25)
				{
					for (c = 0; c < 64; c++)
					{
						if (q[c].name[0] == q[i].name[0] + period[count] * d && q[c].name[1] == q[i].name[1] + period[count + 1] * d && q[c].shash == enemy)
						{
							for (kk = 0; kk < 64; kk++)
							{
								if (q[c].name[0] + d2 * period[count] == q[kk].name[0] && q[c].name[1] + d2 * period[count + 1] == q[kk].name[1] && (q[kk].shash == enemy || q[kk].shash == bro))
								{
									mx = 500;
									nx = 500;
									kk = 64;
									c = 65;
								}
							}
							while (my < 425 && mx < 425 && my > 25 && mx >25)
							{
								for (j = 0; j < 64; j++)
								{

									if (q[j].name[0] == q[c].name[0] + period[count] * d2 && q[j].name[1] == q[c].name[1] + period[count + 1] * d2 && q[j].shash != enemy && q[j].shash != bro)
									{
										q[j].border = true;
										q[i].lockcut = true;
										q[c].target = true;
										block = true;
									}
								}
								if (mx == 500)
									break;

								if (mx == 500)
									break;
								d2 += 50;
								mx = mx + period[count] * 50;
								my = my + period[count + 1] * 50;
							}

						}
						if (q[c].name[0] == q[i].name[0] + period[count] * d && q[c].name[1] == q[i].name[1] + period[count + 1] * d && q[c].shash == bro)
						{
							c = 65;
							nx = 500;
						}
					}
					if (nx == 500)
						break;
					d += 50;
					nx = nx + period[count] * 50;
					ny = ny + period[count + 1] * 50;
				}
			}
		}
	}
	whites = blacks = 0;
	for (i = 0; i < 64; i++)
	{
		if (q[i].shash == white)
			whites++;
		if (q[i].shash == black)
			blacks++;
	}
}
void hod_comp()
{
	int i = 0, //Переменная под счетчик
		b = 0, //Шашка, которой ходим
		p = 0, //Счетчик массива направлений
		bb = 0, //Место, куда ходим
		bufi, //Запоминаем какой ходили,
		bsr = 0, //Шашка, которую срубили
		j = 0, ch = 0, count = 0, k = 0,
		mx = 0, nx = 0, my = 0, ny = 0, d = 0, d2 = 0, c = 0, kk = 0; //Переменные для нахождения координат или счетчики
	bool q = false; //Была ли срублена королева
	bufi = bufx = bufy = bufvalue = 0, bsr = 0;
	value = bufsr = -500;
	for (i = 0; i < 64; i++)
	{
		cop[i].name[0] = desk[i].name[0];
		cop[i].name[1] = desk[i].name[1];
		cop[i].shash = desk[i].shash;
		cop[i].queen = desk[i].queen;
		cop[i].border = desk[i].border;
		cop[i].chosen = desk[i].chosen;
		cop[i].comp = desk[i].comp;
		cop[i].lockcut = desk[i].lockcut;
	}
	scan(black, white, cop);
	for (i = 0; i < blacks; i++)
	{
		bsr = -50;
		if (block)
		{
			while (b < 64)
			{
				if (cop[b].lockcut == true && cop[b].queen != true)
				{
					for (p = 0; p < 8; p += 2)
					{
						bufx = cop[b].name[0] + period[p] * 50;
						bufy = cop[b].name[1] + period[p + 1] * 50;
						bb = 0;
						while (bb < 64)
						{
							if (cop[bb].name[0] == bufx && cop[bb].name[1] == bufy)
								break;
							bb++;
						}
						if (cop[bb].shash == white && abs(cop[b].name[0] - cop[bb].name[0]) == 50 && abs(cop[b].name[1] - cop[bb].name[1]) == 50 && cop[bb].target == true)
						{
							if (bb != 64)
							{
								cop[bb].comp = true;
								cop[bb].shash = quadr;
								bufx = cop[b].name[0] + period[p] * 100;
								bufy = cop[b].name[1] + period[p + 1] * 100;
								if (bufx > 0 && bufy > 0 && bufx < 450 && bufy < 450)
								{
									bsr = bb;
									if (cop[bb].queen == true)
									{
										bufvalue += Eat_queen;
										q = true;
									}
									else
									{
										bufvalue += Eat_simple;
										q = false;
									}
									cop[bb].queen = false;
									bb = 0;
									while (bb < 64)
									{
										if (cop[bb].name[0] == bufx && cop[bb].name[1] == bufy && (cop[bb].shash == empty || cop[bb].shash == quadr))
											break;
										bb++;
									}
									if (bb == 64)
									{
										cop[bsr].comp = false;
										cop[bsr].shash = white;
										break;
									}
									cop[bb].shash = cop[b].shash;
									cop[bb].queen = cop[b].queen;
									if (cop[bb].name[1] == 50)
									{
										cop[bb].queen = true;
										bufvalue += More_queens;
									}
									cop[b].shash = quadr;
									cop[b].queen = false;
									scan(black, white, cop);
									for (j = 0; j < 64; j++)
									{
										intel[j].name[0] = cop[j].name[0];
										intel[j].name[1] = cop[j].name[1];
										intel[j].shash = cop[j].shash;
										intel[j].queen = cop[j].queen;
										intel[j].border = cop[j].border;
										intel[j].chosen = cop[j].chosen;
										intel[j].comp = cop[j].comp;
										intel[j].lockcut = cop[j].lockcut;
									}
									for (ch = 0; ch < 64; ch++)
									{
										if (cop[ch].target)
											bufvalue -= Under_attack;
										else
											bufvalue += Save_move;
									}
									intelegent(Smart);
									if (bufvalue >= value)
									{
										bufsr = bsr;
										value = bufvalue;
										bufi = b;
										xx = cop[bb].name[0];
										yy = cop[bb].name[1];
									}
									cop[b].shash = cop[bb].shash;
									cop[b].queen = cop[bb].queen;
									cop[bsr].shash = white;
									if (q == true)
										cop[bb].queen = true;
									else
										cop[bb].queen = false;
									bufvalue = 0;
									scan(black, white, cop);
								}

							}
						}

					}
				}
				if (cop[b].lockcut == true && cop[b].queen == true)
				{
					for (count = 0; count < 8; count += 2)
					{
						mx = nx = cop[b].name[0];
						my = ny = cop[b].name[1];
						d2 = d = 50;
						while (ny < 450 && nx < 450 && ny > 25 && nx > 25)
						{
							for (c = 0; c < 64; c++)
							{
								if (cop[c].name[0] == cop[b].name[0] + period[count] * d && cop[c].name[1] == cop[b].name[1] + period[count + 1] * d && cop[c].target == true) // Если встречаем жертву
								{
									for (kk = 0; kk < 64; kk++)
									{
										if (cop[c].name[0] + d * period[count] == cop[kk].name[0] && cop[c].name[1] + d * period[count + 1] == cop[kk].name[1] && cop[kk].shash == white) // Есть ли за ней препятствие
										{
											mx = 0;
											nx = 500;
											kk = 64;
											c = 65;
										}
									}
									while (my < 450 && mx < 450 && my > 25 && mx >25)
									{
										for (j = 0; j < 64; j++)
										{
											if (cop[j].name[0] == cop[c].name[0] + period[count] * d2 && cop[j].name[1] == cop[c].name[1] + period[count + 1] * d2 && cop[j].border == true)
											{
												bsr = c;
												cop[c].shash = quadr;
												cop[c].comp = true;
												if (cop[c].queen == true)
												{
													bufvalue += Eat_queen;
													q = true;
												}
												else
												{
													bufvalue += Eat_simple;
													q = false;
												}
												cop[c].queen = false;
												cop[j].shash = cop[b].shash;
												cop[j].queen = cop[b].queen;
												cop[b].shash = quadr;
												cop[b].queen = false;
												scan(black, white, cop);
												for (bb = 0; bb < 64; bb++)
												{
													if (cop[bb].target)
														bufvalue -= Under_attack;
													else
														bufvalue += Save_move;
												}
												for (k = 0; k < 64; k++)
												{
													intel[k].name[0] = cop[k].name[0];
													intel[k].name[1] = cop[k].name[1];
													intel[k].shash = cop[k].shash;
													intel[k].queen = cop[k].queen;
													intel[k].border = cop[k].border;
													intel[k].chosen = cop[k].chosen;
													intel[k].comp = cop[k].comp;
													intel[k].lockcut = cop[k].lockcut;
												}
												intelegent(Smart);
												if (bufvalue >= value)
												{
													bufsr = bsr;
													value = bufvalue;
													bufi = b;
													xx = cop[j].name[0];
													yy = cop[j].name[1];
												}
												cop[b].shash = cop[bb].shash;
												cop[b].queen = cop[bb].queen;
												cop[bb].shash = quadr;
												if (q == true)
													cop[bb].queen = true;
												else
													cop[bb].queen = false;
												bufvalue = 0;

											}
										}
										d2 += 50;
										mx = mx + period[count] * 50;
										my = my + period[count + 1] * 50;
									}

								}
							}
							d += 50;
							nx = nx + period[count] * 50;
							ny = ny + period[count + 1] * 50;
						}
					}
				}
				b++;
			}
			break;
		}
		else
		{
			while (cop[b].shash != black)
				b++;
			for (p = 0; p < 4; p += 2)
			{
				bufx = cop[b].name[0] - period[p] * 50;
				bufy = cop[b].name[1] - period[p + 1] * 50;
				bb = 0;
				while (bb < 64)
				{
					if (cop[bb].name[0] == bufx && cop[bb].name[1] == bufy)
						break;
					bb++;
				}
				if (cop[bb].shash == quadr || cop[bb].shash == empty)
				{
					cop[bb].shash = cop[b].shash;
					cop[b].shash = quadr;
					cop[bb].queen = cop[b].queen;
					cop[b].queen = false;
					if (cop[bb].name[1] == 50)
					{
						cop[bb].queen = true;
						bufvalue += More_queens;
					}
					scan(white, black, cop);
					for (j = 0; j < 64; j++)
					{
						if (cop[j].target)
							bufvalue -= Under_attack;
						else
							bufvalue += Save_move;
					}
					for (j = 0; j < 64; j++)
					{
						intel[j].name[0] = cop[j].name[0];
						intel[j].name[1] = cop[j].name[1];
						intel[j].shash = cop[j].shash;
						intel[j].queen = cop[j].queen;
						intel[j].border = cop[j].border;
						intel[j].chosen = cop[j].chosen;
						intel[j].comp = cop[j].comp;
						intel[j].lockcut = cop[j].lockcut;
					}
					intelegent(Smart);
					if (bufvalue >= value)
					{
						value = bufvalue;
						bufi = b;
						xx = cop[bb].name[0];
						yy = cop[bb].name[1];
					}
					cop[b].shash = cop[bb].shash;
					cop[bb].shash = quadr;
					cop[b].queen = cop[bb].queen;
					cop[bb].queen = false;
					scan(black, white, cop);
					bufvalue = 0;
				}
			}
		}
		b++;
	}
	scan(black, white, desk);
	if (value == -500)
		finish();
	for (i = 0; i < 64; i++)
	{
		if (desk[i].name[0] == xx && desk[i].name[1] == yy)
			break;
	}
	if (desk[bufi].lockcut)
		was = true;
	else
		was = false;
	desk[i].shash = desk[bufi].shash;
	desk[bufi].shash = quadr;
	desk[i].queen = desk[bufi].queen;
	desk[bufi].queen = false;
	if (desk[i].name[1] == 50)
		desk[i].queen = true;
	multi = i;
	if (bufsr > 0)
	{
		desk[bufsr].shash = quadr;
		desk[bufsr].comp = true;
		desk[bufsr].queen = false;
	}
}
void intelegent(int deep)
{
	if (deep == 0)
		return;
	int i = 0, b = 0, p = 0, bb = 0, kolvo = 0, bx = 0, by = 0, j = 0, count = 0, busr = 0;
	int mx = 0, nx = 0, my = 0, ny = 0, d = 0, d2 = 0, c = 0, kk = 0;
	bool q = false;
	color bro, enemy;
	if (deep % 2 == 0)
	{
		bro = white;
		enemy = black;
		kolvo = whites;
	}
	else
	{
		bro = black;
		enemy = white;
		kolvo = blacks;
	}
	scan(bro, enemy, intel);
	for (i = 0; i < kolvo; i++)
	{
		busr = -50;
		q = false;
		if (block)
		{
			while (b < 64)
			{
				if (intel[b].lockcut == true && intel[b].queen != true)
				{
					for (p = 0; p < 8; p += 2)
					{
						bx = intel[b].name[0] + period[p] * 50;
						by = intel[b].name[1] + period[p + 1] * 50;
						bb = 0;
						while (bb < 64)
						{
							if (intel[bb].name[0] == bx && intel[bb].name[1] == by)
								break;
							bb++;
						}
						if (intel[bb].shash == enemy && abs(intel[b].name[0] - intel[bb].name[0]) == 50 && abs(intel[b].name[1] - intel[bb].name[1]) == 50)
						{
							busr = bb;
							intel[bb].comp = true;
							intel[bb].shash = quadr;
							if (intel[bb].queen)
							{
								if (intel[bb].shash == white)
									bufvalue += Eat_queen;
								else
									bufvalue -= Eat_queen;
								q = true;
							}
							else
							{
								if (intel[bb].shash == white)
									bufvalue += Eat_simple;
								else
									bufvalue -= Eat_simple;
								q = false;
							}
							intel[bb].queen = false;
							if (bb != 64)
							{
								bx = intel[b].name[0] + period[p] * 100;
								by = intel[b].name[1] + period[p + 1] * 100;
								if (bx > 0 && by > 0 && bx < 450 && by < 450)
								{
									bb = 0;
									while (bb < 64)
									{
										if (intel[bb].name[0] == bx && intel[bb].name[1] == by && (intel[bb].shash == empty || intel[bb].shash == quadr))
											break;
										bb++;
									}
									if (bb == 64)
										break;
									intel[bb].shash = intel[b].shash;
									intel[bb].queen = intel[b].queen;
									intel[b].shash = quadr;
									intel[b].queen = false;
									scan(enemy, bro, intel);
									for (j = 0; j < 64; j++)
									{
										if (intel[j].target)
											bufvalue -= Under_attack;
										else
											bufvalue += Save_move;
									}
									intelegent(deep - 1);
									intel[b].shash = intel[bb].shash;
									intel[bb].shash = quadr;
									intel[b].queen = intel[bb].queen;
									intel[bb].queen = false;
									intel[busr].comp = true;
									intel[busr].shash = quadr;
									if (q == true)
										intel[busr].queen = true;
								}

							}
						}

					}
				}
				if (intel[b].lockcut == true && intel[b].queen == true)
				{
					for (count = 0; count < 8; count += 2)
					{
						mx = nx = intel[b].name[0];
						my = ny = intel[b].name[1];
						d2 = d = 50;
						while (ny < 450 && nx < 450 && ny > 25 && nx > 25)
						{
							for (c = 0; c < 64; c++)
							{
								if (intel[c].name[0] == intel[b].name[0] + period[count] * d && intel[c].name[1] == intel[b].name[1] + period[count + 1] * d && intel[c].target == true) // Если встречаем жертву
								{
									for (kk = 0; kk < 64; kk++)
									{
										if (intel[c].name[0] + d * period[count] == intel[kk].name[0] && intel[c].name[1] + d * period[count + 1] == intel[kk].name[1] && intel[kk].shash == enemy) // Есть ли за ней препятствие
										{
											mx = 0;
											nx = 500;
											kk = 64;
											c = 65;
										}
									}
									while (my < 450 && mx < 450 && my > 25 && mx >25) // Препятствия нет, теперь ищем куда приземлиться 
									{
										for (j = 0; j < 64; j++)
										{
											if (intel[j].name[0] == intel[c].name[0] + period[count] * d2 && intel[j].name[1] == intel[c].name[1] + period[count + 1] * d2 && intel[j].border == true)
											{
												busr = c;
												intel[c].shash = quadr;
												intel[c].comp = true;
												if (intel[c].queen == true)
												{
													if (intel[c].shash == white)
														bufvalue += Eat_queen;
													else
														bufvalue -= Eat_queen;
													q = true;
												}
												else
												{
													if (intel[bb].shash == white)
														bufvalue += Eat_simple;
													else
														bufvalue -= Eat_simple;
													q = false;
												}
												intel[c].queen = false;
												intel[j].shash = intel[b].shash;
												intel[j].queen = intel[b].queen;
												intel[b].shash = quadr;
												intel[b].queen = false;
												scan(bro, enemy, intel);
												for (kk = 0; kk < 64; kk++)
												{
													if (intel[kk].target)
														bufvalue -= Under_attack;
													else
														bufvalue += Save_move;
												}
												intelegent(deep - 1);
												intel[b].shash = intel[bb].shash;
												intel[bb].shash = quadr;
												intel[b].queen = intel[bb].queen;
												intel[bb].queen = false;
												intel[busr].shash = quadr;
												intel[busr].comp = true;
												if (q == true)
													intel[busr].queen = true;
											}
										}
										d2 += 50;
										mx = mx + period[count] * 50;
										my = my + period[count + 1] * 50;
									}

								}
							}
							d += 50;
							nx = nx + period[count] * 50;
							ny = ny + period[count + 1] * 50;
						}
					}
				}
				b++;
			}
			break;
		}
		else
		{
			while (intel[b].shash != bro)
			{
				if (b == 64)
					break;
				b++;
			}
			if (b == 64)
				break;
			for (p = 0 + (deep + 1) % 2 * 4; p < 4 + (deep + 1) % 2 * 4; p += 2)
			{
				bx = intel[b].name[0] - period[p] * 50;
				by = intel[b].name[1] - period[p + 1] * 50;
				bb = 0;
				while (bb < 64)
				{
					if (intel[bb].name[0] == bx && intel[bb].name[1] == by)
						break;
					bb++;
				}
				if (intel[bb].shash == quadr || intel[bb].shash == empty)
				{
					intel[bb].shash = intel[b].shash;
					intel[b].shash = quadr;
					if (by == 50 && intel[b].queen != true)
					{
						intel[bb].queen = true;
						bufvalue += More_queens;
						q = true;
					}
					intel[b].queen = false;
					scan(enemy, bro, intel);
					for (j = 0; j < 64; j++)
					{
						if (intel[j].target)
						{
							bufvalue -= Under_attack;
							if (intel[j].queen)
								bufvalue -= More_queens;
						}
						else
						{
							bufvalue += Save_move;
							if (intel[j].queen)
								bufvalue += Queen_move;
						}
					}
					intelegent(deep - 1);
					intel[b].shash = intel[bb].shash;
					intel[bb].shash = quadr;
					if (q)
						intel[b].queen = false;
					else
						intel[b].queen = intel[bb].queen;
					intel[bb].queen = false;
					scan(bro, enemy, intel);
				}
			}
		}
		b++;
	}
}
void finish()
{
	glClear(GL_COLOR_BUFFER_BIT);
	char *abc;
	if (blacks < whites)
		abc = "YOU'RE WINNER!";
	else
		abc = "YOU'RE LOSER!";
	glColor3f(1, 0, 0);
	std::string text;
	text = abc;
	drawText(text.data(), text.size(), 100, 230);
	glFlush();
	glutSwapBuffers();
}
void reshape_finish(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutReshapeWindow(200, 100);
}
