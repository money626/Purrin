#pragma once

void rect(float r, float g, float b, float height, float weight, float start_X, float start_Y, bool fill);
void circle(float r, float g, float b, float radius, float center_X, float center_Y, bool fill);
double bezier(double *control_points, int num, double t);
void curve(double X_A, double X_B, double X_C, double Y_A, double Y_B, double Y_C);
double bezier(double A, double B, double C, double D, double t);
void partial_circle(float r, float g, float b, float radius, float center_X, float center_Y, const int degree, const int rotation, bool fill);
