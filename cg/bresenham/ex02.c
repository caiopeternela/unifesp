#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

float location_x = 0;
float location_y = 0;
float location_x2 = 0;
float location_y2 = 0;
float location_x3 = 0;
float location_y3 = 0;

bool triangle = false;

float red = 0.0;
float green = 0.0;
float blue = 1.0;

void mouse(int button, int state, int x, int y) {
    static int count = 0;
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                if (count == 0) {
                    location_x = x;
                    location_y = 500 - y;
                    count++;
                } else if (count == 1) {
                    location_x2 = x;
                    location_y2 = 500 - y;
                    if (triangle) {
                        count++;
                    } else {
                        count = 0;
                    }
                } else if (count == 2) {
                    location_x3 = x;
                    location_y3 = 500 - y;
                    count = 0;
                }
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case '2':
            red = 0.0;
            green = 1.0;
            blue = 0.0;
            break;
        case '3':
            red = 1.0;
            green = 1.0;
            blue = 0.0;
            break;
        case '4':
            red = 1.0;
            green = 1.0;
            blue = 1.0;
            break;
        case '5':
            red = 0.5;
            green = 0.5;
            blue = 0.0;
            break;
        case '6':
            red = 0.2;
            green = 0.4;
            blue = 0.6;
            break;
        case '7':
            red = 1.0;
            green = 0.75;
            blue = 0.8;
            break;
        case '8':
            red = 1.0;
            green = 0.5;
            blue = 0.0;
            break;
        case '9':
            red = 0.5;
            green = 0.0;
            blue = 1.0;
            break;
        case 't':
        case 'T':
            triangle = !triangle;
            break;
        case 'r':
        case 'R':
            location_x = 0;
            location_y = 0;
            location_x2 = 0;
            location_y2 = 0;
            location_x3 = 0;
            location_y3 = 0;
            triangle = false;
            red = 0;
            green = 0;
            blue = 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void point(float x, float y, float r, float g, float b) {
    glPointSize(3.0);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;

    while (1) {
        point(x1, y1, red, green, blue);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err = err - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx) {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}

void draw() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (triangle) {
        bresenham(location_x, location_y, location_x2, location_y2);
        bresenham(location_x2, location_y2, location_x3, location_y3);
        bresenham(location_x3, location_y3, location_x, location_y);
    } else {
        bresenham(location_x, location_y, location_x2, location_y2);
    }
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("EX2");
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}