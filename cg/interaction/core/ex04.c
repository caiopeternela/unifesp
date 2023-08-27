#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

int mode = 0; // 0 = line, 1 = triangle
float vertices[6];
int num_vertices;
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

void triangle(float *vertices) {
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
		glVertex2f(vertices[0], vertices[1]);
		glVertex2f(vertices[2], vertices[3]);
		glVertex2f(vertices[4], vertices[5]);
	glEnd();
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

	if (mode == 0 && num_vertices == 6) {
		triangle(vertices);
	} else if (mode == 1) {
		line(location_x, location_y, location_x2, location_y2);
	}

	glColor3f(1.0, 1.0, 1.0);

	if (mode == 0) {
		for (int i = 0; i < num_vertices; i += 2) {
			point(vertices[i], vertices[i + 1], r, g, b);
		}
	} else {
		point(location_x, location_y, r, g, b);
	}

	glFlush();
}

void mouse(int button, int state, int x, int y) {
	float mouseX = (float) x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
	float mouseY = 1.0 - (float) y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0;

	if (mode == 0) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (num_vertices == 6) {
				num_vertices = 0;
			} else if (num_vertices < 6) {
					vertices[num_vertices++] = mouseX;
					vertices[num_vertices++] = mouseY;
				}
			}
	} else if (mode == 1) {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				location_x = mouseX;
				location_y = mouseY;
			}
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
			r = 0.25, g = 0.5, b = 0.75;
			break;
		case '7':
			r = 1.0, g = 0.75, b = 0.75;
			break;
		case '8':
			r = 1.0, g = 0.5, b = 0.0;
			break;
		case '9':
			r = 0.5, g = 0.0, b = 1.0;
			break;
		case 'r':
		case 'R':
			mode = 1;
			break;
		case 't':
		case 'T':
			mode = 0;
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
	glutCreateWindow("EX4");
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}