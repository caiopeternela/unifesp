#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int startCoordX = 0, startCoordY = 0;
int endCoordX = 0, endCoordY = 0;
int clicks = 0;
int activeColor = 0;

GLfloat palette[][3] = {
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.5, 0.5, 0.5},
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 1.0, 0.0},
    {1.0, 0.5, 0.0},
    {0.0, 0.5, 1.0},
    {0.5, 0.0, 1.0},
    {1.0, 0.0, 1.0}
};

void point(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void line(int fromX, int fromY, int toX, int toY) {
    glColor3fv(palette[activeColor]);

    int deltaX = abs(toX - fromX);
    int deltaY = abs(toY - fromY);
    int stepX, stepY;

    if (fromX < toX) stepX = 1;
    else stepX = -1;

    if (fromY < toY) stepY = 1;
    else stepY = -1;

    int error = deltaX - deltaY;

    while (1) {
        point(fromX, fromY);

        if (fromX == toX && fromY == toY)
            break;

        int twiceError = 2 * error;

        if (twiceError > -deltaY) {
            error -= deltaY;
            fromX += stepX;
        }

        if (twiceError < deltaX) {
            error += deltaX;
            fromY += stepY;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (clicks == 2) {
        line(startCoordX, startCoordY, endCoordX, endCoordY);
    }
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clicks == 0) {
            startCoordX = x;
            startCoordY = 800 - y;
            clicks = 1;
        } else if (clicks == 1) {
            endCoordX = x;
            endCoordY = 600 - y;
            clicks = 2;
        } else if (clicks == 2) {
            startCoordX = -1;
            startCoordY = -1;
            endCoordX = -1;
            endCoordY = -1;
            clicks = 0;
            glClear(GL_COLOR_BUFFER_BIT);
        }

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '0' && key <= '9') {
        activeColor = key - '0';
        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("EX1");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}