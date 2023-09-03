from OpenGL.GL import *
from OpenGL.GLUT import *
from math import pi, sin, cos

def draw():
    n = 50
    ang = 0
    ang_inc = (2 * pi) / n

    glClearColor(0, 0, 0, 0)
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    
    glBegin(GL_LINE_LOOP)
    
    for i in range(n):
        x = 0.5 * cos(ang)
        y = 0.5 * sin(ang)
        glVertex2f(x, y)
        ang += ang_inc
    
    glEnd()
    glFlush()

def main():
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(50, 100)
    glutInitWindowSize(400, 400)
    glutCreateWindow("Circle")
    glutDisplayFunc(draw)
    glutMainLoop()

main()