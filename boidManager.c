#include "BoidManager.h"

float randomFloatGenerator(float max, float min) {
	float result = min + ((float)rand() / RAND_MAX) * (max - min);
	return result;
}

void initializeBoidManager() {
	// Initialize list of Boid
	listOfBoids = malloc(sizeof(*listOfBoids) * FLOCK_SIZE);

	if (listOfBoids == NULL) {
		return -1;
	}

	// Initialize each space for each Boid
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		listOfBoids[boidIndex] = malloc(sizeof(**listOfBoids));
	}
}

void createBoids() {
	// Loop through the flock size
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		Boid* boid = malloc(sizeof(*boid));

		if (boid != NULL) {

			// Random the position
			boid->xCoordinate = randomFloatGenerator(MAX_RANDOM_RANGE, MIN_RANDOM_RANGE);
			boid->yCoordinate = randomFloatGenerator(MAX_RANDOM_RANGE, MIN_RANDOM_RANGE);

			// Random the boid direction in range of 0 and 360
			float angle = randomFloatGenerator(0, 2 * PI);
			boid->xVelocity = cos(angle) * BOID_BASE_SPEED;
			boid->yVelocity = sin(angle) * BOID_BASE_SPEED;

			// Add boid to the list
			listOfBoids[boidIndex] = boid;
		}
		else {
			printf("Failed to create Boid!!");
		}
	}
}