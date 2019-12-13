#include "V_Tree.h"
#include <stdlib.h>
#include <ctime>

using namespace std;

bool compareGNAVData(GNAVData a, GNAVData b) { return (a.shortestDistance<b.shortestDistance); }

void LNAV::showActiveObjecList() const {
	for (int i = 0; i < activeObjectList.size(); i++) {
		cout << "   ObjectIndex = "
			<< activeObjectList[i].getObjectVehicle().getVehicleIndex();
		cout << ", distance  = " << activeObjectList[i].getDistance() << endl;
	}
}

LNAV::LNAV()
	: distance(floatMax - 1), nearestActiveVertex(-1), isBoundaryVertex(false) {
}

void LNAV::moveObject(float delta) {
	for (int i = 0;i < activeObjectList.size();i++) {
		activeObjectList[i].increaseDistance(delta);
	}
}

bool LNAV::pushObject(ActiveObject &newObject) {
	activeObjectList.push_back(newObject);
	nearestActiveVertex = newObject.getObjectVehicle().getDesVertexIndex();
	distance = 0;
	return true;
}

VTree::VTree(const DistanceMatrix &distanceMatrix)
	: distanceMatrix(distanceMatrix) {
	leftNode = nullptr;
	rightNode = nullptr;
	LNAVList = std::vector<LNAV>(distanceMatrix.getSize(), LNAV());
}

// copy constructor
VTree::VTree(const VTree &oldTree) {
	if (oldTree.leftNode != nullptr) {
		leftNode = new VTree(*oldTree.leftNode);
	}
	else {
		leftNode = nullptr;
	}
	if (oldTree.rightNode != nullptr) {
		rightNode = new VTree(*oldTree.rightNode);
	}
	else {
		rightNode = nullptr;
	}
	distanceMatrix = DistanceMatrix(oldTree.distanceMatrix);
	LNAVList = oldTree.LNAVList;
	boundaryVertexList = oldTree.boundaryVertexList;
}

VTree &VTree::operator=(const VTree &anotherTree) {
	if (anotherTree.leftNode != nullptr) {
		delete leftNode;
		leftNode = new VTree(*anotherTree.leftNode);
	}
	else {
		leftNode = nullptr;
	}
	if (anotherTree.rightNode != nullptr) {
		delete rightNode;
		rightNode = new VTree(*anotherTree.rightNode);
	}
	else {
		rightNode = nullptr;
	}
	distanceMatrix = anotherTree.distanceMatrix;
	LNAVList = anotherTree.LNAVList;
	boundaryVertexList = anotherTree.boundaryVertexList;
	return *this;
}

VTree::~VTree() {
	delete leftNode;
	delete rightNode;
}

bool VTree::setLeftNode(const VTree &newleftNode) {
	delete leftNode;
	leftNode = new VTree(newleftNode);

	return true;
}

bool VTree::setRightNode(const VTree &newRightNode) {
	delete rightNode;

	rightNode = new VTree(newRightNode);
	return true;
}

bool VTree::insertObject(const Vehicle &newVehicle, float dis, float maxDis) {
	int insertVertex = newVehicle.getDesVertexIndex();
	int layer = getLayer(*this);
	if (maxDis == -1) maxDis = getDistance(newVehicle.getEdgeVertexIndexFirst(), newVehicle.getEdgeVertexIndexSecond());
	if (layer == 0) {
		int arrIndex = distanceMatrix.getIndex(insertVertex);

		if (arrIndex == -1) {
			cout << "Insert Object Error." << endl;
			return false;
		}

		ActiveObject object(newVehicle, dis, maxDis);

		LNAVList[arrIndex].pushObject(object);
		updateNodeLNAV();
		return true;
	}

	VTree *target = ((insertVertex - 1) / (layer * VERTEX_PER_NODE)) % 2
		? rightNode
		: leftNode;
	int ranDis = dis;
	if (dis<0) {
		//srand(time(0));
		int shortDis = int(getDistance(newVehicle.getEdgeVertexIndexFirst(),
			newVehicle.getEdgeVertexIndexSecond()));
		if (shortDis == -1) {
			return false;
		}
		ranDis = rand() % shortDis;
	}
	if (target->insertObject(newVehicle, ranDis+0.2, maxDis) == true) {
		updateNodeLNAV();
		return true;
	}
	return false;
}

float VTree::getDistance(int vertexA, int vertexB) const {
	float dis = distanceMatrix.getValue(vertexA, vertexB);
	if (getLayer(*this) == 0 && dis == -1) {
		return -1;
	}

	if (dis != -1) {
		return dis;
	}

	return getVertexSideNode(vertexA).getDistance(vertexA, vertexB);
}

