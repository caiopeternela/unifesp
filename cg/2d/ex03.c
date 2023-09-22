#include <GL/glut.h>

float armAngle = 0.0f;
float legAngle = 0.0f;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void drawRect(float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(-width / 2, -height / 2);
    glVertex2f(width / 2, -height / 2);
    glVertex2f(width / 2, height / 2);
    glVertex2f(-width / 2, height / 2);
    glEnd();
}

void drawRobot() {
    glColor3f(0.75f, 0.75f, 0.75f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawRect(0.4f, 0.6f);
    glPopMatrix();

    glColor3f(0.75f, 0.75f, 0.75f);
    glPushMatrix();
    glTranslatef(0.0f, 0.35f, 0.0f);
    drawRect(0.3f, 0.3f);
    glPopMatrix();

    glColor3f(0.75f, 0.75f, 0.75f);
    glPushMatrix();
    glTranslatef(-0.25f, 0.1f, 0.0f);
    glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
    drawRect(0.05f, 0.4f);
    glPopMatrix();

    glColor3f(0.75f, 0.75f, 0.75f);
    glPushMatrix();
    glTranslatef(0.25f, 0.1f, 0.0f);
    glRotatef(-armAngle, 0.0f, 0.0f, 1.0f);
    drawRect(0.05f, 0.4f);
    glPopMatrix();

    glColor3f(0.75f, 0.75f, 0.75f);
    glPushMatrix();
    glTranslatef(-0.1f, -0.45f, 0.0f);
    glRotatef(legAngle, 0.0f, 0.0f, 1.0f);
    drawRect(0.1f, 0.4f);
    glPopMatrix();

    glColor3f(0.75f, 0.75f, 0.75f);
    glPushMatrix();
    glTranslatef(0.1f, -0.45f, 0.0f);
    glRotatef(-legAngle, 0.0f, 0.0f, 1.0f);
    drawRect(0.1f, 0.4f);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawRobot();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
        armAngle += 5.0f;
        break;
    case 'e':
        armAngle -= 5.0f;
        break;
    case 'w':
        legAngle += 5.0f;
        break;
    case 's':
        legAngle -= 5.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Proportional Robot");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}