#include <math.h>
#include <GL/glut.h>

void draw() {
    int i, n = 50;
    float ang = 0;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0 , 1.0);
    glBegin(GL_LINE_LOOP);
        for(i=0; i<n; i++){
            glVertex2f(0.5 * cos(ang), 0.5 * sin(ang));
            ang = ang+(2 * M_PI) / n;
        }
    glEnd();
    glFlush();
}

int main(int argc, char * argv []) {
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (400, 400);
    glutCreateWindow ("Circle");
    glutDisplayFunc (draw);
    glutMainLoop ();

    return 0;
}