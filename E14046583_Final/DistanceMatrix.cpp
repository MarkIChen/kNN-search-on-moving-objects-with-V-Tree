#include "DistanceMatrix.h"

DistanceMatrix::DistanceMatrix() :value(nullptr), indexTable(nullptr), size(0) {};
DistanceMatrix::DistanceMatrix(float *value, int *indexTable, int size)
	: size(size) {
	this->indexTable = new int[size];
	this->value = new float[size * size];

	for (int i = 0; i < size * size; i++) {
		this->value[i] = value[i];
	}
	for (int i = 0; i < size; i++) {
		this->indexTable[i] = indexTable[i];
	}
}

void DistanceMatrix::showMatrix() const {
	for (int i = 0; i < size * size; i++) {
		cout << value[i] << " ";
		if (i % size == size - 1)
			cout << endl;
	}
	cout << endl;
}
DistanceMatrix::DistanceMatrix(const DistanceMatrix &node) : size(node.size) {
	indexTable = new int[node.size];
	value = new float[size * size];

	for (int i = 0; i < node.size * node.size; i++) {
		value[i] = node.value[i];
	}
	for (int i = 0; i < node.size; i++) {
		indexTable[i] = node.indexTable[i];
	}
}
DistanceMatrix& DistanceMatrix::operator=(const DistanceMatrix& node) {
	size = node.size;
	delete value;
	delete indexTable;
	indexTable = new int[node.size];
	value = new float[size * size];
	for (int i = 0; i < node.size * node.size; i++) {
		value[i] = node.value[i];
	}
	for (int i = 0; i < node.size; i++) {
		indexTable[i] = node.indexTable[i];
	}
	return *this;
}

DistanceMatrix::~DistanceMatrix() {
	delete value;
	delete indexTable;
}

int DistanceMatrix::getIndex(int vertexIndex) const {
	for (int i = 0;i<size;i++) {
		if (indexTable[i] == vertexIndex) return i;
	}
	// cout << "DistanceMatrix --> error:cannot find index in indextable."<<endl;
	return -1;
}

float DistanceMatrix::getValue(int vertexIndex1, int vertexIndex2) const {
	int arrIndexRow = getIndex(vertexIndex1);
	int arrIndexCol = getIndex(vertexIndex2);

	if (arrIndexRow == -1 || arrIndexCol == -1) {
		if (vertexIndex1 == 3) {
			cout << "return -1" << endl;
		}
		return -1;
	}
	return value[arrIndexRow * size + arrIndexCol];
}
