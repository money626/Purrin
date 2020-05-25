#pragma once
#include <gl/glut.h>

#define BLOCK_SIZE 60
#define ORANGE_BALL 94
#define ORANGE_MICROPHONE 87
#define RED_BALL 948
#define RED_MICROPHONE 7
#define PURIN 9487
#define GRASS 1
#define MINE 8888

//callback
void on_click_function(int button, int state, int x, int y);
void init_final();
void display_final();
void keyboard_func(unsigned char key, int x, int y);
void special_key_func(int key, int x, int y);

void winReshapeFcn_final(GLint newWidth, GLint newHeight);
void menu(int test);

//display
void next_level();
void home_page();
void red_ball(int x, int y);
void orange_ball(int x, int y);
void grass(int x, int y);
void orange_microphone(int x, int y);
void red_microphone(int x, int y);
void babydin(int x, int y);
void babydin_fail(int x, int y);
void fatdin();
