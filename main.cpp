﻿#include <iostream>
#include <cmath>
#include <Windows.h>
#include "glut.h"

double angleHorizontal = 0.0; 
double departareVerticala = 0.0;    
double radius = 10.0;          
double departareZ = 5.0;

void animatieMasina(int value) {
    while (--value)
    {
        
    }
    std::cout << "called";
    //comentariu
}

void roata(double x, double y, double z) {
    glPushMatrix(); // Salvează starea curentă a matricei
    glTranslated(x, y, z); // Translatează (mută) roata la poziția specificată
    glRotated(90, 0, 1, 0); // Rotește roata astfel încât să fie perpendiculară pe axa X
    glColor3d(0.1, 0.1, 0.1); // Setează culoarea roții
    glutSolidTorus(0.1, 0.3, 12, 36); // Desenează torusul cu raza interioară 0.1 și raza exterioară 0.3
    glPopMatrix(); // Restabilește starea anterioară a matricei
}

void masina() {
    glColor3d(1.0, 0.0, 0.0);
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

    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    {
        // Partea de sus a capotei
        glVertex3d(0.0, 0.5, 0.0);
        glVertex3d(3.0, 0.5, 0.0);
        glVertex3d(3.0, 0.65, -0.8);
        glVertex3d(0.0, 0.65, -0.8);

        // Fața laterală dreapta
        glVertex3d(3.0, 0.5, 0.0);
        glVertex3d(3.0, 0.65, -0.8);
        glVertex3d(3.0, 0.5, -0.8);
        glVertex3d(3.0, 0.5, 0.0);

        // Fața laterală stânga
        glVertex3d(0.0, 0.5, 0.0);
        glVertex3d(0.0, 0.65, -0.8);
        glVertex3d(0.0, 0.5, -0.8);
        glVertex3d(0.0, 0.5, 0.0);

        // Fața frontală (care îmbină capota cu partea din față a mașinii)
        glVertex3d(0.0, 0.5, -0.8);
        glVertex3d(3.0, 0.5, -0.8);
        glVertex3d(3.0, 0.65, -0.8);
        glVertex3d(0.0, 0.65, -0.8);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    {
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(3.0, 0.0, -3.0);
        glVertex3d(3.0, 0.0, 0.0);
    }
    glEnd();

    roata(-0.10, 0.1, -0.7);
    roata(3.1, 0.1, -0.7);
    roata(-0.10, 0.1, -2.50);
    roata(3.1, 0.1, -2.50);
}

void Taste(unsigned char key, int x, int y) {
    std::cout << "tasta " << key << std::endl;
    switch (key) {
    case 27: exit(1);
        break;
    case 'w':
        departareZ += 0.25;
        break;
    case 's':
        departareZ -= 0.25;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void TasteSpeciale(int key, int x, int y) {
    std::cout << "tasta " << key << std::endl;
    switch (key) {
    case GLUT_KEY_LEFT:
        angleHorizontal -= 0.05; // Ajustăm unghiul camerei orizontal
        break;
    case GLUT_KEY_RIGHT:
        angleHorizontal += 0.05; // Ajustăm unghiul camerei orizontal
        break;
    case GLUT_KEY_UP:
        departareVerticala -= 0.5; // Ajustăm unghiul camerei vertical
        break;
    case GLUT_KEY_DOWN:
        departareVerticala += 0.5; // Ajustăm unghiul camerei vertical
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

    double cameraX = radius * cos(departareVerticala) * sin(angleHorizontal);
    double cameraY = radius * sin(departareVerticala);
    double cameraZ = radius * cos(departareVerticala) * cos(angleHorizontal);

    gluLookAt(cameraX, cameraY, cameraZ-departareZ,   // Poziția camerei
        0.0, 0.0, 0.0,   // Punctul la care privește
        0.0, 1.0, 0.0);  // Vectorul de sus

    glTranslated(-2.0, 0.1, 0.0);
    masina();
    //glPushMatrix();
    glRotated(180, 0, 1, 0);
    glTranslatef(2.0, 0.1, 0.0);
    masina();
    //glPopMatrix();

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
    glutTimerFunc(100, animatieMasina, 1);

    glutMainLoop();

    return 1;
}
