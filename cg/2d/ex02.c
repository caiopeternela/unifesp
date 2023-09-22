#include <GL/glut.h>
#include <math.h>

#define PI 3.141592654

int height = 500;
int width = 600;
float rotationAngle = 0.0f;
float positionX = 0.0f; 

void circle(float radius, int segments) {
    float angle = 0.0;
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        angle = 2 * PI * i / segments;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.8, 0.8, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(0.4f, 0.8f, 0.2f);
    glTranslatef(0.0f, -1, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0.2);
    glVertex2f(1, 0.2);
    glVertex2f(1, -0.2);
    glVertex2f(-1, -0.2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(-0.3f + positionX, -0.8f, 0.0f); 
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);  
    circle(0.125, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f + positionX, -0.8f, 0.0f); 
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); 
    circle(0.125, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f + positionX, -0.65, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, 0.1);
    glVertex2f(0.5, 0.1);
    glVertex2f(0.5, -0.1);
    glVertex2f(-0.5, -0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f + positionX, -0.45, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25, 0.1);
    glVertex2f(0.25, 0.1);
    glVertex2f(0.25, -0.1);
    glVertex2f(-0.25, -0.1);
    glEnd();
    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        rotationAngle += 10.0f;
        positionX -= 0.01;
        break;
    case 'd':
        rotationAngle -= 10.0f;
        positionX += 0.01;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("EX2");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}