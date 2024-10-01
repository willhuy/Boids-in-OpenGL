#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Boid.h"

#define PI 3.14159265

// Boid related macros
#define FLOCK_SIZE 40
#define BOID_BASE_SPEED 0.1f
#define NUM_OF_NEAREST_NEIGHBORS 6
#define EDGE_AVOIDANCE_DISTANCE 0.1f

// Randomization related macros
#define MAX_RANDOM_RANGE 0.5f
#define MIN_RANDOM_RANGE -0.5f

// OpenGL realted macros
#define LEFT_WALL_LIMIT -1.0
#define RIGHT_WALL_LIMIT 1.0
#define TOP_WALL_LIMIT 1.0
#define BOTTOM_WALL_LIMIT -1.0

Boid* currentFlock[FLOCK_SIZE];
Boid* previousFlock[FLOCK_SIZE];
Boid* nearestNeighbors[NUM_OF_NEAREST_NEIGHBORS];

float randomFloatGenerator(float max, float min);

void initializeBoidManager();

void createBoids();

void updateBoids();

void avoidWalls(int);

void find6NearestNeighbors(Boid*, int, Boid*[]);

float findEuclideanDistance(float, float, float, float);
