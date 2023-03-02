#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

float xpos = 0;
float zpos = 0;
float rodaz = 0;
float zvalue = 2.0;
float camerax = 6.0;
float cameray = 4.0;
float cameraz = 6.0;

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camerax, cameray, cameraz,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	// put axis drawing in here
	glBegin(GL_LINES);

	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);

	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glEnd();

	// put the geometric transformations here
	glTranslatef(xpos, 0, zpos);
	glRotated(rodaz, 0, 1, 0);
	glutPostRedisplay(); //cria um evento de pedido para desenhar

	// put pyramid drawing instructions here

		// draw triangles
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, zvalue, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, zvalue, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, zvalue, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.0f, zvalue, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();


	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void moves(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		zpos -= 0.8;
		break;
	case 'a':
		xpos -= 0.8;
		break;
	case 's':
		zpos += 0.8;
		break;
	case 'd':
		xpos += 0.8;
		break;
	case 'x':
		rodaz += 0.8;
		break;
	case 'z':
		rodaz -= 0.8;
		break;
	case 'm':
		zvalue += 0.1;
		break;
	case 'n':
		zvalue -= 0.1;
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
	case '7':
		camerax += 0.5;
		break;
	case '8':
		camerax -= 0.5;
		break;
	case '4':
		cameray += 0.5;
		break;
	case '5':
		cameray -= 0.5;
		break;
	case '1':
		cameraz += 0.5;
		break;
	case '2':
		cameraz -= 0.5;
		break;
	}
}




int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(moves);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}