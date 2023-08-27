#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float location_x = 0.0;
float location_y = 0.0;
float location_x2 = 0.0;
float location_y2 = 0.0;
float r = 0.0, g = 0.0, b = 1.0;

void point(float x, float y, float r, float g, float b) {
  glPointSize(5.0);
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
    glVertex2f(x, y);
  glEnd();
  glFlush();
}

void line(float x1, float y1, float x2, float y2) {
  glColor3f(r, g, b);
  glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
  glEnd();
}

void draw() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  line(location_x, location_y, location_x2, location_y2);
  glColor3f(1.0, 1.0, 1.0);
  point(location_x, location_y, r, g, b);
  glFlush();
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
        float mouseX = (float) x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
        float mouseY = 1.0 - (float) y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0;
        location_x = mouseX;
        location_y = mouseY;
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
      r = 1.0, g = 0.0, b = 0.0;
      break;
    case '2':
      r = 0.0, g = 1.0, b = 0.0;
      break;
    case '3':
      r = 1.0, g = 1.0, b = 0.0;
      break;
    case '4':
      r = 1.0, g = 1.0, b = 1.0;
      break;
    case '5':
      r = 0.5, g = 0.5, b = 0.0;
      break;
    case '6':
      r = 0.2, g = 0.4, b = 0.6;
      break;
    case '7':
      r = 1.0, g = 0.75, b = 0.8;
      break;
    case '8':
      r = 1.0, g = 0.5, b = 0.0;
      break;
    case '9':
      r = 0.5, g = 0.0, b = 1.0;
      break;
    default:
      break;
  }

  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("EX3");
  glutDisplayFunc(draw);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}