#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Boid.h"

// Boid related macros
#define BOID_SIZE 0.03f
#define FLOCK_SIZE 40

#define BOID_BASE_SPEED 0.001f
#define MAX_SPEED 0.009f
#define SPEED_STEP 0.0001f

#define NUM_OF_NEAREST_NEIGHBORS 6
#define EDGE_AVOIDANCE_DISTANCE 0.05f
#define VELOCITY_CHANGE_CONSTANT 0.00001f
#define DIRECTION_CHANGE_CONSTANT 0.05f
#define MOVE_AWAY_CONSTANT 0.00001f
#define MIN_NEIGHBORS_DISTANCE 0.05f

// Randomization related macros
#define MAX_RANDOM_RANGE 0.5f
#define MIN_RANDOM_RANGE -0.5f
#define PI 3.14159265f

// OpenGL related macros
#define LEFT_WALL_LIMIT -1.0
#define RIGHT_WALL_LIMIT 1.0
#define TOP_WALL_LIMIT 1.0
#define BOTTOM_WALL_LIMIT -1.0

Boid* currentFlock[FLOCK_SIZE];
Boid* previousFlock[FLOCK_SIZE];
Boid* nearestNeighbors[NUM_OF_NEAREST_NEIGHBORS];

float currentSetSpeed;

float randomFloatGenerator(float, float);

void initializeBoidManager();

void createBoids();

void updateBoids();

void avoidWalls(int);

void findNearestNeighbors(Boid*, int, Boid*[]);

float findEuclideanDistance(float, float, float, float);

void speedLimit(Boid*);

void alignWithNearestNeighborDirection(int);

void moveAwayFromNearestNeighbor(int);