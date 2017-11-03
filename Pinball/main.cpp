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

//Materiales
GLfloat madera_ambient[] = { 0.79f,0.49f,0.16f,1.0f };			// Color background
GLfloat madera_diffuse[] = { 0.5f,0.6f,0.75f,1.0f };			// Object Color main
GLfloat madera_specular[] = { 0.0f,0.16f,0.17f,1.0f };			// Specular color
GLfloat madera_shininess[] = { 50 };							// 1 to greatest

//Iluminación

GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };

//Texturas
CTexture skybox1;
CTexture skybox2;
CTexture skybox3;
CTexture skybox4;
CTexture fondo;

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

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

	objCamera.Position_Camera(0, 200, 100, 0, 100, 0, 0, 1,0);
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

void prisma(GLint texture)
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


void mesa_pinball() {
	glPushMatrix();
		glRotatef(9.462, 1, 0, 0);
		glPushMatrix();
			glScalef(60, 41.099, 118.366);
			prisma(fondo.GLindex);
		glPopMatrix();
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
		glPushMatrix();
			glTranslatef(20, 10.549, 59.183);
			glRotatef(90, 1, 0, 0);
			glScalef(5, 3, 5);
			cilindro(30);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, -30, -61.576);
		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glScalef(116.756, 19.454, 60);
			prisma_tr();
		glPopMatrix();
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
		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
			glScalef(40.54, 6.756, 60);
			prisma_tr();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -30, -6.622);
			glPushMatrix();
				glScalef(60, 60, 13.244);
				prisma();
			glPopMatrix();
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
		glPushMatrix();
			glTranslatef(0, 35, -3.244);
			glScalef(80, 70, 20);
			prisma();
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
				glMaterialfv(GL_FRONT, GL_AMBIENT, madera_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, madera_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, madera_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, madera_shininess);
				mesa_pinball();
			glPopMatrix();
			glColor3f(1.0,1.0,1.0);
		glPopMatrix(); 

	glPopMatrix();

	

	glutSwapBuffers();
	// Swap The Buffers
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
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
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
		objCamera.UpDown_Camera(CAMERASPEED + 0.2);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED - 0.2);
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
	glutMainLoop();          // 

	return 0;
}
