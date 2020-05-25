#include "final.h"
#include "Purin.h"
#include <fstream>
#include "main_function.h"
#include <iostream>
#include <stdio.h>
using namespace std;

Purin::Purin(int n)
{
	fail = false;
	finish = false;
	step_count = 0;
	ifstream inp;
	char filename[11];
	sprintf_s(filename, "level%d.txt", n);
	inp.open(filename);
	for (int y = 9; y >= 0; y--)
	{
		for (int x = 0; x < 10; x++)
		{
			inp >> map[x][y];
			if (map[x][y] == PURIN)
			{
				purin_x = x;
				purin_y = y;
				map[x][y] = 0;
			}
		}
	}
	inp.close();
}
void Purin::display()
{
	if (finish)
	{
		print_step();
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

		glFlush();
		return;
	}
	glColor3f(1, 0, 0);
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			rect(0, 0, 0, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y, 0);

			switch (map[x][y])
			{
				case ORANGE_BALL:
					orange_ball(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case RED_BALL:
					red_ball(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case GRASS:
					grass(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case ORANGE_MICROPHONE:
					orange_microphone(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case RED_MICROPHONE:
					red_microphone(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case ORANGE_BALL + ORANGE_MICROPHONE:
					orange_microphone(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					orange_ball(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case ORANGE_BALL + RED_MICROPHONE:
					red_microphone(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					orange_ball(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case RED_BALL + ORANGE_MICROPHONE:
					orange_microphone(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					red_ball(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				case RED_BALL + RED_MICROPHONE:
					red_microphone(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					red_ball(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
					break;
				default:
					if (x == purin_x && y == purin_y)
					{
						if (fail)
						{
							babydin_fail(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
							glPushMatrix();
							rect(1, 1, 1, 90, 800, 0, 710, true);
							glColor3f(0, 0, 0);
							glTranslatef(325, 25, 0);
							glScalef(0.5, 0.5, 1);
							char str[] = "failed";
							for (int i = 0; i < 6; i++)
							{
								glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
							}

							glPopMatrix();
							glFlush();
						}
						else
						{
							babydin(100 + BLOCK_SIZE * x, 100 + BLOCK_SIZE * y);
						}
					}
					break;
			}
		}
	}
	print_step();
	glFlush();
}
void Purin::print_step()
{
	glPushMatrix();
	rect(1, 1, 1, 90, 800, 0, 710, true);
	glColor3f(0, 0, 0);
	glTranslatef(0, 750, 0);
	glScalef(0.5, 0.5, 1);
	char step[25], str[] = "STEPS";
	sprintf_s(step, "%d", step_count);
	cout << step_count << endl;
	for (int i = 0; i < strlen(step); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, step[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}

	glPopMatrix();
	glFlush();
}
bool Purin::finished()
{
	for (int y = 9; y >= 0; y--)
	{
		for (int x = 0; x < 10; x++)
		{
			if (map[x][y] == RED_BALL || map[x][y] == ORANGE_BALL || map[x][y] == ORANGE_BALL + RED_MICROPHONE || map[x][y] == RED_MICROPHONE || map[x][y] == ORANGE_MICROPHONE)
			{
				return false;
			}
		}
	}
	finish = true;
	return true;
}
bool Purin::move(int x_offset, int y_offset)
{
	if (finish || fail)
	{
		return false;
	}
	cout << "X: " << purin_x << endl;
	cout << "Y: " << purin_y << endl;

	int purin;
	if (x_offset)
	{
		purin = purin_x;
		if (purin_x + x_offset == 10 || purin_x + x_offset == -1)
		{
			return false;
		}
	}
	if (y_offset)
	{
		purin = purin_y;
		if (purin_y + y_offset == 10 || purin_y + y_offset == -1)
		{
			return false;
		}
	}
	cout << purin << endl;

	if (purin <= 9 && purin >= 0)
	{
		if (map[purin_x + x_offset][purin_y + y_offset] == GRASS)
		{
			return false;
		}
		if (map[purin_x + x_offset][purin_y + y_offset] >= ORANGE_BALL)
		{
			if (purin == 8 && (x_offset + y_offset == 1))
			{
				return false;
			}
			else if (purin == 1 && (x_offset + y_offset == -1))
			{
				return false;
			}
			else
			{
				if (map[purin_x + x_offset * 2][purin_y + y_offset * 2] == GRASS)
				{
					return false;
				}
				else if (map[purin_x + x_offset * 2][purin_y + y_offset * 2] >= ORANGE_BALL && map[purin_x + x_offset * 2][purin_y + y_offset * 2] != 8888)
				{
					return false;
				}
				else
				{
					rect(1, 1, 1, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y, true);
					rect(0, 0, 0, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y, false);
					switch (map[purin_x][purin_y])
					{
						case ORANGE_MICROPHONE:
							orange_microphone(100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y);
							break;
						case RED_MICROPHONE:
							red_microphone(100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y);
							break;
						default:
							break;
					}
					rect(1, 1, 1, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * (purin_x + x_offset), 100 + BLOCK_SIZE * (purin_y + y_offset), true);
					rect(0, 0, 0, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * (purin_x + x_offset), 100 + BLOCK_SIZE * (purin_y + y_offset), false);

					char str[] = "failed";
					switch (map[purin_x + x_offset][purin_y + y_offset])
					{
						case ORANGE_BALL:
							orange_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							map[purin_x + x_offset][purin_y + y_offset] -= ORANGE_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += ORANGE_BALL;
							break;
						case RED_BALL:
							cout << "RED" << endl;
							red_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							map[purin_x + x_offset][purin_y + y_offset] -= RED_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += RED_BALL;
							break;
						case ORANGE_BALL + ORANGE_MICROPHONE:
							orange_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							orange_microphone(100 + BLOCK_SIZE * (purin_x + x_offset * 1), 100 + BLOCK_SIZE * (purin_y + y_offset * 1));
							map[purin_x + x_offset][purin_y + y_offset] -= ORANGE_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += ORANGE_BALL;
							break;
						case ORANGE_BALL + RED_MICROPHONE:
							orange_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							red_microphone(100 + BLOCK_SIZE * (purin_x + x_offset * 1), 100 + BLOCK_SIZE * (purin_y + y_offset * 1));
							map[purin_x + x_offset][purin_y + y_offset] -= ORANGE_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += ORANGE_BALL;
							break;
						case RED_BALL + ORANGE_MICROPHONE:
							red_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							orange_microphone(100 + BLOCK_SIZE * (purin_x + x_offset * 1), 100 + BLOCK_SIZE * (purin_y + y_offset * 1));
							map[purin_x + x_offset][purin_y + y_offset] -= RED_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += RED_BALL;
							break;
						case RED_BALL + RED_MICROPHONE:
							red_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							red_microphone(100 + BLOCK_SIZE * (purin_x + x_offset * 1), 100 + BLOCK_SIZE * (purin_y + y_offset * 1));
							map[purin_x + x_offset][purin_y + y_offset] -= RED_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += RED_BALL;
							break;
						case MINE + RED_BALL:
							red_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							map[purin_x + x_offset][purin_y + y_offset] -= RED_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += RED_BALL;
							cout << "BOOM" << endl;
							babydin_fail(100 + BLOCK_SIZE * (purin_x + x_offset), 100 + BLOCK_SIZE * (purin_y + y_offset));
							purin_x += x_offset;
							purin_y += y_offset;
							step_count++;
							fail = true;
							glPushMatrix();
							rect(1, 1, 1, 90, 800, 0, 710, true);
							glColor3f(0, 0, 0);
							glTranslatef(325, 25, 0);
							glScalef(0.5, 0.5, 1);

							for (int i = 0; i < 6; i++)
							{
								glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
							}

							glPopMatrix();
							glFlush();
							return true;
							break;
						case MINE + ORANGE_BALL:
							orange_ball(100 + BLOCK_SIZE * (purin_x + x_offset * 2), 100 + BLOCK_SIZE * (purin_y + y_offset * 2));
							map[purin_x + x_offset][purin_y + y_offset] -= ORANGE_BALL;
							map[purin_x + x_offset * 2][purin_y + y_offset * 2] += ORANGE_BALL;
							cout << "BOOM" << endl;
							babydin_fail(100 + BLOCK_SIZE * (purin_x + x_offset), 100 + BLOCK_SIZE * (purin_y + y_offset));
							purin_x += x_offset;
							purin_y += y_offset;
							step_count++;
							fail = true;
							glPushMatrix();
							rect(1, 1, 1, 90, 800, 0, 710, true);
							glColor3f(0, 0, 0);
							glTranslatef(325, 25, 0);
							glScalef(0.5, 0.5, 1);

							for (int i = 0; i < 6; i++)
							{
								glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
							}

							glPopMatrix();
							glFlush();
							return true;
							break;
						case MINE:
							cout << "BOOM" << endl;
							babydin_fail(100 + BLOCK_SIZE * (purin_x + x_offset), 100 + BLOCK_SIZE * (purin_y + y_offset));
							purin_x += x_offset;
							purin_y += y_offset;
							step_count++;
							fail = true;
							glPushMatrix();
							rect(1, 1, 1, 90, 800, 0, 710, true);
							glColor3f(0, 0, 0);
							glTranslatef(325, 25, 0);
							glScalef(0.5, 0.5, 1);

							for (int i = 0; i < 6; i++)
							{
								glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
							}

							glPopMatrix();
							glFlush();
							return true;
							break;
						default:
							break;
					}
					babydin(100 + BLOCK_SIZE * (purin_x + x_offset), 100 + BLOCK_SIZE * (purin_y + y_offset));
					purin_x += x_offset;
					purin_y += y_offset;
					step_count++;
					return true;
				}
			}
			return false;
		}
		rect(1, 1, 1, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y, true);
		rect(0, 0, 0, BLOCK_SIZE, BLOCK_SIZE, 100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y, false);

		switch (map[purin_x][purin_y])
		{
			case ORANGE_MICROPHONE:
				orange_microphone(100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y);
				break;
			case RED_MICROPHONE:
				red_microphone(100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y);
				break;
			default:
				break;
		}
		purin_x += x_offset;
		purin_y += y_offset;
		babydin(100 + BLOCK_SIZE * purin_x, 100 + BLOCK_SIZE * purin_y);
		step_count++;
		return true;
	}
	else
	{
		return false;
	}
}