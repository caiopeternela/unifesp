#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

int height = 500;
int width = 600;
int radius = 80;
float x_global = 250;
float y_global = 300;
float size = 1.0;

void points(int x, int y, int xc, int yc) {
  glVertex2i(x + xc, y + yc);
  glVertex2i(y + xc, x + yc);
  glVertex2i(y + xc, -x + yc);
  glVertex2i(x + xc, -y + yc);
  glVertex2i(-x + xc, -y + yc);
  glVertex2i(-y + xc, -x + yc);
  glVertex2i(-y + xc, x + yc);
  glVertex2i(-x + xc, y + yc);
}

void bresenDraw(int xc, int yc, int radius) {
  int x = 0;
  int y = radius;
  int d = 1 - radius;
  points(x, y, xc, yc);
  while (y > x) {
    if (d < 0) {
      d = d + 2 * x + 3;
      x = x + 1;
    } else {
      d = d + 2 * (x - y) + 5;
      x = x + 1;
      y = y - 1;
    }
    points(x, y, xc, yc);
  }
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'e':
      exit(0);
      break;
    case 'i':
    case 'I':
      radius += 10;
      break;
    case 'd':
    case 'D':
      radius -= 10;
      break;
    default:
      break;
  }
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    x_global = x;
    y_global = height - y;
  }
  glutPostRedisplay();
}

void display() {
  glPointSize(size);

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POINTS);

  bresenDraw(x_global, y_global, radius);

  glEnd();
  glFlush();
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(0, width, 0, height, -1, 1);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(50, 100);
  glutCreateWindow("EX4");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();

  return 0;
}