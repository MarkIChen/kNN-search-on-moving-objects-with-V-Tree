#include "map_info.h"

MapInfo::MapInfo() {
	vertexList = vector<Vertex>();
	routeList = vector<Route>();

	loadVertex();
	loadRoute();
}

void MapInfo::loadVertex() {
	using namespace VertexRouteData;
	for (int i = 0; i < vertexSize; i++) {
		vertexList.push_back(Vertex(vertex[3*i], vertex[3 * i+1], vertex[3 * i+2]));
	}
}

void MapInfo::loadRoute() {
	using namespace VertexRouteData;
	for (int i = 0; i < routeSize; i++) {
		routeList.push_back(Route(route[2 * i], route[2 * i + 1]));
	}
}