//Semestre 2018 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
#include "Main.h"
#include "texture.h"
#include "Camera.h"
//#include <cctype>

#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "cmodel/CModel.h"

using namespace std;

const float PI = 3.14159265359;
float red[3] = { 1.0, 0.0, 0.0 };
float green[3] = { 0.0,1.0,0.0 };
float blue[3] = { 0.0,0.0,1.0 };
float white[3] = { 1.0,1.0,1.0 };

//Variables para visualizar escenario
float rotX = 0.0;
float rotY = 0.0;
float rotZ = 0.0;
float transX = 0.0;
float transY = 0.0;
float transZ = -200.0;

//Animaciones
GLfloat escala_palanca = 1.0;
GLfloat escala_resorte = 1.0;
bool animacion_canica1 = false;
enum estados_canica1 {
	RESORTE1,
	RESORTE2,
	SUBE,
	REBOTE1,
	REBOTE2,
	REBOTE3,
	BAJA,
	REGRESA
};
int estado_c1 = RESORTE1;
float mov_c1_x = 0.0;
float mov_c1_y = 0.0;
float mov_c1_z = 0.0;

//Materiales mesa
GLfloat madera_ambient[] = { 0.79f,0.49f,0.16f,1.0f };			// Color background
GLfloat madera_diffuse[] = { 0.5f,0.6f,0.75f,1.0f };			// Object Color main
GLfloat madera_specular[] = { 0.0f,0.16f,0.17f,1.0f };			// Specular color
GLfloat madera_shininess[] = { 50 };							// 1 to greatest

//canica 1
GLfloat canicaUno_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
GLfloat canicaUno_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
GLfloat canicaUno_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
GLfloat canicaUno_shininess[] = { 51.2f };

//canica 2
GLfloat canicaDos_ambient[] = { 0.0f,0.05f,0.0f,1.0f };
GLfloat canicaDos_diffuse[] = { 0.4f,0.5f,0.4f,1.0f };
GLfloat canicaDos_specular[] = { 0.04f,0.7f,0.04f,1.0f };
GLfloat canicaDos_shininess[] = { 10.0f };

//piedras
GLfloat piedras_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat piedras_diffuse[] = { 0.55f,0.55f,0.55f,1.0f };
GLfloat piedras_specular[] = { 0.70f,0.70f,0.70f,1.0f };
GLfloat piedras_shininess[] = { 32.0f };

//vidrio
GLfloat vidrio_ambient[] = { 0.0f,0.28f,0.83f,0.4f };
GLfloat vidrio_diffuse[] = { 0.17f,0.64f,0.32f,0.4f };
GLfloat vidrio_specular[] = { 0.07f,0.32f,0.76f,0.4f };
GLfloat vidrio_shininess[] = { 47.0f };

//flik
GLfloat flik_ambient[] = { 0.0f,0.33f,0.33f,1.0f };
GLfloat flik_diffuse[] = { 0.09f,0.52f,1.0f,1.0f };
GLfloat flik_specular[] = { 0.37f,0.56f,0.78f,1.0f };
GLfloat flik_shininess[] = { 65.0f };

