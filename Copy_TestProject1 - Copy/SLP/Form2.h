#pragma once
#include "SudokuSolver.h"  

namespace SLP {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
		{
			InitializeComponent();
		}

	protected:
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Panel^ SudokuPanel;
		array<TextBox^, 2>^ SudokuGrid;
	private: System::Windows::Forms::Button^ SOLVEBUTTON4;
	private: System::Windows::Forms::Button^ CLEARBUTTON4;


		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->SudokuPanel = (gcnew System::Windows::Forms::Panel());
			this->SOLVEBUTTON4 = (gcnew System::Windows::Forms::Button());
			this->CLEARBUTTON4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// SudokuPanel
			// 
			this->SudokuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SudokuPanel->Location = System::Drawing::Point(49, 45);
			this->SudokuPanel->Name = L"SudokuPanel";
			this->SudokuPanel->Size = System::Drawing::Size(180, 180);
			this->SudokuPanel->TabIndex = 0;
			this->SudokuPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form2::SudokuPanel_Paint);
			// 
			// SOLVEBUTTON4
			// 
			this->SOLVEBUTTON4->Location = System::Drawing::Point(287, 99);
			this->SOLVEBUTTON4->Name = L"SOLVEBUTTON4";
			this->SOLVEBUTTON4->Size = System::Drawing::Size(75, 23);
			this->SOLVEBUTTON4->TabIndex = 1;
			this->SOLVEBUTTON4->Text = L"SOLVE";
			this->SOLVEBUTTON4->UseVisualStyleBackColor = true;
			this->SOLVEBUTTON4->Click += gcnew System::EventHandler(this, &Form2::SOLVEBUTTON4_Click);
			// 
			// CLEARBUTTON4
			// 
			this->CLEARBUTTON4->Location = System::Drawing::Point(287, 159);
			this->CLEARBUTTON4->Name = L"CLEARBUTTON4";
			this->CLEARBUTTON4->Size = System::Drawing::Size(75, 23);
			this->CLEARBUTTON4->TabIndex = 2;
			this->CLEARBUTTON4->Text = L"CLEAR";
			this->CLEARBUTTON4->UseVisualStyleBackColor = true;
			this->CLEARBUTTON4->Click += gcnew System::EventHandler(this, &Form2::CLEARBUTTON4_Click);
			// 
			// Form2
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->CLEARBUTTON4);
			this->Controls->Add(this->SOLVEBUTTON4);
			this->Controls->Add(this->SudokuPanel);
			this->Name = L"Form2";
			this->Text = L"4x4 Sudoku Grid";
			this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);
			this->ResumeLayout(false);

		}

	private:
		System::Void Form2_Load(System::Object^ sender, System::EventArgs^ e) {
			GenerateSudokuGrid();
		}

		void GenerateSudokuGrid()
		{
			int cellSize = 45;
			int subgridSize = 2;
			int gridSize = 4;
			int gapSize = 3;

			SudokuGrid = gcnew array<TextBox^, 2>(gridSize, gridSize);
			SudokuPanel->BackColor = System::Drawing::Color::Purple;

			array<Panel^, 2>^ subgridPanels = gcnew array<Panel^, 2>(subgridSize, subgridSize);

			for (int subRow = 0; subRow < subgridSize; subRow++)
			{
				for (int subCol = 0; subCol < subgridSize; subCol++)
				{
					Panel^ subgridPanel = gcnew Panel();
					subgridPanel->Size = System::Drawing::Size(cellSize * subgridSize, cellSize * subgridSize);
					subgridPanel->Location = System::Drawing::Point(
						subCol * (cellSize * subgridSize + gapSize),
						subRow * (cellSize * subgridSize + gapSize)
					);
					subgridPanel->BorderStyle = BorderStyle::FixedSingle;
					subgridPanel->BackColor = System::Drawing::Color::White;
					SudokuPanel->Controls->Add(subgridPanel);
					subgridPanels[subRow, subCol] = subgridPanel;
				}
			}

			for (int row = 0; row < gridSize; row++)
			{
				for (int col = 0; col < gridSize; col++)
				{
					TextBox^ textBox = gcnew TextBox();
					textBox->Size = System::Drawing::Size(cellSize, cellSize);
					textBox->Location = System::Drawing::Point(
						(col % subgridSize) * cellSize,
						(row % subgridSize) * cellSize
					);
					textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18);
					textBox->TextAlign = HorizontalAlignment::Center;
					textBox->MaxLength = 1;
					textBox->BorderStyle = BorderStyle::FixedSingle;
					textBox->AutoSize = false;


					int subgridRow = row / subgridSize;
					int subgridCol = col / subgridSize;
					subgridPanels[subgridRow, subgridCol]->Controls->Add(textBox);
					SudokuGrid[row, col] = textBox;
				}
			}
		}
	private: System::Void SudokuPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {}
	private: System::Void SOLVEBUTTON4_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SudokuSolver::HasDuplicate(SudokuGrid))
		{
			MessageBox::Show("Error: Duplicate numbers found in rows or columns!", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (SudokuSolver::Solve(SudokuGrid))
		{
			MessageBox::Show("Sudoku Solved!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("No solution exists for this puzzle.", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
private: System::Void CLEARBUTTON4_Click(System::Object^ sender, System::EventArgs^ e) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			SudokuGrid[row, col]->Text = ""; 
			SudokuGrid[row, col]->BackColor = System::Drawing::Color::White; 
		}
	}
}
};
}
