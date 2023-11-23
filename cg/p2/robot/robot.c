#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// A animação padrão é a de polichinelo, a de abraço é acionada com B e pra voltar P

int abraco = 0;
float x_angle = 0.0;
float y_angle = 0.0;
float theta = 0.0;

float x = 0.0;
float y = 0.0;
float z = 1.0;

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 6

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "earthTexture.bmp",
        "surface1.bmp",
        "surface2.bmp",
        "surface3.bmp",
        "surface4.bmp",
        "surface5.bmp"
};

GLUquadricObj *obj;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
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

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}

/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                /* texture_id = vetor que guardas os números das texturas */

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
    CarregaTexturas();

}

void lightning(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);               //espalhamento angular
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);              //atenuação angular
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void)
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(4.0, 2.0, 6.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    gluPerspective(20.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva
    glViewport(0, 0, 500, 500);

    lightning();
}

void cube() {  
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glBegin(GL_POLYGON);
    glNormal3f(-0.25,0.25,0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,0.25,0.25);

    glNormal3f(0.25,0.25,0.25);
    glTexCoord2f(0.25,0.25);
    glVertex3f(0.25,0.25,0.25);

    glNormal3f(0.25,-0.25,0.25);
    glTexCoord2f(0.25,-0.25);
    glVertex3f(0.25,-0.25,0.25);

    glNormal3f(-0.25,-0.25,0.25);
    glTexCoord2f(-0.25,-0.25);
    glVertex3f(-0.25,-0.25,0.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glBegin(GL_POLYGON);
    glNormal3f(-0.25,0.25,-0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,0.25,-0.25);

    glNormal3f(0.25,0.25,-0.25);
    glTexCoord2f(0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);

    glNormal3f(0.25,-0.25,-0.25);
    glTexCoord2f(0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);

    glNormal3f(-0.25,-0.25,-0.25);
    glTexCoord2f(-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glBegin(GL_POLYGON);
    glNormal3f(0.25,-0.25,0.25);
    glTexCoord2f(0.25,-0.25);
    glVertex3f(0.25,-0.25,0.25);

    glNormal3f(0.25,0.25,0.25);
    glTexCoord2f(0.25,0.25);
    glVertex3f(0.25,0.25,0.25);

    glNormal3f(0.25,0.25,-0.25);
    glTexCoord2f(0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);

    glNormal3f(0.25,-0.25,-0.25);
    glTexCoord2f(0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glBegin(GL_POLYGON);
    glNormal3f(-0.25,-0.25,0.25);
    glTexCoord2f(-0.25,-0.25);
    glVertex3f(-0.25,-0.25,0.25);

    glNormal3f(-0.25,0.25,0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,0.25,0.25);

    glNormal3f(-0.25,0.25,-0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,0.25,-0.25);

    glNormal3f(-0.25,-0.25,-0.25);
    glTexCoord2f(-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glBegin(GL_POLYGON);
    glNormal3f(-0.25,0.25,0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,0.25,0.25);

    glNormal3f(0.25,0.25,0.25);
    glTexCoord2f(0.25,0.25);
    glVertex3f(0.25,0.25,0.25);

    glNormal3f(0.25,0.25,-0.25);
    glTexCoord2f(0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);

    glNormal3f(-0.25,0.25,-0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,0.25,-0.25);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glBegin(GL_POLYGON);
    glNormal3f(-0.25,0.25,0.25);
    glTexCoord2f(-0.25,0.25);
    glVertex3f(-0.25,-0.25,0.25);

    glNormal3f(0.25,-0.25,0.25);
    glTexCoord2f(0.25,-0.25);
    glVertex3f(0.25,-0.25,0.25);

    glNormal3f(0.25,-0.25,-0.25);
    glTexCoord2f(0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);

    glNormal3f(-0.25,-0.25,-0.25);
    glTexCoord2f(-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
  glEnd();
}

void head(){
  glPushMatrix();
  glTranslatef(0.0,0.65,0.0);
  glScalef(0.25,0.25,0.25);
  glTranslatef(0.0,0.25,0.0);
  cube();
  glPopMatrix();
}

void body(){
  glPushMatrix();
  glTranslatef(0.0,0.25,0.0);
  glScalef(0.25,0.75,0.25);
  glTranslatef(0.0,0.25,0.0);
  cube();
  glPopMatrix();
}

void rightArm(){
  glPushMatrix();
  glTranslatef(0.0,0.6,0.0);
  if(abraco == 1)
    glRotatef(theta, 0.0, 1.0, 0.0);
  else
    glRotatef(theta, 0.0, 0.0, 1.0);
  glTranslatef(0.1,-0.05,0.0);
  glScalef(0.25,0.125,0.125);
  glTranslatef(0.25,0.25,0.0);
  cube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.6,0.0);
  if(abraco == 1)
    glRotatef(theta, 0.0, 1.0, 0.0);
  else
    glRotatef(theta, 0.0, 0.0, 1.0);
  glTranslatef(0.25,-0.05,0.0);
  if(abraco == 1)
    glRotatef(theta, 0.0, 1.0, 0.0);
  else
    glRotatef(theta, 0.0, 0.0, 1.0);
  glScalef(0.25,0.125,0.125);
  glTranslatef(0.25,0.25,0.0);
  cube();
  glPopMatrix();
}

void leftArm(){
  glPushMatrix();
  glScalef(-1.0,1.0,1.0);
  rightArm();
  glPopMatrix();
}

void rightLeg() {
  glPushMatrix();
  glTranslatef(0.0,0.25,0.0);
  
  if(abraco == 0){
    glRotatef(theta, 0.0, 0.0, 1.0);    
  }
  glTranslatef(0.015,-0.225,0.0);
  glScalef(0.1,0.375,0.125);
  glTranslatef(0.25,0.25,0.0);
  cube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.25,0.0);
  if(abraco == 0){
    glRotatef(theta * 1.05, 0.0, 0.0, 1.0);    
  }
  glTranslatef(0.015,-0.44,0.0);
  glScalef(0.1,0.375,0.125);
  glTranslatef(0.25,0.25,0.0);
  cube();
  glPopMatrix();
}

void leftLeg() {
   glPushMatrix();
   glScalef(-1.0,1.0,1.0);
   rightLeg();
   glPopMatrix();
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();

  glRotatef(x_angle,1.0,0.0,0.0);
  glRotatef(y_angle,0.0,1.0,0.0);

  head();
  body();
  rightArm();
  leftArm();
  rightLeg();
  leftLeg();

  glPopMatrix();

  glFlush();
}

void special(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_RIGHT:
    y_angle += 2;
    theta += 2;
    break;
  case GLUT_KEY_LEFT:
    y_angle -= 2;
    theta -= 2;
    break;
  case GLUT_KEY_UP:
    x_angle += 2;
    theta += 2;
    break;
  case GLUT_KEY_DOWN:
    x_angle -= 2;
    theta -= 2;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
  switch (key){
    case 'W':
    case 'w':
        theta += 2.0;
        if(theta >= 45.0)
          theta = 45.0;
      break;
    case 'S':
    case 's':
        theta -= 2.0;
        if(theta <= 0.0)
          theta = 0.0;
      break;
    case 'A':
    case 'a':
      break;
    case 'D':
    case 'd':
      break;
    case 'B':
    case 'b':
      abraco = 1;
      break;
    case 'P':
    case 'p':
      abraco = 0;
      x = 0.0;
      y = 0.0;
      z = 1.0;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
      case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
          printf("x = %i, y = %i\n",x,y);
        break;
      default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("EX01");
  glutDisplayFunc(draw);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutSpecialFunc(special);
  init();
  initTexture();
  glutMainLoop();
  return 0;
}