#include <cmath>
#include <gl/GLUT.H>

double bezier(double *control_points, int num, double t)
{
	double value = 0;
	double s = 1 - t;
	for (int i = 0; i < num; i++)
	{
		value += control_points[i] * pow(s, num - 1 - i) * pow(t, i) * combination(num - 1, i);
	}
	return value;
}
double bezier(double A,  // Start value
			  double B,  // First control value
			  double C,  // Second control value
			  double D,  // Ending value
			  double t)  // Parameter 0 <= t <= 1
{
	double s = 1 - t;
	double AB = A * s + B * t;
	double BC = B * s + C * t;
	double CD = C * s + D * t;
	double ABC = AB * s + BC * t;
	double BCD = BC * s + CD * t;
	return ABC * s + BCD * t;
}
void curve(double X_A, double X_B, double X_C, double Y_A, double Y_B, double Y_C)
{
	double X_control_A = X_A;
	double X_control_B = -(X_A - 8 * X_B + X_C) / 6;
	double X_control_C = X_control_B;
	double X_control_D = X_C;
	double Y_control_A = Y_A;
	double Y_control_B = -(Y_A - 8 * Y_B + Y_C) / 6;
	double Y_control_C = Y_control_B;
	double Y_control_D = Y_C;
	for (int i = 0; i < 1000; i++)
	{
		double x = bezier(X_control_A, X_control_B, X_control_C, X_control_D, i*0.001);
		double y = bezier(Y_control_A, Y_control_B, Y_control_C, Y_control_D, i*0.001);
		glVertex2f(x, y);
	}
}
void rect(float r, float g, float b, float height, float weight, float start_X, float start_Y, bool fill)
{
	glColor3f(r, g, b);

	if (fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}
	glVertex2f(start_X, start_Y);
	glVertex2f(start_X + weight, start_Y);
	glVertex2f(start_X + weight, start_Y + height);
	glVertex2f(start_X, start_Y + height);
	glEnd();

	glFlush();
}

void circle(float r, float g, float b, float radius, float center_X, float center_Y, bool fill)
{
	glColor3f(r, g, b);
	if (fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
	}
	for (int i = 0; i <= 360; i++)
	{
		double x_bias = cos(3.14 / 180 * i) * radius;
		double y_bias = sin(3.14 / 180 * i) * radius;
		glVertex2f(center_X + x_bias, center_Y + y_bias);
	}
	glEnd();
	glFlush();
}

void partial_circle(float r, float g, float b, float radius, float center_X, float center_Y, const int degree, const int rotation, bool fill)
{
	glColor3f(r, g, b);
	if (fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}
	glVertex2f(center_X, center_Y);
	for (int i = 0; i <= degree; i++)
	{
		double x_bias = cos(3.14 / 180 * (i + rotation)) * radius;
		double y_bias = sin(3.14 / 180 * (i + rotation)) * radius;
		glVertex2f(center_X + x_bias, center_Y + y_bias);
	}
	glEnd();
}

