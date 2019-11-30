#include "MapForm.h"
#include <iostream>
#include <vector>
#include "MatrixDistanceDefaultValue.h"
#include<fstream>

using namespace E14046583_Final;
using namespace std;

MapForm::MapForm(void) : vertex_list(nullptr), route_list(nullptr) {
	InitializeComponent();
	objectTimer = gcnew System::Windows::Forms::Timer();
	objectTimer->Interval = 500;
	objectTimer->Start();
	objectTimer->Tick += gcnew EventHandler(this, &MapForm::TimerEventProcessor);
	position = 0;
	buildTree();
	attachVehicle();
	load_vertex();
	load_route();
}

void MapForm::buildTree() {
	const int treeNodeNumber = 7;
	const int boundaryVertexListSize = 8;
	
	DistanceMatrix gxDistanceMatrix[treeNodeNumber];
	using namespace DistanceMatrixDefaultValue;

	for (int i = 0; i < treeNodeNumber; i++) {
		gxDistanceMatrix[i] =
			DistanceMatrix(gxValue[i], gxIndexTable[i], gxSize[i]);
	}
	VTree *VTreeArr[treeNodeNumber];
	for (int i = 0; i < treeNodeNumber; i++) {
		VTreeArr[i] = new VTree(gxDistanceMatrix[i]);
	}
	root = new VTree(*VTreeArr[0]);
	VTree g1(*VTreeArr[1]);
	VTree g2(*VTreeArr[2]);

	g1.setLeftNode(*VTreeArr[3]);
	g1.setRightNode(*VTreeArr[4]);

	g2.setLeftNode(*VTreeArr[5]);
	g2.setRightNode(*VTreeArr[6]);

	root->setLeftNode(g1);
	root->setRightNode(g2);
	root->setBoundaryVertexList(boundaryVertexIndex, boundaryVertexListSize);

}

void MapForm::attachVehicle() {
	vector<Vehicle> vehicleList;
	vehicleList.push_back(Vehicle(1, 4));
	vehicleList.push_back(Vehicle(2, 4));
	vehicleList.push_back(Vehicle(2, 4));
	vehicleList.push_back(Vehicle(3, 6));
	vehicleList.push_back(Vehicle(3, 6));
	vehicleList.push_back(Vehicle(8, 5));
	vehicleList.push_back(Vehicle(8, 5));
	vehicleList.push_back(Vehicle(7, 8));
	vehicleList.push_back(Vehicle(2, 9));
	vehicleList.push_back(Vehicle(6, 13));
	vehicleList.push_back(Vehicle(3, 13));
	vehicleList.push_back(Vehicle(6, 8));
	vehicleList.push_back(Vehicle(9, 11));
	vehicleList.push_back(Vehicle(16, 15));
	
	for (int i = 0; i < vehicleList.size(); i++) {
		if (root->insertObject(vehicleList.at(i)) == false) {
			cout << "insert an object failed" << endl;
		}
	}
	//MessageBox::Show(""+ vehicleList.size());
}

System::Void MapForm::map_area_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	Graphics^ g = this->map_area->CreateGraphics();
	if (VTree::getLayer(*root) != 2) return;
	int node_number = pow(2, VTree::getLayer(*root)) * VERTEX_PER_NODE;

	for (int i = 1;i <= node_number;i++) {
		vector<ActiveObject> objectList = root->getActiveObjectListofIndex(i);
		for (int j = 0;j < objectList.size();j++) {
			int x = objectList.at(j).getDistance();
			//g->FillEllipse(Brushes::Red, Rectangle(x, 50*i+20*j, 10, 10));
		}
	}
	draw_vertex();
	draw_route();
}

void MapForm::TimerEventProcessor(Object^ myObject, System::EventArgs^ myEventArgs) {
	root->moveObject(10);
	// update object list
	
	map_area->Invalidate();
}

void MapForm::update_object_list() {
	object_list->Items->Clear();
	vector<ActiveObject> all_object_list = Algorithm::getAllActiveObject(*root);
	for (int i = 0;i < all_object_list.size();i++) {
		object_list->Items->Add("Vehicle " + all_object_list[i].getObjectVehicle().getVehicleIndex());
	}
}

System::Void MapForm::timer_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	update_object_list();
	map_area->Invalidate();
}

System::Void MapForm::add_vehicle_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	//pop up new form 
	new_vehiicle_query_form ^query_form = gcnew new_vehiicle_query_form();
	query_form->ShowDialog();
	// collect data
	if (query_form->DialogResult == System::Windows::Forms::DialogResult::OK) {
		// check validation

		Vehicle new_vehicle(query_form->derivation_vertex_index, query_form->destination_vertex_index); // dir, des
		root->insertObject(new_vehicle);
	}
	// update the object list
	update_object_list();
}

void MapForm::load_vertex() {
	vertex_list = new vector<Vertex>(0);
	ifstream pFile("vertex.txt");
	if (pFile.is_open())
	{
		int vertex_index;
		float pos_x, pos_y;
		while (! pFile.eof()) {
			pFile >> vertex_index;
			pFile >> pos_x;
			pFile >> pos_y;
			Vertex new_vertex(vertex_index, pos_x, pos_y);
			vertex_list->push_back(new_vertex);
		}
		
	}
	pFile.close();
}

void MapForm::draw_vertex() {
	Graphics^ g = this->map_area->CreateGraphics();
	if (vertex_list == nullptr) return;
	for (int i = 0;i < vertex_list->size();i++) {
		g->FillRectangle(Brushes::Blue, Rectangle(vertex_list->at(i).getPosX() * 30 - 5, vertex_list->at(i).getPosY() * 30 - 5, 10, 10));
	}


}

void  MapForm::load_route() {
	route_list = new vector<Route>(0);
	ifstream pFile("route.txt");
	if (pFile.is_open())
	{
		int source, destination;
		while (!pFile.eof()) {
			pFile >> source;
			pFile >> destination;
			Route new_route(source, destination);
			route_list->push_back(new_route);
		}
	}
	pFile.close();
	
}


void  MapForm::draw_route() {
	Graphics^ g = this->map_area->CreateGraphics();
	if (route_list == nullptr) return;
	for (int i = 0;i < route_list->size();i++) {
		int source = route_list->at(i).getSource();
		int des = route_list->at(i).getDestinaiton();
		PointF point1(vertex_list->at(source-1).getPosX()*30, vertex_list->at(source-1).getPosY()*30);
		PointF point2(vertex_list->at(des-1).getPosX()*30, vertex_list->at(des-1).getPosY()*30);
		g->DrawLine(Pens::Black, point1, point2);
	}
}