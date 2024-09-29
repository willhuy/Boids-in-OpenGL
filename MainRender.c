#include "MainRender.h"


void myDisplay()
{
	// clear the screen 
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the top rectangle
	glBegin(GL_TRIANGLES);
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set window mode to 2D orthographic and set the window size 
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void main(int argc, char** argv)
{

	//
	srand(time(NULL));

	initializeBoidManager();

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


//------------------------------------------------------------------------------------------

//#include <freeglut.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//
//#define PI 3.14159265
//#define NUM_TRIANGLES 1  // Number of triangles to render
//#define TRIANGLE_SIZE 0.05 // Size of the triangles
//
//// Function to generate random float in the range [min, max]
//float randomFloat(float min, float max) {
//    return min + ((float)rand() / RAND_MAX) * (max - min);
//}
//
//// Function to rotate a point (x, y) around a center (cx, cy) by angle (in radians)
//void rotatePoint(float* x, float* y, float cx, float cy, float angle) {
//    float s = sin(angle);
//    float c = cos(angle);
//
//    // Translate point to origin
//    float xnew = *x - cx;
//    float ynew = *y - cy;
//
//    // Rotate point
//    float xrot = xnew * c - ynew * s;
//    float yrot = xnew * s + ynew * c;
//
//    // Translate point back
//    *x = xrot + cx;
//    *y = yrot + cy;
//}
//
//// Function to generate triangle vertices from a center position
//void generateTriangle(float centerX, float centerY) {
//    // Calculate the other two vertices based on the center
//    float angle1 = PI / 3; // 60 degrees
//    float angle2 = -PI / 3; // -60 degrees
//
//    float x1 = centerX + TRIANGLE_SIZE * cos(angle1);
//    float y1 = centerY + TRIANGLE_SIZE * sin(angle1);
//
//    float x2 = centerX + TRIANGLE_SIZE * cos(angle2);
//    float y2 = centerY + TRIANGLE_SIZE * sin(angle2);
//
//    float x3 = centerX + TRIANGLE_SIZE / 2.0f;
//    float y3 = centerY - TRIANGLE_SIZE / 2.0f;
//
//    // Generate a random rotation angle in radians
//    float randomAngle = randomFloat(0.0f, 2.0f * PI);
//
//    // Rotate each vertex around the center
//    rotatePoint(&x1, &y1, centerX, centerY, randomAngle);
//    rotatePoint(&x2, &y2, centerX, centerY, randomAngle);
//    rotatePoint(&x3, &y3, centerX, centerY, randomAngle);
//
//    // Draw the triangle
//    glBegin(GL_TRIANGLES);
//    glVertex2f(centerX, centerY); // Center vertex
//    glVertex2f(x1, y1);           // First vertex
//    glVertex2f(x2, y2);           // Second vertex
//    glEnd();
//}
//
//// Display callback function
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // Set the color for the triangles
//    glColor3f(1.0f, 0.0f, 0.0f); // Red color
//
//    for (int i = 0; i < NUM_TRIANGLES; i++) {
//        float centerX = randomFloat(-0.5f, 0.5f);
//        float centerY = randomFloat(-0.5f, 0.5f);
//        generateTriangle(centerX, centerY);
//    }
//
//    glutSwapBuffers();
//}
//
//// Reshape callback function
//void reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set orthographic projection
//    glMatrixMode(GL_MODELVIEW);
//}
//
//// Main function
//int main(int argc, char** argv) {
//    srand(time(NULL)); // Seed for random number generation
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Random Triangles");
//
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
//
//    glutMainLoop();
//    return 0;
//}

// ---------------------------------------------------------------

//#include <freeglut.h>
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>
//#include <float.h>
//#include <stdio.h>
//
//#define FLOCK_SIZE 40
//#define NEIGHBORHOOD_SIZE 6
//#define M_PI 3.14159265
//#define MAX_SPEED 0.05f
//#define MIN_SPEED 0.01f
//#define WALL_AVOIDANCE_DISTANCE 0.1f
//#define NEIGHBOR_AVOID_DISTANCE 0.05f
//
//typedef struct {
//    float position[2]; // x and y position
//    float velocity[2]; // x and y components of the velocity (flying direction)
//} Boid;
//
//Boid flock[FLOCK_SIZE];
//Boid previousFlock[FLOCK_SIZE];
//float flockSpeed = 0.0000001f;
//int highlightedBoid = -1; // -1 means no boid is highlighted
//int showNeighbors = 0; // Track if we are highlighting neighbors
//
//// Utility function for random float in range [min, max]
//float randomFloat(float min, float max) {
//    return min + ((float)rand() / RAND_MAX) * (max - min);
//}
//
//// Calculate the Euclidean distance between two points
//float calculateDistance(float p1[2], float p2[2]) {
//    return sqrtf((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]));
//}
//
//// Limit the magnitude of a velocity vector (ensure speed is within limits)
//void limitSpeed(Boid* boid) {
//    float speed = sqrtf(boid->velocity[0] * boid->velocity[0] + boid->velocity[1] * boid->velocity[1]);
//    if (speed > MAX_SPEED) {
//        boid->velocity[0] *= MAX_SPEED / speed;
//        boid->velocity[1] *= MAX_SPEED / speed;
//    }
//    else if (speed < MIN_SPEED) {
//        boid->velocity[0] *= MIN_SPEED / speed;
//        boid->velocity[1] *= MIN_SPEED / speed;
//    }
//}
//
//// Initialize the boids with random positions and directions
//void initBoids() {
//    for (int i = 0; i < FLOCK_SIZE; i++) {
//        // Random position between (-0.5, 0.5)
//        flock[i].position[0] = randomFloat(-0.5f, 0.5f);
//        flock[i].position[1] = randomFloat(-0.5f, 0.5f);
//
//        // Random direction for velocity
//        float angle = randomFloat(0.0f, 2.0f * M_PI);
//        flock[i].velocity[0] = cos(angle) * flockSpeed;
//        flock[i].velocity[1] = sin(angle) * flockSpeed;
//    }
//}
//
//// Find the nearest NEIGHBORHOOD_SIZE neighbors for a given boid
//void findNearestNeighbors(Boid* boid, Boid* neighbors[]) {
//    float distances[FLOCK_SIZE];
//    for (int i = 0; i < FLOCK_SIZE; i++) {
//        if (&flock[i] != boid) {
//            distances[i] = calculateDistance(boid->position, flock[i].position);
//        }
//        else {
//            distances[i] = FLT_MAX; // Ignore self
//        }
//    }
//
//    // Sort the distances to find the nearest neighbors
//    for (int i = 0; i < NEIGHBORHOOD_SIZE; i++) {
//        int minIndex = -1;
//        float minDistance = FLT_MAX;
//        for (int j = 0; j < FLOCK_SIZE; j++) {
//            if (distances[j] < minDistance) {
//                minDistance = distances[j];
//                minIndex = j;
//            }
//        }
//        neighbors[i] = &flock[minIndex];
//        distances[minIndex] = FLT_MAX; // Mark as used
//    }
//}
//
//// Boid avoids the wall based on proximity
//void avoidWalls(Boid* boid) {
//    if (boid->position[0] < -1.0f + WALL_AVOIDANCE_DISTANCE)
//        boid->velocity[0] += 0.05f / fabs(boid->position[0] + 1.0f);
//    if (boid->position[0] > 1.0f - WALL_AVOIDANCE_DISTANCE)
//        boid->velocity[0] -= 0.05f / fabs(1.0f - boid->position[0]);
//    if (boid->position[1] < -1.0f + WALL_AVOIDANCE_DISTANCE)
//        boid->velocity[1] += 0.05f / fabs(boid->position[1] + 1.0f);
//    if (boid->position[1] > 1.0f - WALL_AVOIDANCE_DISTANCE)
//        boid->velocity[1] -= 0.05f / fabs(1.0f - boid->position[1]);
//
//    limitSpeed(boid);
//}
//
//// Align boid velocity with neighbors
//void alignWithNeighbors(Boid* boid, Boid* neighbors[]) {
//    float avgVelocity[2] = { 0.0f, 0.0f };
//    for (int i = 0; i < NEIGHBORHOOD_SIZE; i++) {
//        avgVelocity[0] += neighbors[i]->velocity[0];
//        avgVelocity[1] += neighbors[i]->velocity[1];
//    }
//    avgVelocity[0] /= NEIGHBORHOOD_SIZE;
//    avgVelocity[1] /= NEIGHBORHOOD_SIZE;
//
//    // Gradually align boid's velocity with average velocity of neighbors
//    boid->velocity[0] += (avgVelocity[0] - boid->velocity[0]) * 0.05f;
//    boid->velocity[1] += (avgVelocity[1] - boid->velocity[1]) * 0.05f;
//
//    // Limit the boid's speed
//    limitSpeed(boid);
//}
//
//// Boid avoids neighbors if too close
//void avoidNeighbors(Boid* boid, Boid* neighbors[]) {
//    for (int i = 0; i < NEIGHBORHOOD_SIZE; i++) {
//        float distance = calculateDistance(boid->position, neighbors[i]->position);
//        if (distance < NEIGHBOR_AVOID_DISTANCE) {
//            // Move away inversely proportional to distance
//            boid->velocity[0] -= (neighbors[i]->position[0] - boid->position[0]) / distance * 0.05f;
//            boid->velocity[1] -= (neighbors[i]->position[1] - boid->position[1]) / distance * 0.05f;
//        }
//    }
//}
//
//// Keep boids within the screen bounds
//void keepInBounds(Boid* boid) {
//    if (boid->position[0] < -1.0f) boid->position[0] = -1.0f;
//    if (boid->position[0] > 1.0f) boid->position[0] = 1.0f;
//    if (boid->position[1] < -1.0f) boid->position[1] = -1.0f;
//    if (boid->position[1] > 1.0f) boid->position[1] = 1.0f;
//}
//
//// Update all boids based on flocking rules
//void updateBoids() {
//    // Copy current flock state to previousFlock
//    for (int i = 0; i < FLOCK_SIZE; i++) {
//        previousFlock[i] = flock[i];
//    }
//
//    // Update each boid
//    for (int i = 0; i < FLOCK_SIZE; i++) {
//        Boid* boid = &flock[i];
//
//        // Calculate nearest neighbors
//        Boid* neighbors[NEIGHBORHOOD_SIZE];
//        findNearestNeighbors(boid, neighbors);
//
//        // Edge avoidance
//        if (boid->position[0] < -1.0f + WALL_AVOIDANCE_DISTANCE || boid->position[0] > 1.0f - WALL_AVOIDANCE_DISTANCE ||
//            boid->position[1] < -1.0f + WALL_AVOIDANCE_DISTANCE || boid->position[1] > 1.0f - WALL_AVOIDANCE_DISTANCE) {
//            avoidWalls(boid);
//        }
//        else {
//            // Align velocity with neighbors
//            alignWithNeighbors(boid, neighbors);
//
//            // Avoid collisions with neighbors
//            avoidNeighbors(boid, neighbors);
//        }
//
//        // Update position based on velocity
//        boid->position[0] += boid->velocity[0];
//        boid->position[1] += boid->velocity[1];
//
//        // Ensure boids stay within screen bounds
//        keepInBounds(boid);
//    }
//}
//
//// Render each boid as a triangle pointing in its velocity direction
//void renderBoid(Boid* boid, int color) {
//    float angle = atan2(boid->velocity[1], boid->velocity[0]);
//    float baseX = boid->position[0];
//    float baseY = boid->position[1];
//
//    // Vertices of the triangle
//    float x1 = baseX + cos(angle) * 0.03f;
//    float y1 = baseY + sin(angle) * 0.03f;
//    float x2 = baseX + cos(angle + 2.0f * M_PI / 3.0f) * 0.02f;
//    float y2 = baseY + sin(angle + 2.0f * M_PI / 3.0f) * 0.02f;
//    float x3 = baseX + cos(angle - 2.0f * M_PI / 3.0f) * 0.02f;
//    float y3 = baseY + sin(angle - 2.0f * M_PI / 3.0f) * 0.02f;
//
//    // Set color
//    if (color == 0) glColor3f(0.0f, 1.0f, 0.0f); // Normal boid color
//    else glColor3f(1.0f, 0.0f, 0.0f); // Highlighted color
//
//    // Draw the triangle
//    glBegin(GL_TRIANGLES);
//    glVertex2f(x1, y1);
//    glVertex2f(x2, y2);
//    glVertex2f(x3, y3);
//    glEnd();
//}
//
//// Display function called by GLUT to render the boids
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    for (int i = 0; i < FLOCK_SIZE; i++) {
//        int color = (highlightedBoid == i || showNeighbors) ? 1 : 0;
//        renderBoid(&flock[i], color);
//    }
//
//    glutSwapBuffers();
//}
//
//// Keyboard input handling
//void handleKeypress(unsigned char key, int x, int y) {
//    if (key >= '1' && key <= '9') {
//        highlightedBoid = key - '1';
//    }
//    if (key == 'n') {
//        showNeighbors = !showNeighbors;
//    }
//    if (key == 'f') {
//        flockSpeed += 0.01f;
//    }
//    if (key == 's') {
//        flockSpeed = fmaxf(flockSpeed - 0.01f, MIN_SPEED);
//    }
//}
//
//// Update loop
//void update(int value) {
//    updateBoids();
//    glutPostRedisplay();
//    glutTimerFunc(16, update, 0); // 16ms for 60fps
//}
//
//// Main function
//int main(int argc, char** argv) {
//    srand(time(0));
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(600, 600);
//    glutCreateWindow("Boid Simulation");
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glMatrixMode(GL_PROJECTION);
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//
//    initBoids();
//    glutDisplayFunc(display);
//    glutKeyboardFunc(handleKeypress);
//    glutTimerFunc(16, update, 0);
//
//    glutMainLoop();
//    return 0;
//}
