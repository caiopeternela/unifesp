#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.141592654

float up = 0.0;
float right = 0.0;

void circle() {
    int i;
    float angulo = 0.0;
    glBegin(GL_POLYGON);
        for (i=0; i<=50; i++) {
            angulo = 2 * PI * i / 50.0;
            glVertex2f(0.25 * cos(angulo), 0.25 * sin(angulo));
        }
    glEnd();
}

void square(float incX, float incY) {
    glBegin(GL_POLYGON);
        glVertex2f(-0.25 + incX + right, 0.25 + incY + up);
        glVertex2f(0.25 + incX + right, 0.25 + incY + up);
        glVertex2f(0.25 + incX + right, -0.25 + incY + up);
        glVertex2f(-0.25 + incX + right, -0.25 + incY + up);
    glEnd();
}

void draw() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0, 1.0);
    circle();
    glColor3f(1.0, 0.0, 0.0);
    square(0.5, 0.5);
    glColor3f(0.0, 1.0, 0.0);
    square(-0.5, 0.5);
    glColor3f(0.0, 0.0, 1.0);
    square(0.5, -0.5);
    glColor3f(1.0, 1.0, 0.0);
    square(-0.5, -0.5);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'u':
            up += 0.05;
            break;
        case 'd':
            up -= 0.05;
            break;
        case 'r':
            right += 0.05;
            break;
        case 'l':
            right -= 0.05;
        default:
            break;
        }

    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            up += 0.05;
            break;
        case GLUT_KEY_DOWN:
            up -= 0.05;
            break;
        case GLUT_KEY_RIGHT:
            right += 0.05;
            break;
        case GLUT_KEY_LEFT:
            right -= 0.05;
            break;
        default:
            break;
        }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                printf("x = %i, y = %i\n",x,y);
            break;
            
        default:
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char* argv []) {
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 , 100);
    glutInitWindowSize (400 , 400);
    glutCreateWindow ("Squares & Circle Interaction");
    glutDisplayFunc (draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMainLoop ();

    return 0;
}