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
	objectTimer->Interval = 200;
	objectTimer->Start();
	objectTimer->Tick += gcnew EventHandler(this, &MapForm::TimerEventProcessor);
	position = 0;
	selected_vehicle = -1;
	search_center_vertex_index = -1;
	k = -1;
	buildTree();
	attachVehicle();
	load_vertex();
	load_route();
	update_object_list();
	knn_searched_list = new vector<GNAVData>();
	draw_label();
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
	vehicleList.push_back(Vehicle(9, 11));
	vehicleList.push_back(Vehicle(16, 15));
	
	for (int i = 0; i < vehicleList.size(); i++) {
		if (root->insertObject(vehicleList.at(i)) == false) {
			cout << "insert an object failed" << endl;
		}
	}
}

System::Void MapForm::map_area_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	Graphics^ g = this->map_area->CreateGraphics();
	if (VTree::getLayer(*root) != 2) return;
	
	draw_vehicle();
	draw_vertex();
	draw_route();
}

void MapForm::TimerEventProcessor(Object^ myObject, System::EventArgs^ myEventArgs) {
	root->moveObject(0.05);
	// update object list
	map_area->Invalidate();
	update_knn_search_listbox();
	update_knn_result();
}

void MapForm::update_object_list() {
	object_list->Items->Clear();
	vector<ActiveObject> all_object_list = Algorithm::getAllActiveObject(*root);
	for (int i = 0;i < all_object_list.size();i++) {
		object_list->Items->Add("Vehicle " + all_object_list[i].getObjectVehicle().getVehicleIndex());
	}
}

void  MapForm::update_knn_search_listbox() {
	knn_search_listbox->Items->Clear();
	for (int i = 0;i < knn_searched_list->size();i++) {
		knn_search_listbox->Items->Add("Vehicle " + knn_searched_list->at(i).object_index);

	}
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

System::Void MapForm::kNN_search_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	kNN_search_form ^search_form = gcnew kNN_search_form();
	search_form->ShowDialog();
	if (search_form->DialogResult == System::Windows::Forms::DialogResult::OK) {
		search_center_vertex_index = search_form->search_center_vertex_index;
		k = search_form->k;
		update_knn_result();
	}
}

void MapForm::update_knn_result() {
	if (search_center_vertex_index != -1 && k != -1) {
		delete knn_searched_list;
		knn_searched_list = new vector<GNAVData>(root->knn(search_center_vertex_index, k));
	}
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

		/*Label ^namelabel = gcnew Label();
		namelabel->Location = System::Drawing::Point(vertex_list->at(i).getPosX() * 30 - 30, vertex_list->at(i).getPosY() * 30 );
		namelabel->Text = "t";
		namelabel->AutoSize = true;
		this->map_area->Controls->Add(namelabel);*/

		if (search_center_vertex_index == vertex_list->at(i).getVertexIndex()) {
			g->FillRectangle(Brushes::Cyan, Rectangle(vertex_list->at(i).getPosX() * 30 - 5, vertex_list->at(i).getPosY() * 30 - 5, 10, 10));
		}
		else {
			g->FillRectangle(Brushes::Blue, Rectangle(vertex_list->at(i).getPosX() * 30 - 5, vertex_list->at(i).getPosY() * 30 - 5, 10, 10));
			for (int p = 0;p < knn_searched_list->size();p++) {
				if (knn_searched_list->at(p).vertexIndex == vertex_list->at(i).getVertexIndex()) {
					g->FillRectangle(Brushes::Pink, Rectangle(vertex_list->at(i).getPosX() * 30 - 5, vertex_list->at(i).getPosY() * 30 - 5, 10, 10));
				}
			}
		}
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

void MapForm::draw_vehicle() {
	Graphics^ g = this->map_area->CreateGraphics();
	int node_number = pow(2, VTree::getLayer(*root)) * VERTEX_PER_NODE;

	for (int i = 1;i <= node_number;i++) {
		vector<ActiveObject> objectList = root->getActiveObjectListofIndex(i);
		for (int j = 0;j < objectList.size();j++) {
			float d = objectList.at(j).getDistance();
			float max_dis = objectList.at(j).getMaxDistance();
			int source = objectList.at(j).getObjectVehicle().getEdgeVertexIndexFirst();
			int des = objectList.at(j).getObjectVehicle().getEdgeVertexIndexSecond();

			float x = ((max_dis-d) / max_dis)*(vertex_list->at(des - 1).getPosX() - vertex_list->at(source - 1).getPosX())+ vertex_list->at(source - 1).getPosX();
			float y = ((max_dis - d) / max_dis)*(vertex_list->at(des - 1).getPosY() - vertex_list->at(source - 1).getPosY()) + vertex_list->at(source - 1).getPosY();
			// selected vehicle
			g->FillEllipse(Brushes::Red, Rectangle(x*30-5, y*30-5, 10, 10));
			if (selected_vehicle == objectList.at(j).getObjectVehicle().getVehicleIndex()) {
				Pen ^pen = gcnew Pen(Brushes::Green);
				pen->Width = 4.0F;
				g->DrawEllipse(pen, Rectangle(x * 30 - 10, y * 30 - 10, 20, 20));
			}
			// knn object
			for (int p = 0;p < knn_searched_list->size();p++) {
				if (knn_searched_list->at(p).object_index == objectList.at(j).getObjectVehicle().getVehicleIndex()) {
					Pen ^pen = gcnew Pen(Brushes::Green);
					pen->Width = 4.0F;
					g->DrawEllipse(pen, Rectangle(x * 30 - 10, y * 30 - 10, 20, 20));
				}
			}
		}
	}

}

void MapForm::draw_label() {
	for (int i = 0; i < vertex_list->size(); i++) {

		Label ^namelabel = gcnew Label();
		namelabel->Location = System::Drawing::Point(vertex_list->at(i).getPosX() * 30 - 20, vertex_list->at(i).getPosY() * 30);
		namelabel->Text = ""+(i+1);
		namelabel->AutoSize = true;
		this->map_area->Controls->Add(namelabel);

	}
}

System::Void MapForm::object_list_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	String ^i = object_list->Items[object_list->SelectedIndex]->ToString();
	cli::array<String^>^ words = i->Split(' ');
	selected_vehicle = Int32::Parse(words[1]);
}