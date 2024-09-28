#include "boidManager.h"

void initializeBoidManager() {
	// Initialize list of Boid
	listOfBoids = malloc(sizeof(*listOfBoids) * FLOCK_SIZE);

	if (listOfBoids == NULL) {
		return -1;
	}

	// Initialize each Boid
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		listOfBoids[boidIndex] = malloc(sizeof(**listOfBoids));
	}

	// Initialize each Boid vertex
}

void createBoids() {
	// Loop through the flock size
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		Boid* boid = malloc(sizeof(*boid));
		if (boid != NULL) {

			// Random the first point
			boid->x = (rand() / (double)RAND_MAX) * 1.0 - 0.5;
			boid->y = (rand() / (double)RAND_MAX) * 1.0 - 0.5;

			// Random the second and third point

			printf("X: %f, Y: %f \n", boid->x, boid->y);
			listOfBoids[boidIndex] = boid;
		}
		else {
			printf("Failed to create Boid!!");
		}
	}
}