bool VTree::deleteObject(const Vehicle &targetVehicle) {
	int desVertexIndex = targetVehicle.getDesVertexIndex();
	int veichleIndex = targetVehicle.getVehicleIndex();
	int layer = getLayer(*this);

	if (layer == 0) {
		int arrIndex = distanceMatrix.getIndex(desVertexIndex);
		vector<ActiveObject> newList = LNAVList[arrIndex].getActiveObjectList();
		for (int i = 0; i < newList.size(); i++) {
			if (newList[i].getObjectVehicle().getVehicleIndex() == veichleIndex) {
				newList.erase(newList.begin() + i);
				LNAVList[arrIndex].setNearstActiveVertexList(newList);
				break;
			}
		}
		if (newList.size() == 0) {
			for (int i = 0;i<LNAVList.size();i++) {
				if (LNAVList[i].getnearestActiveVertex() == desVertexIndex) {
					LNAVList[i].setNearestActiveVertex(-1);
					LNAVList[i].setDistance(floatMax);
				}
			}
		}
		updateNodeLNAV();
		return true;
	}
	if (getVertexSideNode(desVertexIndex).deleteObject(targetVehicle) == false) {
		cout << "failed to delete vehicle" << endl;
		return false;
	}
	updateNodeLNAV();
	return true;
}

void VTree::showTree() const {
	cout << "my distanceMatrix: " << endl;
	distanceMatrix.showMatrix();

	for (int i = 0; i < distanceMatrix.getSize(); i++) {
		cout << "layer: " << getLayer(*this);
		cout << ", vertex: " << distanceMatrix.getIndexTable()[i] << endl;
		LNAVList[i].showActiveObjecList();
	}
	cout << "Boundary : ";
	for (int i = 0; i < boundaryVertexList.size(); i++) {
		cout << boundaryVertexList[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < LNAVList.size(); i++) {
		cout << "v:" << distanceMatrix.getVertexIndex(i)
			<< ", distance = " << LNAVList[i].getDistance()
			<< ", active Vertex = " << LNAVList[i].getnearestActiveVertex()
			<< endl;
	}
	cout << endl;
}

bool VTree::setBoundaryVertexList(int *vertexList, int listSize) {
	for (int i = 0; i < listSize; i++) {
		if (distanceMatrix.getIndex(vertexList[i]) != -1) {
			boundaryVertexList.push_back(vertexList[i]);
		}
	}
	if (getLayer(*this) != 0) {
		leftNode->setBoundaryVertexList(vertexList, listSize);
		rightNode->setBoundaryVertexList(vertexList, listSize);
	}
	return true;
}

int VTree::getLayer(const VTree &root) {
	VTree *nextNode = root.leftNode;
	int layer = 0;
	while (nextNode != nullptr) {
		nextNode = nextNode->leftNode;
		layer++;
	}
	return layer;
}

VTree &VTree::getLeaveOfIndex(VTree &root, int searchIndex) {
	if (getLayer(root) == 0) {
		return root;
	}
	int index = searchIndex - 1;
	int cluster = index / (VTree::vertexNumPerLeaf * getLayer(root));

	return cluster % 2 ? getLeaveOfIndex(*root.rightNode, searchIndex)
		: getLeaveOfIndex(*root.leftNode, searchIndex);
}

const vector<int> VTree::getActiveVertexList() {
	vector<int> activeVertexList(0);
	if (getLayer(*this) != 0) {
		cout << "Error in getActiveVertexList, this is not leaf" << endl;
		return activeVertexList;
	}

	for (int i = 0; i < LNAVList.size(); i++) {
		if (LNAVList[i].getDistance() == 0) {
			activeVertexList.push_back(distanceMatrix.getIndexTable()[i]);
		}
	}
	return activeVertexList;
}

void VTree::updateNodeLNAV() {
	// leaf
	if (getLayer(*this) == 0) {
		vector<int> activeVertexList = getActiveVertexList();
		for (int i = 0; i < LNAVList.size(); i++) {
			if (LNAVList[i].getDistance() == 0) {
				continue;
			}
			float minDis = LNAVList[i].getDistance();
			for (int j = 0; j < activeVertexList.size(); j++) {
				float distance = distanceMatrix.getValue(
					distanceMatrix.getVertexIndex(i), activeVertexList[j]);
				if (distance < minDis) {
					LNAVList[i].setDistance(distance);
					LNAVList[i].setNearestActiveVertex(activeVertexList[j]);
				}
			}
		}
		return;
	}
	// not leaf
	vector<vector<int> > borderList;
	borderList.push_back(getBoundariesListInSameSide(LEFT_SIDE));
	borderList.push_back(getBoundariesListInSameSide(RIGHT_SIDE));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < borderList[i].size(); j++) {
			int arrIndex = distanceMatrix.getIndex(borderList[i][j]);
			VTree target = (i == 0) ? *leftNode : *rightNode;
			int targetArrIndex = target.distanceMatrix.getIndex(borderList[i][j]);
			float minDis = target.LNAVList[targetArrIndex].getDistance();

			LNAVList[arrIndex].setDistance(minDis);
			LNAVList[arrIndex].setNearestActiveVertex(
				target.LNAVList[targetArrIndex].getnearestActiveVertex());

			target = (i == 0) ? *rightNode : *leftNode;
			for (int p = 0; p < borderList[(i + 1) % 2].size(); p++) {
				// to boundary of another leaf node
				int crossLength = distanceMatrix.getValue(borderList[i][j],
					borderList[(i + 1) % 2][p]);
				if (crossLength < minDis) {

					int targetArrIndex =
						target.distanceMatrix.getIndex(borderList[(i + 1) % 2][p]);
					int crossGraphTotalLength =
						crossLength + target.LNAVList[targetArrIndex].getDistance();
					if (crossGraphTotalLength < minDis) {
						LNAVList[arrIndex].setDistance(crossGraphTotalLength);
						LNAVList[arrIndex].setNearestActiveVertex(
							target.LNAVList[targetArrIndex].getnearestActiveVertex());
					}
				}
			}
		}
	}
}