//Flippers y resorte
GLfloat silver_ambient[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
GLfloat silver_diffuse[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
GLfloat silver_specular[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
GLfloat silver_shininess[] = { 89.6f };

//Iluminación
GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };

//luz_uno
GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light1_diffuse[] = { 0.0, 0.8, 0.0, 1.0 };
GLfloat light1_specular[] = { 1.0, 0.0, 0.0, 0.0 };
GLfloat Pos[] = { 0.0, 90.0, 0.0, 1.0 };
GLfloat PosUno[] = { 0.0, 0.0, 0.0, 1.0 };

//luz_dos
GLfloat light2_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light2_diffuse[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat light2_specular[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat PosDos[] = { 0.0, 00.0, 270.0, 1.0 };
GLfloat PosDos_[] = { 0.0, 0.0, 0.0, 1.0 };

//Texturas
CTexture skybox1;
CTexture skybox2;
CTexture skybox3;
CTexture skybox4;
CTexture fondo;
CTexture tablero_score;
CTexture dot;
CTexture heimlich;
CTexture hopper;

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

//flags
bool flag_luz = true;
bool flag_luz_uno = true;
bool flag_luz_dos = true;

bool flag_flipper_uno = false;
bool flag_flipper_dos = false;
bool flag_flipper_tres = true;

//3ds
CModel hongo3d;
CModel pajaro3d;
CModel resorte;

void InitGL(void)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	//Cargamos texturas
	skybox1.LoadTGA("texturas/textura1.tga");
	skybox1.BuildGLTexture();
	skybox1.ReleaseImage();

	skybox2.LoadTGA("texturas/textura2.tga");
	skybox2.BuildGLTexture();
	skybox2.ReleaseImage();

	skybox3.LoadTGA("texturas/textura3.tga");
	skybox3.BuildGLTexture();
	skybox3.ReleaseImage();

	skybox4.LoadTGA("texturas/textura4.tga");
	skybox4.BuildGLTexture();
	skybox4.ReleaseImage();

	fondo.LoadTGA("texturas/fondo_uno.tga");
	fondo.BuildGLTexture();
	fondo.ReleaseImage();

	tablero_score.LoadTGA("texturas/tablero_score.tga");
	tablero_score.BuildGLTexture();
	tablero_score.ReleaseImage();

	dot.LoadTGA("texturas/dot.tga");
	dot.BuildGLTexture();
	dot.ReleaseImage();

	heimlich.LoadTGA("texturas/Heimlich.tga");
	heimlich.BuildGLTexture();
	heimlich.ReleaseImage();

	hopper.LoadTGA("texturas/hopper.tga");
	hopper.BuildGLTexture();
	hopper.ReleaseImage();

	objCamera.Position_Camera(0, 200, 100, 0, 100, 0, 0, 1,0);

	//3ds
	hongo3d._3dsLoad("3ds/boletus.3ds");
	pajaro3d._3dsLoad("3ds/CHICKDEE.3DS");
	resorte._3dsLoad("3ds/spring.3DS");
}

//Primitivas 
void prisma()
{
	
	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
	};
	glBegin(GL_POLYGON);	//Front	
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[7]);
	glEnd();
}

void prisma_tr() {
	GLfloat vertice[6][3] = {
		{ 0.0,0.0,0.5 },
		{ 0.0,0.0,-0.5 },
		{ 1.0,0.0,0.5 },
		{ 1.0,0.0,-0.5 },
		{ 0.0,1.0,0.5 },
		{ 0.0,1.0,-0.5 }
	};
	glBegin(GL_POLYGON);	//Front		
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f, 1.0f, 0.0f);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[5]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();

}

void prisma_tr(GLint texture) {
	GLfloat vertice[6][3] = {
		{ 0.0,0.0,0.5 },
		{ 0.0,0.0,-0.5 },
		{ 1.0,0.0,0.5 },
		{ 1.0,0.0,-0.5 },
		{ 0.0,1.0,0.5 },
		{ 0.0,1.0,-0.5 }
	};
	glBegin(GL_POLYGON);	//Front		
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[2]);
	glEnd();
	
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_POLYGON);	//Right
			glNormal3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[2]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[5]);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();

}

