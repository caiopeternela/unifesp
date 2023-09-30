#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float x_angle = 0.0;
float y_angle = 0.0;
int quantity = 2;

void clown() {
  glPushMatrix();
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(-2.6, 1, -0.2);
    glColor3f(80/255.0, 250/255.0, 123/255.0);
    glutSolidSphere(1,50,50);
  glPopMatrix();

  glPushMatrix();
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(2.6, 1, -0.2);
    glColor3f(139/255.0, 233/255.0, 253/255.0);
    glutSolidSphere(1,50,50);
  glPopMatrix();

  glPushMatrix();
    glColor3f(98/255.0, 114/255.0, 164/255.0);
    glutSolidSphere(3,50,50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0.2, 3.3);
    glColor3f(255/255.0, 85/255.0, 85/255.0);
    glutSolidSphere(0.5,50,50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.8, 1.5, 3.0);
    glColor3f(241/255.0, 250/255.0, 140/255.0);
    glutSolidSphere(0.5,50,50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.8, 1.5, 3.0);
    glColor3f(255/255.0, 121/255.0, 198/255.0);
    glutSolidSphere(0.5,50,50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.8, 1.5, 3.5);
    glColor3f(248/255.0, 248/255.0, 242/255.0);
    glutSolidSphere(0.17,50,50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.8, 1.5, 3.5);
    glColor3f(189/255.0, 147/255.0, 249/255.0);
    glutSolidSphere(0.17,50,50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0, -1.3, 2.4);
    glColor3f(255/255.0, 184/255.0, 108/255.0);
    glScaled(2,0.5,1);
    glutSolidTorus(0.48,0.40,50,20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glColor3f(68/255.0, 71/255.0, 90/255.0);
    glutSolidCone(0.9, 2.0, 50, 50);
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPopMatrix();
  glPushMatrix();
  glRotatef(x_angle,1.0,0.0,0.0);
  glRotatef(y_angle,0.0,1.0,0.0);
  clown();
  glFlush();
}

void timer(int value) {
    y_angle+=quantity;
    glutPostRedisplay();
    glutTimerFunc(10,timer, 1);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case ' ':
    if (quantity == 2)
      quantity = 0;
    else
     quantity = 2;
    break;
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutCreateWindow("Clown");
  glutDisplayFunc(display);
  glutTimerFunc(10, timer, 1);
  glutKeyboardFunc(keyboard);
  glClearColor(0.7, 0.7, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-7.0,7.0,-7.0,7.0,-7.0,7.0);
  glPushMatrix();
  glutMainLoop();
}