#pragma once
#include <iostream> 
#include <string> 
namespace E14046583_Final {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// new_vehiicle_query_form 的摘要
	/// </summary>
	public ref class new_vehiicle_query_form : public System::Windows::Forms::Form
	{

	public:
		int derivation_vertex_index;
		int destination_vertex_index;
		new_vehiicle_query_form(void):derivation_vertex_index(0), destination_vertex_index(0)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~new_vehiicle_query_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  derivation_label;
	protected:
	private: System::Windows::Forms::Label^  destination_label;
	private: System::Windows::Forms::ComboBox^  derivation_comboBox;
	private: System::Windows::Forms::ComboBox^  destination_comboBox;
	private: System::Windows::Forms::Button^  add_btn;
	private: System::Windows::Forms::Button^  Cancel_btn;

	protected:

	private:
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
			this->derivation_label = (gcnew System::Windows::Forms::Label());
			this->destination_label = (gcnew System::Windows::Forms::Label());
			this->derivation_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->destination_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->add_btn = (gcnew System::Windows::Forms::Button());
			this->Cancel_btn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// derivation_label
			// 
			this->derivation_label->AutoSize = true;
			this->derivation_label->Location = System::Drawing::Point(94, 51);
			this->derivation_label->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->derivation_label->Name = L"derivation_label";
			this->derivation_label->Size = System::Drawing::Size(80, 12);
			this->derivation_label->TabIndex = 0;
			this->derivation_label->Text = L"derivation_label";
			// 
			// destination_label
			// 
			this->destination_label->AutoSize = true;
			this->destination_label->Location = System::Drawing::Point(94, 92);
			this->destination_label->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->destination_label->Name = L"destination_label";
			this->destination_label->Size = System::Drawing::Size(83, 12);
			this->destination_label->TabIndex = 1;
			this->destination_label->Text = L"destination_label";
			// 
			// derivation_comboBox
			// 
			this->derivation_comboBox->FormattingEnabled = true;
			this->derivation_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(16) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7",
					L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16"
			});
			this->derivation_comboBox->Location = System::Drawing::Point(197, 51);
			this->derivation_comboBox->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->derivation_comboBox->Name = L"derivation_comboBox";
			this->derivation_comboBox->Size = System::Drawing::Size(58, 20);
			this->derivation_comboBox->TabIndex = 2;
			// 
			// destination_comboBox
			// 
			this->destination_comboBox->FormattingEnabled = true;
			this->destination_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(16) {
				L"1", L"2", L"3", L"4", L"5", L"6",
					L"7", L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16"
			});
			this->destination_comboBox->Location = System::Drawing::Point(197, 92);
			this->destination_comboBox->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->destination_comboBox->Name = L"destination_comboBox";
			this->destination_comboBox->Size = System::Drawing::Size(58, 20);
			this->destination_comboBox->TabIndex = 3;
			// 
			// add_btn
			// 
			this->add_btn->Location = System::Drawing::Point(68, 189);
			this->add_btn->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->add_btn->Name = L"add_btn";
			this->add_btn->Size = System::Drawing::Size(79, 32);
			this->add_btn->TabIndex = 4;
			this->add_btn->Text = L"Add Vehicle";
			this->add_btn->UseVisualStyleBackColor = true;
			this->add_btn->Click += gcnew System::EventHandler(this, &new_vehiicle_query_form::add_btn_Click);
			// 
			// Cancel_btn
			// 
			this->Cancel_btn->Location = System::Drawing::Point(189, 189);
			this->Cancel_btn->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->Cancel_btn->Name = L"Cancel_btn";
			this->Cancel_btn->Size = System::Drawing::Size(79, 32);
			this->Cancel_btn->TabIndex = 5;
			this->Cancel_btn->Text = L"Cancel";
			this->Cancel_btn->UseVisualStyleBackColor = true;
			this->Cancel_btn->Click += gcnew System::EventHandler(this, &new_vehiicle_query_form::Cancel_btn_Click);
			// 
			// new_vehiicle_query_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(354, 284);
			this->Controls->Add(this->Cancel_btn);
			this->Controls->Add(this->add_btn);
			this->Controls->Add(this->destination_comboBox);
			this->Controls->Add(this->derivation_comboBox);
			this->Controls->Add(this->destination_label);
			this->Controls->Add(this->derivation_label);
			this->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->Name = L"new_vehiicle_query_form";
			this->Text = L"new_vehiicle_query_form";
			this->Load += gcnew System::EventHandler(this, &new_vehiicle_query_form::new_vehiicle_query_form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void new_vehiicle_query_form_Load(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void add_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	if (derivation_comboBox->Text != "" && destination_comboBox->Text != "") {
		derivation_vertex_index = Int32::Parse(derivation_comboBox->Text);
		destination_vertex_index = Int32::Parse(destination_comboBox->Text);
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
	
}
private: System::Void Cancel_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	this->Close();
}
};
}
