#include "BoidManager.h"

float randomFloatGenerator(float max, float min) {
	float result = min + ((float)rand() / RAND_MAX) * (max - min);
	return result;
}

void initializeBoidManager() {
	// Initialize current and previous flock list containing Boids
	currentFlock = malloc(sizeof(Boid*) * FLOCK_SIZE);
	previousFlock = malloc(sizeof(Boid*) * FLOCK_SIZE);

	if (currentFlock == NULL || previousFlock == NULL) {
		printf("Failed to allocate memory for current flock or previous flock");
		return -1;
	}

	// Initialize space for each Boid
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		currentFlock[boidIndex] = malloc(sizeof(Boid));
		previousFlock[boidIndex] = malloc(sizeof(Boid));
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
			currentFlock[boidIndex] = boid;
		}
		else {
			printf("Failed to create Boid!!");
		}
	}
}

void updateBoids() {
	// Copy boids from current to previous flock
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		memcpy(previousFlock[boidIndex], currentFlock[boidIndex], sizeof(Boid*));
	}

	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		// Find 6 nearest neighbors

	}
}

Boid** find6NearestNeighbors(Boid* currentBoid, int indexOfCurrentBoid, Boid** flock) {
	Boid** nearestNeighbors = malloc(sizeof(Boid*) * NUM_OF_NEAREST_NEIGHBORS);

	if (nearestNeighbors != NULL) {
		for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {
			nearestNeighbors[neighborIndex] = malloc(sizeof(Boid));
		}
	}
	else {
		printf("Failed to allocate list of nearest neightbors");
		return -1;
	}

	// Iterate through all boids
	float distance[FLOCK_SIZE] = {0};
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		
		// Skip itself
		if (boidIndex == indexOfCurrentBoid) {
			distance[boidIndex] = -1;
			continue;
		}

		// Find euclidean distance
		float xDistance = currentBoid->xCoordinate - flock[boidIndex]->xCoordinate;
		float yDistance = currentBoid->yCoordinate - flock[boidIndex]->yCoordinate;
		distance[boidIndex] = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
	}
}