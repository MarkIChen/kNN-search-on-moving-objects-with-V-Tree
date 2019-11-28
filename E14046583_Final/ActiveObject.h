#pragma once
#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H
#include "Vehicle.h"
class ActiveObject {
private:
	// const int objectIndex; // objectIndex = vehicleIndex
	Vehicle vehicle;
	float distance;
	ActiveObject();

public:
	ActiveObject(Vehicle, float);
	const Vehicle getObjectVehicle() const { return vehicle; };
	float getDistance() const { return distance; };
	void setDistance(float newDis) { distance = newDis; }
	void increaseDistance(int);
};

#endif