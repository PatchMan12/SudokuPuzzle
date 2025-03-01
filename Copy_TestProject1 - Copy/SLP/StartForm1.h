#pragma once
#include "Form1.h"  // Include header for 9x9 grid form
#include "Form2.h"  // Include header for 4x4 grid form

namespace SLP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class StartForm1 : public System::Windows::Forms::Form
	{
	public:
		StartForm1(void)
		{
			InitializeComponent();
		}

	protected:
		~StartForm1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ Start;

	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->Start = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->BackColor = System::Drawing::Color::MediumPurple;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18.25F));
			   this->label1->Location = System::Drawing::Point(132, 103);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(178, 29);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Sudoku Solver";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->BackColor = System::Drawing::Color::MediumPurple;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			   this->label2->Location = System::Drawing::Point(117, 166);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(206, 60);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"Input a number for grid size.\r\n                4  =  4 x 4\r\n                9  = "
				   L" 9 x 9\r\n";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(170, 266);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(100, 20);
			   this->textBox1->TabIndex = 2;
			   this->textBox1->TextChanged += gcnew System::EventHandler(this, &StartForm1::textBox1_TextChanged);
			   // 
			   // Start
			   // 
			   this->Start->Font = (gcnew System::Drawing::Font(L"MS Gothic", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->Start->Location = System::Drawing::Point(170, 305);
			   this->Start->Name = L"Start";
			   this->Start->Size = System::Drawing::Size(100, 45);
			   this->Start->TabIndex = 3;
			   this->Start->Text = L"Start";
			   this->Start->UseVisualStyleBackColor = true;
			   this->Start->Click += gcnew System::EventHandler(this, &StartForm1::Start_Click);
			   // 
			   // StartForm1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->ClientSize = System::Drawing::Size(436, 395);
			   this->Controls->Add(this->Start);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Name = L"StartForm1";
			   this->Text = L"Sudoku Solver";
			   this->Load += gcnew System::EventHandler(this, &StartForm1::StartForm1_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: System::Void Start_Click(System::Object^ sender, System::EventArgs^ e) {
		// Get user input
		String^ input = textBox1->Text;
		int gridSize;

		
		if (Int32::TryParse(input, gridSize)) {
			if (gridSize == 4) {
				
				Form2^ form3 = gcnew Form2();
				this->Hide(); 
				form3->ShowDialog(); 
				this->Show(); 
			}
			else if (gridSize == 9) {
				
				Form1^ form1 = gcnew Form1();
				this->Hide(); 
				form1->ShowDialog(); 
				this->Show(); 
			}
			else {
				
				MessageBox::Show(L"Invalid grid size! Please enter 4 or 9.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	
		
	}
	private: System::Void StartForm1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}