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
	
	int getVertexIndex() { return index;};
	float getPosX() { return posX; }
	float getPosY() { return posY; }


	friend std::istream &operator >> (std::istream&, Vertex&);
	friend std::ostream &operator<<(std::ostream&, Vertex&);

};

class Route {
private:
	int source;
	int destination;
public:
	Route() {};
	Route(int s, int d):source(s), destination(d) {}

	int getSource() { return source; }
	int getDestinaiton() { return destination; }
};


#endif
