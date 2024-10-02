#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Boid.h"

// Boid related macros
#define FLOCK_SIZE 40
#define BOID_BASE_SPEED 0.005f
#define NUM_OF_NEAREST_NEIGHBORS 6
#define EDGE_AVOIDANCE_DISTANCE 0.05f
#define VELOCITY_CHANGE_CONSTANT 0.0002f
#define DIRECTION_CHANGE_CONSTANT 0.25f
#define MOVE_AWAY_CONSTANT 0.9f
#define MIN_NEIGHBORS_DISTANCE 0.02f
#define MAX_SPEED 0.01f

// Randomization related macros
#define MAX_RANDOM_RANGE 0.5f
#define MIN_RANDOM_RANGE -0.5f
#define PI 3.14159265

// OpenGL related macros
#define LEFT_WALL_LIMIT -1.0
#define RIGHT_WALL_LIMIT 1.0
#define TOP_WALL_LIMIT 1.0
#define BOTTOM_WALL_LIMIT -1.0

Boid* currentFlock[FLOCK_SIZE];
Boid* previousFlock[FLOCK_SIZE];
Boid* nearestNeighbors[NUM_OF_NEAREST_NEIGHBORS];

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