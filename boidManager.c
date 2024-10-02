#include "BoidManager.h"

float randomFloatGenerator(float max, float min) {
	float result = min + ((float)rand() / RAND_MAX) * (max - min);
	return result;
}

void initializeBoidManager() {
	// Initialize space for each Boid
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		currentFlock[boidIndex] = malloc(sizeof(Boid));
		previousFlock[boidIndex] = malloc(sizeof(Boid));
	}

	// Initialize the nearest neighbors list
	for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {
		nearestNeighbors[neighborIndex] = malloc(sizeof(Boid));
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
		previousFlock[boidIndex] = currentFlock[boidIndex];
	}

	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		// Find 6 nearest neighbors
		find6NearestNeighbors(previousFlock[boidIndex], boidIndex, &nearestNeighbors);

		// Check if the boid is in certain distance with a wall
		avoidWalls(boidIndex);

		speedLimit(currentFlock[boidIndex]);

		currentFlock[boidIndex]->xCoordinate += currentFlock[boidIndex]->xVelocity;
		currentFlock[boidIndex]->yCoordinate += currentFlock[boidIndex]->yVelocity;
	}
}

void find6NearestNeighbors(Boid* currentBoid, int indexOfCurrentBoid, Boid* givenNearestNeighbors[]) {

	// Iterate through all boids
	float minDistance = 9999.0f;
	float distance[FLOCK_SIZE] = {0};
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		
		// Skip itself
		if (boidIndex == indexOfCurrentBoid) {
			distance[boidIndex] = -1; // Euclidean distance can't be negative
			continue;
		}

		// Find euclidean distance
		distance[boidIndex] = findEuclideanDistance(currentBoid->xCoordinate, previousFlock[boidIndex]->xCoordinate, 
													currentBoid->yCoordinate, previousFlock[boidIndex]->yCoordinate);
	}

	for (int nearestNeighborIndex = 0; nearestNeighborIndex < NUM_OF_NEAREST_NEIGHBORS; nearestNeighborIndex++) {
		int minDistanceIndex = 0;
		for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
			if (distance[boidIndex] < minDistance && distance[boidIndex] != -1) {
				minDistance = distance[boidIndex];
				minDistanceIndex = boidIndex;
			}
		}

		// Add the Boid from the flock mith min distance to the list
		givenNearestNeighbors[nearestNeighborIndex] = previousFlock[minDistanceIndex];
		distance[minDistanceIndex] = -1; // Flag the value has been recorded
		minDistance = 9999.0f; // Reset minDistance
	}
}

float findEuclideanDistance(float x1, float x2, float y1, float y2) {
	float xDistance = x1 - x2;
	float yDistance = y1 - y2;
	return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}

void avoidWalls(int boidIndex) {

	// Approaching left wall
	float distanceToLeftWall = findEuclideanDistance(LEFT_WALL_LIMIT, previousFlock[boidIndex]->xCoordinate, 0, 0);
	if (distanceToLeftWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->xVelocity += (1 / distanceToLeftWall) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching right wall
	float distanceToRightWall = findEuclideanDistance(RIGHT_WALL_LIMIT, previousFlock[boidIndex]->xCoordinate, 0, 0);
	if (distanceToRightWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->xVelocity -= (1 / distanceToRightWall) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching bottom wall
	float distanceToBottomWall = findEuclideanDistance(0, 0, BOTTOM_WALL_LIMIT, previousFlock[boidIndex]->yCoordinate);
	if (distanceToBottomWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->yVelocity += (1 / distanceToBottomWall) * VELOCITY_CHANGE_CONSTANT; // Update yVelocity
	}

	// Approaching top wall
	float distanceToTopWall = findEuclideanDistance(0, 0, TOP_WALL_LIMIT, previousFlock[boidIndex]->yCoordinate);
	if (distanceToTopWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->yVelocity -= (1 / distanceToTopWall) * VELOCITY_CHANGE_CONSTANT; // Update yVelocity
	}
}

void speedLimit(Boid* boid) {
	float magnitude = findEuclideanDistance(boid->xVelocity, 0, boid->yVelocity, 0);
	if (boid->xVelocity > MAX_SPEED) {
		boid->xVelocity = (boid->xVelocity / magnitude) * MAX_SPEED;
	}

	if (boid->yVelocity > MAX_SPEED) {
		boid->yVelocity = (boid->yVelocity / magnitude) * MAX_SPEED;
	}
}