#include <freeglut.h>

void myDisplay(void)
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

	// send all output to display 
	glFlush();
}

void initializeGL() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

void main(int argc, char** argv)
{

	// initialize the toolkit
	glutInit(&argc, argv);

	// open the screen window
	glutCreateWindow("simple");

	// register redraw function
	glutDisplayFunc(myDisplay);

	initializeGL();

	// go into a perpetual loop
	glutMainLoop();
}

