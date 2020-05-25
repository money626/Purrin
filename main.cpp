#include <gl/GLUT.H>
#include "main_function.h"
#include "final.h"
using namespace std;

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	init_final();
	glutMouseFunc(on_click_function);
	glutDisplayFunc(&display_final);
	glutKeyboardFunc(keyboard_func);
	glutReshapeFunc(winReshapeFcn_final);
	glutSpecialFunc(special_key_func);
	glutCreateMenu(menu);
	glutAddMenuEntry("NEXT LEVEL", 1);
	glutAddMenuEntry("RESTART", 2);
	glutAddMenuEntry("UNDO(NOT YET IMPLEMENTED)", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}