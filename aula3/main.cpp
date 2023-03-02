#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>


struct Polar {
	double radius; // Distance to the point
	float alpha; // Angle in the ZoX plane
	float beta; // Angle in the Y plane
};

float polarToX(Polar coordinate) { return coordinate.radius * cos(coordinate.beta) * sin(coordinate.alpha); }
float polarToY(Polar coordinate) { return coordinate.radius * sin(coordinate.beta); }
float polarToZ(Polar coordinate) { return coordinate.radius * cos(coordinate.alpha) * cos(coordinate.beta); }
//distancia à origem,angulo polar do ponto p, angulo de elevação do ponto p
Polar p = { 10, M_PI_4, M_PI_4 };

float slices = 10;


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}




void drawCylinder(float radius, float height, int slices) {

	// put code to draw cylinder in here
	
	float meia_altura = height / 2.0;
	float amplitude = 2 * M_PI / slices;

	//EIXOS
	glBegin(GL_LINES);
	// X axis -> Red
	glColor3f(1.0f, 0.0, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	// Y axis -> Green
	glColor3f(0.0f, 1.0, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	// Z axis -> Blue
	glColor3f(0.0f, 0.0, 1.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);

	glEnd();


	for (int slice = 0; slice < 10; slice++) {
		//definir novo angulo a cada fatia que se cria
		float angulo = (float)slice * amplitude;
		float angulo_prox = angulo + amplitude;

		//desenhar os triangulos da base superior
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, meia_altura, 0.0f); //vertice centrado na origem e com altura meia_altura
		glVertex3f(sin(angulo) * radius, meia_altura, cos(angulo) * radius);
		glVertex3f(sin(angulo_prox) * radius, meia_altura, cos(angulo_prox) * radius);
		glEnd();

		//base inferior do cilindro
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, -meia_altura, 0.0f); //vertice centrado na origem e com altura -meia_altura
		glVertex3f(sin(angulo_prox) * radius, -meia_altura, cos(angulo_prox) * radius);
		glVertex3f(sin(angulo) * radius, -meia_altura, cos(angulo) * radius);
		glEnd();

		//desenhar parte lateral do cilindro
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0, 0.0f);
		glVertex3f(sin(angulo) * radius, meia_altura,cos(angulo)* radius);
		glVertex3f(sin(angulo) * radius, -meia_altura, cos(angulo)* radius);
		glVertex3f(sin(angulo_prox) * radius, meia_altura,cos(angulo_prox)* radius);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(sin(angulo_prox) * radius, meia_altura, cos(angulo_prox) * radius);
		glVertex3f(sin(angulo) * radius, -meia_altura, cos(angulo) * radius);
		glVertex3f(sin(angulo_prox) * radius, -meia_altura, cos(angulo_prox) * radius);
		glEnd();

	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(polarToX(p), polarToY(p), polarToZ(p),
		0.0, 0.0, 0.0,
		0.0f, p.beta > M_PI / 2 ? -1.0f : 1.0f, 0.0f);
	/*Este vetor define a orientação da câmera no espaço. Neste caso, o vetor está apontando para o eixo y, mas pode ser invertido (tornando-se -y) 
	dependendo do valor do ângulo p.beta. Se p.beta for maior que 90 graus (ou seja, a câmera está apontando para baixo), 
	o vetor para cima é invertido para apontar para baixo (no eixo negativo y), caso contrário, aponta para cima (eixo positivo y).*/

	drawCylinder(1,2,slices);

	// End of frame
	glutSwapBuffers();
	glutPostRedisplay();
}



void processKeys(unsigned char key, int xx, int yy) {
	// put code to process regular keys in here
	switch (key) {
	case 'a':
		p.alpha -= 0.5;
		break;
	case 'd':
		p.alpha += 0.5;
		break;
	case 's':
		p.beta -= 0.5;
		break;
	case 'w':
		p.beta += 0.5;
		break;
	case 'm':
		slices += 1;
		break;
	case 'n':
		slices -= 1;
		break;
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 'l':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}

void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here

}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