void prisma(GLint texture,GLint mode)
{
	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
	};

	GLfloat verticeDos[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
		{ 0.5 ,-0.2, -0.5 },    //Coordenadas Vértice 3 V3
		{ 0.5 ,0.2, 0.5 },    //Coordenadas Vértice 4 V4
		{ 0.5 ,0.2, -0.5 },    //Coordenadas Vértice 5 V5
		{ -0.5 ,0.2, -0.5 },    //Coordenadas Vértice 6 V6
		{ -0.5 ,0.2, 0.5 },    //Coordenadas Vértice 7 V7
	};

	if (mode == 1) {
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_POLYGON);  //Top
			glNormal3f(0.0f, 1.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexCoord2f(1.0f, 0.0f); glVertex3fv(verticeDos[4]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(verticeDos[5]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(verticeDos[6]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(verticeDos[7]);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	else if (mode == 0) {
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_POLYGON);  //Top
			glNormal3f(0.0f, 1.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	
	glBegin(GL_POLYGON);	//Front	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();
	
	
}

void cilindro(int resolucion) {
	GLint i;
	GLfloat theta, thetan;
	GLfloat centro_base[] = { 0.0,0.0,0.0 };
	GLfloat centro_altura[] = { 0.0,1.0,0.0 };

	for (i = 0; i < resolucion; i++) {
		theta = (2 * PI * i / resolucion);
		thetan = (2 * PI * (i + 1) / resolucion);
		glBegin(GL_POLYGON);
			glNormal3f(0.5*cos(theta), 0.0f, 0.5*sin(theta));
			glVertex3f(0.5*cos(theta), 0, 0.5*sin(theta));
			glVertex3f(0.5*cos(theta), 1, 0.5*sin(theta));
			glVertex3f(0.5*cos(thetan), 1, 0.5*sin(thetan));
			glVertex3f(0.5*cos(thetan), 0, 0.5*sin(thetan));
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.5*cos(theta), 0, 0.5*sin(theta));
			glVertex3fv(centro_base);
			glVertex3f(0.5*cos(thetan), 0, 0.5*sin(thetan));
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5*cos(theta), 1, 0.5*sin(theta));
			glVertex3fv(centro_altura);
			glVertex3f(0.5*cos(thetan), 1, 0.5*sin(thetan));
		glEnd();
	}
}

void skybox(float altura, float largo, float profundidad)
{

	GLfloat vertice[8][3] = {
		{ 0.5*largo ,-0.5*altura, 0.5*profundidad },    //Coordenadas Vértice 1 V1
		{ -0.5*largo ,-0.5*altura , 0.5*profundidad },    //Coordenadas Vértice 2 V2
		{ -0.5*largo ,-0.5*altura , -0.5*profundidad },    //Coordenadas Vértice 3 V3
		{ 0.5*largo ,-0.5*altura , -0.5*profundidad },    //Coordenadas Vértice 4 V4
		{ 0.5*largo ,0.5*altura , 0.5*profundidad },    //Coordenadas Vértice 5 V5
		{ 0.5*largo ,0.5*altura , -0.5*profundidad },    //Coordenadas Vértice 6 V6
		{ -0.5*largo ,0.5*altura , -0.5*profundidad },    //Coordenadas Vértice 7 V7
		{ -0.5*largo ,0.5*altura , 0.5*profundidad },    //Coordenadas Vértice 8 V8
	};

	glBindTexture(GL_TEXTURE_2D, skybox1.GLindex);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox2.GLindex);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox3.GLindex);   // choose the texture to use.
	glBegin(GL_POLYGON);  //Left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox4.GLindex);   // choose the texture to use.
	glBegin(GL_POLYGON);  //Back
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();
}

void canica_uno(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, canicaUno_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, canicaUno_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, canicaUno_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, canicaUno_shininess);

	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

void canica_dos(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, canicaDos_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, canicaDos_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, canicaDos_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, canicaDos_shininess);

	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

void piedra(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, piedras_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, piedras_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, piedras_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, piedras_shininess);

	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

void foco(GLfloat radio, int meridianos, int paralelos, GLuint text)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, madera_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, madera_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, madera_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, madera_shininess);

	GLdouble theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

//luces
void luz_uno() {
	glPushMatrix();	
		glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light1_specular);

		glLightfv(GL_LIGHT2, GL_POSITION, Pos);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, PosUno);

		glEnable(GL_LIGHT2);
		glTranslatef(0, 130, 0);
		//foco(5, 30, 30, 0);
	glPopMatrix();
	//glDisable(GL_LIGHT2);
}

void luz_dos() {
	glPushMatrix();
	glLightfv(GL_LIGHT3, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light2_specular);

	glLightfv(GL_LIGHT3, GL_POSITION, PosDos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, PosDos_);

	glEnable(GL_LIGHT3);
	glTranslatef(0, 30, 0);
	//foco(5, 30, 30, 0);
	glPopMatrix();
	//glDisable(GL_LIGHT3);
}

