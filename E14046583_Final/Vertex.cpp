#include "vertex.h"

Vertex::Vertex() : index(0), posX(0), posY(0) {};
Vertex::Vertex(int index, float posX, float posY)
	: index(index), posX(posX), posY(posY) {};

std::istream &operator >> (std::istream &is, Vertex &vertex) {
	is >> vertex.index;
	is >> vertex.posX;
	is >> vertex.posY;
	return is;
}

std::ostream &operator<<(std::ostream &os, Vertex &vertex) {
	std::cout << "vertex = " << vertex.index << ", x = " << vertex.posX
		<< " , y = " << vertex.posY << std::endl;
	return os;
}
