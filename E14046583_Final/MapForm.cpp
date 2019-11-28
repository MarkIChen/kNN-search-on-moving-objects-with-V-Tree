#include "MapForm.h"
#include <iostream>
#include <vector>
#include "MatrixDistanceDefaultValue.h"

using namespace E14046583_Final;
using namespace std;

MapForm::MapForm(void) {
	InitializeComponent();
	objectTimer = gcnew System::Windows::Forms::Timer();
	objectTimer->Interval = 500;
	objectTimer->Start();
	objectTimer->Tick += gcnew EventHandler(this, &MapForm::TimerEventProcessor);
	position = 0;
	buildTree();
	attachVehicle();
	//test
	vechicle = new Vehicle(1, 4);
	object = new ActiveObject(*vechicle, 2);
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
			g->FillEllipse(Brushes::Red, Rectangle(x, 50*i+20*j, 10, 10));
		
		}
	}
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