#pragma once

#include "V_Tree.h"
#include "ManagerTree.h"
#include "new_vehiicle_query_form.h"
#include "kNN_search_form.h"
#include "Vertex.h"
namespace E14046583_Final {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MapForm 的摘要
	/// </summary>
	public ref class MapForm : public System::Windows::Forms::Form
	{
	public:
		MapForm(void);

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MapForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  map_area;

	private:
		System::Windows::Forms::Timer^ objectTimer;
		int position;
		vector<Vertex> *vertex_list;
		vector<Route> *route_list;
		vector<GNAVData> *knn_searched_list;
		int selected_vehicle;
		int search_center_vertex_index;
		int k;

	private: System::Windows::Forms::ListBox^  object_list;
	private: System::Windows::Forms::Button^  add_vehicle_btn;
	private: System::Windows::Forms::ListBox^  knn_search_listbox;

	private: System::Windows::Forms::Button^  kNN_search_btn;
			 VTree *root;
	
			 void load_vertex();
			 void draw_vertex();
			 void load_route();
			 void draw_route();
			 void draw_vehicle();
			 void draw_label();
		void buildTree();
		void attachVehicle();
		void update_object_list();
		void update_knn_search_listbox();
		void update_knn_result();
		void TimerEventProcessor(Object^ myObject,
			EventArgs^ myEventArgs);


			 /// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->map_area = (gcnew System::Windows::Forms::Panel());
			this->object_list = (gcnew System::Windows::Forms::ListBox());
			this->add_vehicle_btn = (gcnew System::Windows::Forms::Button());
			this->knn_search_listbox = (gcnew System::Windows::Forms::ListBox());
			this->kNN_search_btn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// map_area
			// 
			this->map_area->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->map_area->Location = System::Drawing::Point(54, 19);
			this->map_area->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->map_area->Name = L"map_area";
			this->map_area->Size = System::Drawing::Size(608, 689);
			this->map_area->TabIndex = 0;
			this->map_area->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MapForm::map_area_Paint);
			// 
			// object_list
			// 
			this->object_list->FormattingEnabled = true;
			this->object_list->ItemHeight = 12;
			this->object_list->Location = System::Drawing::Point(733, 125);
			this->object_list->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->object_list->Name = L"object_list";
			this->object_list->Size = System::Drawing::Size(147, 280);
			this->object_list->TabIndex = 2;
			this->object_list->SelectedIndexChanged += gcnew System::EventHandler(this, &MapForm::object_list_SelectedIndexChanged);
			// 
			// add_vehicle_btn
			// 
			this->add_vehicle_btn->Location = System::Drawing::Point(733, 435);
			this->add_vehicle_btn->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->add_vehicle_btn->Name = L"add_vehicle_btn";
			this->add_vehicle_btn->Size = System::Drawing::Size(144, 36);
			this->add_vehicle_btn->TabIndex = 3;
			this->add_vehicle_btn->Text = L"add vehicle";
			this->add_vehicle_btn->UseVisualStyleBackColor = true;
			this->add_vehicle_btn->Click += gcnew System::EventHandler(this, &MapForm::add_vehicle_btn_Click);
			// 
			// knn_search_listbox
			// 
			this->knn_search_listbox->FormattingEnabled = true;
			this->knn_search_listbox->ItemHeight = 12;
			this->knn_search_listbox->Location = System::Drawing::Point(915, 125);
			this->knn_search_listbox->Name = L"knn_search_listbox";
			this->knn_search_listbox->Size = System::Drawing::Size(147, 280);
			this->knn_search_listbox->TabIndex = 4;
			// 
			// kNN_search_btn
			// 
			this->kNN_search_btn->Location = System::Drawing::Point(915, 438);
			this->kNN_search_btn->Name = L"kNN_search_btn";
			this->kNN_search_btn->Size = System::Drawing::Size(147, 33);
			this->kNN_search_btn->TabIndex = 5;
			this->kNN_search_btn->Text = L"kNN Search";
			this->kNN_search_btn->UseVisualStyleBackColor = true;
			this->kNN_search_btn->Click += gcnew System::EventHandler(this, &MapForm::kNN_search_btn_Click);
			// 
			// MapForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1087, 729);
			this->Controls->Add(this->kNN_search_btn);
			this->Controls->Add(this->knn_search_listbox);
			this->Controls->Add(this->add_vehicle_btn);
			this->Controls->Add(this->object_list);
			this->Controls->Add(this->map_area);
			this->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->Name = L"MapForm";
			this->Text = L"MapForm";
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void map_area_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

	private: System::Void add_vehicle_btn_Click(System::Object^  sender, System::EventArgs^  e);
	
	private: System::Void object_list_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

	private: System::Void kNN_search_btn_Click(System::Object^  sender, System::EventArgs^  e);
};
}
