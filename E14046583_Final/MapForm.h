#pragma once
//#include "ActiveObject.h"

#include "V_Tree.h"
#include "ManagerTree.h"
#include "new_vehiicle_query_form.h"
#include "Vertex.h"
namespace E14046583_Final {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MapForm ���K�n
	/// </summary>
	public ref class MapForm : public System::Windows::Forms::Form
	{
	public:
		MapForm(void);

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
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

	private: System::Windows::Forms::ListBox^  object_list;
	private: System::Windows::Forms::Button^  add_vehicle_btn;
			 VTree *root;
	
			 void load_vertex();
			 void draw_vertex();
			 void load_route();
			 void draw_route();
			
		void buildTree();
		void attachVehicle();
		void update_object_list();
		void TimerEventProcessor(Object^ myObject,
			EventArgs^ myEventArgs);

	private: System::Windows::Forms::Button^  timer_btn;
			 /// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->map_area = (gcnew System::Windows::Forms::Panel());
			this->timer_btn = (gcnew System::Windows::Forms::Button());
			this->object_list = (gcnew System::Windows::Forms::ListBox());
			this->add_vehicle_btn = (gcnew System::Windows::Forms::Button());
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
			// timer_btn
			// 
			this->timer_btn->Location = System::Drawing::Point(847, 325);
			this->timer_btn->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->timer_btn->Name = L"timer_btn";
			this->timer_btn->Size = System::Drawing::Size(144, 34);
			this->timer_btn->TabIndex = 1;
			this->timer_btn->Text = L"update list";
			this->timer_btn->UseVisualStyleBackColor = true;
			this->timer_btn->Click += gcnew System::EventHandler(this, &MapForm::timer_btn_Click);
			// 
			// object_list
			// 
			this->object_list->FormattingEnabled = true;
			this->object_list->ItemHeight = 12;
			this->object_list->Location = System::Drawing::Point(847, 19);
			this->object_list->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->object_list->Name = L"object_list";
			this->object_list->Size = System::Drawing::Size(147, 256);
			this->object_list->TabIndex = 2;
			// 
			// add_vehicle_btn
			// 
			this->add_vehicle_btn->Location = System::Drawing::Point(847, 395);
			this->add_vehicle_btn->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->add_vehicle_btn->Name = L"add_vehicle_btn";
			this->add_vehicle_btn->Size = System::Drawing::Size(144, 36);
			this->add_vehicle_btn->TabIndex = 3;
			this->add_vehicle_btn->Text = L"add vehicle";
			this->add_vehicle_btn->UseVisualStyleBackColor = true;
			this->add_vehicle_btn->Click += gcnew System::EventHandler(this, &MapForm::add_vehicle_btn_Click);
			// 
			// MapForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1087, 729);
			this->Controls->Add(this->add_vehicle_btn);
			this->Controls->Add(this->object_list);
			this->Controls->Add(this->timer_btn);
			this->Controls->Add(this->map_area);
			this->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->Name = L"MapForm";
			this->Text = L"MapForm";
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void map_area_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

	private: System::Void timer_btn_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void add_vehicle_btn_Click(System::Object^  sender, System::EventArgs^  e);
};
}
