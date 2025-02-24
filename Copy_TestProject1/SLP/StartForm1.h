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
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18.25F));
			   this->label1->Location = System::Drawing::Point(133, 65);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(178, 29);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Sudoku Solver";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			   this->label2->Location = System::Drawing::Point(121, 169);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(206, 80);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"Input a number for grid size.\r\n4 = 4 x 4 \r\n9 = 9 x 9";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(170, 281);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(100, 20);
			   this->textBox1->TabIndex = 2;
			   // 
			   // Start Button
			   // 
			   this->Start->Location = System::Drawing::Point(170, 321);
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
			   this->ClientSize = System::Drawing::Size(436, 438);
			   this->Controls->Add(this->Start);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Name = L"StartForm1";
			   this->Text = L"Sudoku Solver";
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
				
				Form2^ form2 = gcnew Form2();
				this->Hide(); 
				form2->ShowDialog(); 
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
		else {
			
			MessageBox::Show(L"Please enter a valid number.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	};
}