#include "final.h"
#include "Purin.h"
#include <iostream>
#include "main_function.h"
using namespace std;
int current_level = 1;
Purin my_map = Purin(current_level);
bool clicked = false;
void special_key_func(int key, int x, int y)
{
	if (!clicked)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		my_map.display();
		clicked = true;
		return;
	}
	switch (key)
	{
		case GLUT_KEY_UP:
			cout << "UP" << endl;
			my_map.move(0, 1);
			break;
		case GLUT_KEY_DOWN:
			cout << "DOWN" << endl;
			my_map.move(0, -1);
			break;
		case GLUT_KEY_LEFT:
			cout << "LEFT" << endl;
			my_map.move(-1, 0);
			break;
		case GLUT_KEY_RIGHT:
			cout << "RIGHT" << endl;
			my_map.move(1, 0);
			break;
		default:
			cout << key << endl;
			break;
	}
	my_map.print_step();
	if (current_level < 6)
	{
		if (my_map.finished())
		{
			rect(1, 1, 1, 600, 600, 100, 100, true);
			rect(0, 0, 0, 600, 600, 100, 100, false);

			glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(260, 25, 0);
			glScalef(0.5, 0.5, 1);
			char str[] = "CLEARED!";
			for (int i = 0; i < 8; i++)
			{
				glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
			}

			glPopMatrix();
			rect(0, 0, 0, 600, 600, 100, 100, false);
			fatdin();
		}
	}
	else
	{
		fatdin();
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(100, 680, 0);
		glScalef(0.4, 0.4, 1);
		char str[] = "ALL LEVEL CLEARED";
		for (int i = 0; i < 18; i++)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
		}

		glPopMatrix();
		glFlush();
	}
}
void keyboard_func(unsigned char key, int x, int y)
{
	if (key == 32 || key == 13)
	{
		if (my_map.finished())
		{
			next_level();
		}
		else
		{
			glClear(GL_COLOR_BUFFER_BIT);
			my_map.display();
		}
	}
}
void next_level()
{
	glClear(GL_COLOR_BUFFER_BIT);
	current_level++;
	if (current_level < 6)
	{
		my_map = Purin(current_level);
		my_map.display();
	}
	else
	{
		fatdin();
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(100, 680, 0);
		glScalef(0.4, 0.4, 1);
		char str[] = "ALL LEVEL CLEARED";
		for (int i = 0; i < 18; i++)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
		}

		glPopMatrix();
		glFlush();
	}
}
void menu(int value)
{
	switch (value)
	{
		case 1:
			if (my_map.finished())
			{
				next_level();
			}
			break;
		case 2:
			if (clicked)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				my_map = Purin(current_level);
				my_map.display();
			}
			break;
		default:
			break;
	}
}
void winReshapeFcn_final(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);
}

