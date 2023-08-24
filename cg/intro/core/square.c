#include <GL/glut.h>
#include <GL/gl.h>

void draw() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(-0.5, -0.5);
    glEnd();
    glFlush();
}

int main(int argc, char * argv []) {
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 , 100);
    glutInitWindowSize (400 , 400);
    glutCreateWindow ("Square");
    glutDisplayFunc (draw);
    glutMainLoop();

    return 0;
}