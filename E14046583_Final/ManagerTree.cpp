#include "ManagerTree.h"

vector<ActiveObject> Algorithm::getAllActiveObject(const VTree &root) {
	int leaf_number = pow(2, VTree::getLayer(root)) * VERTEX_PER_NODE;

	vector<ActiveObject> list;
	for (int i = 1;i <= leaf_number;i++) {
		vector<ActiveObject> vertex_list = root.getActiveObjectListofIndex(i);
		for (int j = 0;j < vertex_list.size();j++) {
			list.push_back(vertex_list[j]);
		}
	}
	return list;
}
