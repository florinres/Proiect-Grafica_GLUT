#include <iostream>
#include <cmath>
#include <Windows.h>
#include "glut.h"

double angleHorizontal = 0.0;  // Unghiul pentru rotația camerei orizontală
double angleVertical = 0.0;    // Unghiul pentru rotația camerei verticală
double radius = 10.0;          // Raza cercului pe care se mișcă camera, setată mai mare pentru a muta camera mai departe de obiect

void masina() {
    glColor3d(1.0, 0.0, 0.0);
    glTranslated(-2.0, -0.5, 0.0);
    glBegin(GL_QUADS);
    {//bumper
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(3.0, 0.0, 0.0);
        glVertex3d(3.0, 0.5, 0.0);
        glVertex3d(0.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {//laterala +x
        glVertex3d(3.0, 0.0, 0.0);
        glVertex3d(3.0, 0.0, -3.0);
        glVertex3d(3.0, 0.5, -3.0);
        glVertex3d(3.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {//laterala -x
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(0.0, 0.5, -3.0);
        glVertex3d(0.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {//bumper spate
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(0.0, 0.5, -3.0);
        glVertex3d(0.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {//bumper spate
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(3.0, 0.0, -3.0);
        glVertex3d(3.0, 0.5, -3.0);
        glVertex3d(0.0, 0.5, -3.0);
    }
    glEnd();

    glColor3d(1.0, 1.0, 0.0);
    glBegin(GL_QUADS); 
    {//far fata
        glVertex3d(0.1, 0.15, 0.01);
        glVertex3d(0.3, 0.15, 0.01);
        glVertex3d(0.3, 0.35, 0.01);
        glVertex3d(0.1, 0.35, 0.01);

        glVertex3d(2.7, 0.15, 0.01);
        glVertex3d(2.9, 0.15, 0.01);
        glVertex3d(2.9, 0.35, 0.01);
        glVertex3d(2.7, 0.35, 0.01);
    }
    glEnd();

    glColor3f(0.5f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    {// Far stânga spate
        glVertex3d(0.2, 0.2, -3.01);
        glVertex3d(0.5, 0.2, -3.01);
        glVertex3d(0.5, 0.4, -3.01);
        glVertex3d(0.2, 0.4, -3.01);
    }
    glEnd();

    glBegin(GL_QUADS);
    {// Far dreapta spate
        glVertex3d(2.5, 0.2, -3.01);
        glVertex3d(2.8, 0.2, -3.01);
        glVertex3d(2.8, 0.4, -3.01);
        glVertex3d(2.5, 0.4, -3.01);
    }
    glEnd();

}

void Taste(unsigned char key, int x, int y) {
    std::cout << key;
    switch (key) {
    case 27: exit(1);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void TasteSpeciale(int key, int x, int y) {
    std::cout << key;
    switch (key) {
    case GLUT_KEY_LEFT:
        angleHorizontal -= 0.05; // Ajustăm unghiul camerei orizontal
        break;
    case GLUT_KEY_RIGHT:
        angleHorizontal += 0.05; // Ajustăm unghiul camerei orizontal
        break;
    case GLUT_KEY_UP:
        angleVertical -= 0.05; // Ajustăm unghiul camerei vertical
        break;
    case GLUT_KEY_DOWN:
        angleVertical += 0.05; // Ajustăm unghiul camerei vertical
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void reshape(GLsizei w, GLsizei h) {
    if (h == 0) return;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    double cameraX = radius * cos(angleVertical) * cos(angleHorizontal);
    double cameraY = radius * sin(angleVertical);
    double cameraZ = radius * cos(angleVertical) * sin(angleHorizontal);

    gluLookAt(cameraX, cameraY, cameraZ,  // Poziția camerei
        -2.0, -0.5, 0.0,   // Punctul la care privește
        0.0, 1.0, 0.0);  // Vectorul de sus

    masina();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Masinute pe Sosea");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(TasteSpeciale);
    glutKeyboardFunc(Taste);

    glutMainLoop();

    return 1;
}