void on_click_function(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		clicked = true;
		my_map.display();
	}
}
void display_final()
{
	if (!clicked)
	{
		home_page();
	}
	else
	{
		my_map.display();
	}
}
void home_page()
{
	fatdin();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(80, 680, 0);
	glScalef(0.6, 0.6, 1);
	char str[] = "CLICK TO START";
	for (int i = 0; i < 15; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}

	glPopMatrix();
	glFlush();
}
void init_final()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Quiz3-1");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 800, 0, 800);
	glClear(GL_COLOR_BUFFER_BIT);
}
void red_ball(int x, int y)
{
	const GLfloat r = BLOCK_SIZE / 2;
	const GLfloat X = x + r, Y = y + r;
	partial_circle(1.0, 0.0, 0.0, r, X, Y, 180, 0, true);
	circle(0.0, 0.0, 0.0, r, X, Y, false);

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(X + r, Y);
	glVertex2f(X - r, Y);
	glEnd();

	circle(0.0, 0.0, 0.0, r * 2 / 5, X, Y, true);
	circle(1.0, 1.0, 1.0, r * 4 / 15, X, Y, true);
	glLineWidth(1);
	circle(0.0, 0.0, 0.0, r * 2 / 15, X, Y, false);
	glFlush();
}
void orange_ball(int x, int y)
{
	const GLfloat r = BLOCK_SIZE / 2;
	const GLfloat X = x + r, Y = y + r;
	glLineWidth(1);
	partial_circle(1.0, 0.6, 0.0, r, X, Y, 180, 0, true);
	circle(0.0, 0.0, 0.0, r, X, Y, false);
	partial_circle(0.0, 0.0, 0.0, r, X, Y, 40, 70, true);

	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glVertex2f(X + r * cos(2 * 3.14 / 360 * 70), Y + r * sin(2 * 3.14 / 360 * 70));
	glVertex2f(X, Y);
	glVertex2f(X + r * cos(2 * 3.14 / 360 * 110), Y + r * sin(2 * 3.14 / 360 * 110));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(X + r, Y);
	glVertex2f(X - r, Y);
	glEnd();
	circle(0.0, 0.0, 0.0, r * 2 / 5, X, Y, true);
	circle(1.0, 1.0, 1.0, r * 4 / 15, X, Y, true);
	glLineWidth(1);
	circle(0.0, 0.0, 0.0, r * 2 / 15, X, Y, false);
	glFlush();
}
void grass(int x, int y)
{
	const int n = 1000;
	const GLfloat r = 30 / 2;
	const GLfloat X = x + r, Y = y + r;
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(5 + X + r * cos(2 * 3.14 / n * i), 15 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(10 + X + r * cos(2 * 3.14 / n * i), 18 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(15 + X + r * cos(2 * 3.14 / n * i), 20 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 + X + r * cos(2 * 3.14 / n * i), 18 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(25 + X + r * cos(2 * 3.14 / n * i), 15 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 + X + r * cos(2 * 3.14 / n * i), 12 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(15 + X + r * cos(2 * 3.14 / n * i), 12 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(10 + X + r * cos(2 * 3.14 / n * i), 12 + Y + r * sin(2 * 3.14 / n * i));
	}
	glEnd();

	//花1
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(8 + X + (r / 5)*cos(2 * 3.14 / n * i), 18.3 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(9 + X + (r / 5)*cos(2 * 3.14 / n * i), 19.3 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(10 + X + (r / 5)*cos(2 * 3.14 / n * i), 18.3 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(9.5 + X + (r / 5)*cos(2 * 3.14 / n * i), 17 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(8.5 + X + (r / 5)*cos(2 * 3.14 / n * i), 17 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(9 + X + (r / 8)*cos(2 * 3.14 / n * i), 18 + Y + (r / 8)*sin(2 * 3.14 / n * i));
	}
	glEnd();

	//花2
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(17 + X + (r / 5)*cos(2 * 3.14 / n * i), 11.3 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(18 + X + (r / 5)*cos(2 * 3.14 / n * i), 12.3 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(19 + X + (r / 5)*cos(2 * 3.14 / n * i), 11.3 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(18.5 + X + (r / 5)*cos(2 * 3.14 / n * i), 10 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(17.5 + X + (r / 5)*cos(2 * 3.14 / n * i), 10 + Y + (r / 5)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(18 + X + (r / 8)*cos(2 * 3.14 / n * i), 11 + Y + (r / 8)*sin(2 * 3.14 / n * i));
	}
	glEnd();
	glFlush();
}
void orange_microphone(int x, int y)
{
	const GLfloat height = BLOCK_SIZE * 2 / 3;
	const GLfloat width = BLOCK_SIZE / 6;

	rect(0.0, 0.0, 0.0, height, width, x + (BLOCK_SIZE - width) / 2, y + BLOCK_SIZE / 15, true);
	circle(1.0, 0.8, 0.4, width, x + BLOCK_SIZE / 2, y + BLOCK_SIZE * 3 / 4, true);
	rect(0.5, 0.5, 0.5, BLOCK_SIZE / 15, width, x + (BLOCK_SIZE - width) / 2, y + BLOCK_SIZE * 15 / 30, true);
	rect(0.5, 0.5, 0.5, BLOCK_SIZE / 15, width, x + (BLOCK_SIZE - width) / 2, y + BLOCK_SIZE * 12 / 30, true);
}
void red_microphone(int x, int y)
{
	const GLfloat height = BLOCK_SIZE * 2 / 3;
	const GLfloat width = BLOCK_SIZE / 6;

	rect(0.0, 0.0, 0.0, height, width, x + (BLOCK_SIZE - width) / 2, y + BLOCK_SIZE / 15, true);
	circle(1.0, 0.0, 0.0, width, x + BLOCK_SIZE / 2, y + BLOCK_SIZE * 3 / 4, true);
	rect(0.5, 0.5, 0.5, BLOCK_SIZE / 15, width, x + (BLOCK_SIZE - width) / 2, y + BLOCK_SIZE * 15 / 30, true);
	rect(0.5, 0.5, 0.5, BLOCK_SIZE / 15, width, x + (BLOCK_SIZE - width) / 2, y + BLOCK_SIZE * 12 / 30, true);
}
void babydin(int x, int y)
{
	const GLfloat r = BLOCK_SIZE / 2;
	const GLfloat X = x + r;
	const GLfloat Y = y + r;

	glColor3f(0.0, 0.0, 0.0); //left
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X - r / 5) + (r / 6)*cos(2 * 3.14 / 360 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //left
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X - r / 5) + (r / 6)*cos(2 * 3.14 / 360 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X + r / 5) + (r / 6)*cos(2 * 3.14 / 360 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //right
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X + r / 5) + (r / 6)*cos(2 * 3.14 / 360 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //mid
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(X + (r / 6)*cos(2 * 3.14 / 360 * i), (Y + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //mid
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(X + (r / 6)*cos(2 * 3.14 / 360 * i), (Y + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	//body
	glLineWidth(2);
	circle(0, 0, 0, r / 1.8, X, Y, false);

	glColor3f(0.0, 0.0, 0.0); //left foot
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X - r / 4) + (r / 5)*cos(2 * 3.14 / 360 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //left foot
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X - r / 4) + (r / 5)*cos(2 * 3.14 / 360 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right foot
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X + r / 4) + (r / 5)*cos(2 * 3.14 / 360 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //right foot
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 5)*cos(2 * 3.14 / 1000 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	//body
	circle(1.0, 0.7, 0.75, r / 1.8, X, Y, true);

	glColor3f(0.0, 0.0, 0.0); //left head
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(X - r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X - r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X - r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X - r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //left head
	glBegin(GL_POLYGON);
	glVertex2f(X - r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X - r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X - r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right head
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(X + r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X + r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X + r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X + r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //right head
	glBegin(GL_POLYGON);
	glVertex2f(X + r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X + r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X + r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP); //hair

	for (float i = 200; i < 1700; i++)
	{
		glVertex2f(X + (r / 5 - (i / 500))*cos(2 * 3.14 / 1000 * i), (Y + r / 15 * 5) + (r / 5 - (i / 500))*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //left eye
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.3, 0.3); //left eye red
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //left eye black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 16)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 16)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0); //left eye white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 3.3) + (r / 20)*cos(2 * 3.14 / 1000 * i), (Y + r / 10) + (r / 20)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right eye
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.3, 0.3); //right eye red
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right eye black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 16)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 16)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0); //right eye white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4.75) + (r / 20)*cos(2 * 3.14 / 1000 * i), (Y + r / 10) + (r / 20)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP); //mouth

	for (float i = 550; i < 900; i++)
	{
		glVertex2f((X - r / 10) + (r / 10)*cos(2 * 3.14 / 1000 * i), (Y - r / 8) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	for (float i = 550; i < 950; i++)
	{
		glVertex2f((X + r / 10) + (r / 10)*cos(2 * 3.14 / 1000 * i), (Y - r / 8) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();
	glFlush();
}

void fatdin()
{
	const int n = 10000;
	glColor3ub(255, 192, 203);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(280 + 80 * cos(2 * 3.14 / n * i), 130 + 30 * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(280 + 80 * cos(2 * 3.14 / n * i), 130 + 30 * sin(2 * 3.14 / n * i));
	}
	glEnd();

	glColor3ub(255, 192, 203);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(520 + 80 * cos(2 * 3.14 / n * i), 130 + 30 * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(520 + 80 * cos(2 * 3.14 / n * i), 130 + 30 * sin(2 * 3.14 / n * i));
	}
	glEnd();
	glColor3ub(255, 192, 203); //右耳
	glBegin(GL_POLYGON);
	for (int i = 0; i < 3; i++)
		glVertex2f(210 + 110 * sin(2 * 3.14 / 3 * i + 1.1*3.14), 580 + 110 * cos(2 * 3.14 / 3 * i + 1.1*3.14));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 3; i++)
		glVertex2f(210 + 110 * sin(2 * 3.14 / 3 * i + 1.1*3.14), 580 + 110 * cos(2 * 3.14 / 3 * i + 1.1*3.14));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 3; i++)
		glVertex2f(200 + 65 * sin(2 * 3.14 / 3 * i + 1.1*3.14), 590 + 65 * cos(2 * 3.14 / 3 * i + 1.1*3.14));
	glEnd();

	glColor3ub(255, 192, 203);//左耳
	glBegin(GL_POLYGON);
	for (int i = 0; i < 3; i++)
		glVertex2f(590 + 110 * sin(2 * 3.14 / 3 * i + 1.58*3.14), 580 + 110 * cos(2 * 3.14 / 3 * i + 1.58*3.14));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 3; i++)
		glVertex2f(590 + 110 * sin(2 * 3.14 / 3 * i + 1.58*3.14), 580 + 110 * cos(2 * 3.14 / 3 * i + 1.58*3.14));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 3; i++)
		glVertex2f(600 + 65 * sin(2 * 3.14 / 3 * i + 1.58*3.14), 590 + 65 * cos(2 * 3.14 / 3 * i + 1.58*3.14));
	glEnd();
	glColor3ub(255, 192, 203);	//胖丁的身體
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(400 + 250 * cos(2 * 3.14 / n * i), 370 + 250 * sin(2 * 3.14 / n * i));
	glEnd();
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(400 + 250 * cos(2 * 3.14 / n * i), 370 + 250 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3f(1.0, 1.0, 1.0);	//左眼
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(280 + 60 * cos(2 * 3.14 / n * i), 420 + 60 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3ub(0, 199, 140);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(280 + 50 * cos(2 * 3.14 / n * i), 420 + 50 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3ub(3, 168, 158);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(273 + 35 * cos(2 * 3.14 / n * i), 432 + 35 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(262 + 15 * cos(2 * 3.14 / n * i), 449 + 15 * sin(2 * 3.14 / n * i));
	glEnd();

	glColor3f(1.0, 1.0, 1.0);	//右眼
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(520 + 60 * cos(2 * 3.14 / n * i), 420 + 60 * sin(2 * 3.14 / n * i));
	glEnd();

	glColor3ub(0, 199, 140);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(520 + 50 * cos(2 * 3.14 / n * i), 420 + 50 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3ub(3, 168, 158);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(513 + 35 * cos(2 * 3.14 / n * i), 432 + 35 * sin(2 * 3.14 / n * i));
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(505 + 15 * cos(2 * 3.14 / n * i), 449 + 15 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3ub(255, 99, 71);
	glBegin(GL_POLYGON);
	curve(350, 400, 450, 300, 220, 300);
	glEnd();
	glColor3ub(255, 192, 203);//右手
	glBegin(GL_POLYGON);
	curve(170, 50, 180, 370, 320, 270);

	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	curve(170, 50, 180, 370, 320, 270);
	glEnd();

	glColor3ub(255, 192, 203);//左手
	glBegin(GL_POLYGON);
	curve(630, 750, 630, 370, 400, 270);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	curve(630, 750, 630, 370, 400, 270);
	glEnd();
	glColor3ub(255, 192, 203);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 3 * n / 5; i++)
		glVertex2f(350 + 70 * cos(2 * 3.14 / n * i + 3.14 / 4), 572 + 70 * sin(2 * 3.14 / n * i + 3.14 / 4));
	glEnd();
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 3 * n / 5; i++)
		glVertex2f(350 + 70 * cos(2 * 3.14 / n * i + 3.14 / 4), 572 + 70 * sin(2 * 3.14 / n * i + 3.14 / 4));
	glEnd();
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = n / 2; i < 1.3*n; i++)
		glVertex2f(357 + 35 * cos(2 * 3.14 / n * i + 0.3*3.14), 534 + 35 * sin(2 * 3.14 / n * i + 0.3*3.14));
	glEnd();
	glColor3ub(48, 128, 20);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(62 + 30 * cos(2 * 3.14 / n * i), 380 + 30 * sin(2 * 3.14 / n * i));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(50, 360);
	glVertex2f(75, 360);
	glVertex2f(75, 250);
	glVertex2f(50, 250);
	glEnd();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(50, 350);
	glVertex2f(75, 350);
	glVertex2f(75, 330);
	glVertex2f(50, 330);
	glEnd();
	glFlush();
}
void babydin_fail(int x, int y)
{
	const GLfloat r = BLOCK_SIZE / 2;
	const GLfloat X = x + r;
	const GLfloat Y = y + r;

	glColor3f(0.0, 0.0, 0.0); //left
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X - r / 5) + (r / 6)*cos(2 * 3.14 / 360 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //left
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f((X - r / 5) + (r / 6)*cos(2 * 3.14 / 360 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 360 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 5) + (r / 6)*cos(2 * 3.14 / 1000 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //right
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 5) + (r / 6)*cos(2 * 3.14 / 1000 * i), ((Y - r / 10) + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //mid
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f(X + (r / 6)*cos(2 * 3.14 / 1000 * i), (Y + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //mid
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f(X + (r / 6)*cos(2 * 3.14 / 1000 * i), (Y + r / 1.55) + (r / 5.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP); //body

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f(X + (r / 1.8)*cos(2 * 3.14 / 1000 * i), Y + (r / 1.8)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //left foot
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 5)*cos(2 * 3.14 / 1000 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //left foot
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 5)*cos(2 * 3.14 / 1000 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right foot
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 5)*cos(2 * 3.14 / 1000 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //right foot
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 5)*cos(2 * 3.14 / 1000 * i), (Y - r / 15 * 7.5) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //body
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f(X + (r / 1.8)*cos(2 * 3.14 / 1000 * i), Y + (r / 1.8)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //left head
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(X - r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X - r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X - r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X - r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //left head
	glBegin(GL_POLYGON);
	glVertex2f(X - r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X - r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X - r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right head
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(X + r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X + r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X + r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X + r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(1.0, 0.7, 0.75); //right head
	glBegin(GL_POLYGON);
	glVertex2f(X + r / 15 * 7.5, Y + r / 15 * 1);
	glVertex2f(X + r / 15 * 10, Y - r / 15 * 3.5);
	glVertex2f(X + r / 15 * 6.5, Y - r / 15 * 2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP); //hair

	for (float i = 200; i < 1700; i++)
	{
		glVertex2f(X + (r / 5 - (i / 500))*cos(2 * 3.14 / 1000 * i), (Y + r / 15 * 5) + (r / 5 - (i / 500))*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //left eye
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.3, 0.3); //left eye red
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //left eye black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 4) + (r / 16)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 16)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0); //left eye white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 3.3) + (r / 20)*cos(2 * 3.14 / 1000 * i), (Y + r / 10) + (r / 20)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right eye
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 0.3, 0.3); //right eye red
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 9.5)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 9.5)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //right eye black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4) + (r / 16)*cos(2 * 3.14 / 1000 * i), (Y + r / 15) + (r / 16)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0); //right eye white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 4.75) + (r / 20)*cos(2 * 3.14 / 1000 * i), (Y + r / 10) + (r / 20)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP); //mouth

	for (float i = 0; i < 500; i++)
	{
		glVertex2f((X)+(r / 10)*cos(2 * 3.14 / 1000 * i), (Y - r / 6) + (r / 10)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.6, 0.9, 1.0); //right tear
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X + r / 3) + (r / 18)*cos(2 * 3.14 / 1000 * i), (Y - r / 50) + (r / 28)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();

	glColor3f(0.6, 0.9, 1.0); //left tear
	glBegin(GL_POLYGON);
	for (int i = 0; i < 1000; i++)
	{
		glVertex2f((X - r / 2.85) + (r / 18)*cos(2 * 3.14 / 1000 * i), (Y - r / 50) + (r / 28)*sin(2 * 3.14 / 1000 * i));
	}
	glEnd();
	glFlush();
}