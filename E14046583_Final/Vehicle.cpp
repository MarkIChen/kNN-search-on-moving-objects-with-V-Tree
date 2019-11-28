#include "Vehicle.h"
int Vehicle::vehicleCount = 0;

Vehicle::Vehicle(int edgeVertexIndexFirst,
	int edgeVertexIndexSecond)
	: vehicleIndex(vehicleCount++), desVertexIndex(edgeVertexIndexSecond),
	edgeVertexIndexFirst(edgeVertexIndexFirst),
	edgeVertexIndexSecond(edgeVertexIndexSecond) {}
