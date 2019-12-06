#include "ActiveObject.h"

ActiveObject::ActiveObject(Vehicle vehicle, float distance, float maxDistance)
	: vehicle(vehicle), distance(distance), maxDistance(maxDistance), direction(FORWARD) {}

void ActiveObject::increaseDistance(float delta) {
	float newDistance;
	newDistance =  direction == FORWARD ? distance - delta:  distance + delta;
	if (newDistance < 0.1) {
		newDistance < 0.1;
		distance = maxDistance - 0.1;
		//direction = BACKWARD;
	}
	else if (newDistance > maxDistance - 0.1) {
		//direction = FORWARD;
	}
	else {
		distance = newDistance;
	}
}