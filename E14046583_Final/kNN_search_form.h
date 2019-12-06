#pragma once

namespace E14046583_Final {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// kNN_search_form 的摘要
	/// </summary>
	public ref class kNN_search_form : public System::Windows::Forms::Form
	{
	public:
		int search_center_vertex_index;
		int k;
		kNN_search_form(void)
		{
			InitializeComponent();
			search_center_vertex_index = -1;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~kNN_search_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  search_center_label;
	protected:
	private: System::Windows::Forms::ComboBox^  search_center_combobox;
	private: System::Windows::Forms::Button^  search_btn;
	private: System::Windows::Forms::Button^  cancel_btn;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  k_textbox;

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
			this->search_center_label = (gcnew System::Windows::Forms::Label());
			this->search_center_combobox = (gcnew System::Windows::Forms::ComboBox());
			this->search_btn = (gcnew System::Windows::Forms::Button());
			this->cancel_btn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->k_textbox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// search_center_label
			// 
			this->search_center_label->AutoSize = true;
			this->search_center_label->Location = System::Drawing::Point(49, 83);
			this->search_center_label->Name = L"search_center_label";
			this->search_center_label->Size = System::Drawing::Size(68, 12);
			this->search_center_label->TabIndex = 0;
			this->search_center_label->Text = L"search_center";
			// 
			// search_center_combobox
			// 
			this->search_center_combobox->FormattingEnabled = true;
			this->search_center_combobox->Items->AddRange(gcnew cli::array< System::Object^  >(16) {
				L"1", L"2", L"3", L"4", L"5", L"6",
					L"7", L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16"
			});
			this->search_center_combobox->Location = System::Drawing::Point(153, 80);
			this->search_center_combobox->Name = L"search_center_combobox";
			this->search_center_combobox->Size = System::Drawing::Size(121, 20);
			this->search_center_combobox->TabIndex = 1;
			// 
			// search_btn
			// 
			this->search_btn->Location = System::Drawing::Point(34, 178);
			this->search_btn->Name = L"search_btn";
			this->search_btn->Size = System::Drawing::Size(118, 55);
			this->search_btn->TabIndex = 2;
			this->search_btn->Text = L"Search";
			this->search_btn->UseVisualStyleBackColor = true;
			this->search_btn->Click += gcnew System::EventHandler(this, &kNN_search_form::search_btn_Click);
			// 
			// cancel_btn
			// 
			this->cancel_btn->Location = System::Drawing::Point(183, 178);
			this->cancel_btn->Name = L"cancel_btn";
			this->cancel_btn->Size = System::Drawing::Size(118, 55);
			this->cancel_btn->TabIndex = 3;
			this->cancel_btn->Text = L"Cancel";
			this->cancel_btn->UseVisualStyleBackColor = true;
			this->cancel_btn->Click += gcnew System::EventHandler(this, &kNN_search_form::cancel_btn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 133);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(11, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"k";
			// 
			// k_textbox
			// 
			this->k_textbox->Location = System::Drawing::Point(205, 133);
			this->k_textbox->Name = L"k_textbox";
			this->k_textbox->Size = System::Drawing::Size(69, 22);
			this->k_textbox->TabIndex = 5;
			this->k_textbox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// kNN_search_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(374, 340);
			this->Controls->Add(this->k_textbox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cancel_btn);
			this->Controls->Add(this->search_btn);
			this->Controls->Add(this->search_center_combobox);
			this->Controls->Add(this->search_center_label);
			this->Name = L"kNN_search_form";
			this->Text = L"kNN_search_form";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void search_btn_Click(System::Object^  sender, System::EventArgs^  e) {
		if (search_center_combobox->Text != "" && k_textbox->Text != "") {
			search_center_vertex_index = Int32::Parse(search_center_combobox->Text);
			k = Int32::Parse(k_textbox->Text);
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
	
	}
private: System::Void cancel_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	this->Close();
}
};
}
