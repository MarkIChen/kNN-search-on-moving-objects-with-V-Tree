#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

class Vertex {
private:
	int index;
	float posX;
	float posY;

public:
	Vertex();
	Vertex(int, float, float);
	// ~Vertex();

	friend std::istream &operator >> (std::istream&, Vertex&);

	friend std::ostream &operator<<(std::ostream&, Vertex&);

};
#endif
