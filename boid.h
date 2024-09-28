#pragma once

typedef struct Vertex {
	double x;
	double y;
} Vertex;

typedef struct Boid {
	Vertex* vertex1;
	Vertex* vertex2;
	Vertex* vertex3;
} Boid;
