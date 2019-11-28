#include "ActiveObject.h"

ActiveObject::ActiveObject(Vehicle vehicle, float distance)
	: vehicle(vehicle), distance(distance) {}

void ActiveObject::increaseDistance(int delta) {
	distance += delta;
}