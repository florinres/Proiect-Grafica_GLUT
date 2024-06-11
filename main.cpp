#include <iostream>
#include <cmath>
#include <Windows.h>
#include "glut.h"

#define pi 3.14159265358979323846

GLUquadric* cilindru;
float cameraAngle = 0.0f;
float cameraRadius = 20.0f;
const float cameraHeight = 5.0f;
const float cameraSpeed = 0.1f;
const float radiusSpeed = 0.5f;
double cameraX = 0.0;

void myinit() {
    cilindru = gluNewQuadric();
    gluQuadricDrawStyle(cilindru, GLU_LINE);
    gluQuadricNormals(cilindru, GLU_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void procesareTastatura(unsigned char key, int x, int y) {
    std::cout << "tasta " << key << std::endl;
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 's':
        //s
        break;
    case 'w':
        //w
        break;
    case 'a':
        //pentru mutare camera catre stanga pe X
        cameraX -= 0.0;
        break;
    case 'd':
        //pentru mutare camera catre dreapta pe X
        cameraX += 0.0;
        break;
    default:
        break;
    }
}

void procesareTastaturaSpecial(int key, int x, int y) {
    std::cout << "tasta " << key << std::endl;
    switch (key)
    {
    case GLUT_KEY_LEFT:
        cameraAngle -= cameraSpeed;
        if (cameraAngle < 0) {
            cameraAngle += 2 * pi;
        }
        break;
    case GLUT_KEY_RIGHT:
        cameraAngle += cameraSpeed;
        if (cameraAngle > 2 * pi) {
            cameraAngle -= 2 * pi;
        }
        break;
    case GLUT_KEY_UP:
        cameraRadius -= radiusSpeed;
        if (cameraRadius < 1.0f) {
            cameraRadius = 1.0f;
        }
        break;
    case GLUT_KEY_DOWN:
        cameraRadius += radiusSpeed;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0f / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Calculează poziția camerei folosind trigonometrie
    float cameraX = cameraRadius * cos(cameraAngle);
    float cameraZ = cameraRadius * sin(cameraAngle);
    gluLookAt(cameraX, cameraHeight, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Desenează cilindrul
    gluCylinder(cilindru, 1.0, 1.0, 3.0, 6, 1);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Masinute pe sosea");

    myinit();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    //tastatura
    glutKeyboardFunc(procesareTastatura);
    glutSpecialFunc(procesareTastaturaSpecial);

    //depth test
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