void vidrio() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMaterialfv(GL_FRONT, GL_AMBIENT, vidrio_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, vidrio_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, vidrio_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, vidrio_shininess);

	GLfloat vertice[8][3] = {
					{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
					{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
					{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
					{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
					{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
					{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
					{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
					{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
				};
				glRotatef(9.462, 1, 0, 0);
				glScalef(60, 41.099, 118.366);
				glPushMatrix();
					glBegin(GL_POLYGON);	//Front	
					glNormal3f(0.0f, 0.0f, 1.0f);
					glVertex3fv(vertice[4]);
					glVertex3fv(vertice[5]);
					glVertex3fv(vertice[6]);
					glVertex3fv(vertice[7]);
					glEnd();
				glPopMatrix();
				glDisable(GL_BLEND);
}

void piedras_uno() {
	glPushMatrix();
		glTranslatef(-20, 3, 35);
		glScalef(1, 0.9, 1.5);
		piedra(0.5, 30, 30, 0);
		glPushMatrix();
			glTranslatef(0, 0.9, 0);
			glScalef(2, 0.9, 1);
			piedra(0.5, 30, 30, 0);
			glPushMatrix();
				glTranslatef(0, 0.8, 0);
				glScalef(2, 0.8, 2);
				piedra(0.5, 30, 30, 0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void piedras_dos() {
	glPushMatrix();
		glTranslatef(10, 13, -25);
		glScalef(1, 0.9, 1.5);
		piedra(0.5, 30, 30, 0);
			glPushMatrix();
				glTranslatef(0, 0.9, 0);
				glScalef(2, 0.9, 1);
				piedra(0.5, 30, 30, 0);
				glPushMatrix();
				glTranslatef(0, 0.8, 0);
				glScalef(2, 0.8, 2);
				piedra(0.5, 30, 30, 0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

//3ds
void hongo_uno() {
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.5, 0.1, 0.9);

	glPushMatrix();
		glScalef(0.05, 0.05, 0.05);
		glTranslatef(130, 80, 500);
		hongo3d.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void hongo_dos() {
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.05, 0.8, 0.8);
    glPushMatrix();
		glScalef(0.05, 0.05, 0.05);
		glTranslatef(-260, 215, -300);
		hongo3d.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void pajaro_uno() {
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.5, 0.05, 0.05);
	
	glPushMatrix();
		glScalef(200, 200, 200);
		glTranslatef(0, 0.022, 0.04);
		pajaro3d.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void pajaro_dos() {
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.9, 0.9, 0.05);

	glPushMatrix();
	glScalef(200, 200, 200);
	glRotatef(0, 0, -180, 1);
	glTranslatef(-0.1, 0.065, -0.2);
	pajaro3d.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void flik() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, flik_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, flik_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, flik_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, flik_shininess);

	float transZ = -5.0f;
	float transX = 0.0f;
	float transY = 0.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotY1 = 0.0f;
	float rotY3 = 0.0f;
	float rotY4 = 0.0f;
	float rotY7 = 0.0f;
	float rotX1 = 0.0f;
	float rotY10 = 0.0f;
	float rotY14 = 0.0f;

	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	glTranslatef(70.0, 4.5, 190.0);

	// Cuerpo
	glPushMatrix();

	glTranslatef(-2.0f, 0.0f, transZ);

	glPushMatrix(); //brazo der
	glTranslatef(0.3f, 0.0f, 0.0);
	glRotatef(rotY, 0, 1, 0);
	glTranslatef(1.05f, 1.5f, -0.5f);

	glPushMatrix();//antebrazo der
	glTranslatef(1.0f, 0.0f, 0.0);
	glRotatef(rotY1, 0, 1, 0);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(2.0, .75, 2.0);
	glRotatef(90, 1, 0, 0);
	prisma();
	glPopMatrix();

	glScalef(2.0, 1.0, 2.0);
	glRotatef(90, 1, 0, 0);
	prisma();
	glPopMatrix(); // Fin brazo der

	glPushMatrix(); //brazo izq
	glTranslatef(-0.3f, 0.0f, 0.0);
	glRotatef(rotY3, 0, 1, 0);
	glTranslatef(-1.05f, 1.5f, -0.5f);

	glPushMatrix();//antebrazo izq
	glTranslatef(-1.0f, 0.0f, 0.0);
	glRotatef(rotY4, 0, 1, 0);
	glTranslatef(-1.0f, 0.0f, 0.0f);
	glScalef(2.0, .75, 2.0);
	glRotatef(180, 1, 0, 0);
	prisma();
	glPopMatrix();


	glScalef(2.0, 1.0, 2.0);
	glRotatef(180, 1, 0, 0);
	prisma();
	glPopMatrix(); // Fin brazo izq

	glPushMatrix(); //muslo der
	glTranslatef(1.5f, 0.0f, 0.0);
	glRotatef(rotX, 1, 0, 0);
	glTranslatef(-0.5f, -3.5f, -0.5f);
	glRotatef(270, 0, 0, 1);

	glPushMatrix();//rodilla der
	glTranslatef(1.0f, 0.0f, 0.0);
	glRotatef(rotY7, 0, 1, 0);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(2.0, .75, 2.0);
	glRotatef(270, 1, 0, 0);
	prisma();
	glPopMatrix();


	glScalef(2.0, 1.0, 2.0);
	glRotatef(270, 1, 0, 0);
	prisma();
	glPopMatrix(); // Fin pierna der

	glPushMatrix(); //muslo izq
	glTranslatef(1.5f, 0.0f, 0.0);
	glRotatef(rotX1, 1, 0, 0);
	glTranslatef(-2.5f, -3.5f, -0.5f);
	glRotatef(270, 0, 0, 1);

	glPushMatrix();//rodilla izq
	glTranslatef(1.0f, 0.0f, 0.0);
	glRotatef(rotY10, 0, 1, 0);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(2.0, .75, 2.0);
	glRotatef(270, 1, 0, 0);
	prisma();
	glPopMatrix();


	glScalef(2.0, 1.0, 2.0);
	glRotatef(270, 1, 0, 0);
	prisma();
	glPopMatrix(); // Fin pierna izq

	glPushMatrix(); //Cara
	glRotatef(rotY14, 0, 1, 0);  //Rotamiento de cabeza
	glTranslatef(0.0f, 3.5f, -0.4f);
	/*glRotatef(90, 0, 0, 1);
	glScalef(1.0, 1.0, 1.0);
	glRotatef(90, 0, 1, 0);*/
	//prisma();
	esfera(1, 30, 30, 0);
	glScalef(0.2, 2.5, 0.2);
	glTranslatef(3.0f, 0.0f, 0.0f);
	cilindro(30);
	glTranslatef(-3.0f, 0.0f, 0.0f);
	cilindro(30);

	glPopMatrix(); // Fin cara
	glTranslatef(0.0f, -2.0f, 0.0f);
	glScalef(1, 5, 1);
	cilindro(30);           // Cuerpo
	glPopMatrix(); // Fin cuerpo 

	glPushMatrix(); // Fin cuerpo 
	glScalef(1, 1, 2);
	glTranslatef(-2.0f, -2.0f, -2.0f);
	esfera(1, 30, 30, 0);
	glPopMatrix(); 
	glPopMatrix();
}

void spring() {
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
		glScalef(1, 1, 1);
		resorte.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void flippers() {

	glMaterialfv(GL_FRONT, GL_AMBIENT, silver_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, silver_shininess);

	glPushMatrix();
		glTranslatef(-5, 3, 45);
		glRotatef(-90, 0, 0, 1);
		if (flag_flipper_uno == false)
		{
			glRotatef(45, 1, 0, 0);
		}
		glScalef(2, 7, 2);
		cilindro(50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10, 3, 45);
		glRotatef(90, 0, 0, 1);
		if (flag_flipper_dos == false)
		{
			glRotatef(45, 1, 0, 0);
		}
		glScalef(2, 7, 2);
		cilindro(50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-20, 3, 37);
		glRotatef(-90, 0, 0, 1);
		glRotatef(45, 1, 0, 0);
		if (flag_flipper_tres == false)
		{
			glRotatef(-45, 1, 0, 0);
		}
		glScalef(2, 7, 2);
		cilindro(50);
	glPopMatrix();
}

void canal(int resolucion) {
	GLint i;
	GLfloat theta, thetan;
	GLfloat centro_base[] = { 0.0,0.0,0.0 };

	for (i = 0; i < resolucion / 2; i++) {
		theta = (2 * PI * i / resolucion);
		thetan = (2 * PI * (i + 1) / resolucion);
		glBegin(GL_POLYGON);
			glNormal3f(0.5*cos(theta), 0.0f, 0.5*sin(theta));
			glVertex3f(0.5*cos(theta), 0, 0.5*sin(theta));
			glVertex3f(0.5*cos(theta), 1, 0.5*sin(theta));
			glVertex3f(0.5*cos(thetan), 1, 0.5*sin(thetan));
			glVertex3f(0.5*cos(thetan), 0, 0.5*sin(thetan));
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.5*cos(theta), 0, 0.5*sin(theta));
			glVertex3fv(centro_base);
			glVertex3f(0.5*cos(thetan), 0, 0.5*sin(thetan));
		glEnd();
		
	}
}

void mesa_pinball() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, madera_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, madera_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, madera_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, madera_shininess);
	glPushMatrix();
		glRotatef(9.462, 1, 0, 0);
		//Caja principal
		glPushMatrix();
			glScalef(60, 41.099, 118.366);
			prisma(fondo.GLindex,1);
		glPopMatrix();
		//Estructuras adicionales
		for (int i = 0; i < 10; i++) {
			glPushMatrix();
				glTranslatef(27, 8.11, -53.2647 + 11.8366 * i);
				glPushMatrix();
					glTranslatef(0, 4.06, 0);
					glScalef(6, 0.1, 11.8366);
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.1);
					prisma(dot.GLindex, 0);
					glDisable(GL_ALPHA_TEST);
				glPopMatrix();
				glScalef(6, 8, 11.8366);
				prisma();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-27, 8.11, -53.2647 + 11.8366 * i);
				glPushMatrix();
					glTranslatef(0, 4.06, 0);
					glScalef(6, 0.1, 11.8366);
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.1);
					prisma(dot.GLindex, 0);
					glDisable(GL_ALPHA_TEST);
				glPopMatrix();
				glScalef(6, 8, 11.8366);
				prisma();
			glPopMatrix();
		}
		glPushMatrix();
			glTranslatef(-14, 8.11, 54.183);
			glPushMatrix();
				glTranslatef(0, 4.06, 0);
				glScalef(20, 0.1, 10);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				prisma(heimlich.GLindex, 0);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			glScalef(20, 8, 10);
			prisma();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(7, 8.11, 55.683);
			glPushMatrix();
				glTranslatef(0, 4.06, 0);
				glScalef(22, 0.1, 7);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				prisma(heimlich.GLindex, 0);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			glScalef(22, 8, 7);
			prisma();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-24, 8.11, 49.183);
			glRotatef(-90, 1, 0, 0);
			glScalef(20, 10, 8);
			prisma_tr();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(18, 8.11, 49.183);
			glRotatef(-90, 1, 0, 0);
			glRotatef(180, 0, 1, 0);
			glScalef(10, 10, 8);
			prisma_tr();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-14, 8.11, 54.183);
			glPushMatrix();
				glTranslatef(0, 4.06, 0);
				glScalef(20, 0.1, 10);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				prisma(heimlich.GLindex, 0);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			glScalef(20, 8, 10);
			prisma();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(27, 8.11, -59.183);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			glScalef(10, 10, 8);
			prisma_tr(hopper.GLindex);
		glPopMatrix();
		//Botones flippers
		glPushMatrix();
			glTranslatef(-30, 10.549, 49.183);
			glRotatef(90, 0, 0, 1);
			glScalef(5, 3, 5);
			cilindro(30);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(30, 10.549, 49.183);
			glRotatef(-90, 0, 0, 1);
			glScalef(5, 3, 5);
			cilindro(30);
		glPopMatrix();
		//Palanca resorte
		glPushMatrix();
			glTranslatef(20, 10, 57.183);
			glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glPushMatrix();
					glTranslatef(0, 4 - 4 * (1 - escala_palanca), 0);
					glScalef(5, 3, 5);
					cilindro(30);
				glPopMatrix();
				glScalef(3, 4*escala_palanca, 3);
				cilindro(30);
			glPopMatrix();
			glPushMatrix();
				glPushMatrix();
					glTranslatef(-1.15, 0, 0);
					glScalef(0.3, 0.3, 0.25*escala_resorte);
					spring();
				glPopMatrix();
				glPushMatrix();
					glRotatef(-90, 1, 0, 0);
					glRotatef(180, 0, 1, 0);
					glScalef(3.3,100,3.3);
					canal(30);
				glPopMatrix();				
				glMaterialfv(GL_FRONT, GL_AMBIENT, madera_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, madera_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, madera_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, madera_shininess);
				
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, -30, -61.576);
		//Base
		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glScalef(116.756, 19.454, 60);
			prisma_tr();
		glPopMatrix();
		//Patas delanteras
		glPushMatrix();
			glTranslatef(-25, -60, 111.756);
			glScalef(10, 60, 10);
			cilindro(30);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(25, -60, 111.756);
			glScalef(10, 60, 10);
			cilindro(30);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 30, -61.576);
		//Base
		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
			glScalef(40.54, 6.756, 60);
			prisma_tr();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -30, -6.622);
			//Base
			glPushMatrix();
				glScalef(60, 60, 13.244);
				prisma();
			glPopMatrix();
			//Patas traseras
			glPushMatrix();
				glTranslatef(-25, -90, -1.622);
				glScalef(10, 60, 10);
				cilindro(30);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(25, -90, -1.622);
				glScalef(10, 60, 10);
				cilindro(30);
			glPopMatrix();
		glPopMatrix();
		//Tablero score
		glPushMatrix();
			glTranslatef(0, 35, -3.244);
			glRotatef(90, 1, 0, 0);
			glScalef(80, 20, 70);
			prisma(tablero_score.GLindex,0);
		glPopMatrix();
	glPopMatrix();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0, 150, 0);
				skybox(300.0, 500.0, 500.0);
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,90,0);
				mesa_pinball();
				
				piedras_uno();
				piedras_dos();

				hongo_uno();
				hongo_dos();

				pajaro_uno();
				pajaro_dos();
				glPushMatrix();
					glRotatef(9.462, 1, 0, 0);
					glTranslatef(20 + mov_c1_x, 10 + mov_c1_y, 50.5 + mov_c1_z);
					glScalef(3, 3, 3);
					canica_uno(0.5, 30, 30, 0);
				glPopMatrix();
				
				//canica_dos(0.5, 30, 30, 0);
				
				flik(); //canica 3

				flippers();

				
				

				vidrio(); //poner al final

				
				
				if (flag_luz == true)
				{
					glEnable(GL_LIGHTING);
				}
				else {
					glDisable(GL_LIGHTING);
				}
				if (flag_luz_uno == true)
				{
					luz_uno();
				}
				else {
					glDisable(GL_LIGHT2);
				}
				if (flag_luz_dos == true)
				{
					luz_dos();
				}
				else {
					glDisable(GL_LIGHT3);
				}


				glPopMatrix();
			glColor3f(1.0,1.0,1.0);
		glPopMatrix(); 

	glPopMatrix();
	glutSwapBuffers();
	// Swap The Buffers
}

