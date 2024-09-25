#include <freeglut.h>

#define FLOCK_SIZE 40

void myDisplay()
{
	// clear the screen 
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the top rectangle
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.3, 0.7);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0, 0.7);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.3, 0.3);

	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(0, 0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.5, 0.3);

	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(0.5, 0);
	glEnd();

	// Swap the double buffers
	glutSwapBuffers();
}

void myIdle() {

}

void initializeGL() {
	glClearColor(0, 0, 0, 1);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void main(int argc, char** argv)
{

	// initialize the toolkit
	glutInit(&argc, argv);

	// Set inital display properties
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 150);

	// open the screen window
	glutCreateWindow("Assignment 1");

	// register redraw function
	glutDisplayFunc(myDisplay);

	// register idle function
	glutIdleFunc(myIdle);

	initializeGL();
	glutMainLoop();
}

