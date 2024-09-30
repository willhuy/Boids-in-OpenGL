#include "MainRender.h"

void renderBoid(Boid* boid) {

	// Get the angle from velocity x and y component
	float angle = atan2(boid->yVelocity, boid->xVelocity);
	
	// Vertex 1 from position as center point
	float xVertex1 = cos(angle) * BOID_SIZE + boid->xCoordinate;
	float yVertex1 = sin(angle) * BOID_SIZE + boid->yCoordinate;

	// I want to make an equilateral triangle, so angle has to be 60
	float xVertex2 = cos(angle + (2 * PI / 3)) * BOID_SIZE + boid->xCoordinate;
	float yVertex2 = sin(angle + (2 * PI / 3)) * BOID_SIZE + boid->yCoordinate;

	float xVertex3 = cos(angle - (2 * PI / 3)) * BOID_SIZE + boid->xCoordinate;
	float yVertex3 = sin(angle - (2 * PI / 3)) * BOID_SIZE + boid->yCoordinate;

	glVertex2f(xVertex1, yVertex1);
	glVertex2f(xVertex2, yVertex2);
	glVertex2f(xVertex3, yVertex3);
}

void myDisplay()
{
	// clear the screen 
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the boid as triangles
	glBegin(GL_TRIANGLES);

	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		renderBoid(currentFlock[boidIndex]);
	}

	glEnd();

	// Swap the double buffers
	glutSwapBuffers();
}

void myIdle() {
	glutPostRedisplay();
}

void initializeGL() {
	// Background set to block
	glClearColor(0, 0, 0, 1);

	// Set drawing color to be blue
	glColor3f(0.0, 0.0, 1.0);

	// Set matrix mode
	glMatrixMode(GL_PROJECTION);

	// Load the identity matrix
	glLoadIdentity();

	// Set window mode to 2D orthographic and set the window size 
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void main(int argc, char** argv)
{
	printf("\n\n\nScreen Controls:\n");
	printf("----------------------\n");
	printf("Page Up : faster\n");
	printf("Page Down : slower\n");
	printf("[1 - 9] : highlight boid and its neighbors\n");
	printf("0 : turn off highlighting\n");
	printf("q : quit\n\n\n");
	printf("Note : may need to use FN key to use Page Up and Page Down on Laptops.\n");

	// Set the seed for rand() function
	srand(time(NULL));

	initializeBoidManager();

	// Create boids with random coordinate and velocity
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