char VTree::getNodeSide(int vertexIndex) const {
	int layer = getLayer(*this);
	return ((vertexIndex - 1) / (layer * VERTEX_PER_NODE)) % 2;
}

float VTree::SPDist(int vertexIndex1, int vertexIndex2) const {
	// on the shortest distance matrix -> return the value directely
	if (distanceMatrix.getIndex(vertexIndex1) != -1 &&
		distanceMatrix.getIndex(vertexIndex2) != -1) {
		return distanceMatrix.getValue(vertexIndex1, vertexIndex2);
	}
	// at the same side, pass to the node
	if (getNodeSide(vertexIndex1) == getNodeSide(vertexIndex2)) {
		return getNodeSide(vertexIndex1) == LEFT_SIDE
			? leftNode->SPDist(vertexIndex1, vertexIndex2)
			: rightNode->SPDist(vertexIndex1, vertexIndex2);
	}
	vector<int> sideABoundList =
		getBoundariesListInSameSide(getNodeSide(vertexIndex1));
	vector<int> sideBBoundList =
		getBoundariesListInSameSide(getNodeSide(vertexIndex2));

	vector<float> sideASLengthList =
		getShortestDisList(sideABoundList, vertexIndex1);
	vector<float> sideBSLengthList =
		getShortestDisList(sideBBoundList, vertexIndex2);

	float shortestDistance = floatMax;
	for (int i = 0; i < sideASLengthList.size(); i++) {
		for (int j = 0; j < sideBBoundList.size(); j++) {
			float BToB =
				distanceMatrix.getValue(sideABoundList[i], sideBBoundList[j]);
			float candidate = sideASLengthList[i] + sideBSLengthList[j] + BToB;
			if (candidate < shortestDistance)
				shortestDistance = candidate;
		}
	}
	return shortestDistance;
}

const vector<float> VTree::getShortestDisList(const vector<int> targetList,
	int vertexIndex) const {
	vector<float> result;
	for (int i = 0; i < targetList.size(); i++) {
		float shortestLength = getNodeSide(vertexIndex) == LEFT_SIDE
			? leftNode->SPDist(targetList[i], vertexIndex)
			: rightNode->SPDist(targetList[i], vertexIndex);
		result.push_back(shortestLength);
	}
	return result;
}
const vector<int> VTree::getBoundariesListInSameSide(char targetSide) const {
	vector<int> result(0);
	// char targetSide = getNodeSide(vertexIndex);
	for (int i = 0; i < LNAVList.size(); i++) {
		if (targetSide == getNodeSide(distanceMatrix.getVertexIndex(i))) {
			result.push_back(distanceMatrix.getVertexIndex(i));
		}
	}
	return result;
}

VTree &VTree::getVertexSideNode(int vertexIndex) const {
	int layer = getLayer(*this);
	return ((vertexIndex - 1) / (layer * VERTEX_PER_NODE)) % 2 ? *rightNode
		: *leftNode;
}

