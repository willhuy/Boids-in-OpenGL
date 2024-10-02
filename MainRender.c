#include "MainRender.h"

void renderBoid(Boid* boid) {

	// Get the angle from velocity x and y component
	float angle = atan2(boid->yVelocity, boid->xVelocity);
	
	// Vertex 1 from position as center point
	float xVertex1 = cos(angle) * BOID_SIZE + boid->xCoordinate;
	float yVertex1 = sin(angle) * BOID_SIZE + boid->yCoordinate;

	// I want to make an equilateral triangle angle, so angle has to be 60
	float xVertex2 = cos(angle + (2 * PI / 3)) * (BOID_SIZE - 0.01f) + boid->xCoordinate;
	float yVertex2 = sin(angle + (2 * PI / 3)) * (BOID_SIZE - 0.01f) + boid->yCoordinate;

	float xVertex3 = cos(angle - (2 * PI / 3)) * (BOID_SIZE - 0.01f) + boid->xCoordinate;
	float yVertex3 = sin(angle - (2 * PI / 3)) * (BOID_SIZE - 0.01f) + boid->yCoordinate;

	// Draw the triangle vertex
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
		chooseBoidColor(boidIndex);
		renderBoid(currentFlock[boidIndex]);
	}

	glEnd();

	// Draw the menu
	drawMenu();

	// Swap the double buffers
	glutSwapBuffers();
}

void chooseBoidColor(int boidIndex) {
	if (highlightedBoidIndex != -1 && highlightedBoidIndex < FLOCK_SIZE) {
		if (boidIndex == highlightedBoidIndex) {
			glColor3f(1.0, 0.0, 0.0); // Red for the boid being highlighted
		}
		else {
			findNearestNeighbors(currentFlock[highlightedBoidIndex], highlightedBoidIndex, &nearestNeighborOfBoid);
			for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {
				// If this is the neighbor of the highlighted boid
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
}

void drawMenu() {
	// Switch matrix mode to draw fixed menu
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Draw the menu area
	glColor3f(0.81f, 0.81f, 0.57f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f, -0.5f);
	glVertex2f(1.0f, -0.5f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();

	// Draw a small lines
	glLineWidth(4.0f);
	glColor3f(0.91f, 0.91f, 0.7f);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, -0.63f);
	glVertex2f(1.0f, -0.63f);
	glEnd();

	// Draw the button
	glColor3f(0.91f, 0.91f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.25f, -0.75f);
	glVertex2f(0.25f, -0.75f);
	glVertex2f(0.25f, -0.875f);
	glVertex2f(-0.25f, -0.875f);
	glEnd();

	// Initial drawing color to be black
	glColor3f(0.0f, 0.0f, 0.0f);

	// Position for the text and draw
	glRasterPos2f(-0.12f, -0.84f);
	char* s = "boids";
	for (int i = 0; i < 5; i++) {
		char letter = s[i];
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
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

	// NOTE: FREEGLUT DOENS'T DETECT MY LAPTOP PAGE UP AND PAGE DOWN KEY
	// THEREFORE, I'M USING THE 'w' key for increase speed and 's' for decrease speed
	// Increase speed
	if (key == 'w') {
		if (currentSetSpeed < MAX_SPEED) {
			currentSetSpeed += SPEED_STEP;
			printf("Speed: %f\n", currentSetSpeed);
		}
		else {
			printf("Maximum allowed speed reached\n");
		}
	}

	// Decrease speed
	if (key == 's') {
		if (currentSetSpeed > BOID_BASE_SPEED) {
			currentSetSpeed -= SPEED_STEP;
			printf("Speed: %f\n", currentSetSpeed);
		}
		else {
			printf("Minimum allowed speed reached\n");
		}
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

void update() {
	updateBoids();
	glutPostRedisplay();
	glutTimerFunc(FRAME_EXIST_TIME, update, 0);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 150);

	// open the screen window
	glutCreateWindow("Assignment 1");

	// register redraw function
	glutDisplayFunc(myDisplay);

	// register timer callback function
	glutTimerFunc(FRAME_EXIST_TIME, update, 0);

	// register keyboard input function
	glutKeyboardFunc(myKey);

	// Initialize OpenGL settings
	initializeGL();

	// Enter the program main loop
	glutMainLoop();
}
