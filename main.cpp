/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/gl.h>
#include <windows.h>
#include <vector>
#include <Ponto.h>
#include <Pca.h>

using namespace std;
GLfloat angle, fAspect;
Ponto* vetorMedia;


/* GLUT callback Handlers */

void ReadFile(std::vector <Ponto>* pontos, int *np);
void calculaVetorDaMedia();
void drawVectorMean();
std::vector<Ponto> pontos;
float angX = 5.0;
float angY = 4.0;
float angZ = 5.0;
int np;
//GLfloat width = 1240.0;
//GLfloat height = 720.0;

static void resize()
{
    //const float ar = (float) width / (float) height;

   // glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect,0.0, 100);
    gluLookAt(angX, angY, angZ, 0.0, 0.0, 0.0,0,1,0);
    //glFrustum(-ar, ar, -6.0, 6.0, 6.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* desenhar eixos
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(10.0,0.0,0.0);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,10.0,0.0);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,10.0);
    glEnd();
*/
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
        for (unsigned int i=1;i<pontos.size();i++) {
            glVertex3f(pontos[i].coor[0],pontos[i].coor[1],pontos[i].coor[2]);
        }
    glEnd();
    glutSwapBuffers();
}
void drawVectorMean(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,0.0,1.0);

    glBegin(GL_POINTS);
        glVertex3f(vetorMedia->coor[0],vetorMedia->coor[1],vetorMedia->coor[2]);
    glEnd();
    glutSwapBuffers();
}


void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	resize();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= -10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 200) angle += 5;
		}
	resize();
	glutPostRedisplay();
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 's':
            angY -= 1;
            resize();
            //glTranslatef(0.0f,-10.0f,0.0f);
            break;
        case 'w':
            angY += 1;
            resize();
            //glTranslatef(0.0f,10.0f,0.0f);
            break;
        case 'z':
             glRotatef(-10.0f,0.0,0.0,1.0);
            break;
        case 'x':
             glRotatef(-10.0f,1.0,0.0,0.0);
            break;
        case 'y':
            for (int f=0;f<pontos.size();f++) {
                    pontos.at(f).rotaciona(-10.0);
            }
            //rotate();
            //glRotatef(-10.0f,0.0,1.0,0.0);
            break;
        case 'u':
         glRotatef(10.0f,0.0,1.0,0.0);
        break;
        case 'p':
            calculaVetorDaMedia();
            break;
    }

    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    //vetorMedia->coor[0] = 0.0;
    //vetorMedia->coor[1] = 0.0;
    //vetorMedia->coor[2] = 0.0;
    angle = 60;
    ReadFile(&pontos,&np);
    glutInit(&argc, argv);
    glutInitWindowSize(1480,700);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glClearColor(1.0,1.0,1.0,1.0);
    glutCreateWindow("PCA");

//    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);

    glutMainLoop();

    return EXIT_SUCCESS;
}


void ReadFile(std::vector<Ponto> *pontos, int *np){
    FILE *file;
    //file = fopen("C:\\Users\\Usuario\\Desktop\\suzannePDI.txt", "r");
    file = fopen("C:\\Users\\Usuario\\Desktop\\monkeyTest.txt", "r");

    if (file== NULL) {
        printf("Problemas no arquivo");
        return;
    }

    fscanf(file, "%i",np);
    printf("\n numero de pontos: %i",*np);
    char letra;
    float x,y,z;
    int kl = 1;
    while ((fscanf(file,"%c %f %f %f", &letra, &x, &y, &z))!= EOF) {
        pontos->push_back(Ponto(x,y,z));
        printf("\n %f %f %f",x,y,z);
        printf("\ncontador:  %i",kl);
        kl++;
        //if (kl%100 == 0) system("PAUSE");
    }
    printf("\n tamanho do vetor: %i",pontos->size());
    fclose(file);
}
void calculaVetorDaMedia(){

    Pca* pca = new Pca(&pontos, vetorMedia);
;
}
