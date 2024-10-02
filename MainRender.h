#pragma once
#include <freeglut.h>
#include <time.h>

#include "BoidManager.h"

#define FRAME_EXIST_TIME 1000 / 60

int highlightedBoidIndex = -1; // Use to track which Boid are being highlight, -1 if none are highlight
Boid* nearestNeighborOfBoid[NUM_OF_NEAREST_NEIGHBORS]; // Use to store nearest neighbors of the Boid being highlighted

void renderBoid(Boid*);

void myDisplay();

void myIdle();

void myKey(unsigned char, int, int);

void initializeGL();

void update();