#include <freeglut.h>

#include "boidManager.h"

void myDisplay()
{
	/* Draw the boids */
	// clear the screen 
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the top rectangle
	glBegin(GL_TRIANGLES);

		for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
			glVertex2f(listOfBoids[boidIndex]->x, listOfBoids[boidIndex]->y);
		}

	glEnd();

	// Swap the double buffers
	glutSwapBuffers();
}

void myIdle() {
	glutPostRedisplay();
}

void initializeGL() {
	glClearColor(0, 0, 0, 1);
	glColor3f(0.0, 0.0, 1.0);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void main(int argc, char** argv)
{

	// Create boids with random coordinate
	createBoids();

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

