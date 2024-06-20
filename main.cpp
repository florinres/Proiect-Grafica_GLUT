#include <iostream>
#include <cmath>
#include <Windows.h>
#include "GL.H"
#include "glut.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


double angleHorizontal = 0.0;
double departareVerticala = 0.0;
double radius = 10.0;
double departareZ = 5.0;
double carPositionOne = -12.0;
double carPositionTwo = -12.0;
GLuint textureID = 0, textureID1 = 0, textureID2 = 0;
GLfloat angle = 0.0f;

struct Nume {
    GLubyte litera_R[24] = {
        0xF0, 0x00,
        0xF8, 0x00,
        0xD8, 0x00,
        0xD8, 0x00,
        0xF8, 0x00,
        0xF0, 0x00,
        0xD8, 0x00,
        0xD8, 0x00,
        0xD8, 0x00,
        0xD8, 0x00,
        0xD8, 0x00,
        0xD8, 0x00
    };

    GLubyte litera_A[24] = {
        0x30, 0x00,
        0x78, 0x00,
        0xCC, 0x00,
        0xCC, 0x00,
        0xCC, 0x00,
        0xFC, 0x00,
        0xFC, 0x00,
        0xCC, 0x00,
        0xCC, 0x00,
        0xCC, 0x00,
        0xCC, 0x00,
        0xCC, 0x00
    };

    GLubyte litera_E[24] = {
        0xFC, 0x00,
        0xFC, 0x00,
        0xC0, 0x00,
        0xC0, 0x00,
        0xC0, 0x00,
        0xFC, 0x00,
        0xFC, 0x00,
        0xC0, 0x00,
        0xC0, 0x00,
        0xC0, 0x00,
        0xFC, 0x00,
        0xFC, 0x00
    };

    GLubyte litera_S[24] = {
        0x7C, 0x00,
        0xFC, 0x00,
        0xC0, 0x00,
        0xC0, 0x00,
        0xF8, 0x00,
        0x7C, 0x00,
        0x3C, 0x00,
        0x0C, 0x00,
        0x0C, 0x00,
        0x0C, 0x00,
        0xFC, 0x00,
        0xF8, 0x00
    };
};

Nume Rares;

void drawText(const char* text, float x, float y, void* font) {
    glRasterPos3d(x, y,-10);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void myName() {
    glColor3f(1.0, 1.0, 1.0);
    const char* name = "BOLCA RARES";
    float x = 11.0f; 
    float y = -6.f;
    drawText(name, x, y, GLUT_BITMAP_TIMES_ROMAN_24);
}


void animatie() {
    if (carPositionOne >= 12.0)
    {
        carPositionOne = -12.0;
    }
    if (carPositionTwo >= 12.0)
    {
        carPositionTwo = -8.0;
    }

    carPositionOne += 0.1;
    carPositionTwo += 0.1;
    glutPostRedisplay();
}

GLuint loadTexture(const char* filename, GLuint id) {
    int width, height, numComponents;
    unsigned char* data = stbi_load(filename, &width, &height, &numComponents, STBI_rgb);

    if (!data) {
        std::cerr << "Error loading texture: " << filename << std::endl;
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data);

    return id;
}


void teren() {
    GLUquadric* teren = gluNewQuadric();
    gluQuadricTexture(teren, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPushMatrix();
    
    glTranslatef(1.1f, -0.3f, 0.0f);

    gluQuadricDrawStyle(teren, GLU_FILL);
    gluQuadricNormals(teren, GLU_SMOOTH);

    glRotatef(-90, 1, 0, 0); 

    gluDisk(teren, 0.0, 10.0, 256, 256); 

    glPopMatrix();

    gluDeleteQuadric(teren);
    glDisable(GL_TEXTURE_2D);
}

void lumina() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void asfalt() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);

    GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat mat_shininess[] = { 5.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_QUADS);
    {
        glVertex3f(-5.0f, 0.0f, -10.0f);
        glVertex3f(5.0f, 0.0f, -10.0f);
        glVertex3f(5.0f, 0.0f, 10.0f);
        glVertex3f(-5.0f, 0.0f, 10.0f);
    }
    glEnd();

    gluDeleteQuadric(quad);
}

