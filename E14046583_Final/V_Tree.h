#ifndef V_TREE_H
#define V_TREE_H
#define VERTEX_PER_NODE 4
// #define floatMax std::numeric_limits<float>::max()
#define floatMax 99999999
#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#include "Vehicle.h"
#include "distanceMatrix.h"
#include "vertex.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "ActiveObject.h"
using namespace std;


class LNAV {
private:
	float distance;
	int nearestActiveVertex;
	bool isBoundaryVertex;
	vector<ActiveObject> activeObjectList;

public:
	LNAV();

	void setDistance(int newDistance) { distance = newDistance; }
	void setNearestActiveVertex(int vertex) { nearestActiveVertex = vertex; }

	float getDistance() const { return distance; }
	int getnearestActiveVertex() const { return nearestActiveVertex; }
	void setNearstActiveVertexList(const vector<ActiveObject> &newList) {
		activeObjectList = newList;
	}
	void moveObject(int);
	bool pushObject(ActiveObject &);
	const vector<ActiveObject> getActiveObjectList() const { return activeObjectList; }
	void showActiveObjecList() const;
	void setBoundaryVertex() { isBoundaryVertex = true; };
};
struct GNAVData {
	int vertexIndex;
	float shortestDistance;
	GNAVData(int vertexIndex = -1, float shortestDistance = floatMax) :vertexIndex(vertexIndex), shortestDistance(shortestDistance) {}
};

class VTree {
private:
	DistanceMatrix distanceMatrix;
	vector<LNAV> LNAVList;
	vector<int> boundaryVertexList;
	VTree() {};

	static VTree &getLeaveOfIndex(VTree &, int);

	char getNodeSide(int) const;
	void updateAllLeaves();
	void updateNodeLNAV();

	VTree &getVertexSideNode(int) const;
	const vector<int> getBoundariesListInSameSide(char) const;
	const vector<float> getShortestDisList(const vector<int>, int) const;

	float getDistance(int, int) const;

public:
	const static int vertexNumPerLeaf = 4;
	VTree *leftNode;
	VTree *rightNode;

	VTree(const DistanceMatrix &);
	VTree(const VTree &);
	~VTree();
	VTree &operator=(const VTree &anotherTree);

	bool findVertex(int);

	bool setLeftNode(const VTree &);
	bool setRightNode(const VTree &);

	bool insertObject(const Vehicle &, int dis = -1);
	bool deleteObject(const Vehicle &);

	bool setBoundaryVertexList(int *, int);

	void showTree() const;
	const DistanceMatrix &getDistanceMatrix() const { return distanceMatrix; };

	static int getLayer(const VTree &);
	const vector<int> getActiveVertexList(); // only for leaf
	const vector<ActiveObject> getActiveObjectListofIndex(int vertexIndex)const;
	void moveObject(int);

	float SPDist(int, int) const;


	const GNAVData gnav(int vertexIndex) const;
	const GNAVData nnav(int vertexIndex, const GNAVData) const;
	vector<GNAVData> knn(int vertexIndex, int k) const;

};

bool compareGNAVData(const GNAVData, const GNAVData);


#endif

