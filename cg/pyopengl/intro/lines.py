from OpenGL.GL import *
from OpenGL.GLUT import *

location_x = 0.0
location_y = 0.0
location_x2 = 0.0
location_y2 = 0.0
r, g, b = 0.0, 0.0, 1.0

def point(x, y, r, g, b):
    glPointSize(5.0)
    glColor3f(r, g, b)
    glBegin(GL_POINTS)
    glVertex2f(x, y)
    glEnd()
    glFlush()

def line(x1, y1, x2, y2):
    glColor3f(r, g, b)
    glBegin(GL_LINES)
    glVertex2f(x1, y1)
    glVertex2f(x2, y2)
    glEnd()

def draw():
    glClearColor(0, 0, 0, 0)
    glClear(GL_COLOR_BUFFER_BIT)
    line(location_x, location_y, location_x2, location_y2)
    glColor3f(1.0, 1.0, 1.0)
    point(location_x, location_y, r, g, b)
    glFlush()

def mouse(button, state, x, y):
    global location_x, location_y
    if button == GLUT_LEFT_BUTTON:
        if state == GLUT_DOWN:
            location_x = x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0
            location_y = 1.0 - y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0
    glutPostRedisplay()

def keyboard(key, x, y):
    global r, g, b
    if key == b'1':
        r, g, b = 1.0, 0.0, 0.0
    elif key == b'2':
        r, g, b = 0.0, 1.0, 0.0
    elif key == b'3':
        r, g, b = 1.0, 1.0, 0.0
    elif key == b'4':
        r, g, b = 1.0, 1.0, 1.0
    elif key == b'5':
        r, g, b = 0.5, 0.5, 0.0
    elif key == b'6':
        r, g, b = 0.2, 0.4, 0.6
    elif key == b'7':
        r, g, b = 1.0, 0.75, 0.8
    elif key == b'8':
        r, g, b = 1.0, 0.5, 0.0
    elif key == b'9':
        r, g, b = 0.5, 0.0, 1.0
    glutPostRedisplay()

def main():
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(50, 100)
    glutInitWindowSize(1000, 1000)
    glutCreateWindow("EX3")
    glutDisplayFunc(draw)
    glutMouseFunc(mouse)
    glutKeyboardFunc(keyboard)
    glutMainLoop()

if __name__ == "__main__":
    main()
