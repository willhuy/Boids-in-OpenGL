#pragma once
#include <freeglut.h>
#include <time.h>

#include "BoidManager.h"

#define BOID_SIZE 0.02f

void renderBoid(Boid*);

void myDisplay();

void myIdle();

void initializeGL();