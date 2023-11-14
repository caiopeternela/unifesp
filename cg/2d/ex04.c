#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

float xMin = -0.5, xMax = 0.5, yMin = -0.5, yMax = 0.5;
float posX1 = -0.7, posY1 = -0.6;
float posX2 = 0.6, posY2 = 0.9;

int clickCount = 0;

const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int clipFlag = 0, drawFlag = 1;

int code1, code2;

int computeOutCode(float x, float y) {
    int code = 0;
    if (x < xMin) code |= LEFT;
    if (x > xMax) code |= RIGHT;
    if (y < yMin) code |= BOTTOM;
    if (y > yMax) code |= TOP;
    return code;
}

void clipLine() {
    int outCode;
    float x, y;

    outCode = code1 ? code1 : code2;

    if (outCode & LEFT) {
        x = xMin;
        y = posY1 + (posY2 - posY1) * (x - posX1) / (posX2 - posX1);
    } else if (outCode & RIGHT) {
        x = xMax;
        y = posY1 + (posY2 - posY1) * (x - posX1) / (posX2 - posX1);
    } else if (outCode & BOTTOM) {
        y = yMin;
        x = posX1 + (posX2 - posX1) * (y - posY1) / (posY2 - posY1);
    } else if (outCode & TOP) {
        y = yMax;
        x = posX1 + (posX2 - posX1) * (y - posY1) / (posY2 - posY1);
    }

    if (outCode == code1) {
        posX1 = x;
        posY1 = y;
        code1 = computeOutCode(posX1, posY1);
    } else {
        posX2 = x;
        posY2 = y;
        code2 = computeOutCode(posX2, posY2);
    }
}

void drawScene() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xMin, yMin);
    glVertex2f(xMax, yMin);
    glVertex2f(xMax, yMax);
    glVertex2f(xMin, yMax);
    glEnd();

    if (drawFlag) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(posX1, posY1);
        glVertex2f(posX2, posY2);
        glEnd();
    }

    if (clipFlag) {
        code1 = computeOutCode(posX1, posY1);
        code2 = computeOutCode(posX2, posY2);

        while (true) {
            if (!(code1 | code2)) {
                break;
            } else if (code1 & code2) {
                drawFlag = 0;
                break;
            } else {
                clipLine();
            }
        }
    }

    glFlush();
}

void mouseInteraction(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float mouseX = (float)x / (float)glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float mouseY = 1.0f - (float)y / (float)glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        if (clickCount == 0) {
            posX1 = mouseX;
            posY1 = mouseY;
            clickCount++;
        } else if (clickCount == 1) {
            posX2 = mouseX;
            posY2 = mouseY;
            clickCount = 0;
        }
    }
    glutPostRedisplay();
}

void keyboardInteraction(unsigned char key, int x, int y) {
    clipFlag = 1;
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(50, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Line Clipping Example");
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardInteraction);
    glutMouseFunc(mouseInteraction);
    glutMainLoop();

    return 0;
}
