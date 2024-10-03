#pragma once
#include <freeglut.h>
#include <time.h>

#include "BoidManager.h"

// GLUT related macros
#define FRAME_EXIST_TIME 1000 / 60
#define WIDTH 500
#define HEIGHT 500

// Menu button macros
#define BUTTON_X_LEFT -0.25f
#define BUTTON_X_RIGHT 0.25f
#define BUTTON_Y_TOP -0.75f
#define BUTTON_Y_BOTTOM -0.875f
#define BUTTON_SHADOW_SHIFT 0.015f

int stopSimulation = 0; // Use for menu button to check the game state, 0 is false, 1 is true
int highlightedBoidIndex = -1; // Use to track which Boid are being highlight, -1 if none are highlight
Boid* nearestNeighborOfBoid[NUM_OF_NEAREST_NEIGHBORS]; // Use to store nearest neighbors of the Boid being highlighted

void renderBoid(Boid*);

void chooseBoidColor(int);

void drawMenu();

void myDisplay();

void myMouseButton(int, int, int, int);

void myKey(unsigned char, int, int);

void initializeGL();

void update();