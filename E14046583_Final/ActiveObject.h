#pragma once
#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H
#include "Vehicle.h"
#define FORWARD 0
#define BACKWARD 1
class ActiveObject {
private:
	// const int objectIndex; // objectIndex = vehicleIndex
	Vehicle vehicle;
	float distance;
	float maxDistance;
	char direction;
	ActiveObject();

public:
	ActiveObject(Vehicle, float, float);
	const Vehicle getObjectVehicle() const { return vehicle; };
	float getDistance() const { return distance; };
	float getMaxDistance() const { return maxDistance; }
	void setDistance(float newDis) { distance = newDis; }
	void increaseDistance(float);
};

#endif