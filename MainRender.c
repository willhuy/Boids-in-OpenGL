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
		if (highlightedBoidIndex != -1) {
			if (boidIndex == highlightedBoidIndex) {
				glColor3f(1.0, 0.0, 0.0); // Red for the boid being highlighted
			}
			else {
				find6NearestNeighbors(currentFlock[highlightedBoidIndex], highlightedBoidIndex, &nearestNeighborOfBoid);
				for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {
					// If this is the neighbor of the highlighted boid
					printf("Current boid : %p, the nearest neighbors: %p\n", currentFlock[boidIndex], nearestNeighbors[neighborIndex]);
					if (currentFlock[boidIndex] == nearestNeighborOfBoid[neighborIndex]) {
						glColor3f(0.0, 1.0, 0.0); // Green for the highlighted boid's neighbors
						break;
					}
					else {
						glColor3f(0.0, 0.0, 1.0);
					}
				}
			}
		}
		else {
			glColor3f(0.0, 0.0, 1.0);
		}

		renderBoid(currentFlock[boidIndex]);
	}

	glEnd();

	// Swap the double buffers
	glutSwapBuffers();
}

void myIdle() {
	updateBoids();
	glutPostRedisplay();
}

void myKey(unsigned char key, int x, int y) {
	// User press 'q' to quit
	if (key == 'q') {
		printf("User press 'q'!\n");
		exit(0);
	}

	// User press number key from 1 to 9 to highlight the Boid
	if (key >= '1' && key <= '9') {
		printf("User press %c, the highlight boid index is %d\n", key, key - '1');
		highlightedBoidIndex = key - '1'; // Convert character to integer and minus 1 to get the index
	}

	// Un-highlight the boid
	if (key == '0') {
		highlightedBoidIndex = -1;
	}
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
	gluOrtho2D(LEFT_WALL_LIMIT, RIGHT_WALL_LIMIT, BOTTOM_WALL_LIMIT, TOP_WALL_LIMIT);
}

void main(int argc, char** argv)
{
	// Print out the control instructions
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

	// Create the boid manager containing the current, previoud flock and nearest neighbor list
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

	// register keyboard input function
	glutKeyboardFunc(myKey);

	// Initialize OpenGL settings
	initializeGL();

	// Enter the program main loop
	glutMainLoop();
}
