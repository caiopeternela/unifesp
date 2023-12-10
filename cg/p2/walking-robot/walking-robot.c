#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BMPImage {
    int   width;
    int   height;
    char *data;
} BMPImage;

#define MAX_NO_TEXTURES 6

GLuint texture_id[MAX_NO_TEXTURES];
char* filenameArray[MAX_NO_TEXTURES] = {
    "surface2.bmp", "surface2.bmp", "surface2.bmp",
    "surface2.bmp", "surface2.bmp", "surface2.bmp"
};

GLfloat angleY = 0.0f;
bool rising = false;
bool walking = false;
float theta = 0.0f, legTheta = 0.0f;

void getBitmapImageData( char *pFileName, BMPImage *pImage ) {
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    char charTemp;
    for(i = 0; i < nTotalImagesize; i += 3 ) {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}

void loadTextures() {
    BMPImage textura;

    glGenTextures(MAX_NO_TEXTURES, texture_id);

    for (int i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void lightning() {
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void) {
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 2.0, 8.0);
    glViewport(0, 0, 500, 500);

    lightning();
}

void initTexture (void) {
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    loadTextures();
}

void cube() {
     float size = 1.0;
     GLfloat n[6][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
     };
     GLint faces[6][4] = {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
     };
     GLfloat v[8][3];
     GLint i;

     v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
     v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
     v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
     v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
     v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
     v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

     for (i = 5; i >= 0; i--) {
         glBindTexture(GL_TEXTURE_2D, texture_id[i]);
         glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f,0.0f);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1.0f,0.0f);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f,1.0f);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0.0f,1.0f);
            glVertex3fv(&v[faces[i][3]][0]);
         glEnd();
     }
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glRotatef(angleY,0.0,1.0,0.0);
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(0.0, 2.4, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glScalef(0.8, 1.0, 0.5);
    glTranslatef(0.0, 0.4, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glScalef(0.125, 0.125, 0.125);
    glTranslatef(4.5, 6.0, 0.0);
    glutSolidCube(2.575);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glTranslatef(2.8, 0.75, 0.0);
    glRotatef(theta,1.0,0.0,0.0);
    glTranslatef(-2.8, -0.75, 0.0);
    glScalef(0.2, 0.7, 0.2);
    glTranslatef(2.8, 0.75, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glTranslatef(5.65, 0.5, 0.0);
    glRotatef(theta,1.0,0.0,0.0);
    glTranslatef(-5.65, -0.5, 0.0);
    glScalef(0.1, 0.1, 0.1);
    glTranslatef(5.65, 0.5, 0.0);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glTranslatef(2.8, 0.5, 0.0);
    glRotatef(theta,1.0,0.0,0.0);
    glTranslatef(-2.8, -0.5, 0.0);
    glScalef(0.2, 0.7, 0.2);
    glTranslatef(2.8, -0.5, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glScalef(0.125, 0.125, 0.125);
    glTranslatef(-4.5, 6.0, 0.0);
    glutSolidCube(2.575);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glTranslatef(-2.8, 0.75, 0.0);
    glRotatef(-theta,1.0,0.0,0.0);
    glTranslatef(2.8, -0.75, 0.0);
    glScalef(0.2, 0.7, 0.2);
    glTranslatef(-2.8, 0.75, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glTranslatef(-5.65, 0.5, 0.0);
    glRotatef(-theta,1.0,0.0,0.0);
    glTranslatef(5.65, -0.5, 0.0);
    glScalef(0.1, 0.1, 0.1);
    glTranslatef(-5.65, 0.5, 0.0);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glTranslatef(-2.8, 0.5, 0.0);
    glRotatef(-theta,1.0,0.0,0.0);
    glTranslatef(2.8, -0.5, 0.0);
    glScalef(0.2, 0.7, 0.2);
    glTranslatef(-2.8, -0.5, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glRotatef(-theta, 1.0, 0.0, 0.0);
    glScalef(0.3, 0.8, 0.3);
    glTranslatef(0.65, -0.65, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glRotatef(theta,1.0,0.0,0.0);
    glScalef(0.135, 0.135, 0.135);
    glTranslatef(-1.4, -7.6, 0.0);
    glutSolidCube(2.25);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glRotatef(-theta,1.0,0.0,0.0);
    glTranslatef(0.65, -1.8, 0.0);
    glRotatef(fabsf(legTheta),1.0,0.0,0.0);
    glTranslatef(-0.65, 1.8, 0.0);
    glScalef(0.3, 0.8, 0.3);
    glTranslatef(0.65, -1.8, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glRotatef(theta, 1.0, 0.0, 0.0);
    glScalef(0.3, 0.8, 0.3);
    glTranslatef(-0.65, -0.65, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glRotatef(-theta,1.0,0.0,0.0);
    glScalef(0.135, 0.135, 0.135);
    glTranslatef(1.4, -7.6, 0.0);
    glutSolidCube(2.25);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleY,0.0,1.0,0.0);
    glRotatef(theta,1.0,0.0,0.0);
    glTranslatef(-0.65, -1.8, 0.0);
    glRotatef(fabsf(legTheta),1.0,0.0,0.0);
    glTranslatef(0.65, 1.8, 0.0);
    glScalef(0.3, 0.8, 0.3);
    glTranslatef(-0.65, -1.8, 0.0);
    cube();
    glPopMatrix();

    glFlush();
}

void keyboardFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            walking = true;
            break;
        case GLUT_KEY_DOWN:
            walking = true;
            break;
        case GLUT_KEY_LEFT:
            angleY-=15;
           break;
        case GLUT_KEY_RIGHT:
           angleY+=15;
           break;
        default:
           break;
    }
    glutPostRedisplay() ;
}

void updateThetaAndRising() {
    if (theta == 40.0) {
        rising = false;
    } else if (theta == -40.0) {
        rising = true;
    }

    if (rising) {
        theta += 2.0;
        legTheta += 1.0;
    } else {
        theta -= 2.0;
        legTheta -= 1.0;
    }

    if (legTheta > 20.0) legTheta = 20.0;
}

void timerFunc(int value) {
    if (walking || theta != 0.0) {
        updateThetaAndRising();
    }

    walking = false;

    glutPostRedisplay();
    glutTimerFunc(100, timerFunc, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Walking Robot");
    init();
    initTexture();
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(keyboardFunc);
    glutTimerFunc(100, timerFunc, 0);
    glutMainLoop();

    return 0;
}