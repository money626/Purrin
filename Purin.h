#pragma once
#ifndef PURIN_H
#define PURIN_H

class Purin
{
public:
	Purin(int n);
	bool move(int x_offset, int y_offset);
	bool finished();
	void display();
	void print_step();
private:
	int map[10][10];
	int purin_x;
	int purin_y;
	int step_count;
	bool finish;
	bool fail;
};

#endif