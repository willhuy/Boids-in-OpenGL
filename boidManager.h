#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Boid.h"

#define PI 3.14159265
#define FLOCK_SIZE 3
#define MAX_RANDOM_RANGE 0.5f
#define MIN_RANDOM_RANGE -0.5f

Boid** listOfBoids;

float randomFloatGenerator(float max, float min);

void initializeBoidManager();

void createBoids();