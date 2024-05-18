#include <iostream>
#include <Windows.h>
#include "glut.h"

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINE);
	glVertex2d(0.0, 0.0);
	glVertex2d(4.0, 0.0);
	glEnd();

	glFlush();
}

int main(int argv, char** argc)
{
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Masinute pe sosea");
	glutDisplayFunc(display);
	glutMainLoop();

	return 1;
}