const GNAVData VTree::gnav(int vertexIndex) const {
	if (getLayer(*this) == 0) {
		int arrIndex = distanceMatrix.getIndex(vertexIndex);
		if (arrIndex == -1) {
			cout << "ERROR: This node do not have this vertex." << endl;
		}
		return GNAVData(LNAVList[arrIndex].getnearestActiveVertex(), LNAVList[arrIndex].getDistance());
	}

	GNAVData shortDisVertex = getVertexSideNode(vertexIndex).gnav(vertexIndex);

	vector<int> sideBoundList =
		getBoundariesListInSameSide(getNodeSide(vertexIndex));
	for (int i = 0; i < sideBoundList.size(); i++) {
		int arrIndex = distanceMatrix.getIndex(sideBoundList[i]);
		if (LNAVList[arrIndex].getDistance() < shortDisVertex.shortestDistance) {

			int candidate = SPDist(vertexIndex, sideBoundList[i]) +
				LNAVList[arrIndex].getDistance();
			if (candidate < shortDisVertex.shortestDistance) {
				shortDisVertex = GNAVData(LNAVList[i].getnearestActiveVertex(), candidate);
			}
		}
	}
	return shortDisVertex;
}

const vector<ActiveObject> VTree::getActiveObjectListofIndex(int vertexIndex)const {
	const VTree *ptTree = this;
	while (getLayer(*ptTree)>0) {
		ptTree = &ptTree->getVertexSideNode(vertexIndex);
	}
	int arrIndex = ptTree->distanceMatrix.getIndex(vertexIndex);
	return ptTree->LNAVList[arrIndex].getActiveObjectList();
}

const GNAVData VTree::nnav(int vertexIndex, const GNAVData previousGNAV) const {
	if (previousGNAV.vertexIndex == -1) return previousGNAV;
	VTree copyTree(*this);
	GNAVData firstNAV;
	do {
		firstNAV = copyTree.gnav(vertexIndex);

		vector<ActiveObject> targetList = getActiveObjectListofIndex(firstNAV.vertexIndex);

		for (int i = 0;i<targetList.size();i++) {
			copyTree.deleteObject(targetList[i].getObjectVehicle());
		}
	} while (firstNAV.vertexIndex != previousGNAV.vertexIndex);

	return copyTree.gnav(vertexIndex);
}

vector<GNAVData> VTree::knn(int vertexIndex, int k) const {
	vector<GNAVData> queue(k);  //GNAVData

								// in leaf
	GNAVData currentNAV = gnav(vertexIndex);
	const vector<ActiveObject> activeObjectList = getActiveObjectListofIndex(currentNAV.vertexIndex);

	for (int i = 0;i<activeObjectList.size();i++) {
		float candidate = SPDist(currentNAV.vertexIndex, vertexIndex) + activeObjectList[i].getDistance();
		if (candidate < queue[k - 1].shortestDistance) {
			queue.insert(queue.begin(), GNAVData(currentNAV.vertexIndex, candidate, activeObjectList[i].getObjectVehicle().getVehicleIndex()));
			queue.erase(queue.end() - 1);
		}
		// sort
		std::sort(queue.begin(), queue.end(), compareGNAVData);
	}
	// TODO:: nnav's
	while (true) {
		currentNAV = nnav(vertexIndex, currentNAV);
		if (currentNAV.vertexIndex == -1) break;
		if (SPDist(currentNAV.vertexIndex, vertexIndex) >= queue[k - 1].shortestDistance) {
			break;
		}
		const vector<ActiveObject> activeObjectList = getActiveObjectListofIndex(currentNAV.vertexIndex);
		for (int i = 0;i<activeObjectList.size();i++) {
			float candidate = SPDist(currentNAV.vertexIndex, vertexIndex) + activeObjectList[i].getDistance();
			if (candidate < queue[k - 1].shortestDistance) {
				queue.insert(queue.begin(), GNAVData(currentNAV.vertexIndex, candidate, activeObjectList[i].getObjectVehicle().getVehicleIndex()));
				queue.erase(queue.end() - 1);
			}
			// sort
			std::sort(queue.begin(), queue.end(), compareGNAVData);
		}
	}
	return queue;
}

void VTree::moveObject(float delta) {
	
	if (getLayer(*this) == 0) {
		for (int i = 0; i < LNAVList.size();i++) {
			LNAVList[i].moveObject(delta);
		}
	}
	else {
		leftNode->moveObject(delta);
		rightNode->moveObject(delta);
	}
}

