#include <iostream>
#include <Windows.h>
#include "glut.h"

#define pi 3.14f

void procesareTastatura(unsigned char key, int x, int y) {
	std::cout << "tasta " << key << std::endl;
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 115:
		//s
		break;
	case 119:
		//w
		break;
	case 97:
		//a
		break;
	case 100:
		//d
		break;
	default:
		break;
	}
}

void procesareTastaturaSpecial(int key, int x, int y) {
	std::cout << "tasta " << key << std::endl;
	switch (key)
	{
	case 100:
		//sag stanga
		x -= 0.1f;
		break;
	case 101:
		//sag sus
		break;
	case 102:
		x += 0.1f;
		//sag dreapta
		break;
	case 103:
		//sag jos
		break;
	default:
		break;
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

GLUquadricObj* q;

void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	//primi parametri pozitia camerei, urmatorii matricea de vizualizare, urmatorii nu am inteles
	gluLookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, -2.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);

	gluSphere(q, 1.0f, 10, 20);

	glutSwapBuffers();
}

int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Masinute pe sosea");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//tastatura
	glutKeyboardFunc(procesareTastatura);
	glutSpecialFunc(procesareTastaturaSpecial);

	//depth test
	glEnable(GL_DEPTH_TEST);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
