#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

int spin = 1;
int num_frames = 0;
float speed = 1.0;

void pinwheel() {
  int i;
  glColor3f(0.97, 0.97, 0.95);
  glBegin(GL_POLYGON);
  glVertex2f(-0.05, 0);
  glVertex2f(0.05, 0);
  glVertex2f(0.05, 3);
  glVertex2f(-0.05, 3);
  glEnd();
  
  glTranslatef(0, 3, 0);
  glRotated((1 * (num_frames * (180.0/70))), 0, 0, 1);
  
  for (i = 0; i < 4; i++) {
    switch(i){
      case 0:
        glColor3f(1.0, 0.33, 0.33);
        break;
      case 1:
        glColor3f(0.31, 0.98, 0.48);
        break;
      case 2:
        glColor3f(0.55, 0.57, 0.64);
        break;
      case 3:
        glColor3f(1.0, 0.97, 0.93);
        break;
      default:
        break;
    }
    glRotated(90, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0.5, 0.5);
    glVertex2f(1, -1.0);
    glEnd();
  }

  float radius = 0.2f;
  int num_segments = 100;
  glColor3f(0.97, 0.97, 0.95);
  
  glBegin(GL_POLYGON);
  for(i = 0; i < num_segments; i++) {
    float theta = 2.0f * 3.1415926f * i / num_segments;
    float dx = radius * cosf(theta);
    float dy = radius * sinf(theta);
    glVertex2f(dx, dy);
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();
  glTranslated(3.5, -0.7, 1);
  glScaled(1.0, 1.0, 1);
  pinwheel();
  glPopMatrix();
  glutSwapBuffers();
}

void frame(int v) {
  num_frames++;
  glutPostRedisplay();
  if (spin) {
    glutTimerFunc(20 / speed, frame, 0);
  }
}

void increase_speed() {
  spin = 1;
  speed += 0.05;
  glutTimerFunc(20 / speed, frame, 0);
}

void decrease_speed() {
  speed -= 0.05;
  if (speed < 0.1) {
    speed = 0.1;
    spin = 0;
  }
}

void special(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      increase_speed();
      break;
    case GLUT_KEY_DOWN:
      decrease_speed();
      break;
    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(800,600);
  glutCreateWindow("Pinwheel");
  glClearColor(0.16f, 0.16f, 0.21f, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 7, -1, 4, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glutDisplayFunc(display);
  glutTimerFunc(200, frame, 0);
  glutSpecialFunc(special);
  glutMainLoop(); 
  return 0;
}