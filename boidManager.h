#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Boid.h"

#define PI 3.14159265

#define FLOCK_SIZE 40
#define BOID_BASE_SPEED 0.1f
#define NUM_OF_NEAREST_NEIGHBORS 6

#define MAX_RANDOM_RANGE 0.5f
#define MIN_RANDOM_RANGE -0.5f

Boid** currentFlock;
Boid** previousFlock;

float randomFloatGenerator(float max, float min);

void initializeBoidManager();

void createBoids();

void updateBoids();

Boid** find6NearestNeighbors(Boid*, int, Boid**);
