#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle {
private:

	int vehicleIndex;
	int desVertexIndex;
	int edgeVertexIndexFirst;
	int edgeVertexIndexSecond;
	Vehicle();

public:
	static int vehicleCount;
	Vehicle(int, int);

	int getVehicleIndex() const { return vehicleIndex; }
	int getDesVertexIndex() const { return desVertexIndex; }
	int getEdgeVertexIndexFirst() const { return edgeVertexIndexFirst; }
	int getEdgeVertexIndexSecond() const { return edgeVertexIndexSecond; }

	void setDesVertexIndex(int newValue) { desVertexIndex = newValue; }
	void setEdgeVertexIndexFirst(int newValue) { edgeVertexIndexFirst = newValue; }
	void setEdgeVertexIndexSecond(int newValue) { edgeVertexIndexSecond = newValue; }
};

#endif
