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

	// Initiallize current speed
	currentSetSpeed = BOID_BASE_SPEED;
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
		// Find nearest neighbors
		findNearestNeighbors(previousFlock[boidIndex], boidIndex, &nearestNeighbors);

		// Check if the boid is in certain distance with a wall
		if (previousFlock[boidIndex]->xCoordinate < -1.0f + EDGE_AVOIDANCE_DISTANCE || previousFlock[boidIndex]->xCoordinate > 1.0f - EDGE_AVOIDANCE_DISTANCE ||
			previousFlock[boidIndex]->yCoordinate < -1.0f + EDGE_AVOIDANCE_DISTANCE || previousFlock[boidIndex]->yCoordinate > 1.0f - EDGE_AVOIDANCE_DISTANCE) {
			avoidWalls(boidIndex);
		}
		else {
			alignWithNearestNeighborDirection(boidIndex);

			moveAwayFromNearestNeighbor(boidIndex);
		}

		//speedLimit(currentFlock[boidIndex]);
		currentFlock[boidIndex]->xCoordinate += currentFlock[boidIndex]->xVelocity;
		currentFlock[boidIndex]->yCoordinate += currentFlock[boidIndex]->yVelocity;
	}
}

void findNearestNeighbors(Boid* currentBoid, int indexOfCurrentBoid, Boid* givenNearestNeighbors[]) {

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
	//printf("Boid %d avoid walls\n", boidIndex);
	// Approaching left wall
	float distanceToLeftWall = findEuclideanDistance(LEFT_WALL_LIMIT, previousFlock[boidIndex]->xCoordinate, 0, 0);
	if (distanceToLeftWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->xVelocity += (1.0f / distanceToLeftWall) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching right wall
	float distanceToRightWall = findEuclideanDistance(RIGHT_WALL_LIMIT, previousFlock[boidIndex]->xCoordinate, 0, 0);
	if (distanceToRightWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->xVelocity -= (1.0f / distanceToRightWall) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching bottom wall
	float distanceToBottomWall = findEuclideanDistance(0, 0, BOTTOM_WALL_LIMIT, previousFlock[boidIndex]->yCoordinate);
	if (distanceToBottomWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->yVelocity += (1.0f / distanceToBottomWall) * VELOCITY_CHANGE_CONSTANT; // Update yVelocity
	}

	// Approaching top wall
	float distanceToTopWall = findEuclideanDistance(0, 0, TOP_WALL_LIMIT, previousFlock[boidIndex]->yCoordinate);
	if (distanceToTopWall <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex]->yVelocity -= (1.0f / distanceToTopWall) * VELOCITY_CHANGE_CONSTANT; // Update yVelocity
	}

	speedLimit(currentFlock[boidIndex]);
}

void speedLimit(Boid* boid) {
	float magnitude = findEuclideanDistance(boid->xVelocity, 0, boid->yVelocity, 0);
	if (boid->xVelocity > currentSetSpeed) {
		boid->xVelocity = (boid->xVelocity / magnitude) * currentSetSpeed;
	}

	if (boid->yVelocity > currentSetSpeed) {
		boid->yVelocity = (boid->yVelocity / magnitude) * currentSetSpeed;
	}

	if (boid->xVelocity < currentSetSpeed) {
		boid->xVelocity = (boid->xVelocity / magnitude) * currentSetSpeed;
	}

	if (boid->yVelocity < currentSetSpeed) {
		boid->yVelocity = (boid->yVelocity / magnitude) * currentSetSpeed;
	}
}

void alignWithNearestNeighborDirection(int boidIndex) {
	//printf("Boid %d align\n", boidIndex);
	// Average all the nearest neighbor x and y component
	float sumX = 0, sumY = 0, avgX = 0, avgY = 0;
	for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {
		sumX += nearestNeighbors[neighborIndex]->xVelocity;
		sumY += nearestNeighbors[neighborIndex]->yVelocity;
	}

	avgX = sumX / NUM_OF_NEAREST_NEIGHBORS;
	avgY = sumY / NUM_OF_NEAREST_NEIGHBORS;

	// Gradually align with the nearest neighbors's direction
	currentFlock[boidIndex]->xVelocity = (1 - DIRECTION_CHANGE_CONSTANT) * currentFlock[boidIndex]->xVelocity + DIRECTION_CHANGE_CONSTANT * avgX;
	currentFlock[boidIndex]->yVelocity = (1 - DIRECTION_CHANGE_CONSTANT) * currentFlock[boidIndex]->yVelocity + DIRECTION_CHANGE_CONSTANT * avgY;

	speedLimit(currentFlock[boidIndex]);
}

void moveAwayFromNearestNeighbor(int boidIndex) {
	float distanceToNeighborHorizontal = -1.0f;
	float distanceToNeighborVertical = -1.0f;
	for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {

		// Approaching neighbor horizontally => update xVelocity
		distanceToNeighborHorizontal = findEuclideanDistance(nearestNeighbors[neighborIndex]->xCoordinate, previousFlock[boidIndex]->xCoordinate, 0, 0);
		if (distanceToNeighborHorizontal <= MIN_NEIGHBORS_DISTANCE) {
			//printf("Boid %d move horizontal\n", boidIndex);
			// Neighbor on the left
			if (nearestNeighbors[neighborIndex]->xCoordinate < previousFlock[boidIndex]->xCoordinate) {
				currentFlock[boidIndex]->xVelocity += (1.0f / distanceToNeighborHorizontal) * MOVE_AWAY_CONSTANT; 
			}
			else { // right
				currentFlock[boidIndex]->xVelocity -= (1.0f / distanceToNeighborHorizontal) * MOVE_AWAY_CONSTANT;
			}
		}

		// Approaching neighbor vertically => update yVelocity
		distanceToNeighborVertical = findEuclideanDistance(0, 0, nearestNeighbors[neighborIndex]->yCoordinate, previousFlock[boidIndex]->yCoordinate);
		if (distanceToNeighborVertical <= MIN_NEIGHBORS_DISTANCE) {
			//printf("Boid %d move vertical\n", boidIndex);

			// Neighbor on the bottom
			if (nearestNeighbors[neighborIndex]->yCoordinate < previousFlock[boidIndex]->yCoordinate) {
				currentFlock[boidIndex]->yVelocity += (1.0f / distanceToNeighborVertical) * MOVE_AWAY_CONSTANT;
			}
			else { // top
				currentFlock[boidIndex]->yVelocity -= (1.0f / distanceToNeighborVertical) * MOVE_AWAY_CONSTANT;
			}
		}
	}

	speedLimit(currentFlock[boidIndex]);
}