void animacion() {
	if (animacion_canica1) {
		switch (estado_c1) {
		case RESORTE1:
			escala_resorte -= 0.05;
			escala_palanca += 0.025;
			mov_c1_z += 0.25;
			if (escala_resorte < 0.5) {
				estado_c1 = RESORTE2;
			}
			break;
		case RESORTE2:
			escala_resorte += 0.1;
			escala_palanca -= 0.05;
			mov_c1_z -= 0.5;
			if (escala_resorte > 1) {	
				estado_c1 = SUBE;
			}
			break;
		case SUBE:
			mov_c1_z -= 1;
			if (mov_c1_z < -104) {
				animacion_canica1 = false;
				estado_c1 = RESORTE1;
			}
			break;
		}
	}
	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 750.0);
	
	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED/4);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-CAMERASPEED/4);
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-CAMERASPEED/2);
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED/2);
		break;

	case 'z':
	case 'Z':
		if (flag_luz == false)
		{
			flag_luz = true;
		}
		else
		{
			flag_luz = false;
		}
		break;
	case 'x':
	case 'X':
		if (flag_luz_uno == true)
		{
			flag_luz_uno = false;
		}
		else
		{
			flag_luz_uno = true;
		}
		break;
	case 'c':
	case 'C':
		if (flag_luz_dos == true)
		{
			flag_luz_dos = false;
		}
		else
		{
			flag_luz_dos = true;
		}
		break;
	case 'n':
	case 'N':
		if (flag_flipper_uno == true)
		{
			flag_flipper_uno = false;
		}
		else
		{
			flag_flipper_uno = true;
		}
		break;
	case 'm':
	case 'M':
		if (flag_flipper_dos == true)
		{
			flag_flipper_dos = false;
		}
		else
		{
			flag_flipper_dos = true;
		}
		break;
	case 'b':
	case 'B':
		if (flag_flipper_tres == true)
		{
			flag_flipper_tres = false;
		}
		else
		{
			flag_flipper_tres = true;
		}
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void raton(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		animacion_canica1 = !animacion_canica1;
	}
}

int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Pinball"); // Nombre de la Ventana
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMouseFunc(raton);
	glutMainLoop();          // 

	return 0;
}
