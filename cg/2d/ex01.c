#include <GL/glut.h>
#include <math.h>

#define PI 3.141592654

int height = 500;
int width = 600;
float rotationAngle = 0.0f;
float rotationSpeed = 0.0f;

void circle(float radius) {
    int i;
    float angle;
    glBegin(GL_POLYGON);
    for (i = 0; i < 30; i++) {
        angle = 2 * PI * i / 30;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void drawPetals(int quantity, float radius) {
    for (int i = 0; i < quantity; i++) {
        float angle = i * (360.0 / quantity);
        float x = radius * cos(angle * PI / 180.0);
        float y = radius * sin(angle * PI / 180.0);

        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(x, y, 0.0f);
        circle(0.125);
        glPopMatrix();
    }
}

void drawStem() {
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.025, 0.5);
    glVertex2f(0.025, 0.5);
    glVertex2f(0.025, -0.5);
    glVertex2f(-0.025, -0.5);
    glEnd();
    glPopMatrix();
}

void init(void) {
    glClearColor(0.0, 0.4, 1.0, 0.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    circle(0.125);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    drawPetals(10, 0.2);
    glPopMatrix();

    drawStem();

    rotationAngle += rotationSpeed;

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'l':
        case 'L':
            rotationSpeed = 0.05f;
            break;
        case 'r':
        case 'R':
            rotationSpeed = -0.05f;
            break;
        case 's':
        case 'S':
            rotationSpeed = 0.0f;
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
    glutCreateWindow("EX1");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}