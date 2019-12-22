#pragma once
#ifndef MAP_INFO_H_
#define MAP_INFO_H_

#include "Vertex.h"
#include <iostream>
#include <vector>
using namespace std;

class MapInfo {
private:
	vector<Vertex> vertexList;
	vector<Route> routeList;
	void loadVertex();
	void loadRoute();

public:
	MapInfo();

	vector<Vertex> getVertexList() { return vertexList; }
	vector<Route> getRouteList() { return routeList; }
};

namespace VertexRouteData {
	const static int vertexSize = 16;
	const static float vertex[] =
	{
		1, 6.7, 4, 2, 7, 7, 3, 6, 10,
		4, 1, 8, 5, 1.5, 15, 6, 6, 13,
		7, 8, 17, 8, 4, 19, 9, 13, 7,
		10, 11, 8, 11, 14, 8, 12, 19, 7,
		13, 13, 13, 14, 17, 11, 15, 14, 15,
		16, 15, 17
	};
	const static int routeSize = 20;
	const static int route[] =
	{
		1, 2, 1, 4, 2, 4,
		2, 3, 3, 4, 4, 5,
		5, 8, 7, 8, 6, 7,
		3, 6, 3, 13, 6, 13,
		13, 15,	15, 16, 13, 14,
		10, 13, 9, 10, 2, 9,
		9, 11, 11, 12
	};

}

#endif // !1