void roata(double x, double y, double z) {
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(90, 0, 1, 0);
    glColor3d(0.1, 0.1, 0.1);
    glutSolidTorus(0.1, 0.3, 12, 36);
    glPopMatrix();
}

void masina() {
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    {
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(3.0, 0.0, 0.0);
        glVertex3d(3.0, 0.5, 0.0);
        glVertex3d(0.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex3d(3.0, 0.0, 0.0);
        glVertex3d(3.0, 0.0, -3.0);
        glVertex3d(3.0, 0.5, -3.0);
        glVertex3d(3.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(0.0, 0.5, -3.0);
        glVertex3d(0.0, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex3d(0.0, 0.0, -3.0);
        glVertex3d(3.0, 0.0, -3.0);
        glVertex3d(3.0, 0.5, -3.0);
        glVertex3d(0.0, 0.5, -3.0);
    }
    glEnd();

    glColor3d(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    {
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
    {
        glVertex3d(0.2, 0.2, -3.01);
        glVertex3d(0.5, 0.2, -3.01);
        glVertex3d(0.5, 0.4, -3.01);
        glVertex3d(0.2, 0.4, -3.01);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex3d(2.5, 0.2, -3.01);
        glVertex3d(2.8, 0.2, -3.01);
        glVertex3d(2.8, 0.4, -3.01);
        glVertex3d(2.5, 0.4, -3.01);
    }
    glEnd();

    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    {
        glVertex3d(0.0, 0.5, 0.0);
        glVertex3d(3.0, 0.5, 0.0);
        glVertex3d(3.0, 0.65, -0.8);
        glVertex3d(0.0, 0.65, -0.8);

        glVertex3d(3.0, 0.5, 0.0);
        glVertex3d(3.0, 0.65, -0.8);
        glVertex3d(3.0, 0.5, -0.8);
        glVertex3d(3.0, 0.5, 0.0);

        glVertex3d(0.0, 0.5, 0.0);
        glVertex3d(0.0, 0.65, -0.8);
        glVertex3d(0.0, 0.5, -0.8);
        glVertex3d(0.0, 0.5, 0.0);

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
    case 'w': departareZ += 0.25;
        break;
    case 's': departareZ -= 0.25;
        break;
    default: break;
    }
    glutPostRedisplay();
}


void TasteSpeciale(int key, int x, int y) {
    std::cout << "tasta " << key << std::endl;
    switch (key) {
    case GLUT_KEY_LEFT: angle -= -0.50f;
        break;
    case GLUT_KEY_RIGHT: angle += 0.50;
        break;
    case GLUT_KEY_UP: departareVerticala -= 0.5;
        break;
    case GLUT_KEY_DOWN: departareVerticala += 0.5;
        break;
    default: break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.2f, 1.0f, 0.0f);
    textureID = loadTexture("iarba2.bmp", textureID);
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

    GLdouble camX = 30.0 * cos(angle);
    GLdouble camZ = 30.0 * sin(angle);
    
    gluLookAt(0.0,5.0,-30.0,
        0.0,1.0,0.0,
        0,1,0);

    teren();
    lumina();

    glPushMatrix();
    glTranslated(2.0, 0.1, carPositionOne);
    masina();
    glPopMatrix();

    glPushMatrix();
    glRotated(180, 0, 1, 0);
    glTranslatef(-1.0, 0.1, carPositionTwo);
    masina();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.4, -0.2, 0.0);
    asfalt();
    glPopMatrix();

    myName();

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
    glutIdleFunc(animatie);

    glutMainLoop();

    return 1;
}
