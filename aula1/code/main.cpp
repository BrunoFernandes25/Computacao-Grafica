#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <C:\Users\ferna\OneDrive\Ambiente de Trabalho\Uni(22-23)\CG\toolkits\glut\GL\glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>


void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;
void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	//para teapot, cubo, torus
	gluLookAt(0.0f, 0.0f, 5.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f);
	/*
	auto ms = .. 
	double dimension ...
	
	Completar resolucao
	*/
	 
	
		//para a esfera
	/*gluLookAt(-15.0f, -10.0f, -5.0f,
		-1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f);
     */	

	//para o cone 
	/*
	gluLookAt(0.0f, 1.5f, 6.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	// coloca o cone na vertical
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	*/

	//faz rotação de 45º para a esquerda
	//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);


	/* translação sobre o eixo dos x
	static float angle = 0.0f;
	static float x = 0.0f;
	angle += 0.5f;
	x += 0.05f;
	glTranslatef(x,0.0f, 0.0f);
	*/

	/* translação sobre o eixo dos y
	static float angle = 0.0f;
	static float y = 0.0f;
	angle += 0.5f;
	y += 0.05f;
	glTranslatef(0.0f,y, 0.0f);
	*/
	
	//translação sobre o eixo dos z
	/*static float angle = 0.0f;
	static float z = 0.0f;
	angle += 0.5f;
	z += 0.05f;
	glTranslatef(0.0f,0.0f, z);
	*/

	// update rotation angle
	angle += 0.5f;
	

	// faz rotação da esfera sobre o eixo x
	//glRotatef(angle, 1.0f, 0.0f, 0.0f);
	// faz rotação da esfera sobre o eixo y
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	// faz rotação da esfera sobre o eixo z
	//glRotatef(angle, 0.0f, 0.0f, 1.0f);

	// put drawing instructions here
	glutWireTeapot(1);
	//glutWireCube(2);
	//glutWireSphere(3, 20, 20);
	//glutWireCone(1,2,8,10); //colocar camera sem ser pela vista de cima
	//glutWireTorus(0.5,1,20,16);
	// End of frame
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	// put GLUT�s init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI");
	
	// put callback registry here
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	
	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// enter GLUT�s main cycle
	glutMainLoop();
	
	return 1;
}