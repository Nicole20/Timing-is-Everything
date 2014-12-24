// Timing is Everything.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<glut.h>
#include<freeglut.h>

using namespace std;

void initialize();
void draw();
void drawScore();

void Timer(int value);
void mouse(int button, int state, int x, int y);

int blockx = 0, blocky = 0, points = 0, sec = 1000;
bool right_x = false;
char *score = { "Score = " };
char *numbers = { "0123456789" };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Timing is Everything");

	initialize();

	glutDisplayFunc(draw);
	glutMouseFunc(mouse);

	glutTimerFunc(sec, Timer, 0);

	glutMainLoop();

	return 0;
}

void initialize()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 9, 0, 9);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 4; i++)
	{
		if (blockx == i)
		{
			glColor3f(1, 1, 0);
		}
		else
		{
			glColor3f(0.4, 0.4, 0);
		}
		glBegin(GL_QUADS);
		glVertex2f(i, i);
		glVertex2f(i + 1, i);
		glVertex2f(i + 1, i + 1);
		glVertex2f(i, i + 1);
		glEnd();
	}

	for (int i = 0; i < 4; i++)
	{
		if (blockx == i + 5)
		{
			glColor3f(1, 1, 0);
		}
		else
		{
			glColor3f(0.4, 0.4, 0);
		}
		glBegin(GL_QUADS);
		glVertex2f(i + 5, 3 - i);
		glVertex2f(i + 6, 3 - i);
		glVertex2f(i + 6, 4 - i);
		glVertex2f(i + 5, 4 - i);
		glEnd();
	}

	if (blockx == 4)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		glColor3f(0.4, 0, 0);
	}

	glBegin(GL_QUADS);
	glVertex2f(4, 4);
	glVertex2f(4, 5);
	glVertex2f(5, 5);
	glVertex2f(5, 4);
	glEnd();

	drawScore();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void drawScore()
{
	glColor3f(0, 0, 0);
	glRasterPos2f(1, 7);

	for (int i = 0; i < 8; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
	}

	if (points < 10)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[points]);
	}
	else
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[points / 10]);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[points % 10]);
	}
}

void Timer(int value)
{
	if (blockx == 8)
	{
		right_x = false;
	}
	if (blockx == 0)
	{
		right_x = true;
	}

	if (blockx >= 4)
	{
		blocky--;
	}
	else
	{
		blocky++;
	}

	if (right_x)
	{
		blockx++;
	}
	else
	{
		blockx--;
	}

	glutTimerFunc(sec, Timer, 0);
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (blockx == 4)
			{
				points++;
				if (sec > 950)
				{
					sec = sec - 10;
				}
				else if (sec > 800)
				{
					sec = sec - 20;
				}
				else if (sec > 600)
				{
					sec = sec - 25;
				}
				else if (sec > 100)
				{
					sec = sec - 50;
				}
			}
			else
			{
				points = 0;
				blockx = 0;
				blocky = 0;
				sec = 1000;
			}
		}
	}
}
